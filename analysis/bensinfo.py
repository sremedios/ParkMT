fin = open('AlecsBane.txt','r')
fout = open('BensInfo.txt','w')

line = fin.readline()

while line:
    line = line[:-1]
    for row in range(24):
        for col in range(5):
            fout.write(line)
        fout.write("\n")
    fout.write("\n")
    line = fin.readline()

fin.close()
fout.close()
