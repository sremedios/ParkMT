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


void readFile(string filename, Building*);
void manageReadData(int selection, string value, Building* buildingList);
void storeProperDays(string value, Building*  buildingList);

int main(){
    Building *buildingList = new Building[NUMBER_OF_BUILDINGS];
    Lot lotList[NUMBER_OF_LOTS];
    string s = "./webscraper/course_data/AAS/testclass.csv";

    readFile(s, buildingList);

    delete[] buildingList;
    return 0;
}

void readFile(string filename, Building* buildingList)
/* reads CSV file and holds data in structs */
{
    ifstream file(filename);
    string value;

    for (int i = 0; i < 57; i++){
        getline(file,value,',');
        //cout << value << endl;
    }
    getline(file,value); /* clear last one */

    for(int i = 0; file.good(); i++){
        getline(file,value,',');
        manageReadData(i, value, buildingList);
        if (i > 18)
            i = 0;
    }
}

void manageReadData(int selection, string value, Building* buildingList)
/* */
{
  switch(selection){
    case DAYS_COL: //if current read data is the days of the week this class meets
      storeProperDays(value, buildingList);
      break;
    case TIME_COL: //the time slot this class meets
      cout << string(value) << endl;
      break;
    case ACT_COL: //number of students registered for the class
      cout << string(value) << endl;
      break;
    case XLACT_COL:
      cout << string(value) << endl;
      break;
    case LOCATION_COL:
      cout << string(value) << endl;
      break;
    default:
      break;
  }
}


void storeProperDays(string value, Building*  buildingList)
/*Data given is the days of the week */
{
  for(int curDay = 0; curDay < value.length(); curDay++){
    switch (value[curDay]){
      case 'M':
        cout << "hey" << endl;
        break;
      case 'T':
        cout << "hey" << endl;
        break;
      case 'W':
        cout << "hey" << endl;
        break;
      case 'R':
        cout << "hey" << endl;
        break;
      case 'F':
        cout << "hey" << endl;
        break;
      default:
        cout << "idk" << endl;
        break;
    }
  }
}
