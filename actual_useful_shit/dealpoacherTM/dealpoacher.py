'''
Why the poacher?
because the poacher is the best!

WHY?
-it filters out expired deals
-it filters out deals with less than -5 ratings (todo)
-ad free
-FREE & MIT (the ™ and ©  are fake)
-it is a terminal friendly experiance
-auto-logs deals to file with date name and query
-compatable with these systems!
    -Windows
    -MacOS
    -Linux
    -IOS via Pythonista
    -boomers (developed in 1958!)

Anyways if you are seeing this from your local disk:
Thank you for choosing DealPoacher, and lets save some...
BUCKS. (get it? bucks? poaching? ok Imma stop before you uninstall)
'''
from bs4 import BeautifulSoup
import requests
import os
import datetime
from data import filehandler
import math
import time
import platform
from versions import essencials

def mobileEdition():
    '''
    SHORTCUTS = [
    {'title': 'New Email', 'url': 'mailto:', 'color': '#5e96ff', 'icon': 'iow:email_24'},
    {'title': 'New Message', 'url': 'sms://', 'color': '#5ec0ff', 'icon': 'iow:chatbox_24'},
    {'title': 'Pythonista', 'url': 'pythonista3://', 'color': '#45d3e8', 'icon': 'iow:chevron_right_24'},
    {'title': 'Forum', 'url': 'http://forum.omz-software.com', 'color': '#4dd19d'},
    {'title': 'Google', 'url': 'http://google.com', 'color': '#a9de31'},
    {'title': 'DuckDuckGo', 'url': 'http://duckduckgo.com', 'color': '#ffd026' },
    {'title': 'Amazon', 'url': 'http://amazon.com', 'color': '#ff8e13'},
    {'title': 'eBay', 'url': 'http://ebay.com', 'color': '#ff4a09'},
    ]
    '''
    
    

def main():
    '''if platform.machine().startswith("iP"):
        mobileEdition()
    elif os.name() == "darwin":
        macEdition()
    elif os.name() == "posix":
        winEdition()
    else:'''
    from versions import console
    console.main()


if __name__ == '__main__':
    essencials.logo()
    time.sleep(1)
    main() #start the deal hunt!
