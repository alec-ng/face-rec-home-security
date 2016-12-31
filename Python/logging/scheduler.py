from datetime import datetime
import time
import os
import topdf,pmail
import logging
import psycopg2
from apscheduler.schedulers.background import BackgroundScheduler

#returns the size of the file, in bytes
def getSize(filename):
    st = os.stat(filename)
    return st.st_size

#process running every 5 minutes

def sendLog():
	#Select records added during the last 5 min
	cur.execute("SELECT * from log where date between now()-interval'5 minutes' and now()")
	#fetch the rows
	rows = cur.fetchall()
	
	#construct the name of the file (current date)
	datefmt="%m.%d.%Y %H.%M.%S"
	today = datetime.now()
	global currentname
	if (today.strftime(datefmt).index('0')==0):
		currentname='/home/pi/logs/'+today.strftime(datefmt)+'.log'

	f=open(currentname,'a')
	#write every record to the .log file 
	for row in rows:
		f.write(str(row[0])+"\t\r")
		print str(row[0])
		f.write(str(row[1])+"\t\r")
		print str(row[1])
		f.write(str(row[2])+"\t\r\n")
		print str(row[2])
	f.close()
	#if the .log file exists and is not empty, convert it to pdf and send in the email
	if (currentname):
		if(getSize(currentname)!=0):
			oldfilename=currentname.split('/')[4]
			topdf.drawlog(currentname)
			pmail.sendmail(oldfilename.split('.l')[0])	

if __name__ == '__main__':
	#comment this out if sure no errors are thrown
	logging.basicConfig()
	scheduler = BackgroundScheduler()
	#initialize currentname with null value
	global currentname
	currentname = None
	#add the job (function sendLog) to the scheduler
	scheduler.add_job(sendLog,'interval', minutes=5)
	scheduler.start()
	
	try:
		conn = psycopg2.connect(database="securitysystem", user="root")
		cur = conn.cursor()
		print "Connected to the database successfully"
		while True:
			time.sleep(1)
						
	except (KeyboardInterrupt, SystemExit):
		scheduler.shutdown()  # Not strictly necessary if daemonic mode is enabled but should be done if possible