#include <fstream>
#include <iostream>
#include <string>

#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

using namespace std;

int main(){
    ifstream fin;
    string dir, filepath;
    int num;
    DIR *dp;
    struct dirent *dirp;
    struct stat filestat;

    dir = "../webscraper/course_data/csv/";

    dp = opendir(dir.c_str());

    if (dp == NULL){
        cout << "Error(" << errno << ") opening " << dir << endl;
        return errno;
    }

    while ((dirp = readdir(dp))){
        cout << dirp->d_name << ' ';

    }

    closedir(dp);
    return 0;
}
