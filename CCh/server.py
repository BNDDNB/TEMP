import socket
import sys
import ini
import time
from thread import *
import datadl as dl
import threading
import signal
import pandas as pd
from datetime import date, datetime, timedelta


'''
Defalt & setting on host&port
'''
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

#default value for PORT and HOST

HOST = 'localhost' if HOST is None else HOST
PORT = 8000 if PORT is None else PORT
ini.init()





##############################Background Section ####################

'''
This is the process that runs in the background for updating purposes,
upon start, the process will run from download module for file obtain
and update. There is no input nor output from the function

'''

def background_proc():
    #global ini.dataf, background_controller
    dl.catchhist('http://api.bitcoincharts.com/v1/csv/bitfinexUSD.csv.gz', False)
    startime = time.time()
    dl.dataupdtr('https://api.bitcoinaverage.com/history/USD/per_minute_24h_sliding_window.csv',1)
    while ini.background_controller:
        time.sleep(60-(time.time()-startime))
        startime =time.time()
        dl.dataupdtr('https://api.bitcoinaverage.com/history/USD/per_minute_24h_sliding_window.csv',0)





##############################CLIENT SECTION#####################################

'''
Function thread that handels client request, uses the connection as an input
the thread handles user requiremend based on the input, if wrong input, server
reply unrecognized, otherwise, sending not on server.

input: connection handle
output: none

Imp: lock and server systems
'''
  
def clientthread(conn):
    #Sending message to connected client
    conn.send('Welcome to the server. Type something and hit enter\n') #send only takes string
     
    #infinite loop so that function do not terminate and thread do not end.
    while True:
        #Receiving from client
        data = conn.recv(1024)
        
        #in order of price, signal and reset
        if data[0:7] == '--price':
            try:
                timestr = data[8:24]
                timeobj = datetime.strptime(timestr,'%Y-%m-%d-%H:%M')
                timestmp = pd.Timestamp(timeobj)
                reply = str(ini.dataf.loc[timestmp]['price'])
            except:
                reply = 'Server has no data...'      
        elif data[0:8] == '--signal':
            try:
                timestr = data[9:25]
                timeobj = datetime.strptime(timestr,'%Y-%m-%d-%H:%M')
                timestmp = pd.Timestamp(timeobj)
                reply = str(ini.dataf.loc[timestmp]['signal'])
            except:
                reply = 'Server has no data...'
        elif data[0:7] =='--reset':
            ini.background_controller = False
            print "closing down background process in 60s.."
            time.sleep(60)
            print "restarting now..."
            ini.dataf = pd.DataFrame()
            thread2 = threading.Thread(target = background_proc)
            thread2.daemon = True
            ini.background_controller = True
            thread2.start()
            reply = 'Reset completed...'
        else:
            reply = 'Not Recognized... \n'

        conn.sendall(reply)
        if not data: 
            break
    #came out of loop
    conn.close()




################################## SERVER SYS SECTION ##################################

'''
Server socket binding program that deals with receiving the first level user connection
when such connection is connected, a new thread will be passed to the user level program
for connection handling

input/output: none

imp: resolving hanging on socket issue, improving threading

'''




def client_proc():
    #global client_controller
    #Bind socket to local host and port
    try:
        s.bind((HOST, PORT))
    except socket.error as msg:
        print 'Bind failed. Error Code : ' + str(msg[0]) + ' Message ' + msg[1]
        sys.exit()
         
    print 'Socket bind complete'
     
    #Start listening on socket
    s.listen(5)
    print 'Socket now listening'

    while ini.client_controller:
        #wait to accept a connection - blocking call
        conn, addr = s.accept()
        print 'Connected with ' + addr[0] + ':' + str(addr[1])
        #start new thread takes 1st argument as a function name to be run, second is the tuple of arguments to the function.
        start_new_thread(clientthread ,(conn,))
    s.close()

 

 
############################ BASE SYSTEM #########################################

'''
below is the server starting script for the above process, it will create two thread that
respectively handles user programs and as well deals with termination of program
'''

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
print 'Socket created'



#now keep talking with the client (daemon for killing)
thread = threading.Thread(target = client_proc)
thread.daemon = True
thread.start()

thread2 = threading.Thread(target = background_proc)
thread2.daemon = True
thread2.start()

def signal_handler(signal, frame):
    ini.background_controller = False
    ini.client_controller = False
    print "closing down background process in 60s.."
    time.sleep(60)
    print "Terminating Processes..."
    s.close()
    sys.exit(0)

print "Press Ctrl-C to terminate server..."
signal.signal(signal.SIGINT, signal_handler)  
signal.pause()
