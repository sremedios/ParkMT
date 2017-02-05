#include <fstream>
#include <string>
#include <map>
#include <vector>
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
using std::vector;

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
    
    for(int i = 0; i < NUMBER_OF_BUILDINGS; i++) 
        buildingList[i].name = "";
   
    /* open list of all courses */
    string path = "./data/courses.txt";
    string prefix;
    vector<string> courseList;
    ifstream file(path);
   
    /* hold all courses in courseList */ 
    while(file.good()){
        getline(file,prefix,' ');
        if (prefix == "." || prefix == "..")
            continue;
        courseList.push_back(prefix);
    }

    /* execute for each file */
    path = "./webscraper/course_data/csv/";

    for (int i = 0; i < courseList.size(); i++){
        file.open(path + courseList[i]);
        
        readFile(file, buildingList);

        file.close();
        writeOutput(buildingList);
    }

    buildingList = NULL;
    delete[] buildingList;
    return 0;
}

void writeOutput(Building *buildingList){
  cout << "started writeOutput\n";
  for(int i = 0; i < NUMBER_OF_BUILDINGS; i++){
    ofstream curBuildingOutput("./data/buildingFrequency/" + buildingList[i].name + ".txt");
    for(int j = 0; j < NUMBER_OF_HOURS; j++){
      for(int k = 0; k < NUMBER_OF_DAYS; k++)
        curBuildingOutput << buildingList[i].numStudents[j][k] << " ";
    }
    curBuildingOutput.close();
  }
}

void readFile(ifstream& file, Building* buildingList)
/* reads CSV file and holds data in structs */
{
    cout << "started readFile\n";
    string value;
    //reading through explanatory first two rows
    //aka: trash garbage rows
    for (int i = 0; i < 57; i++) 
        getline(file,value,',');
    
    getline(file,value); /* clear last one */

    /* iterate through columns */
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
  cout << "started neededData\n";
  cout << "selection: " << selection << endl;
  if(selection == DAYS_COL || selection == TIME_COL || selection == ACT_COL ||
    selection == XLACT_COL || selection == INSTRUCTOR_COL || selection == LOCATION_COL)
  {

     cout << "exit neededData\n";
     return true;
  }
  return false;
}


void storeStudentCount(ifstream& file, string value, Building*  buildingList, int selection)
/*Data given is the days of the week */
{
  cout << "started storeStudentCount\n";
  string daysOfWeek = value, start_endTime, instructor, classLoc, buildingName, timeCompact;
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
  /* do not track online courses */
  if(instructor[0] == 'R' && instructor[1] == 'O' && instructor[2] == 'D' &&
      instructor[3] == 'P') return;

  timeCompact += start_endTime[0];
  timeCompact += start_endTime[1];
  
  timeCompact += start_endTime[9];
  timeCompact += start_endTime[10];
  
  lowerBound = atoi(timeCompact.c_str());
  nightTime = (start_endTime[6] == 'A') ? false : true;

  int hour = (nightTime) ? lowerBound + 12: lowerBound;
  upperBound = atoi(timeCompact.c_str()) + 1;
  
  for(int i = 0; classLoc[i] != ' '; i++) 
      buildingName += classLoc[i];
  
  while(buildingList[curBuilding].name != buildingName && buildingList[curBuilding].name != ""
        && curBuilding < NUMBER_OF_BUILDINGS) 
      curBuilding++;
  
  buildingList[curBuilding].name = buildingName;
  
  for(int curDay = 0; curDay < daysOfWeek.length(); curDay++){
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
}

void updateBuildingList(Building* buildingList, int curBuilding, int hour, int day, int lowerBound, int upperBound, int stuCount){
  cout << "started updateBuildingList\n";
  int timesToUpdate;
  buildingList[curBuilding].numStudents[hour][day] = stuCount;
  if(upperBound < lowerBound) 
      timesToUpdate = 12 - lowerBound + upperBound;
  else 
      timesToUpdate = upperBound - lowerBound;
  for(int i = 0; i <= timesToUpdate; i++){
      
      if (curBuilding < NUMBER_OF_BUILDINGS && hour < NUMBER_OF_HOURS && day < NUMBER_OF_DAYS)
        buildingList[curBuilding].numStudents[hour][day] = stuCount;

  }
}
