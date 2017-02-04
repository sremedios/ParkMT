#include <iostream>
#include <iomanip>
#include <cmath>
#include <fstream>
#include <string>

using std::cout;
using std::cin;
using std::endl;
using std::ifstream;
using std::ofstream;
using std::setw;
using std::getline;
using std::string;

const int LOTS = 28;
const int COL  = 2;

struct ParkingLot{
    string lotId;
    int    capacity;
};

void Gamma(std::string lotId, float distanceFromLot, float time, char day);
void beta(float time, char day, std::string lotArray);
void Population(float time, char day);
int main()
{
    ParkingLot lotArray[LOTS];
    ifstream   inFile;
    string     trashCollect;

    inFile.open("parkinglots.dat");
    getline(inFile, trashCollect);

    for(int i = 0; i < LOTS; i++)
    {
        inFile >> lotArray[i].lotId;
        for(int j = 0; j < COL; j++)
            inFile >> trashCollect;
        inFile >> lotArray[i].capacity;
        cout << lotArray[i].lotId << " " << lotArray[i].capacity << endl;
    }
    //beta(time, day, lotArray);
    return 0;
}

