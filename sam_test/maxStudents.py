import pandas
import numpy as np
from os import listdir
from os.path import isfile,join
from math import isnan

path = "../webscraper/course_data/csv/"
filenames = [f for f in listdir(path) if isfile(join(path,f))]

buildings = {}

for f in filenames:
    df = pandas.read_csv(path+f)
    n_rows = df.shape[0]
    n_cols = df.shape[1]
    
    for row in range(2,n_rows):
        room = df.iloc[row,18].split()[0]

        if room != "TBA" and df.iloc[row,16].split()[0] != "RODP":
            # initialize matrix
            buildings[room] = [[0 for x in range(5)] for y in range(24)]

            time = []
            
            tmpTime = df.iloc[row,9]
            if tmpTime.split()[0] == "TBA":
                continue
            if tmpTime[7:9] == "pm":
                time.append(int(tmpTime[0:2]) + 12)
            else:
                time.append(int(tmpTime[0:2]))
            if tmpTime[-2]+tmpTime[-1] == "pm":
                time.append(int(tmpTime[-8:-6]) + 12)
            else:
                time.append(int(tmpTime[-8:-6]))
            # time[0] is start time, time[1] is end time

            days = df.iloc[row,8]
            for day in range(len(days)):
                if days[day] == 'M':
                    dayIndex = 0
                if days[day] == 'T':
                    dayIndex = 1
                if days[day] == 'W':
                    dayIndex = 2
                if days[day] == 'R':
                    dayIndex = 3
                if days[day] == 'F':
                    dayIndex = 4
                if not isnan(float(df.iloc[row,11])):
                    for hour in range(time[0]-1,time[1]):
                        buildings[room][hour][dayIndex] += int(df.iloc[row,11])

                if not isnan(float(df.iloc[row,14])):
                    for hour in range(time[0]-1,time[1]):
                        buildings[room][hour][dayIndex] += int(df.iloc[row,14])

TotalStudentsPerDay = []
total = 0
for day in range(5):
    for room in buildings:
        for hour in range(24):
            total += buildings[room][hour][day]
    TotalStudentsPerDay.append(total)
    total = 0


# print(TotalStudentsPerDay.index(max(TotalStudentsPerDay)))

total = 0
TotalStudentsInBuildings = []
for day in range(5):
    for hour in range(24):
        for room in buildings:
            total += buildings[room][hour][day]
        TotalStudentsInBuildings.append(total)
        total = 0

    print("Day:",day)
    print(TotalStudentsInBuildings.index(max(TotalStudentsInBuildings)))
    print(sum(TotalStudentsInBuildings))

    TotalStudentsInBuildings = []
    total = 0


# print(sum(TotalStudentsPerDay)/5)
