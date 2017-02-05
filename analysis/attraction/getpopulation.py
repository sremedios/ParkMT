# getdistance.py BY Ben Burton for 
#
#
#

def main():
    out_file = open('../../data/population.dat','w')
    in_name  = 'RyansDesires.txt'
    
    pop_dict = get_pop_dict(in_name)
    keys = sorted(pop_dict.items(), key=lambda kv: kv[0], reverse=False)
    for key in keys:
        key = key[0]
        print(key)
        days = pop_dict[key]
        out_file.write(key+"\n")
        for i in range(5):
            for j in range(24):
                out_file.write(format(days[i][j], '5'))
            out_file.write("\n")





    out_file.close()
   
    
# This function takes the input files and turn them in to arrays.
# Each element corresponds to one building or parking lot.
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






main()
