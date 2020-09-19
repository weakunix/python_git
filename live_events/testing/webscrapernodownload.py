import requests
from bs4 import BeautifulSoup
import re

parafo = BeautifulSoup(requests.get("https://randomtextgenerator.com/").content, 'html.parser').find_all("textarea", id="generatedtext")

parafoRegExed = re.sub('</textarea>]', "", str(re.sub('\[<textarea id="generatedtext">', "", str(parafo))))
#sounds like fed-ex IK lol

print(parafoRegExed)