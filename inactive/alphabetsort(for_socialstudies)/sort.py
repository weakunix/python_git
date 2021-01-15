import re

with open("file.txt", "r", encoding="utf8") as f:
    FileContents = f.readlines()
    NewLinesv1 = []
    for line in FileContents:
        NewLinesv1.append(re.sub("\d.*\.", "", line).lstrip().capitalize())
    NewLinesv2 = []
    for line in NewLinesv1:
        try:
            if(line != "" and line != " " and line != "\n"):
                NewLinesv2.append(line.strip() + "\n")             
        except:
            pass

with open("output.txt", "w+",  encoding="utf8") as w:
    w.write("".join(sorted(NewLinesv2)))