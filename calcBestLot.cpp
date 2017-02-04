#include <fstream>
#include <string>
#include <map>
#include <iostream>

#define NUMBER_OF_BUILDINGS 40
#define NUMBER_OF_LOTS 28
#define NUMBER_OF_DAYS 5
#define NUMBER_OF_HOURS 24
#define DAYS_COL 8
#define TIME_COL 9
#define ACT_COL 11
#define XLACT_COL 14
#define INSTRUCTOR_COL 16
#define LOCATION_COL 18

using std::string;
using std::map;
using std::ifstream;
using std::ofstream;
using std::cout;
using std::endl;

struct Building{
    string name;
    int numStudents[NUMBER_OF_HOURS][NUMBER_OF_DAYS] = { 0 }; /* rows are in 30 min increments */
};

struct Lot{
    string name;
    int desirability = 0;
    map<string,int> distFromBuilding;
};


void readFile(ifstream& file, Building* buildingList);
bool neededData(int selection);
void storeStudentCount(ifstream& file, string value, Building* buildingList, int selection);
void updateBuildingList(Building* buildingList, int curBuilding, int row, int col, int lowerBound, int upperBound, int stuCount);
void writeOutput(Building *buildingList);

int main(){
    Building *buildingList = new Building[NUMBER_OF_BUILDINGS];
    for(int i = 0; i < NUMBER_OF_BUILDINGS; i++) buildingList[i].name = "";
    Lot lotList[NUMBER_OF_LOTS];
    string s = "./webscraper/course_data/csv/AAS.csv";
    ifstream file(s);
    readFile(file, buildingList);
    file.close();
    writeOutput(buildingList);
    buildingList = NULL;
    delete[] buildingList;
    return 0;
}

void writeOutput(Building *buildingList){
  for(int i = 0; i < NUMBER_OF_BUILDINGS; i++){
    ofstream curBuildingOutput("./data/buildingFrequency/" + buildingList[i].name + ".txt");
    for(int j = 0; j < NUMBER_OF_HOURS; j++){
      for(int k = 0; k < NUMBER_OF_DAYS; k++)
        curBuildingOutput << buildingList[i].numStudents[j][k] << " ";
      cout << endl;
    }
    curBuildingOutput.close();
  }
}

void readFile(ifstream& file, Building* buildingList)
/* reads CSV file and holds data in structs */
{
    string value;
    //reading through explanatory first two rows
    for (int i = 0; i < 57; i++) getline(file,value,',');
    getline(file,value); /* clear last one */

    for(int i = 0; file.good(); i++){
        getline(file,value,',');
        if(neededData(i)) {
          storeStudentCount(file, value, buildingList, i);
          i = 0;
        }

    }
}

bool neededData(int selection)
{
  if(selection == DAYS_COL || selection == TIME_COL || selection == ACT_COL ||
    selection == XLACT_COL || selection == INSTRUCTOR_COL || selection == LOCATION_COL)
     return true;
  return false;
}


void storeStudentCount(ifstream& file, string value, Building*  buildingList, int selection)
/*Data given is the days of the week */
{
  string daysOfWeek = value, start_endTime, instructor, classLoc, buildingName;
  bool nightTime;
  int studentCount = 0, lowerBound, upperBound, curBuilding = 0;
  for(int itemsAdded = 0; selection < 18; selection++){
    getline(file,value,',');
    if(neededData(selection)){
      switch(itemsAdded){
        case 0:
          start_endTime = value;
          break;
        case 1:
          studentCount += atoi(value.c_str());
          break;
        case 2:
          studentCount += atoi(value.c_str());
          break;
        case 3:
          instructor = value;
          break;
        case 4:
          classLoc = value;
          break;
      }
      itemsAdded++;
    }
  }
  if(instructor[0] == 'R' && instructor[1] == 'O' && instructor[2] == 'D' &&
      instructor[3] == 'P') return;

  buildingName[0] = start_endTime[0];
  buildingName[1] = start_endTime[1];
  lowerBound = atoi(buildingName.c_str());
  nightTime = (start_endTime[6] == 'A') ? false : true;
  buildingName[0] = start_endTime[9];
  buildingName[1] = start_endTime[10];
  int hour = (nightTime) ? lowerBound + 12: lowerBound;
  upperBound = atoi(buildingName.c_str()) + 1;
  for(int i = 0; classLoc[i] != ' '; i++) buildingName[i] = classLoc[i];
  while(buildingList[curBuilding].name != buildingName && buildingList[curBuilding].name != ""
        && curBuilding < NUMBER_OF_BUILDINGS) curBuilding++;
  buildingList[curBuilding].name = buildingName;
  for(int curDay = 0; curDay < daysOfWeek.length(); curDay++){
    cout << "hey" << endl;
    switch (daysOfWeek[curDay]){
      case 'M': // col 0
        updateBuildingList(buildingList, curBuilding, hour, 0, lowerBound, upperBound, studentCount);
        break;
      case 'T': // col 1
        updateBuildingList(buildingList, curBuilding, hour, 1, lowerBound, upperBound, studentCount);
        break;
      case 'W': // col 2
        updateBuildingList(buildingList, curBuilding, hour, 2, lowerBound, upperBound, studentCount);
        break;
      case 'R': // col 3
        updateBuildingList(buildingList, curBuilding, hour, 3, lowerBound, upperBound, studentCount);
        break;
      case 'F': // col 4
        updateBuildingList(buildingList, curBuilding, hour, 4, lowerBound, upperBound, studentCount);
        break;
      default:
        return;
    }
  }
  cout << "hey3" << endl;
}

void updateBuildingList(Building* buildingList, int curBuilding, int hour, int day, int lowerBound, int upperBound, int stuCount){
  int timesToUpdate;
  cout << "hey2" << endl;
  buildingList[curBuilding].numStudents[hour][day] = stuCount;
  if(upperBound < lowerBound) timesToUpdate = 12 - lowerBound + upperBound;
  else timesToUpdate = upperBound - lowerBound;
  for(int i = 0; i <= timesToUpdate; i++) buildingList[curBuilding].numStudents[hour][day] = stuCount;
}
