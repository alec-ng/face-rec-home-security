import smtplib,os
from email import encoders
from email.mime.base import MIMEBase
from email.MIMEMultipart import MIMEMultipart
from email.MIMEText import MIMEText
import socket 


def sendmail(logname):
	#Initialize the email addresses
	fromaddr ='eece381@gmail.com'
	toaddr ='eece381@gmail.com'
	name = '/home/pi/reports/'+logname+'.pdf'
	print name
	#Create a message made out of two components: text and pdf
	msg = MIMEMultipart()
	#Message attributes
	msg['Subject'] = 'Your log from '+logname
	msg['From'] = fromaddr
	msg['To'] = toaddr

	# Read a text message file and attach it to the email
	fp = open('msg.txt', 'rb')
	msg.attach(MIMEText(fp.read()))
	fp.close()
	print ('TXT Message attached')
	#Specify the type of attachment as 
	pdfAttachment = MIMEBase('application',"octet-stream")

	#Specify the payload of a message
	pdfAttachment.set_payload(open(name,'rb').read())
	 
	encoders.encode_base64(pdfAttachment)

	#Add header to the message
	pdfAttachment.add_header('content-disposition', 'attachment; filename="{0}"'.format(os.path.basename(name)))
	msg.attach(pdfAttachment)
	print ('PDF Message attached')
	# Enapsulate SMTP connection, set identification parameters
	# put the SMTP connection in TLS mode, login and send the message via our own SMTP server
	# See this: https://docs.python.org/2/library/smtplib.html
	socket.setdefaulttimeout(10)
	s = smtplib.SMTP('smtp.gmail.com', 587)	
	#Set the debug output level: show all messages for the connection process if param is 1
	s.set_debuglevel(0)
	s.ehlo()
	s.starttls()
	#login/password information for the email
	s.login("eece381@gmail.com", "eceeceece")
	s.sendmail(fromaddr, [toaddr], msg.as_string())
	s.quit()

if __name__ == '__main__':
	sendmail(logname)