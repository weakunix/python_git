import socket
import sys
import datetime
import time
import urllib.request
import os
import encryption_decryption

external_ip = urllib.request.urlopen('https://ident.me').read().decode('utf8');
message = '';
name = input("what is your name");
port = 12345;
def get_ip():
  s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
  try: 
    # doesn't even have to be reachable
    s.connect(('10.255.255.255', 1))
    IP = s.getsockname()[0]
  except:
    IP = '127.0.0.1'
  finally:
    s.close()
  return IP
c=0;
while c!=-1:
  while c==0:
    port = int(input("port?"));
    ipplaceholder = get_ip();
    s = socket.socket();
    s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1);
    print("logged in on local ip:",ipplaceholder);
    print("\nglobal IP:",external_ip);
    print(port);
    host=input(str("please enter host name of server"));
    s.connect((host,port));
    name1 = s.recv_all(1024);
    name1 = name1.decode();
    name = name.encode();
    s.sendall(name);#
    name = name.decode();
    print(ipplaceholder);
    ipplaceholder=ipplaceholder.encode();
    s.sendall(ipplaceholder);#
    ipplaceholder = ipplaceholder.decode()
    time.sleep(0.5);
    extern=external_ip.encode();
    s.sendall(extern);
    #
    temptuple = ("convos",str(datetime.datetime.now()),".txt")
    namething = str("".join(temptuple));
    print(namething);
    namething = namething.replace(' ','_');
    namething = namething.replace(':','_');
    print(namething);
    h=open(namething,"w+");
    temptuple1 = ("From NOST, on port: ",str(port),": conversation between ",name," (",ipplaceholder,")(",external_ip,") and ",name1," (",host,") (",host,")\n ================= \n");
    #temptuple1 = ("conversation between ",name," (",ipplaceholder,") and ",name1," (",host,") \n ================= \n")
    temptuple1= "".join(temptuple1);
    h.write(str(temptuple1));
    h.close()
    print("successfully connected to server, 1 other online:"+name1)
    sendReadAlerts = input("send read alerts? (yes,no)");
    if(sendReadAlerts != "yes" and sendReadAlerts != "no"):
      print("yes or no dumbo! defaulted to no");
      sendReadAlerts = "no";
    c=1
  while c==1:
    print(21);
    #time.sleep(0.5);
    incoming_message = s.recv_all(1024);
    incoming_message = incoming_message.decode();
    print(12);
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
      s.close();
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
      s.sendall(status);
    else:
      print(1); #ghjejejjeke
      print("at ",datetime.datetime.now(),">",name1+": ", incoming_message);
      if (sendReadAlerts == "yes"):
        status = "read"
      else:
        status = "1"
      status = status.encode();
      s.sendall(status);
      print("");
      #asdfadf
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
        s.sendall(message);
        s.close()
        s.close();
        print("delivered");
        rec = input("Record this conversation?(yes or no)");
        if (rec == "no"):
          os.remove(namething);
        c=0;
      elif(message == "/stop"):
        message = "[ACTION]:the recipient has exited the chat room!";
        h=open(namething,"a");
        h.write(name)
        h.write(message);
        h.write("\n");
        h.close();
        message = message.encode();
        s.sendall(message);
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
        s.sendall(message);
        print("delivered");
        rec = input("Record this conversation?(yes or no)");
        if (rec == "no"):
          os.remove(namething);
        c=0;
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
        s.sendall(message);
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
        s.sendall(message);
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
        s.sendall(message)
        print("delivered");
        #if(sendReadAlerts == "yes"):
        status1 = s.recv_all(1024);
        status1 = status1.decode();
        if(status1 != "1"):
          print(status1);
        else:
          print("");
        print("");
