def BuildingPositions(infile1):
    
    #initialize an array for the building positions
    #first index is building (determined alphabetically, ranges from 0-29)
    #second index holds x and y values (ranges from 0-1)
    buildPos =  [[]]

    #scan building location data and put the data in an array
    for i in range(0,30):
            str1 = infile1.read()
            for j in range(0,2):
                buildPos[i][j] = int(infile1.read())
            int1 = int(infile1.read())
                
    return buildPos

def LotPositions(infile2):
    #initializes an array for the parking lot positions
    #first index is parking lots (determined alphabetically, ranges from 0-29)
    #second index is x,y coordinates (ranges from 0-1)
    lotPos = [[]]
        
    #scan parking lot location data and put the data in an array
    for i in range(0,30):
        str1 = infile2.read()
        for j in range(0,2):
            lotPos[i][j] = int(infile2.read())
    
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


def main():
        infile1 = open('buildings.dat.txt','r')
        infile2 = open('parkinglots.dat.txt','r')

        outfile1 = open('buildingToLotDistance.dat','w')
        buildPos = BuildingPositions(infile1)
        lotPos = LotPositions(infile2)
        distances[[]] = Distances(buildPos,lotPos)
main()
