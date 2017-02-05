from bs4 import BeautifulSoup
import csv


f = open('/home/hammy/python/ParkMT/webscraper/course_data/AAS/classes.html', 'r')


soup = BeautifulSoup(f)


list_of_data = []
table = soup.findAll('td')
length = len(table)
count = 1
list_of_cells = []
for row in table:
	if count == 18:
		list_of_data.append(list_of_cells)
		count = 1
		list_of_cells = []
	list_of_cells.append(row.text)

outfile = open("./classlist.csv", "wb")
writer = csv.writer(outfile)
writer.writerows(list_of_data)	
		

	
