import csv
import urllib2
import time
from datetime import date, datetime, timedelta


#def filewriter():

def catchbyurl(url24, is_saved):
	response = urllib2.urlopen(url24)
	cr = csv.reader(response, delimiter = ',' )
	next (cr, None) # remove extra
	temp_dict = dict(cr)
	fin_dict = dict ((key[:-3],value) for key, value in temp_dict.items())
	#improve with checkr of file existance
	with open('24hr.csv', 'wb') as csv_file:
	    writer = csv.writer(csv_file)
	    for key, value in mydict.items():
	       writer.writerow([key, value])


def catchdaily(url, is_saved):
	#find day time range
	curtime = time.time()
	yesterday = date.today() - timedelta(1)
	unix_yesterday = yesterday.strftime("%s")
	response = urllib2.urlopen(url)
	cr = csv.reader(response, delimiter = ',' )

	#grab only available data
	for row in cr:





if __name__ == "__main__":
	catchbyurl('https://api.bitcoinaverage.com/history/USD/per_minute_24h_sliding_window.csv', False)