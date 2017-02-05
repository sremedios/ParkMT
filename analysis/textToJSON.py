import json


#building list
building_list = {'PCS', 'FAIR', 'EHS', 'ING', 'ALOF', 'ALUM', 'UP', 'HARR',
    'BH','JUB', 'PH', 'KOM', 'VET', 'AMG', 'SFA', 'WMB', 'JH', 'TODD', 'WPS', 
    'DSB', 'KUC', 'FH', 'BDA', 'CKNB', 'LRC', 'SCI','LIB', 'BAS', 'SAG',
    'HMA', 'TCM', 'HOB', 'TLC', 'MB', 'BRAGG','COE', 'VA', 'HC', 'GH',
    'HONR'}

for x in building_list:
    filename = './' + x + '.txt'	
    myIn = open(filename, 'r')

    Buildings = {}
	
    for z in range(28):
	#starts loop to read the entire file. 24 times for 24 hours
        hour_density = []
	lot = myIn.readline().rstrip()
	for y in range(24):
	    day_density = []
	    for x in range(5)
	        day_density.append(myIn.readline().rstrip())
	    hour_density.append(day_density)

    Buildings.update({ lot : hour_density})
    myIn.close()
    jsonStr = json.dumps(Buildings)
    name = x + '.json'
    myIn = open(name, 'w')
    myIn.write(jsonStr)
    myIn.close()



		
	
