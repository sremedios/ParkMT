# getdistance.py BY Ben Burton for 
#
#
#

def main():
    out_file = open('../data/distance_array.dat','w')
    parking_lots = get_array("../data/parkinglots.dat")
    buildings = get_array("../data/buildings.dat")
    # make header
    out_file.write(" "*15)
    for building in buildings:
        out_file.write(format(building[0],'>7'))
    out_file.write("\n")
    # write distances
    for i in range(len(parking_lots)):
        out_file.write(format(parking_lots[i][0],'15'))
        for j in range(len(buildings)):
            distance = get_distance(parking_lots[i],buildings[j])
            out_file.write(format(int(distance),'7'))
        out_file.write("\n")

# This function takes the input files and turn them in to arrays.
# Each element corresponds to one building or parking lot.
# building[i]     = ["name", x, y]
# parking_lots[i] = ["name", x, y, capacity] 
def get_array(filename):
    data_array  = []
    in_file = open(filename,"r")
    max = len(in_file.readline().split()) # sneakily read past heading line
    for line in in_file:
        data_array.append(line.split())
        for i in range(max):
            try:
                data_array[-1][i] = int(data_array[-1][i])
            except:
                pass
    in_file.close()
    return data_array

# This function will get the distance between two spots of the map.
# distance = sqrt([x1-x2]^2+[y1-y2]^2)
# Inputs should be building[i] and/or parking_lot[i]
def get_distance(place1, place2):
    x1 = place1[1]
    x2 = place2[1]
    y1 = place1[2]
    y2 = place2[2]
    return (((x1-x2)**2) + ((y1-y2))**2)**0.5






main()
