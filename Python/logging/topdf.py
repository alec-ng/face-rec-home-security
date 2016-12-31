from __future__ import division
from reportlab.pdfgen import canvas
from reportlab.lib.units import inch, cm


def pdf (c,logname):
	#define picture, date shift and y-height of the pdf document page
	y=550
	picshift=250
	codeshift=190
	dateshift=10
	
	#define the coordinate difference between the current and next record
	nextline=250
	
	#define picture width and heigh in cm
	width=10*cm
	height=8*cm
	j=0;
	
	#form an array out of text file records (date/picture path)
	with open(logname,'r') as f:
		content = f.read().split('\t')
	
	#figure out the number of pages we'll need to create
	if ((len(content)-1)/3!=int((len(content)-1)/3) or len(content)==1):
		page=int((len(content)-1)/6)+1
	else:
		page=int((len(content)-1)/6)
	
	#insert max 3 pictures on every page of pdf file
	for i in range(0,page):
		k=0
		while k!=3:
			if(j<len(content)-1):
				#insert date
				c.drawString(dateshift, y-k*nextline, content[j].strip('\r\n'))
				j+=1
				
				#insert code
				c.drawString(codeshift, y-k*nextline, content[j].strip('\r\n'))
				j+=1
				
				#if the next record is a link to picture, draw it
				#else insert space
				if (len(content[j])>15):
					c.drawImage(content[j].strip('\r\n'), picshift, y-k*nextline, width, height)
				else:
					c.drawString(picshift, y-k*nextline, content[j].strip('\r\n'))
				
				j+=1
				k+=1
			else:
				break
			# stop drawing on the current page, switch to the new one
		c.showPage()

def drawlog(logname):

	#define the canvas variable containing the path to the text document we'll read
	logfilename=logname.split('/')[4]
	print 'HERE logname in pdf '+logfilename
	c = canvas.Canvas('/home/pi/reports/'+logfilename.split('.l')[0]+'.pdf')

	#call the function to create a pdf file out of the text file contents we passed
	pdf(c,logname)
	#save and generate pdf document
	c.save()
	
if __name__ == '__main__':
	#logname=''
	drawlog(logname)