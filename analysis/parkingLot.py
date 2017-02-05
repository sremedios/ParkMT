import json

myIn = open("./PCS.txt",'r')

parkinglots_dict = {}
for x in range(28):
    lot = myIn.readline().rstrip()
    density_of_day = []
    for y in range(24):
        density_of_hour = []
        for z in range(5):
            density_of_hour.append(myIn.readline().rstrip())
	density_of_day.append(density_of_hour)
    parkinglots_dict.update({ lot : density_of_day})


myIn.close()

myIn = open("KOM.json", 'w')
jsonStr = json.dumps(parkinglots_dict)
myIn.write(jsonStr)
myIn.close()
		
