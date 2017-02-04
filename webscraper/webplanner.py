import requests
from bs4 import BeautifulSoup

url = "http://ssb.mtsu.edu/pls/PROD/bwskfcls.p_sel_crse_search"
r = requests.get(url)
soup = BeautifulSoup(r.content)

print soup.prettify()
