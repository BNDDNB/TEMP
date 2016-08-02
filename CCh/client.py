import socket
import sys
import time


###############################Variables Used###################
# Symbolic name meaning all available interfaces
try:
	HOST = input("Please enter host address:")
except SyntaxError:
	HOST = None
   
# Arbitrary non-privileged port
try:
	PORT = int(input("Port number:"))
except SyntaxError:
	PORT = None

HOST = 'localhost' if HOST is None else HOST
PORT = 8000 if PORT is None else PORT




##########################Email Function####################

'''
This is the function that handels email sending etc. before using this program,
one need to setup the configuration file in the same directory.
the format of the config file should follow username, password on separate lines
the default value uses programmer's address to demonstrate.

input: none
ouput:none

imp:handles text that is based on error or user input/will

'''



def email_sendr():
	import smtplib
	with open('ini.conf') as f:
		username = f.readline()
		password = f.readline()

	f.close()

	sender = 'bonan.dong@gmail.com'
	receivers = ['bonan.dong@gmail.com']

	SUBJECT = "SMTP e-mail test"
	TEXT = "This is a test e-mail message."

	message  = 'Subject: %s\n\n%s' % (SUBJECT, TEXT)
	server = smtplib.SMTP('smtp.gmail.com:587')
	server.ehlo()
	server.starttls()
	server.ehlo()

	try:
		server.login(username, password)
		server.sendmail(sender, receivers, message)         
		print "Successfully sent email"
	except smtplib.SMTPException:
		print "Error: unable to send email"


###########################Client Base#########################




'''
similar to the base of the server, the client binds socket, interact
with users and connect with server. upon error, the emailing function aobve will be
called and an error email will be sent, process is then terminated.

'''




# Create a TCP/IP socket
sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

# Connect the socket to the port where the server is listening
server_address = (HOST, PORT)
print >>sys.stderr, 'connecting to %s port %s' % server_address

try:
	sock.connect(server_address)

except socket.error as msg:
	#print 'Sending Email : ' + str(msg[0]) + ' Message ' + msg[1]
	email_sendr()
	sys.exit()

try:
	
	time.sleep(1)
	data = sock.recv(1024)
	print data

	while True:
		message = input ("Please give command: ")
		sock.sendall(message)
		time.sleep(1)
		data = sock.recv(1024)
		print data

finally:
    print >>sys.stderr, 'closing socket'
    sock.close()