# temp_dict = dict(cr)
	# fin_dict = dict ((key[:-3],value) for key, value in temp_dict.items())
	
	#improve with checkr of file existance
	# if not os.path.exists(DATA_DIRECTORY):
	# 		os.makedirs(DATA_DIRECTORY)
	# with open('data/24hr.csv', 'wb') as csv_file:
	#     writer = csv.writer(csv_file)
	#     for key, value in fin_dict.items():
	#        print key, value


#other wise do nothing
	#data.to_csv(finname, sep=',', encoding='utf-8')

	#cr = csv.reader(response, delimiter = ',')
	#grab only available data
	# with open('data/daily.csv','wb') as csv_file:
	# 	writer = csv.writer(csv_file)
	# 	for row in cr:
			# if row[0]<=curtime and row[0]>=unix_yesterday:
			# 	writer.writerow(row)
	
#error checking for current value
	# if not updatehlpr(date_now,last_date_in_frame,1):
	# 	print 'The data at ... time is incorrect, forward in time'
	# 	return


	#newS = pd.Series([tmpprice, 0, np.nan], tmstmp)
			#dataf.append(newS)


# temptest = datetime.now()

# def catchbyurl(url24):
# 	response = urllib2.urlopen(url24)
# 	cr = csv.reader(response, delimiter = ',' )
# 	next (cr, None) # remove extra
# 	for row in cr:
# 		dateobj =  datetime.strptime(row[0],'%Y-%m-%d %H:%M:%S')
# 		timediff = dateobj - temptest
# 		exdays = timediff.days
# 		exmins = timediff.seconds//60
# 		print str(exdays) + ' ' + str(exmins)
# 		if exdays >= 0 and exmins >0:
# 			print 'aaa'


#def filewriter():