import json

myIn = open("./AlecsBane.txt",'r')

buildings_dict = {}
for x in range(53):
    building = myIn.readline().rstrip('\n')
    density_of_day = []
    for y in range(5):
        density_of_hour = []
        for z in range(24):
            density_of_hour.append(myIn.readline().rstrip('\n'))
	density_of_day.append(density_of_hour)
    buildings_dict[building] = density_of_day


myIn.close()

myIn = open("jsonStr.json", 'w')
jsonStr = json.dumps(buildings_dict)
myIn.write(jsonStr)
myIn.close()
		
