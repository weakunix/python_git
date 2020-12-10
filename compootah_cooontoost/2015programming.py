#declaration
digits = []

readOrWrite = {
  0 : "r",
  1 : "w",
  2 : "x"
}

specialPerms = {
  1 : [0, "s"],
  2 : [1,"s"],
  4 : [2,"t"],
}

def perms(ADigits):
  itemsToPrint = []
  for i in range(1, len(ADigits)):
    binned = str(bin(int(ADigits[i]))).replace("0b", "")

    if len(str(binned)) != 3:
      binned = binned.zfill(3) #checks for stuff like 001 or 010 to make sure they arent just 1 or 10

    print(f"{str(binned)}", end=" ")
    for indexOfLetter in range(len(str(binned))):
      if(bool(int(binned[indexOfLetter]))):
        append = readOrWrite[int(indexOfLetter)]
        if int(ADigits[0]) != 0:
          if readOrWrite[int(indexOfLetter)] == "x" and i - 1 == specialPerms[int(ADigits[0])][0]:
            append = specialPerms[int(ADigits[0])][1]

        itemsToPrint.append(append)
      else:
        itemsToPrint.append("-")
      
      if indexOfLetter == len(str(binned)) - 1:
        itemsToPrint.append(" ") #if it reaches the end add a seperator space
  
  for item in itemsToPrint:
    print(item, end=" ")

for i in range(4):
  digits.append(int(input(str(i)+"th digit:\n>>>")))

perms(digits)