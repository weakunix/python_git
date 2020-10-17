# ProjectChatty

This is a IP to IP and port console messenger! Designed as a last ditch effort to communicate between us two if our parents screen time our messages. (Oh yea this also works on Pythonista, Windows, and Mac (haven't tested it on Linux) )

## Is this project abandoned or is it done?

Both, the chatting service has bugs when you exit the chat that I've never fixed for ages as atleast the messages still went through. (still won't fix it, abandoned forever... sorry!)

## Dependencies

* socket
* sys
* datetime
* time
* urlib.request
* os

## How do you use it?

There are two files, host.py and nost.py, host is the guy that has the port forwarding already setup, and nost is the guy that is connecting to the host's ip adress. 

1. You will run the files using Python 3.8.5 (tested to work) 
1. The host enters their port to host the service on. 
1. Have the client enter the host's EXTERNAL IP ADRESS and their port
1. Type away!!!

**But the reality is much more complex than that. Here is some stuff you need to do before you use this:**

* Get Python 3.8.5... duh
* The host has to go to their router settings and configure the port to forward to their local device
* After every power outage to their ISP or their house they'll have to reconfigure the port (unless you turn on static, in which case, good for you)
* Beware of firewalls!

Am I talking gibberish? If so look up some articles and tutorials on how to port forward (if you have a Minecraft server hosted locally, you're already ahead of the game!)

## Test versions

**Beware, these are unstable!**

They behave the same way as regular ones do, however with some experimental features!
