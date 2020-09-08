def palincheck(text, counter = 0) -> bool: #appanrently you can use counter = 0 and it won't override anything 
    if text[counter] == text[len(text) - counter - 1]:
        if counter <= len(text) / 2:
            print(True)
            return(True)
        palincheck(text, counter + 1)
    else:
        print(False)
        return False

palincheck("mootbingnibtoom")