

import os
import pathlib
from os import listdir
from os.path import isfile, join
from enum import IntEnum
from functools import reduce

class ConfigType(IntEnum):
    INPUT_FILE_NAME = 0
    OUTPUT_TYPE = 1
    AMOUNT_OF_CHUNKS = 2
    AMOUNT_OF_SUBS = 3
    AMOUNT_OF_LINES = 4

class CdrDetails():
    def __init__(self,IMSI=None,Date=None,Downlink=None,Uplink=None,Duration=None):
        self.IMSI = IMSI
        self.Date = Date
        self.Downlink = Downlink
        self.Uplink = Uplink
        self.Duration = Duration

    def getDownLink(self):
        return self.Downlink

    def getUpLink(self):
        return self.Uplink

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

def ParseInputLine(line):
    line = line[0: len(line) - 1]
    cdrDataList = line.split('|')
    # print(cdrDataList)
    Imsi = cdrDataList[0]
    #print(Imsi)
    return Imsi,cdrDataList

def ParseOutputLine(line):
    line = line[0 : len(line)-1] # remove '\n' from the end of 'line'
    cdrDataList = line.split(' ')
    result = []
    Imsi = cdrDataList[0][cdrDataList[0].find('=') + 1:len(cdrDataList[0])]
    # print("Imsi = " + Imsi)
    #print(line.find("Downlink=") + len("Downlink="))
    for cdrData in cdrDataList:
        pos = cdrData.find('=') + 1
        str = cdrData[pos:len(cdrData)]
        # print(str)
        result.append(str)
    return Imsi,result


def SortTuple(tup):
    # tuple of Imsi,Date,Downlink,Uplink,Call Duration
    # is sorted by Downlink in an ascending order
    return (sorted(tup, key=lambda cdrDetails: cdrDetails.getDownLink()))

def SortListByUplink(tup):
    i = 0
    while i < len(tup) - 1:
        j = i
        while (int(tup[j].Downlink) == int(tup[j + 1].Downlink)):
            # print(tup[j].Downlink)
            j = j + 1
            if j == len(tup) - 1:
                break
        if j > i:
            tup[i : j + 1] = sorted(tup[i : j + 1], key=lambda cdrDetails: cdrDetails.getUpLink())
        i = j + 1
    return tup

def BuildDictFromOutputFile(path = os.path.dirname(os.getcwd())):
    print(path)
    absPath  = path + "/output"
    os.chdir(absPath)
    directory = os.getcwd()
    print("directory "  + directory)
    onlyTxtFiles = [f for f in listdir(directory) if isfile(join(directory, f)) and f.endswith(".txt")]
    # print(onlyTxtFiles)
    ImsiListDictionary = {}
    ImsikeyList = []
    for file in onlyTxtFiles:
        imsiList = []
        Imsi = ' '
        with open(file,'r') as file:
            for line in file:
                # print(line)
                Imsi,CdrData = ParseOutputLine(line)
                cdrDetails = CdrDetails(CdrData[0],CdrData[1],CdrData[2],CdrData[3],CdrData[4])
                imsiList.append(cdrDetails)
        imsiList = SortTuple(imsiList)

        # print(imsiList)
        # for index in imsiList:
            # print(index)
        ImsiListDictionary[Imsi]  = imsiList
        ImsikeyList.append(Imsi)
        # for index in imsiList:
            # print(index.IMSI + " " + index.Downlink + " " + index.Uplink)
    return  ImsikeyList,ImsiListDictionary


def BuildDictFromInputFile(path = os.path.dirname(os.getcwd()), file = "datafile.txt"):
    absPath = path + "/" + file
    print("absPath " + absPath)
    ImsiListDictionary = {}
    with open(absPath,'r') as file:
        for line in file:
            Imsi,CdrData = ParseInputLine(line)
            cdrDetails = CdrDetails(CdrData[0], CdrData[1], CdrData[2], CdrData[3], CdrData[4])
            if Imsi in ImsiListDictionary.keys():
                imsiList = ImsiListDictionary[Imsi]
                imsiList.append(cdrDetails)
            else:
                imsiList = []
                imsiList.append(cdrDetails)
                ImsiListDictionary[Imsi] = imsiList
    for key,value in ImsiListDictionary.items():
        imsiList = value
        imsiList = SortTuple(imsiList)
        imsiList = SortListByUplink(imsiList)
        ImsiListDictionary[key] = imsiList
    return ImsiListDictionary

def CompareLists(Imsikey,ImsiOutputDictionary, ImsiInputDictionary):
    ImsiInputList = ImsiInputDictionary[str(Imsikey)]
    ImsiOutputList = ImsiOutputDictionary[str(Imsikey)]
    for (item1,item2) in zip(ImsiInputList,ImsiOutputList):
        # print("item1 " + item1.Uplink + " item2 "+ item2.Uplink)
        print("item1 " + item1.Downlink + " item2 " + item2.Downlink)
    # result = reduce(lambda firstCdr, secondCdr: firstCdr and secondCdr,
    # map(lambda firstCdr, secondCdr: firstCdr.Downlink == secondCdr.Downlink and firstCdr.Uplink == secondCdr.Uplink,
    # ImsiInputList, ImsiOutputList))
    # print(result)

def ComplareDictionaries(ImsikeyList,ImsiOutputDictionary, ImsiInputDictionary):
    for Imsikey in ImsikeyList:
        CompareLists(Imsikey, ImsiOutputDictionary, ImsiInputDictionary)
        # ImsiInputList = ImsiInputDictionary[str(Imsikey)]
        # ImsiOutputList = ImsiOutputDictionary[str(Imsikey)]
        # for (item1,item2) in zip(ImsiInputList,ImsiOutputList):
        #     print("item1 " + item1.Downlink + " item2 "+ item2.Downlink)