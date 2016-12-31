from datetime import datetime
import time
import os
import topdf,pmail
import logging
import psycopg2

from apscheduler.schedulers.background import BackgroundScheduler
from twilio.rest import TwilioRestClient

#returns the size of the file, in bytes
def getSize(filename):
    st = os.stat(filename)
    return st.st_size
	
#the function formats current date and time and inserts 
#the record into the log file
def curTime():
	datefmt="%b %d/%Y %H:%M:%S"
	today=datetime.now()
	createlog.addrecord(today.strftime(datefmt)+'\t')
	return
	
#main process running at the background every time interval 
#specified by scheduler.add_job function
#creates a new log file, converts the old one to pdf and sends as
#an email with attachment
def sendLog():
	#Select records added during the last 5 min
	cur.execute("SELECT * from log where date between now()-interval'10 minutes' and now()")
	rows = cur.fetchall()
	
	print "Rows selected"
	
	datefmt="%m.%d.%Y %H.%M.%S"
	today = datetime.now()
	global currentname
	#If the log file is created for the first time/empty 
	#then we don't send it
	if (today.strftime(datefmt).index('0')==0):
		currentname='/home/pi/logs//'+today.strftime(datefmt)+'.log'
	else:
		currentname='/home/pi/logs/'+today.strftime(datefmt)+'.log'

	print "Currentname is "+currentname
	f=open(currentname,'a')
	
	for row in rows:
		f.write(str(row[0])+"\t\r")
		print str(row[0])
		f.write(str(row[1])+"\t\r")
		print str(row[1])
		f.write(str(row[2])+"\t\r\n")
		print str(row[2])
	f.close()

	if (currentname):
		if(getSize(currentname)!=0):
			oldfilename=currentname.split('/')[4]
			topdf.drawlog(currentname)
			pmail.sendmail(oldfilename.split('.l')[0])	

if __name__ == '__main__':
	
	#uncomment this to enable error throwing
	logging.basicConfig()
	scheduler = BackgroundScheduler()
	#initialize currentname with null value
	global currentname
	currentname = None
	scheduler.add_job(sendLog,'interval', minutes=10)
	scheduler.start()
	
	try:
		conn = psycopg2.connect(database="securitysystem", user="root")
		cur = conn.cursor()
		print "Connected to the database successfully"
		while True:
			time.sleep(1)
						
	except (KeyboardInterrupt, SystemExit):
		scheduler.shutdown()  # Not strictly necessary if daemonic mode is enabled but should be done if possible