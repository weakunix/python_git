import datetime
from versions import essencials
from data import filehandler

def fp():
    essencials.printFirstPage()
    if input("\n\n>>>save? (Y/N)\n>>>")[0].lower() == "y":
        with open("./savedlist/deal_of_"+str(datetime.datetime.now()).replace(" ","_")+".txt", "w+") as f:
            for timedDeal in essencials.printFirstPage(True):
                f.write(timedDeal + "\n")

def main():
    if datetime.datetime.now().timestamp() - float(filehandler.yamlload("./data/settings.yaml")["LastLog"]) > 3600: #if a hour has passed then show frontpage deals
        fp()
    filehandler.yaml_it("./data/settings.yaml", "LastLog", str(datetime.datetime.now().timestamp())) #stamp now login time
    while True:
        essencials.clearScreen()
        command = input("Welcome to dealpoacher (not slickdeals ahem)\n Command list: \n type 'q' to quit\n type 'f' to display frontpage deals \n type 's item' to search all deals for item! \n>>>")
        if command[0] == "q":
            break
        elif command[0] == "f":
            fp()
        elif command[0] == "s":
            essencials.clearScreen()
            q = essencials.query(command[2:]) 
            if q != False:
                deal, link, times = q
                dealstuff = []
                item = 0
                while item < len(deal if len(deal) == len(link) == len(times) else ""):
                    if deal[item].replace(" ", "") != "" and "Expired" not in times[item]:
                        dealstuff.append("| Deal | " + deal[item] + " | " + times[item] + " | " + link[item] + " |")
                        print(dealstuff[item])
                        print("=----<=>----=")
                        item += 1
                if input("\n\n>>>save? (Y/N)\n>>>")[0].lower() == "y":
                    with open("./savedlist/deal_"+str(command[2:]).replace(" ","_")+"_"+str(datetime.datetime.now()).replace(" ","_")+".txt", "w+") as f:
                        for timedDeal in dealstuff:
                            f.write(timedDeal + "\n")
            else:
                input(f"\n We are sorry, but there doesn't seem to be any great results for '{str(command[2:])}' ... Check your spelling and capitalization. :( \n\n Enter to continue...")
    essencials.clearScreen()
    essencials.logo()
    print("Dealpoacher™ has been closed. You may now exit. \n\n THANK YOU FOR CHOOSING Dealpoacher™!\n\n ASCII art by (http://patorjk.com/software/taag/#p=display&f=Graffiti&t=DealPoacher) \n\n\n Check out other apps by Cowland Software Technologies Lab™ \n [Bingternet]()")
