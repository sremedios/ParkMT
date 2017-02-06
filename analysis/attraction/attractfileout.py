# attractfileout.py BY Ben Burton for ParkMT at MTHacks
#
# This program will determine the attraction value for a parking lot on
# MTSU campus based on its location, the population of nearby buildings,
# and the amount of spots in the parking spot. This version will write
# this info to the ouput folder, with a file for each building.

from math import exp

#the no no global variables
parking_lots = []
buildings = []
populations={}
dist = {} 
def main():
    # Open lot and building position data files and convert to arrays
    global parking_lots
    global buildings
    global populations
    global dist

    parking_lots= get_array("../../data/parkinglots.dat")
    buildings   = get_array("../../data/buildings.dat")
    populations = get_pop_dict("RyansDesires.txt")
    dist = get_dist_array()

    attract = get_attract_array()
    write_to_file(attract)    

#filename is building
#first line parking lot
#groups of 5 weekday at hour
def write_to_file(att):
    for b in range(len(buildings)):
        b_name = buildings[b][0]
        filename = "output/"+b_name+".txt"
        out_file = open(filename,'w')
        for p in range(len(parking_lots)):
            p_name = parking_lots[p][0]
            out_file.write(p_name+"\n")
            for t in range(24):
                for d in range(5):
                    out_file.write(format(att[d][t][b][p],'8')+"\n")

# Generate all atractions normalized
# attract[day][time][building_index][lot_index]
def get_attract_array():
    d_list = []
    for d in range(5):
        t_list = []
        for t in range(24):
            b_list = []
            for b in range(len(buildings)):
                p_list = []
                for p in range(len(parking_lots)):
                    att = attractiveness(p,b,t,d)
                    p_list.append(att)
                b_list.append(normalize(p_list))
            t_list.append(b_list)
        d_list.append(t_list)
    return d_list

# This will normalize a list so that the values  fall from 0 to 1
def normalize(alist):
    small, large = min(alist), max(alist)
    return [(x-small)/(large-small) for x in alist]

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

# Makes a dictionary from Ryans magical 1 dimensional text file.
# Access values like so:
# dict[building_name][day][hour]
def get_pop_dict(filename):
    dict1 = {}
    in_file = open(filename,"r")

    building = in_file.readline().strip()
    while building != '':
        days = [[],[],[],[],[]]
        for i in range(24):
            for j in range(5):
                popval = in_file.readline()
                days[j].append(int(popval))
        dict1[building] = days
        days = []
        building = in_file.readline().strip()

    in_file.close()
    return dict1

# This function will create an array of every distance in our data.
# acces along lines of dist[parking_index][building_index]
def get_dist_array():
    dist_array = []
    for p in parking_lots:
        dist_list = []
        for b in buildings:
            dist_list.append(get_distance(b,p))
        dist_array.append(dist_list)
    return dist_array


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

# This function will return the rating of a parking lot given a building destination and time.
# lot = parking_lots[i]
# destination = buildings[i]
def attractiveness(lot,destination,time,day):
    capacity = parking_lots[lot][2]
    attraction = distance_preference(lot,destination) * available_parking(lot, time, day) #/ capacity
    return attraction

# This function is $100% cheese.
# It gives a value that decreases as distance increases.
# domain is 0 < y < 1
def distance_preference(lot, destination):
    A = 10.0  # This is a parameter we can play with
    distance = dist[lot][destination]
    preference = 1/(A*distance/5280.0 + 1.0)
    #B = .75
    #walkfar = 5280/2
    #preference = 1/(1 + exp(B/528*(distance-walkfar))+1)
    return preference
    #return 1
# This function returns a calculated value for amount of spots available.
# Value returned can be negative. Might change and make it return 0 if negative
def available_parking(lot, time, day):
    capacity = parking_lots[lot][2]
    # sum up all that may be parked
    total_parked = 0
    for b in range(len(buildings)):
        total_parked += parked(lot, b, time, day)

    available = capacity - total_parked
    return available

# This function will predict how many people from a building will be parked in a particular lot
def parked(lot, building, time, day):
    distance = dist[lot][building]
    pop = population(building, time, day)
    # Sum up total distance of all paths from every parking lot to a building.
    total_distance = 0
    for p in range(len(parking_lots)):
        total_distance += dist[p][building]
    
    parkers = pop * (1 - distance / total_distance)
    return parkers

# This function will return the theoretical population for a given time.
# This function is probably going to cause the most error in our results.
# Access population of building on a day at a time as such:
# populations[building_name][day][hour]
def population(building, time, day):
    pop_total = attempt_pop_read(building, time, day)
#    for i in range(1,4):
#        pop_total += attempt_pop_read(building, time+i, day)/(3**i)
#        pop_total += attempt_pop_read(building, time-i, day)/(3**i)
    a_rate = 0.9  # attendence
    c_rate = 0.8  # commuters

    return pop_total * a_rate * c_rate

def attempt_pop_read(building, time, day):
    try:   # See if we have data for building
        pop = populations[building[0]][day][time]
    except:
        return 0
    return pop





main()
