'''
Refer to readme.md
'''

#imports

import os #for scanning directories
import getpass #for getting username
import shutil #move files
import yaml #if settings is changed refer to it
import math #to calculate percentage of movements

#files
def main(downloadDir, printAll):
    #array to store the files and folders
    files = []
    folders = []

    for x in os.listdir(downloadDir): #for every item (directory and file) in download's direcotry
        if printAll:
            print(x)
        if os.path.isfile(downloadDir + x): #saves all the files into an array
            files.append(x) 
        elif os.path.isdir(downloadDir + x):#saves all the folders into an array
            folders.append(x)

    if printAll:
        print("\nFiles\n")

    for file in files: #for every file in that directory
        ending = (file.split(".")[len(file.split(".")) - 1]).lower() 
        #get all the file types, and if it isn't already made into a folder (folders display as "foldername" and nothing else)
        #Seperates the files by dot and gets the last dot, just in case there are some ambigous words like "Chapter 3.2"
        #made into lower case so that it doesnt make a folder for .mov file named mov and .MOV file MOV (helps with
        #  duplicate folders as they are not case sensitive)
        if printAll:
            print(file + " ending " + ending)
        if ending not in folders and ending != "ds_store":  #make sure it isn't ds_store and also file ending folder is not already made
            try:
                os.mkdir(downloadDir + ending.lower()) #make directory that hasn't been made yet
            except Exception as e: #if there is an error then print it
                print(e)
            finally:
                folders.append(ending.lower()) #append the folder name to array of folders made

    percent = 0 #used to calculate done percent
    totals = len(os.listdir(downloadDir)) #how many files/folders in current dir
    print("\nMovement progress\n") #print to screen

    for file in os.listdir(downloadDir):
        ending = (file.split(".")[len(file.split(".")) - 1]).lower()  #get ending of file
        if file not in folders:
            try:
                shutil.move(downloadDir + file, downloadDir + ending) #try to move the file to the new destination
                percent += 1
                print(f"{file} moved to {downloadDir + ending} percent left {(totals - len(folders)) - percent} files left ({math.ceil(((percent / (totals - len(folders)))) * 100)}%)")
                #print to screen the percent of completion and what got moved where and how many files left in the operation
            except Exception as e:
                print(e) #uh oh, whoopsies!

    return totals - len(folders)

if __name__ == '__main__':

    with open("./settings.yaml", 'r') as f:
        settings = yaml.load(f, Loader=yaml.Loader)

    if settings["defaultPath"] != "":
        downloadDir = settings["defaultPath"] #oh well, I guess if you are THAT disorganized and THAT lazy
    else:
        downloadDir = f"/Users/{str(getpass.getuser())}/downloads/" #get user's downloads folder or wherever else

    printAll = settings["printsProcess"] #do you really want to see everything?

    print("directory: " + downloadDir)

    main(downloadDir, printAll)
    
    print("\n Done! \n")