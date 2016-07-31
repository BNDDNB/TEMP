import csv
import urllib2
import time
from datetime import date, datetime, timedelta
import urllib
import gzip
import pandas as pd
from proc import strategy1
import numpy as np

#def filewriter():
dataf = pd.DataFrame()

def catchbyurl(url24, is_saved):
	response = urllib2.urlopen(url24)
	cr = csv.reader(response, delimiter = ',' )
	next (cr, None) # remove extra
	temp_dict = dict(cr)
	fin_dict = dict ((key[:-3],value) for key, value in temp_dict.items())
	#improve with checkr of file existance
	# if not os.path.exists(DATA_DIRECTORY):
	# 		os.makedirs(DATA_DIRECTORY)
	with open('data/24hr.csv', 'wb') as csv_file:
	    writer = csv.writer(csv_file)
	    for key, value in mydict.items():
	       writer.writerow([key, value])


def filehlpr(filename, targetname):
	inF = gzip.GzipFile(filename, 'rb')
	s = inF.read()
	inF.close()
	outF = file(targetname, 'wb')
	outF.write(s)
	outF.close()


def catchhist(url, is_saved):
	dlname = 'data/data.gz'
	tgname = 'data/daily.csv'
	finname ='data/dailyproc.csv'
	#urllib.urlretrieve(url,dlname)
	filehlpr(dlname,tgname)

	###########Proc & After########
	dataf = pd.read_csv(tgname, names = ['unix', 'price', 'vol'])
	dataf['unix'] = pd.to_datetime(dataf['unix'],unit='s')
	dataf = dataf.set_index('unix')
	dataf = dataf.resample('1min', how = {'price':'last'})
	dataf.price = dataf.price.fillna(method = 'ffill')
	dataf['signal']=0
	dataf['pnl'] = np.nan
	print len(dataf.index)
	
	for i in range(987655,992000-1441):
		#print "im working"
		dataarr = dataf['price'][i:1440+i].tolist()
		oldpos = dataf['signal'][1439+i]
		newpos,pnl = strategy1(dataarr,oldpos)
		dataf.ix[1440+i,'signal']= newpos
		dataf.ix[1439+i,'pnl'] = pnl

	print dataf['signal'][1441:1700]
	print dataf['pnl'][1441:1700]
	#####if dataf.index[-1].to_datetime <= datetime.utcnow():


	#data.to_csv(finname, sep=',', encoding='utf-8')

	#cr = csv.reader(response, delimiter = ',')
	#grab only available data
	# with open('data/daily.csv','wb') as csv_file:
	# 	writer = csv.writer(csv_file)
	# 	for row in cr:
			# if row[0]<=curtime and row[0]>=unix_yesterday:
			# 	writer.writerow(row)



def main():
	catchhist('http://api.bitcoincharts.com/v1/csv/bitfinexUSD.csv.gz', False)
	#catchbyurl('https://api.bitcoinaverage.com/history/USD/per_minute_24h_sliding_window.csv', False)


if __name__ == "__main__":
	main()