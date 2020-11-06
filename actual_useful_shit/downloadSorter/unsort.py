#idk why but maybe for testing???

#imports

import os #for scanning directories
import getpass #for getting username
import shutil #move files
import yaml #if settings is changed refer to it
import math #to calculate percentage of movements

with open("./settings.yaml", 'r') as f:
    settings = yaml.load(f, Loader=yaml.Loader)

if settings["defaultPath"] != "":
    downloadDir = settings["defaultPath"] #oh well, I guess if you are THAT disorganized and THAT lazy
else:
    downloadDir = f"/Users/{str(getpass.getuser())}/downloads/" #get user's downloads folder or wherever else to get rid of everything from

printAll = settings["printsProcess"] #do you really want to see everything?

print("directory: " + downloadDir)

if printAll:
    print("Unfolding folders\n")

folders = []

for x in os.listdir(downloadDir): #for every item (directory and file) in download's direcotry
    if printAll:
        print(x)
    elif os.path.isdir(downloadDir + x):#saves all the folders into an array
        folders.append(x)

totals = 0
percent = 0

for folder in folders:
    for file in os.listdir(downloadDir + folder):
        totals += 1

for folder in folders:
    for file in os.listdir(downloadDir + folder):
        try:
            shutil.move(downloadDir + folder + "/" + file, downloadDir) #try to move the file to the new destination
            percent += 1
            print(f"{file} in {folder} moved to {downloadDir} percent left {totals - percent} files left ({math.ceil(percent / (totals) * 100)}%)")
            #print to screen the percent of completion and what got moved where and how many files left in the operation
        except Exception as e:
            print(e) #uh oh, whoopsies!

print("Done!")
