import smtplib

print("SMTP Client")
mailfrom = raw_input("FROM    : ")
mailto   = raw_input("TO      : ")
msg      = raw_input("MESSAGE : ")

# Using a try-except block to try sending a mail
try:
	# Setting up the IP and Port at which the mail transmission occurs
	server = smtplib.SMTP('127.0.0.1', 4444)
	server.sendmail(mailfrom, mailto, msg)
	print('Mail Transmission Successful!')
except smtplib.SMTPException:
	print('Mail Transmission Failed!')
finally:
	server.quit()