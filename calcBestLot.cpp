#include <fstream>
#include <string>
#include <map>
#include <iostream>

#define NUMBER_OF_BUILDINGS 30
#define NUMBER_OF_LOTS 30
#define NUMBER_OF_DAYS 5
#define NUMBER_OF_HOURS 48 
#define DAYS_COL 8
#define TIME_COL 9
#define ACT_COL 11
#define XLACT_COL 14
#define LOCATION_COL 18

using std::string;
using std::map;
using std::ifstream;
using std::ofstream;
using std::cout;
using std::endl;

struct Building{
    string name;
    int numStudents[NUMBER_OF_HOURS][NUMBER_OF_DAYS]; /* rows are in 30 min increments */
};

struct Lot{
    string name;
    int desirability = 0;
    map<string,int> distFromBuilding;
};


void readFile(string filename);

int main(){
    Building buildingList[NUMBER_OF_BUILDINGS];
    Lot lotList[NUMBER_OF_LOTS];
    string s = "./webscraper/course_data/AAS/testclass.csv";

    readFile(s);


    return 0;
}

void readFile(string filename)
/* reads CSV file and holds data in structs */
{
    
    ifstream file(filename);
    string value;
    
    for (int j = 0; j < 57; ++j){
        getline(file,value,',');
        //cout << value << endl;
    }
    getline(file,value); /* clear last one */

    int i = 0; 
    while(file.good()){
        getline(file,value,',');
        if (i == DAYS_COL || i == TIME_COL || i == ACT_COL || i == XLACT_COL || i == LOCATION_COL)
            cout << string(value) << endl;
        ++i;
        if (i > 18)
            i = 0;
    }
}
