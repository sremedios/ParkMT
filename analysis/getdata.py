def main():
    parking_lots = get_array("../data/parkinglots.dat")
    buildings = get_array("../data/buildings.dat")
    print(buildings)
    print(parking_lots)

def get_array(filename):
    print(filename)
    data_array  = []
    in_file = open(filename,"r")
    max = len(in_file.readline().split())
    for line in in_file:
        data_array.append(line.split())
        for i in range(1,max):
            data_array[-1][i] = int(data_array[-1][i])
    in_file.close()
    return data_array

main()
