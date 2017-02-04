def main():
        infile1 = open('buildings.dat','r')
        infile2 = open('parkinglots.dat','r')

        outfile1 = open('buildingToLotDistance.dat','w')
        buildPos = BuildingPositions()
        lotPos = LotPositions()
        distances[[]] = Distances(buildPos,lotPos)

main()


def BuildingPositions():
    
    #initialize an array for the building positions
    #first index is building (determined alphabetically, ranges from 0-29)
    #second index holds x and y values (ranges from 0-1)
    buildPos =  [[]]

    #scan building location data and put the data in an array
    for i in range(0,30):
            str1 = infile.read()
            for j in range(0,2):
                buildPos[i][j] = int(infile.read())
            int1 = int(infile.read())
                
    return buildPos

def LotPositions():
    #initializes an array for the parking lot positions
    #first index is parking lots (determined alphabetically, ranges from 0-29)
    #second index is x,y coordinates (ranges from 0-1)
    lotPos = [[]]
        
    #scan parking lot location data and put the data in an array
    for i in range(0,30):
        str1 = infile2.read()
        for j in range(0,2):
            lotPos[i][j] = int(infile.read())
    
    return lotPos

def Distances(buildPos,lotPos):
    #create an array to store the distances between each parking lot and each building
    #first index indicates the parking lot
    #second index indicates the building
    distances = [[]]

    #for loop that adds the distances between each parking lot and each building
    for i in range(0,30):
        for j in range(0,30):
            distances[i][j] = ((((buildPos[i][0]-lotPos[j][0]) ** 2)+(buildPos[i][1] - lotPos[j[1]] ** 2)) ** 0.5)

    return distances
