# model.py BY Ben Burton for ParkMT at MTHacks
# This program will determine the attraction value for a parking lot on
# MTSU campus based on its location, the population of nearby buildings,
# and the amount of spots in the parking spot.

import operator

#the no no variables
parking_lots = []
buildings = []
 
def main():
    # Open lot and building position data files and convert to arrays
    global parking_lots
    global buildings

    parking_lots=get_array("../../data/parkinglots.dat")
    buildings =  get_array("../../data/buildings.dat")

#    day, time, destination = get_user_input()
    day, time, destination = 1, 15, 10

    # get attractiveness of each lot based on input
    attractions = {}
    for lot in parking_lots:
        building_name = lot[0]
        attractions[building_name] = attractiveness(lot, buildings[destination], time, day)

    # sort by attraction
    sorted_attractions = sorted(attractions.items(), key=lambda kv: kv[1], reverse=True)
#    print(sorted_attractions)

    # ouput building ranked by attraction
    weekday = "MTWRF"
    print("On",weekday[day],"at",time,"going to",buildings[destination][0],"these lots have these attractions:")
    for i in range(len(sorted_attractions)):
        print(format(i,'2'),format(sorted_attractions[i][0],'15'),sorted_attractions[i][1])

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
    distance = ((x1-x2)**2 + (y1-y2)**2)**0.5
    return distance

# Ask user for day, time, and building. building should be number.
def get_user_input():
    # initialize with sentinel values
    day, time, destination= -1, -1, -1
    
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
    # Get building number. Note that the user list is not zero origin index!
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
# lot = parking_lots[i]
# destination = buildings[i]
def attractiveness(lot,destination,time,day):
    capacity = lot[2]
    attraction = distance_preference(lot,destination) * available_parking(lot, time, day) / capacity
    return attraction

# This function is $100% cheese.
# It gives a value that decreases as distance increases.
# domain is 0 < y < 1
def distance_preference(lot, destination):
    A = 4.0  # This is a parameter we can play with
    distance = get_distance(lot, destination)
    preference = 1/(A*distance/5280.0 + 1.0)
    return preference

# This function returns a calculated value for amount of spots available.
# Value returned can be negative. Might change and make it return 0 if negative
def available_parking(lot, time, day):
    capacity = lot[2]
    # sum up all that may be parked
    total_parked = 0
    for building in buildings:
        total_parked += parked(lot, building, time, day)

    available = capacity - total_parked
    return available

# This function will predict how many people from a building will be parked in a particular lot
def parked(lot, building, time, day):
    distance = get_distance(lot, building)
    pop = population(building, time, day)
    # Sum up total distance of all paths from every parking lot to a building.
    total_distance = 0
    for lot in parking_lots:
        total_distance += get_distance(lot, building)
    
    parkers = pop * distance / total_distance
    return parkers

# This function will return the theoretical population for a given time.
# This function is probably going to cause the most error in our results.
def population(building, time, day):
    return 500







main()
