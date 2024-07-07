import smtpd
import asyncore

class CustomSMTPServer(smtpd.SMTPServer):
	# Function which displays the details of each mail transmitted by the client
	def process_message(self, peer, mailfrom, recpt, msg):
		print('Recieving Message From : ' + str(peer)) 
		print('Message Addressed From : ' + str(mailfrom))
		print('Message Addressed To   : ' + str(recpt))
		print('Message Length         : ' + str(len(msg)))
	

# Setting the IP and Port at which the message transmission takes place 
server = CustomSMTPServer(('127.0.0.1', 4444), None)
# Runs as long as the program is shutdown
asyncore.loop()