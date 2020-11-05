'''
Refer to readme.md
'''

#imports

import os #for scanning directories
import getpass #for getting username
import shutil #move files
import yaml #if settings is changed refer to it

#files

downloadDir = f"/Users/{str(getpass.getuser())}/downloads/" #get user's downloads folder or wherever else
files = []
folders = []

for x in os.listdir(downloadDir): #for every item (directory and file) in download's direcotry
    if os.path.isfile(downloadDir + x): #saves all the files into an array
        files.append(x) 
    elif os.path.isdir(downloadDir + x):#saves all the folders into an array
        folders.append(x)

for file in files: #for every file in that directory
    ending = (file.split(".")[len(file.split(".")) - 1]).lower() 
    #get all the file types, and if it isn't already made into a folder (folders display as "foldername" and nothing else)
    #Seperates the files by dot and gets the last dot, just in case there are some ambigous words like "Chapter 3.2"
    #made into lower case so that it doesnt make a folder for .mov file named mov and .MOV file MOV (helps with
    #  duplicate folders as they are not case sensitive)
    if ending not in folders and ending != "ds_store":  #make sure it isn't ds_store and also file ending folder is not already made
        try:
            os.mkdir(downloadDir + ending.lower()) #make directory that hasn't been made yet
        except Exception as e: #if there is an error then print it
            print(e)
        finally:
           folders.append(ending.lower()) #append the folder name to array of folders made

for file in os.listdir(downloadDir):
    ending = (file.split(".")[len(file.split(".")) - 1]).lower()  #get ending of file
    try:
        shutil.move(downloadDir + file, downloadDir + ending) #try to move the file to the new destination
    except Exception as e:
        print(e) #uh oh, whoopsies!