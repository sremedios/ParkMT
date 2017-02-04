import requests
from bs4 import BeautifulSoup
from selenium import webdriver
from selenium.webdriver.common.keys import Keys

driver = webdriver.Firefox()
actual =  driver.get('https://lum4prod.mtsu.edu/cp/home/displaylogin')
url = 'https://lum4prod.mtsu.edu/cp/home/displaylogin'
Assert.assertEquals(url, actual)


driver.find_element_by_name("user").send_keys('ajf4p')
driver.find_element_by_id("pass").send_keys('AF+hw+2357')
driver.find_element_by_name("login_btn").click()

url = "https://ssb.mtsu.edu/pls/PROD/bwskfcls.p_sel_crse_search"
actual = driver.get("https://ssb.mtsu.edu/pls/PROD/bwskfcls.p_sel_crse_search")
Assert.assertEquals(url, actual) 
