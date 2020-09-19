import requests
from requests_html import HTMLSession
session = HTMLSession()
r = session.get('https://randomwordgenerator.com/paragraph.php')
r.html.render() 
print(r.html.find(".support-paragraph")[0].text)

#THE BAD ONE DONT USE THIS TAKES FOREVER TO LOAD THE SITE THIS WAS JUST FOR TESTING