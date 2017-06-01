__author__ = 'Smallb'

import os

currentPath = os.getcwd()
currentPath = currentPath[0:currentPath.rfind('\\') + 1]
fileName = "2016.05.01 13.24.20offset.txt"  # input()
if os.path.exists(currentPath + fileName):
    file = open(currentPath + fileName, 'r')
    i = 0
    temp = ""
    n = 0
    s = 0
    d = {}
    for line in file:
        temp += line
        if i % 5 == 4:
            s = int(line[line.rfind(' ') + 1:-1])
            t = tuple([temp, s])
            if d.get(n) is None:
                d[n] = list()
            d[n].append(t)
            temp = ""
        elif i % 5 == 1:
            n = int(line[line.rfind(' ') + 1:-1])
        i += 1
    file.close()
    file = open("sorted" + fileName, 'w')
    file2 = open("diff1 " + fileName, 'w')
    for key in sorted(d.keys()):
        sortedDKey = sorted(d[key], key=lambda x: x[1])
        for t in sortedDKey:
            file.write(t[0])
            if sortedDKey[-1][1] - 1 <= t[1]:
                file2.write(t[0])

    file.close()

else:
    print("file not found")