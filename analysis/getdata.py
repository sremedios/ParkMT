def main():
    buildings = getarray("../data/parkinglots.dat")
    buildings = getarray("../data/buildings.dat")
    print(buildings)


def getarray(filename):
    print(filename)
    data_array  = []
    in_file = open(filename,"r")
    max = len(in_file.readline().split())
    print(max)
    for line in in_file:
        data_array.append(line.split())
        for i in range(1,len(line)):
            data_array[-1][i] = int(data_array[-1][i])
    in_file.close()
    return array

main()
