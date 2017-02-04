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
const int LOT = 28;
const int BLD  = 40;
const int COL  = 2;

//Store parking lot info.
struct ParkingLot{
    string lotId;
    int    capacity;
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

void ReadFiles(ParkingLot lotArray[LOT], float distanceFromLot[LOT][BLD]);
void Gamma(string lotId, float distanceFromLot, float time, char day);
void beta(float time, char day, std::string lotArray);
void Population(float time, char day);

int main()
{
    ParkingLot lotArray[LOT];
    float      distanceFromLot[LOT][BLD];
    ReadFiles(lotArray, distanceFromLot);

   // Gamma(lotArray[].lotId, distanceFromLot[][], time, day);
   // beta(time, day, );
   // Population();
    return 0;
}

//Read parkinglots.dat file into an array of type ParkingLot.
void ReadFiles(ParkingLot lotArray[LOT], float distanceFromLot[LOT][BLD])
{
    ifstream   inFile1,
               inFile2;
    string     trashCollect;

    inFile1.open("parkinglots.dat");
    inFile2.open("buildingToLotDistance.dat");
    getline(inFile1, trashCollect);
    getline(inFile2, trashCollect);

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
    return;
}

void Gamma(string lotId, float distanceFromLot, float time, char day)
{
    //beta(time, day, lotarray)

    return;
}
