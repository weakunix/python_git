import socket
import sys
import datetime
import time
import urllib.request
import os
#files:
import send_recv

external_ip = urllib.request.urlopen('https://ident.me').read().decode('utf8');
name = input("what is your name");
name1 = "";
namething = '';
sendReadAlerts = "";
s = '';
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
def setupN():
    global name;
    global port;
    global external_ip;
    global name1;
    global namething;
    global s;
    global sendReadAlerts;
    port = int(input("port?"));
    ipplaceholder = get_ip();
    s = socket.socket();
    s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1);
    print("logged in on local ip:",ipplaceholder);
    print("\nglobal IP:",external_ip);
    print(port);
    host=input(str("please enter host name of server"));
    s.connect((host,port));
    name1 = s.recv(1024);
    name1 = name1.decode();
    name = name.encode();
    s.send(name);#
    name = name.decode();
    print(ipplaceholder);
    ipplaceholder=ipplaceholder.encode();
    s.send(ipplaceholder);#
    ipplaceholder = ipplaceholder.decode()
    time.sleep(0.5);
    extern=external_ip.encode();
    s.send(extern);
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
while c!=-1:
  while c==0:
    setupN();
    c=1
  while c==1:
    if(send_recv.sendMsg(s,namething,name,name1,sendReadAlerts) == 0):
      c=0;
    if(send_recv.recvMsg(s,namething,name,name1,sendReadAlerts) == 0):
      c=0;
