import csv
import urllib2
import time
from datetime import date, datetime, timedelta
import urllib
import gzip
import pandas as pd
from proc import strategy1
import numpy as np
import ini


'''
File helper function that uncompresses the 
downloaded historical files for further processing

Input: Input to the function contains two strings,
first string represent the filename to uncompress,
second string is the target location.

Ouput: None

Imp: can use gz reader directly edit depending on 
the requirement in future
'''

def filehlpr(filename, targetname):
	inF = gzip.GzipFile(filename, 'rb')
	s = inF.read()
	inF.close()
	outF = file(targetname, 'wb')
	outF.write(s)
	outF.close()





'''
Postproc is the fuction that sends the data structure
into the modelling engine for processing

Input: lowerbound and upper bound of the structure to 
feed data into modelling engine

Output: none

Imp: use datastructure's own rolling_avg function to create
a function that is faster for rolling avg generation.
However, only for this task...
'''

def postproc(low_bound, up_bound):
	for i in range(low_bound,up_bound):
		dataarr = ini.dataf['price'][i:1440+i].tolist()
		oldpos = ini.dataf['signal'][1439+i]
		newpos,pnl = strategy1(dataarr,oldpos)
		ini.dataf.ix[1440+i,'signal']= newpos
		ini.dataf.ix[1439+i,'pnl'] = pnl




'''
catchhist is the function that used to download all historical
data from the bitcoin site. url and file helper can be disabled
for testing purposes, re-enable them to test the full function

input: url of the historical file, and a parameter indicating
if wanting to save the result back into a file. 

Output: none

Improve: Need to understand the datastructure of raw data first

'''

def catchhist(url, is_saved):
	dlname = 'data/hist.gz'
	tgname = 'data/hist.csv'
	finname ='data/dailyproc.csv'
	urllib.urlretrieve(url,dlname)
	filehlpr(dlname,tgname)

	###########Proc & After########
	ini.dataf = pd.read_csv(tgname, names = ['unix', 'price', 'vol'])
	ini.dataf['unix'] = pd.to_datetime(ini.dataf['unix'],unit='s')
	ini.dataf = ini.dataf.set_index('unix')
	ini.dataf = ini.dataf.resample('1min', how = {'price':'last'})
	ini.dataf.price = ini.dataf.price.fillna(method = 'ffill')
	ini.dataf['signal'] = 0
	ini.dataf['pnl'] = np.nan
	postproc(0, len(ini.dataf.index)-1440)
	ini.dataf.to_csv(finname, sep = ',', encoding = 'utf-8')




'''
time_calc function calculates time difference with given objects.
there are two methods that the function could run. 1. is for the first time
catching up with historical data, where <=0 does not matter 2. is for 
per-min update, where <0 matters

Input: require 3 inputs, the date value showing on row number, from the object and
a indicator for the runnign mode.

Ouput: the difference of time in minutes

Imp: None yet...
'''


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




'''
data_filler function uses given data to fill the data structure
record with either previous row values or the new row value 
depending on the mode indicator

input: the data row from url, the iteration value and the 
mode indicator value

Output: None

Imp: None...
'''


def data_filler (row ,value, mode_val):
	if mode_val ==0:
		for i in range(0,value):
			last_date_in_frame = ini.dataf.index[-1].to_datetime()
			tmstmp = pd.Timestamp(last_date_in_frame + timedelta(0,60))
			tmpprice = ini.dataf.price[-1]
			ini.dataf.loc[tmstmp] = [tmpprice,0,np.nan]
	elif mode_val == 1:
		row_date =  datetime.strptime(row[0],'%Y-%m-%d %H:%M:%S')
		row_date = row_date.replace(second = 0, microsecond = 0)
		tmstmp = pd.Timestamp(row_date)
		ini.dataf.loc[tmstmp] = [float(row[1]),0,np.nan]





'''
updtr_hlpr_once function is the one time update right after the
restart of server to catch up with any new data in the distant past

Input: a handlr to the file reader hence the data can be read by this function

Ouput: None

Imp: May be combined with permin update, depends on data structure
'''

def updtr_hlpr_once(handlr):
	for row in handlr:
		row_date =  datetime.strptime(row[0],'%Y-%m-%d %H:%M:%S')
		last_date_in_frame = ini.dataf.index[-1].to_datetime()
		value = time_calc(row_date, last_date_in_frame,1)
		if value == 1:
			data_filler(row, 0,1)
			ini.ctr+=1
		elif value > 1:
			data_filler(None, value - 1, 0)
			data_filler(row, 0,1)
			ini.ctr+=value




'''
updtr_hlpr_min function is the perminute update function 
this runs every minutes to update existing data structure

Input: same as the one-time updater

Ouput: none

Imp:...

'''

def updtr_hlpr_min (handlr):
	for row in reversed(list(handlr)):
		row_date = datetime.strptime(row[0],'%Y-%m-%d %H:%M:%S')
		last_date_in_frame = ini.dataf.index[-1].to_datetime()
		value = time_calc(row_date, last_date_in_frame,0)
		if value == 1:
			data_filler(row, 0,1)
			ini.ctr+=1
		elif value <= 0:
			data_filler(None, 1,0)
			ini.ctr+=1
		elif value >1:
			data_filler(None, value - 1, 0)
			data_filler(row, 0,1)
			ini.ctr+=value
		break




'''
dataupdtr function is the main controller of all the updates
the function uses given url to check the given csv file 
and create handles for the one-time / per-min update function to use

input: a string representing url of the updated data, and the mode
indicator to determine which mode the function should be running in.

output: none

Imp: none
'''


def dataupdtr(url24, mode_val):
	ini.ctr = 0
	last_date_in_frame = ini.dataf.index[-1].to_datetime()
	date_now = datetime.utcnow()
	#write into another function
	response = urllib2.urlopen(url24)
	cr = csv.reader(response, delimiter = ',' )
	next (cr, None) # remove extra
	if mode_val:
		updtr_hlpr_once(cr)
	else:
		updtr_hlpr_min(cr)

	#now update positions and pnl
	if ini.ctr:
		postproc(len(ini.dataf.index)-1440-ini.ctr,len(ini.dataf.index)-1440)





'''
Below is used for testing purposes
'''
#import threading
#ini.dataf = pd.DataFrame()
#ini.ctr = 0

# def repeaterfun():
# 	startime = time.time()
# 	dataupdtr('https://api.bitcoinaverage.com/history/USD/per_minute_24h_sliding_window.csv',1)
# 	while True:
# 		time.sleep(60-(time.time()-startime))
# 		startime =time.time()
# 		dataupdtr('https://api.bitcoinaverage.com/history/USD/per_minute_24h_sliding_window.csv',0)

# if __name__ == "__main__":
# 	catchhist('http://api.bitcoincharts.com/v1/csv/bitfinexUSD.csv.gz', False)
# 	repeaterfun()
# 	#catchbyurl('https://api.bitcoinaverage.com/history/USD/per_minute_24h_sliding_window.csv')