import mobileWidget
import json
import essencials
import re
import html
from bs4 import BeautifulSoup
import io

def main():
    deal, link, cost = essencials.frontpage()
    SHORTCUTS = [{"title":"Search for deals","url":"pythonista3://","color": "#5e96ff"}]
    for item in range(len(deal) if len(deal) == len(link) == len(cost) else len("")):
        if deal[item] != "" and link[item] != "":
            deal[item] = str(BeautifulSoup(deal[item]))
            deal[item] = re.sub("<.*>", "", deal[item])
            SHORTCUTS.append({"title": (str(cost[item]) + "" + str(deal[item])), "url": str((link[item])), "color": "#5e96ff"})
    print(str(SHORTCUTS))
    with open("mobilestored.txt","w+") as f:
        f.write()
        mobileWidget.main()

if __name__ == "__main__":
    main()
