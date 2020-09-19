import requests
from bs4 import BeautifulSoup
import re

'''
Thanks to:
https://randomtextgenerator.com/ 
for the paragraphs generated!
'''

parafoRegExed = re.sub('</textarea>]', "", str(re.sub('\[<textarea id="generatedtext">', "", str(BeautifulSoup(requests.get("https://randomtextgenerator.com/").content, 'html.parser').find_all("textarea", id="generatedtext")))))
#sounds like fed-ex IK lol

print(parafoRegExed)