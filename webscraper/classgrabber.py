from urllib.request import urlopen
from time import sleep
classKeysFile = "classkeys.txt"
baseURL = "http://sched.mtsu.edu/api/index.php/classes/201710/"
finalURL = ""


lines = [line.rstrip('\n') for line in open(classKeysFile)]
outData = open('classes.txt', 'w')



for classKey in lines:
    finalURL = baseURL+classKey
    html = urlopen(finalURL)
    sleep(0.1)
    print(str(html.read(),"utf-8"))
    outData.write(str(html.read(),"utf-8"))

outData.close()
