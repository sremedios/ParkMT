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
    int    occupancy[5];
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
float  Gamma(string lotId, float distanceFromLot, float time, char day);
void   beta(float time, char day, std::string lotArray);
float  Population(float time, char day);

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
    Population(time, day);
    return 0;
}

//Read parkinglots.dat file into an array of type ParkingLot.
void ReadFiles(ParkingLot lotArray[LOT], Building bldArray[BLD],
        float distanceFromLot[LOT][BLD])
{
    ifstream   inFile1,
               inFile2,
               inFile3,
               inFile4,
               inFile5,
               inFile6,
               inFile7,
               inFile8,
               inFile9,
               inFile10,
               inFile11,
               inFile12,
               inFile13,
               inFile14,
               inFile15,
               inFile16,
               inFile17,
               inFile18,
               inFile19,
               inFile20,
               inFile21,
               inFile22,
               inFile23,
               inFile24,
               inFile25,
               inFile26,
               inFile27,
               inFile28,
               inFile29,
               inFile30,
               inFile31,
               inFile32,
               inFile33,
               inFile34,
               inFile35,
               inFile36,
               inFile37,
               inFile38,
               inFile39,
               inFile40,
               inFile41,
               inFile42;
    string     trashCollect;

    inFile1.open("parkinglots.dat");
    inFile2.open("buildingToLotDistance.dat");
    inFile3.open("PCS.txt");
    inFile4.open("FAIR.txt");
    inFile5.open("EHS.txt");
    inFile6.open("ING.txt");
    inFile7.open("ALOF.txt");
    inFile8.open("ALUM.txt");
    inFile9.open("UP.txt");
    inFile10.open("HARR.txt");
    inFile11.open("BH.txt");
    inFile12.open("JUB.txt");
    inFile13.open("PH.txt");
    inFile14.open("KOM.txt");
    inFile15.open("VET.txt");
    inFile16.open("AMG.txt");
    inFile17.open("SFA.txt");
    inFile18.open("WMB.txt");
    inFile19.open("JH.txt");
    inFile20.open("TODD.txt");
    inFile21.open("WPS.txt");
    inFile22.open("DSB.txt");
    inFile23.open("KUC.txt");
    inFile24.open("FH.txt");
    inFile25.open("BDA.txt");
    inFile26.open("CKNB.txt");
    inFile27.open("LRC.txt");
    inFile28.open("SCI.txt");
    inFile29.open("LIB.txt");
    inFile30.open("BAS.txt");
    inFile31.open("SAG.txt");
    inFile32.open("HMA.txt");
    inFile33.open("TCM.txt");
    inFile34.open("HOB.txt");
    inFile35.open("TLC.txt");
    inFile36.open("MB.txt");
    inFile37.open("BRAGG.txt");
    inFile38.open("COE.txt");
    inFile39.open("VA.txt");
    inFile40.open("HC.txt");
    inFile41.open("GH.txt");
    inFile42.open("HONR.txt");

    getline(inFile1, trashCollect);
    getline(inFile2, trashCollect);
    getline(inFile3, trashCollect);

    for(int i = 0; i < LOT; i++)
    {
        inFile1 >> lotArray[i].lotId;
        for(int j = 0; j < COL; j++)
            inFile1 >> trashCollect;
        inFile1 >> lotArray[i].capacity;
//        cout << lotArray[i].lotId << " " << lotArray[i].capacity << endl;
    }

    for(int i = 0; i < LOT; i++)
    {
        inFile2 >> trashCollect;
        inFile2 >> trashCollect;
        for(int j = 0; j < BLD; j++)
        {
            inFile2 >> distanceFromLot[i][j];
            //cout << distanceFromLot[i][j] << " ";
        }
        //cout << endl;
    }

    for(int i = 0; i < BLD; i++)
    {
        inFile2 >> bldArray[i].bldId;
        cout << bldArray[i].bldId << endl;
    }
    return;
}

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
