import csv
import urllib2
import time
from datetime import date, datetime, timedelta
import urllib
import gzip
import pandas as pd
from proc import strategy1
import numpy as np
import threading


#dataf = pd.DataFrame()
#ctr = 0	


def filehlpr(filename, targetname):
	inF = gzip.GzipFile(filename, 'rb')
	s = inF.read()
	inF.close()
	outF = file(targetname, 'wb')
	outF.write(s)
	outF.close()


def postproc(low_bound, up_bound, dataf):
	for i in range(low_bound,up_bound):
		#print "im working"
		dataarr = dataf['price'][i:1440+i].tolist()
		oldpos = dataf['signal'][1439+i]
		newpos,pnl = strategy1(dataarr,oldpos)
		dataf.ix[1440+i,'signal']= newpos
		dataf.ix[1439+i,'pnl'] = pnl



def catchhist(url, is_saved, dataf):
	dlname = 'data/data.gz'
	tgname = 'data/daily_test.csv'
	finname ='data/dailyproc.csv'
	#urllib.urlretrieve(url,dlname)
	#filehlpr(dlname,tgname)

	###########Proc & After########
	dataf = pd.read_csv(tgname, names = ['unix', 'price', 'vol'])
	dataf['unix'] = pd.to_datetime(dataf['unix'],unit='s')
	dataf = dataf.set_index('unix')
	dataf = dataf.resample('1min', how = {'price':'last'})
	dataf.price = dataf.price.fillna(method = 'ffill')
	dataf['signal'] = 0
	dataf['pnl'] = np.nan
	postproc(0, len(dataf.index)-1440, dataf)


def time_calc(rowdate, dateobj, funcform):
	rw_truncate = rowdate.replace(second = 0, microsecond =0)
	timediff = rw_truncate - dateobj
	exdays = timediff.days
	exmin = timediff.seconds//60
	if funcform:
		if exdays >= 0:
			return exmin
		else:
			return 0
	return exmin


def data_filler (row ,value, mode_val, dataf):
	if mode_val ==0:
		for i in range(0,value):
			last_date_in_frame = dataf.index[-1].to_datetime()
			tmstmp = pd.Timestamp(last_date_in_frame + timedelta(0,60))
			tmpprice = dataf.price[-1]
			dataf.loc[tmstmp] = [tmpprice,0,np.nan]
	elif mode_val == 1:
		row_date =  datetime.strptime(row[0],'%Y-%m-%d %H:%M:%S')
		row_date = row_date.replace(second = 0, microsecond = 0)
		tmstmp = pd.Timestamp(row_date)
		dataf.loc[tmstmp] = [float(row[1]),0,np.nan]


def updtr_hlpr_once(handlr, dataf, ctr):
	for row in handlr:
		row_date =  datetime.strptime(row[0],'%Y-%m-%d %H:%M:%S')
		last_date_in_frame = dataf.index[-1].to_datetime()
		value = time_calc(row_date, last_date_in_frame,1)
		#print "last date is " + str(last_date_in_frame) + 'row is '+ str(row_date) + "val is " + str(value)
		if value == 1:
			data_filler(row, 0,1, dataf)
			ctr+=1
		elif value > 1:
			data_filler(None, value - 1, 0, dataf)
			data_filler(row, 0,1, dataf)
			ctr+=value


def updtr_hlpr_min (handlr, dataf, ctr):
	
	for row in reversed(list(handlr)):
		row_date = datetime.strptime(row[0],'%Y-%m-%d %H:%M:%S')
		last_date_in_frame = dataf.index[-1].to_datetime()
		value = time_calc(row_date, last_date_in_frame,0)
		if value == 1:
			data_filler(row, 0,1, dataf)
			ctr+=1
		elif value <= 0:
			data_filler(None, 1,0, dataf)
			ctr+=1
		elif value >1:
			data_filler(None, value - 1, 0,dataf)
			data_filler(row, 0,1, dataf)
			ctr+=value
		break


def dataupdtr(url24, mode_val, dataf, ctr):
	ctr = 0
	last_date_in_frame = dataf.index[-1].to_datetime()
	date_now = datetime.utcnow()
	#write into another function
	response = urllib2.urlopen(url24)
	cr = csv.reader(response, delimiter = ',' )
	next (cr, None) # remove extra
	if mode_val:
		updtr_hlpr_once(cr,dataf, ctr)
	else:
		updtr_hlpr_min(cr, dataf, ctr)

	#now update positions and pnl
	if ctr:
		postproc(len(dataf.index)-1440-ctr,len(dataf.index)-1440, dataf)
	#print dataf


def repeaterfun(dataf, ctr):
	startime = time.time()
	dataupdtr('https://api.bitcoinaverage.com/history/USD/per_minute_24h_sliding_window.csv',1, dataf, ctr)
	while True:
		time.sleep(60-(time.time()-startime))
		startime =time.time()
		dataupdtr('https://api.bitcoinaverage.com/history/USD/per_minute_24h_sliding_window.csv',0, dataf, ctr)

# if __name__ == "__main__":
# 	catchhist('http://api.bitcoincharts.com/v1/csv/bitfinexUSD.csv.gz', False, dataf)
# 	repeaterfun()
# 	#catchbyurl('https://api.bitcoinaverage.com/history/USD/per_minute_24h_sliding_window.csv')