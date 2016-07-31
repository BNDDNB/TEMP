import csv
import urllib2
import time
from datetime import date, datetime, timedelta
import urllib
import gzip
import pandas as pd


#def filewriter():

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
	#find day time range
	# curtime = time.time()
	# yesterday = date.today() - timedelta(1)
	# unix_yesterday = yesterday.strftime("%s")
	dlname = 'data/data.gz'
	tgname = 'data/daily.csv'
	urllib.urlretrieve(url,dlname)
	filehlpr(dlname,tgname)
	data = pd.read_csv(tgname, names = ['unix', 'price', 'vol'])
	data['unix'] = pd.to_datetime(df['unix'],unit='s')
	data = data.set_index('unix')
	data.resample('M', how = {'price':'last','vol':'sum'})
	for row in data:
		print row

	#panda
	# reader = csv.reader('data/daily.csv', delimiter = ',')
	# for row in reader:

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