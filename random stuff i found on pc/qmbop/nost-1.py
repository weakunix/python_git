import socket
import sys
import datetime

message = '';
name = input("what is your name");
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
        ipplaceholder = get_ip();
        s = socket.socket();
        s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1);
        host=input(str("please enter host name of server"));
        port = 23;
        s.connect((host,port));
        name1 = s.recv(1024);
        name1 = name1.decode();
        name = name.encode();
        s.send(name);
        name = name.decode();
        ipplaceholder=ipplaceholder.encode();
        s.send(ipplaceholder);
        print("successfully connected to server, 1 other online:"+name1)
        c=1
    while c==1:
        incoming_message = s.recv(1024);
        incoming_message = incoming_message.decode();
        if (incoming_message == "[ACTION]:the recipient has exited the chat room!" or incoming_message == "[ACTION]:the recipient has ended the conversation!" or incoming_message == "[ACTION]:the recipient has blocked you"):
            print("at ",datetime.datetime.now(),">",name1,": ",incoming_message);
            c=0;
            s.close();
        else:
            print("at ",datetime.datetime.now(),">",name1+": ", incoming_message);
            status1 = ("read")
            status1 = status1.encode();
            s.send(status1);
            print("");
            #asdfadf
            message = input(str(">>"))
            if(message == "/block"):
                message = "[ACTION]:the recipient has blocked you";
                message = message.encode();
                bf=open("blocked.txt","a");
                bf.write(host+"\n");
                bf.close();
                s.send(message);
                print("delivered");
                c=0;
            elif(message == "/stop"):
                message = "[ACTION]:the recipient has exited the chat room!";
                message = message.encode();
                s.send(message);
                print("delivered");
                c =-1;
            elif(message == "/end"):
                message = "[ACTION]:the recipient has ended the conversation!";
                message = message.encode();
                s.send(message);
                print("delivered");
                c=0;
            else:
                message = message.encode();
                s.send(message)
                print("delivered");
                status = s.recv(1024);
                status = status.decode();
                print(status);
                print("");

