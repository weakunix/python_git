import socket
import sys
import datetime
import time
import urllib.request
import os
import threading
import encryption_decryption

def recvMsg():
  incoming_message = s.recv(1024);
  incoming_message = incoming_message.decode();
  h=open(namething,"a");
  temptuple2 = ("\n at:",str(datetime.datetime.now())," \n ",name1,">> ",incoming_message,"\n")
  temptuple2= "".join(temptuple2);
  h.write(str(temptuple2));
  h.close();
  if (incoming_message == "[ACTION]:the recipient has exited the chat room!" or incoming_message == "[ACTION]:the recipient has ended the conversation!" or incoming_message == "[ACTION]:the recipient has blocked you"):
    print("at ",datetime.datetime.now(),">",name1,": ",incoming_message);
    h=open(namething,"a");
    temptuple2 = ("\n at:",str(datetime.datetime.now())," \n ",name1,">> ",incoming_message,"\n")
    temptuple2= "".join(temptuple2);
    h.write(str(temptuple2));
    h.close();
    rec = input("Record this conversation?(yes or no)");
    if (rec == "no"):
      os.remove(namething);
    c=0;
    return 0;
    #s.close();
  elif(incoming_message == "[retract%message]"):
    print("at ",datetime.datetime.now(),">",name1,": ",incoming_message);
    h=open(namething,"a");
    temptuple2 = ("\n \n ",name1,">> [retract last message]\n")
    temptuple2= "".join(temptuple2);
    h.write(str(temptuple2));
    h.close();
    if (sendReadAlerts == "yes"):
      status = "read"
    else:
      status = "1"
    status = status.encode();
    s.send(status);
  else:
    print(1); #ghjejejjeke
    print("at ",datetime.datetime.now(),">",name1+": ", incoming_message);
    if (sendReadAlerts == "yes"):
      status = "read"
    else:
      status = "1"
    status = status.encode();
    s.send(status);
    print("");
def sendMsg():
  message = input(str(">>"))
  if(message == "/block"):
    message = "[ACTION]:the recipient has blocked you";
    h=open(namething,"a");
    h.write(name)
    h.write(message);
    h.write("\n");
    h.close();
    message = message.encode();
    bf=open("blocked.txt","a");
    bf.write(str(host)+"\n");
    bf.close();
    s.send(message);
    s.close()
    s.close();
    print("delivered");
    rec = input("Record this conversation?(yes or no)");
    if (rec == "no"):
      os.remove(namething);
    c=0;
    return 0;
  elif(message == "/stop"):
    message = "[ACTION]:the recipient has exited the chat room!";
    h=open(namething,"a");
    h.write(name)
    h.write(message);
    h.write("\n");
    h.close();
    message = message.encode();
    s.send(message);
    print("delivered");
    rec = input("Record this conversation?(yes or no)");
    if (rec == "no"):
      os.remove(namething);
    c=-1;
  elif(message == "/end"):
    message = "[ACTION]:the recipient has ended the conversation!";
    h=open(namething,"a");
    h.write(name)
    h.write(message);
    h.write("\n");
    h.close();
    message = message.encode();
    s.send(message);
    print("delivered");
    rec = input("Record this conversation?(yes or no)");
    if (rec == "no"):
      os.remove(namething);
    c=0;
    return 0;
  elif(message == "/retract"):
    message = "[retract%message]"
    #h=open(namething,"r"); RUOYU NEED FILE READER HERE
        #h.readline(((messageNum*3)+2));
        #get message to variable and send it off as retracted
        #h.close();
    h=open(namething,"a");
    h.write(name)
    h.write(message);
    h.write("\n");
    h.close();
    message = message.encode();
    s.send(message);
    print("delivered");
  elif(message == "/contact add"):
    contactName=str(input("new contact name?"));
    message = ("[ACTION]:the recipient added you as a contact: ",contactName);
    d = open("contact.txt","a");
    d.write(contactName);
    d.write(host);
    message = "".join(message);
    h=open(namething,"a");
    h.write(name)
    h.write(message);
    h.write("\n");
    h.close();
    message = message.encode();
    s.send(message);
  else:
    if (message == "<e>"):
      secureMessage = True;
    else:
      secureMessage = False;
    if(secureMessage==True):
      message = input(str("SECURE MODE >>"));
      message = encryption_decryption.encrypt(message);
    h=open(namething,"a");
    temptuple3 = ("\n at:",str(datetime.datetime.now())," \n ",name,">> ",message,"\n");
    temptuple3= "".join(temptuple3);
    h.write(str(temptuple3));
    h.close();
    message = message.encode();
    s.send(message)
    print("delivered");
        #if(sendReadAlerts == "yes"):
    status1 = s.recv(1024);
    status1 = status1.decode();
    if(status1 != "1"):
      print(status1);
    else:
      print("");
    print("");
