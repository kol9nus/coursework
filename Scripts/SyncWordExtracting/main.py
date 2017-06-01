import os

__author__ = 'Smallb'


def extract_sync_words(from_file, to_file):
    i = 0
    for line in from_file:
        if i % 5 == 3:
            to_file.write(line)
        i += 1


pathToMainFolder = os.getcwd()
pathToMainFolder = pathToMainFolder[0:pathToMainFolder.rfind('\\Scripts') + 1]
fileName = "combinations117441.txt"
resultFileName = "117441syncWords.txt"
if os.path.exists(pathToMainFolder + fileName):
    file = open(pathToMainFolder + fileName, 'r')
    resultFile = open(pathToMainFolder + resultFileName, 'w')
    extract_sync_words(file, resultFile)
    file.close()
    resultFile.close()
else:
    print("file not found")
