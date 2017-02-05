#include <iostream>
#include <iomanip>
#include <cmath>
#include <fstream>
#include <string>

//For convenience.
using std::cout;
using std::cin;
using std::endl;
using std::ifstream;
using std::ofstream;
using std::setw;
using std::getline;
using std::string;

//Constant declarations.
const int   LOT  = 28;
const int   BLD  = 40;
const int   COL  = 2;
const float MAX  = 200000.0;

//Store parking lot info.
struct ParkingLot{
    string lotId;
    int    capacity;
};
//Store building info.
struct Building{
    string bldId;
    int    occupancy[24][5];
};

//For readability.
enum LotNames{ROSE, FAIRVIEW, BELL, INGRAMN, INGRAMS, PARKINGSERV, MAINST,
              PUBLICSAFETY, COLLEGEHEIGHTS, SPORTSPLEX, CITYVIEW, GREEKROW,
              RUTHERFORD, SOFTBALL, EZELL, MTSUBLVDG, REC, ABERNATHY, MTSU,
              HIGHLAND, MEC, BELLSTG, JACKSON, LIVESTOCK, GREENHOUSE,
              CHAMPIONWAYG, GREENLAND, MIDDLETN};

enum BldNames{PCS, FAIR, EHS, ING, ALOF, ALUM, UP, HARR, BH, JUB, PH, KOM, VET,
              AMG, SFA, WMB, JH, TODD, WPS, DSB, KUC, FH, BDA, CKNB, LRC, SCI,
              LIB, BAS, SAG, HMA, TCM, HOB, TLC, MB, BRAGG, COE, VA, HC, GH,
              HONR};

enum Weekday{MON, TUE, WED, THUR, FRI};

void   ReadFiles(ParkingLot lotArray[LOT], float distanceFromLot[LOT][BLD],
                 Building bldArray[BLD]);
/*
float  Gamma(string lotId, float distanceFromLot, float time, char day);
void   beta(float time, char day, std::string lotArray);
float  Population(float time, char day);
*/
int main()
{
    ParkingLot lotArray[LOT];
    Building   bldArray[BLD];
    float      distanceFromLot[LOT][BLD],
               time;
    char       day;
    ReadFiles(lotArray, distanceFromLot, bldArray);

   // Gamma(lotArray[].lotId, distanceFromLot[][], time, day);
   // beta(time, day, );
//    Population(time, day);
    return 0;
}

//Read parkinglots.dat file into an array of type ParkingLot.
void ReadFiles(ParkingLot lotArray[LOT], float distanceFromLot[LOT][BLD],
        Building bldArray[BLD])
{
    ifstream   inFile1,
               inFile2,
               inFile3;
    string     trashCollect;

    inFile1.open("parkinglots.dat");
    inFile2.open("buildingToLotDistance.dat");
    inFile3.open("RyansDesires.txt");

    getline(inFile1, trashCollect);
    getline(inFile2, trashCollect);

    for(int i = 0; i < LOT; i++)
    {
        inFile1 >> lotArray[i].lotId;
        for(int j = 0; j < COL; j++)
            inFile1 >> trashCollect;
        inFile1 >> lotArray[i].capacity;
    }

    for(int i = 0; i < LOT; i++)
    {
        inFile2 >> trashCollect;
        inFile2 >> trashCollect;
        for(int j = 0; j < BLD; j++)
            inFile2 >> distanceFromLot[i][j];
    }

    for(int i = 0; i < BLD; i++)
    {
        inFile3 >> bldArray[i].bldId;
        for(int j = 0; j < 24; j++)
            for(int k = MON; k <= FRI; k++)
                inFile3 >> bldArray[i].occupancy[j][k];

        cout << bldArray[i].bldId << endl << "-----------------------" << endl;
        for(int j = 0; j < 24; j++)
        {
            for(int k = MON; k <= FRI; k++)
                cout << bldArray[i].occupancy[j][k] << " ";
             cout << endl;
        }
    }

}
/*
float Gamma(string lotId, float distanceFromLot, float time, char day)
{
    float population;
    //beta(time, day, lotarray)
    if(time == 6 || time == 18)
        return MAX;
    population = ((time - 12)*(time - 12))/((time - 6)*(time - 18));

   return 0.01;
}

void beta(float time, char day, std::string lotArray)
{
    Population(time, day);
    return;
}

int Population(float time, char day, Building bldArray[BLD])
{
    int population = 0;

    if(day == 'm')
        for(int i = 0; i < BLD; i++)
            population += bldArray[i].occupancy[MON];
    else if(day == 't')
        for(int i = 0; i < BLD; i++)
            population += bldArray[i].occupancy[TUE];
    else if(day == 'w')
        for(int i = 0; i < BLD; i++)
            population += bldArray[i].occupancy[WED];
    else if(day == 'r')
        for(int i = 0; i < BLD; i++)
            population += bldArray[i].occupancy[THUR];
    else if(day == 'f')
        for(int i = 0; i < BLD; i++)
            population += bldArray[i].occupancy[FRI];

    return population;
}

*/
