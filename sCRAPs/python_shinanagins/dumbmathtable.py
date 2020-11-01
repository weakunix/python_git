try:
    a = int(input("number top row \n"))
    print(((a - 2) * 180) / a)
    print(360 / a)
except:
    try:
        a = int(input("number mid row \n"))
        print((360 / a))
        print((((360 / a) - 2) * 180) / (360 / a))
    except:
        a = int(input("number bottom row \n"))
        print(360 / (180 - a))
        print(180 - a)
