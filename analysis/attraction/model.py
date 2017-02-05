# model.py BY Ben Burton for ParkMT at MTHacks
# This program will determine the attraction value for a parking lot on
# MTSU campus based on its location, the population of nearby buildings,
# and the amount of spots in the parking spot.
 
def main():
    # Open lot and building position data files and convert to arrays
    parking_lots = get_array("../../data/parkinglots.dat")
    buildings = get_array("../../data/buildings.dat")

    day, time, building = get_user_input(buildings)


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
    return (((x1-x2)(x1-x2)) + ((y1-y2)(y1-y2))**0.5

# Ask user for day, time, and building. building should be number.
def get_user_input(buildings):
    # initialize with sentinel values
    day ,time,destination= -1,-1,-1
    
    # Get day. M=0, T=1, ... , F=4
    while day == -1:
        day = input("Enter day of week (M T W R F): ")
        day = "MTWRF".find(day)
        if day ==-1:
            print("Please input M, T, W, R, or F!")
    
    # Get time
    while (time < 6) or (time > 18):
        time = input("What time do will you arrive on campus? (24hr, enter integer from 6 through 18): ")
        try:   # I hope the at least put a number in
            time = int(time)
        except: # if user is dumb
            time = -1
        if (time < 6) or (time > 18):
            print("Please input a whole number between 6 and 18!")
    
    # Ouput building list:
    for i in range(len(buildings)):
        print(format(i+1,'2'),". ",buildings[i][0],sep='')
    # Get building number. Note the user list is not zero origin index!
    while (destination<1) or (destination>len(buildings)):
        destination = input("Please select the number corresponding to your destination: ")
        try:    # I hope the at least put a number in
            destination = int(destination)
        except: # if user is dumb
            destination = -1
        if (destination<1) or (destination>len(buildings)):
            print("Please input a number from the list")
    
    return day, time, destination - 1

# This function will return the rating of a parking lot given a building destination and time.
#def attractiveness(lot,destination,time):
#    attraction = distancePreference(destination,lot) * availableParking(time,lot) / capacity(lot)
main()
