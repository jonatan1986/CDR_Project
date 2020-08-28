

import os
import pathlib
from os import listdir
from os.path import isfile, join

from enum import IntEnum

class ConfigType(IntEnum):
    INPUT_FILE_NAME = 0
    OUTPUT_TYPE = 1
    AMOUNT_OF_CHUNKS = 2
    AMOUNT_OF_SUBS = 3
    AMOUNT_OF_LINES = 4



def SetConfigFile(path = os.path.dirname(os.getcwd()), filename = 'cdrconfig.txt',
                  outputType = 'MultipleOutput', amountOfChunks = '5', amountOfSubs = '20',
                  amountOfLines = '10000'):
    # Use a breakpoint in the code line below to debug your script.
    filepath = path + filename
    lineArray = {}
    with open(filepath, 'r') as file:
        lineArray = file.readlines()
        lineArray[ConfigType.OUTPUT_TYPE] = lineArray[ConfigType.OUTPUT_TYPE].split(' ')[0] + ' ' + outputType + '\n'
        lineArray[ConfigType.AMOUNT_OF_CHUNKS] = lineArray[ConfigType.AMOUNT_OF_CHUNKS].split(' ')[0] + ' ' + amountOfChunks + '\n'
        lineArray[ConfigType.AMOUNT_OF_SUBS] = lineArray[ConfigType.AMOUNT_OF_SUBS].split(' ')[0] + ' ' + amountOfSubs + '\n'
        lineArray[ConfigType.AMOUNT_OF_LINES] = lineArray[ConfigType.AMOUNT_OF_LINES].split(' ')[0] + ' '+ amountOfLines + '\n'
        for line in lineArray:
            print(line)
    file.close()

    with open(filepath, 'w') as file:
        file.writelines(lineArray)
    file.close()


def GenerateInputFile(path = os.path.dirname(os.getcwd()) + '/', filename = 'cdrconfig.txt',
                      command = './GenerateFile'):
    os.chdir(path)
    os.system(command)
    # print(path)
    # fileAbsPath = path + filename


def GenerateOutputFile(path = os.path.dirname(os.getcwd()) + '/', filename = 'cdrconfig.txt',
                      command = './GenerateCdr'):
    os.chdir(path)
    os.system(command)

def BuildDictFromInputFile(path = os.path.dirname(os.getcwd())):
    os.chdir("output")
    directory = os.getcwd()
    onlyTxtFiles = [f for f in listdir(directory) if isfile(join(directory, f)) and f.endswith(".txt")]
    # print(onlyTxtFiles)
    num = 0
    for file in onlyTxtFiles:
        print(file)

        with open(file,'r') as file:
            for line in file:
                num = num + 1
    print("num " + str(num))