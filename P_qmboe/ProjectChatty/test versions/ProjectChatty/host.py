import socket
import sys
import datetime
import time
import urllib.request
import os
import threading
#files:
import send_recv

external_ip = urllib.request.urlopen('https://ident.me').read().decode('utf8');
name = input("what is your name");
name1 = "";
namething = '';
conn = '';
port = 12345;
sendReadAlerts = "";
theirEIP = "";
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
def setupH():
    global name;
    global port;
    global external_ip;
    global name1;
    global namething;
    global conn;
    global sendReadAlerts;
    global host;
    global theirEIP;
    port = int(input("port?"));
    s = socket.socket();
    s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1);
    host = get_ip();#
    #host = external_ip;
    s.bind((host,port))
    print("logged in on local ip:",host);
    print("\nglobal IP:",external_ip);
    print(port);
    print("\nsuccessfully connected \n waiting for connections\n cancel?");
    #pplJoin = threading.Thread(target=)
    s.listen(1);
    conn, adr = s.accept();
    #send files
    name = name.encode();
    conn.sendall(name);
    name = name.decode();
    name1 = conn.recv(1024);
    name1 = name1.decode();#
    theirIP = conn.recv(1024);
    theirIP=theirIP.decode();#
    print(theirIP);
    theirEIP = conn.recv(1024);
    theirEIP = theirEIP.decode();
    print(theirEIP);
    temptuple = ("convos",str(datetime.datetime.now()),".txt")
    namething = str("".join(temptuple));
    print(namething);
    namething = namething.replace(' ','_');
    namething = namething.replace(':','_');
    print(namething);
    h=open(namething,"w+");
    temptuple1 = ("From HOST, on port: ",str(port),": conversation between ",name," (",host,")(",external_ip,") and ",name1," (",theirIP,") (",theirEIP,")\n ================= \n");
    #temptuple1 = ("conversation between ",name," (",host,") and ",name1," (",theirIP,") \n ================= \n")
    temptuple1= "".join(temptuple1);
    h.write(str(temptuple1));
    h.close()
    os.system('clear')
    print(theirIP," known as ",name1," Joined the server!\n=======Talk======\n");
    sendReadAlerts = input("send read alerts? (yes,no)")
    if(sendReadAlerts != "yes" and sendReadAlerts != "no"):
      print("yes or no dumbo! defaulted to no");
      sendReadAlerts = "no";
    return name,name1
while c!=-1:
  while c==0:
    time.sleep(1);
    setupH();
    c=1;
    if(c==1):
      tSend = threading.Thread(target=send_recv.sendMsg,args=(conn,namething,name,name1,sendReadAlerts,theirEIP,), daemon=True);
      tRecv = threading.Thread(target=send_recv.recvMsg,args=(conn,namething,name,name1,sendReadAlerts,), daemon=True);
      tRecv.start();
      tSend.start();
