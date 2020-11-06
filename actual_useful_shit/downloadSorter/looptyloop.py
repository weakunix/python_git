import os #for scanning directory
import time #for time.sleep
import sorter #for the actual stuff 
import yaml #to read settings
import getpass #to get user name
import datetime #to log when you scanned
import threading

#files
with open("./settings.yaml", 'r') as f:
    settings = yaml.load(f, Loader=yaml.Loader)

if settings["defaultPathLoop"] != []:
    downloadDir = settings["defaultPathLoop"] #oh well, I guess if you are THAT disorganized and THAT lazy
else:
    downloadDir = f"/Users/{str(getpass.getuser())}/downloads/" #get user's downloads folder or wherever else

if settings["scanTime"] != "":
    scanTime = settings["scanTime"] #
else:
    scanTime = 30

def mainLoop(downloadDirs):
    print(f"\n\n\nScanner set for '{downloadDirs}', it will periodicly check for updates every '{scanTime}' seconds and automatically move the new files accordingly to its appropriate folders! \n You may now minimize this app and let it run in the background")
    while True:
        directoryListener = os.listdir(downloadDirs)
        time.sleep(scanTime)
        changes = 0
        errors = []
        if directoryListener != os.listdir(downloadDirs):
            try:
                changes = sorter.main(downloadDirs, False)
                raise Exception("SHIT YOU!!!!")
            except Exception as e:
                errors.append(e)
        
        print(f"Scan at {datetime.datetime.now()} in '{downloadDirs}', recieved {changes} changes.")
        for e in errors:
            print(f"Uh oh an error!, here's the log: {e}")

if type(downloadDir) == str:
    mainLoop(downloadDir)
else:
    for x in downloadDir:
        t = threading.Thread(target = lambda : [mainLoop(x)])
        t.start()
