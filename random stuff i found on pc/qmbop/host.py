import socket
import sys
import datetime 
import time
message = '';
incoming_message = '';
name = input("what is your name");
c=0;
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
def isBlocked(): #here ruoyu asdydfkffkkffllfkfoeoleld,d,kdkjrkfmmckmihjjhuhfehujjuejuju3j8j88
	count = 0;
	with open("blocked.txt", 'r') as f:
	  for line in f:
	    count += 1#first gets number of lines with count
	w = open("blocked.txt",'r')
	for i in range(count):
		x=str(w.readline(i));#assigns lines as x then compares it with blocked ones
		print(str(w.readline(i)),"< x\n");
		if(x==theirIP):
			conn.send(("you got blocked boi!").encode);
			conn.close();
			w.close()
			return 1;
	w.close()
	return 0;
while c!=-1:
        while c==0:
                time.sleep(1);
                s = socket.socket();
                s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1);
                host = get_ip();
                port = 23;
                s.bind((host,port))
                print("logged in on:",host);
                print("successfully connected \n waiting for connections\n cancel?");
                s.listen(1);
                conn, adr = s.accept();
                z=0;
                w = open("blocked.txt", 'r');
                name = name.encode();
                conn.send(name);
                name = name.decode();
                name1 = conn.recv(1024);
                name1 = name1.decode();
                theirIP = conn.recv(1024);
                theirIP=theirIP.decode();
                blocorno = isBlocked();
                print(theirIP," known as ",name1," Joined the server!\n=======Talk======\n");
                temptuple = ("convos",str(datetime.datetime.now()),".txt") 
                namething = "".join(temptuple);
                h=open(namething,"w");
                temptuple1 = ("conversation between ",name," (",host,") and ",name1," (",theirIP,")\n ================= \n")
                temptuple1= "".join(temptuple1);
                h.write(str(temptuple1));
                h.close()
                c=1
        while c==1:
                message = input(str(">>"));
                h=open(namething,"a");
                temptuple3 = ("\n at:",str(datetime.datetime.now())," \n ",name,">> ",message,"\n");
                temptuple3= "".join(temptuple3);
                h.write(str(temptuple3));
                h.close();
                if(message == "/block"):
                        message = "[ACTION]:the recipient has blocked you";
                        message = message.encode();
                        bf=open("blocked.txt","a");
                        bf.write(str(theirIP)+"\n");
                        bf.close();
                        conn.send(message);
                        conn.close()
                        s.close();
                        print("delivered");
                        c=0;
                elif(message == "/stop"):
                        message = "[ACTION]:the recipient has exited the chat room!";
                        message = message.encode();
                        conn.send(message);
                        print("delivered");
                        c=-1;
                elif(message == "/end"):
                        message = "[ACTION]:the recipient has ended the conversation!";
                        message = message.encode();
                        conn.send(message);
                        print("delivered");
                        c=0;
                elif(message == "/contact add"):
                        contactName=str(input("new contact name?"));
                        message = ("[ACTION]:the recipient added you as a contact: ",contactName);
                        d = open("contact.txt","a");
                        d.write(contactName);
                        d.write(theirIP);
                        message = "".join(message);
                        message = message.encode();
                        conn.send(message);
                else:
                        #sdfasdfh
                        message = message.encode();
                        conn.send(message);
                        print("delivered");
                        status1 = conn.recv(1024);
                        status1 = status1.decode();
                        print(status1);
                        print("");
                        #adwfdas
                        incoming_message = conn.recv(1024);
                        incoming_message = incoming_message.decode();
                        h=open(namething,"a");
                        temptuple2 = ("\n at:",str(datetime.datetime.now())," \n ",name1,">> ",incoming_message,"\n")
                        temptuple2= "".join(temptuple2);
                        h.write(str(temptuple2));
                        h.close();
                        if (incoming_message == "[ACTION]:the recipient has exited the chat room!" or incoming_message == "[ACTION]:the recipient has ended the conversation!" or incoming_message == "[ACTION]:the recipient has blocked you"):
                        	print("at ",datetime.datetime.now(),">",name1,": ",incoming_message);
                        	c=0;
                        	conn.close();
                        else:
                        	print("at ",datetime.datetime.now(),">",name1,": ",incoming_message);
                        	print("");
	                        status = ("read")
                        	status = status.encode();
                        	conn.send(status);

