#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <iomanip>

using std::ofstream;
using std::ifstream;
using std::endl;
using std::getline;
using std::string;
using std::setw;

const int LOT = 28;
const int BLD = 40;

void ReadFiles(int buildPos[BLD][2], int lotPos[LOT][3],
        string buildingCollect[BLD], string lotCollect[LOT],
        string &garbageCollect1, string &garbageCollect2);
void CalculateDistances(int buildPos[BLD][2], int lotPos[LOT][3], float
        distances[LOT][BLD]);
void WriteFile(string buildingCollect[BLD], string lotCollect[LOT],
      string garbageCollect1, string garbageCollect2, float
      distances[LOT][BLD]);

int main()
{
    string garbageCollect1,
           garbageCollect2,
           buildingCollect[BLD],
           lotCollect[LOT];
    int    buildPos[BLD][2],
           lotPos[LOT][3];
    float  distances[LOT][BLD];

    ReadFiles(buildPos, lotPos, buildingCollect, lotCollect, garbageCollect1,
              garbageCollect2);

CalculateDistances(buildPos, lotPos, distances);

    WriteFile(buildingCollect, lotCollect, garbageCollect1, garbageCollect2,
            distances);
    return 0;
}

void ReadFiles(int buildPos[BLD][2], int lotPos[LOT][3],
        string buildingCollect[BLD], string lotCollect[LOT],
        string &garbageCollect1, string &garbageCollect2)
{
    ifstream inFile1,
             inFile2;
    inFile1.open("buildings.dat");
    inFile2.open("parkinglots.dat");

    getline(inFile1, garbageCollect1);
    getline(inFile2, garbageCollect2);

    for(int i = 0; i < BLD; i++)
    {
        inFile1 >> buildingCollect[i];

        for(int j = 0; j < 2; j++)
            inFile1 >> buildPos[i][j];

    }
    for(int i = 0; i < LOT; i++)
    {
        inFile2 >> lotCollect[i];

        for(int j = 0; j < 3; j++)
            inFile2 >> lotPos[i][j];
    }

//    for(int i = 0; i < LOT; i++)
 //       std::cout << lotPos[i][0] << " " << lotPos[i][1] << " " << lotPos[i][2]
  //                << std::endl;

    return;
}

void CalculateDistances(int buildPos[BLD][2],int lotPos[LOT][3], float
        distances[LOT][BLD])
{
    int delX,
        x1,
        x2,
        y1,
        y2,
        delY,
        takeTheSquareRootOfThis;

    for(int i = 0; i < LOT; i++)
        std::cout << lotPos[i][0] << " " << lotPos[i][1] << " " << lotPos[i][2]
                  << std::endl;

    for(int i = 0; i < LOT; i++)
        for(int j = 0; j < BLD; j++)
        {
            distances[i][j] = sqrt(pow((lotPos[i][0]-buildPos[j][0]),2) +
                    pow((lotPos[i][1]-buildPos[j][1]),2));
        }

    return;
}

void WriteFile(string buildingCollect[BLD], string lotCollect[LOT],
        string garbageCollect1, string garbageCollect2, float
        distances[LOT][BLD])
{
    ofstream outFile,
             SamsDesires;
    outFile.open("buildingToLotDistance.dat");
    SamsDesires.open("SamsDesires.txt");

    outFile << std::setw(15) << " ";
    for(int i = 0; i < BLD; i++)
        outFile <<  std::setw(8) << buildingCollect[i] << " ";
    outFile << endl;
    for(int i = 0; i < LOT; i++)
    {
        outFile << std::setw(15) << std::left << lotCollect[i] << " : ";
        for(int j = 0; j < BLD; j++)
            outFile << std::setw(8) << distances[i][j] << " ";
        outFile << endl;
    }

    SamsDesires << std::left << setw(15) << "Buildings" << "Lots" << endl
                << "--------------------" << endl;
    for(int i = 0; i < LOT; i++)
        SamsDesires << std::left << setw(15) << buildingCollect[i]
                    << lotCollect[i] << endl;
    for(int i = BLD - LOT - 1; i < BLD; i++)
        SamsDesires << buildingCollect[i] << endl;

    outFile.close();
    SamsDesires.close();

    return;
}
