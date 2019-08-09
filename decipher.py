alpha="abcdefghijklmnopqrstuvwxyz"
current=""
digit=-1
coded=input("What is the message?\n")
cipher=input("What is the cipher?\n")
decoded=""
 
for i in range(len(coded)):
    digit+=1
    current=cipher[digit]
    digit+=1
    current+=cipher[digit]
    current=int(current)
    new=coded[i]
    if new==" ":
        decoded+=" "
    else:
        new=int(alpha.find(new))
        new-=current
        new=new%26
        new=alpha[new]
        decoded+=new
print(decoded)
