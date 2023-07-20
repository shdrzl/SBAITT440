import socket 
import sys
import json

print ("This is SERVER.")
#create socket
s = socket.socket()
print ("Socket successfully created")

port = 8484 

#binding socket to port 8484
s.bind (('', port))
print ("Socket binded to " + str(port))

s.listen (5)
print ("Socket is listening")

c,addr = s.accept()

print ("Got conncection from" + str(addr))
#receiving data from Client and decode into string
data2 = float(c.recv(1024).decode())

#convert bar into atm
dataJ = float(data2) / 1.01325

unit = " atm"
message = str(dataJ) + unit 

#convert string into JSON-formatted string
sendData3 = json.dumps(message)
#encode string into data and send it to Client
c.send(sendData3.encode())
print("After conversion : " ,message)
print ("Message send to Client")

#close the socket
c.close()
