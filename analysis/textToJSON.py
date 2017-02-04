import json


#building list
building_list = {'PCS', 'FAIR', 'EHS', 'ING', 'ALOF', 'ALUM', 'UP', 'HARR', 'BH',
	'JUB', 'PH', 'KOM', 'VET', 'AMG', 'SFA', 'WMB', 'JH', 'TODD', 'WPS', 
	'DSB', 'KUC', 'FH', 'BDA', 'CKNB', 'LRC', 'SCI','LIB', 'BAS', 'SAG',
	'HMA', 'TCM', 'HOB', 'TLC', 'MB', 'BRAGG','COE', 'VA', 'HC', 'GH',
	'HONR'}


Buildings = {}

for x in building_list:
	filename = './' + x + '.txt'	
	myIn = open(filename, 'r')

	#starts loop to read the entire file. 24 times for 24 hours
	hour_density = []
	for y in range(24):
		day_density = []
		line = myIn.readline()
		students = line.split()
		for student in students:
			day_density.append(student)
		hour_density.append(day_density)

	Buildings.update({ x : hour_density})
	myIn.close()

jsonStr = json.dump(Buildings)

myIn = open('jsonStr.json', 'w')
myIn.write(jsonStr)
myIn.close()



		
	
