

import os
import pathlib
from os import listdir
from os.path import isfile, join
from enum import IntEnum

SingleOutputFileName = "SingleFile.txt"

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

    # def getUpLink(self):
    #     return self.Uplink

def SetConfigFile(path = os.path.dirname(os.getcwd()), filename = 'cdrconfig.txt',
                  outputType = 'MultipleOutput', amountOfChunks = '5', amountOfSubs = '20',
                  amountOfLines = '10000'):
    filepath = path + '/'  + filename
    lineArray = {}
    with open(filepath, 'r') as file:
        lineArray = file.readlines()
        lineArray[ConfigType.OUTPUT_TYPE] = lineArray[ConfigType.OUTPUT_TYPE].split(' ')[0] + ' ' + outputType + '\n'
        lineArray[ConfigType.AMOUNT_OF_CHUNKS] = lineArray[ConfigType.AMOUNT_OF_CHUNKS].split(' ')[0] + ' ' + amountOfChunks + '\n'
        lineArray[ConfigType.AMOUNT_OF_SUBS] = lineArray[ConfigType.AMOUNT_OF_SUBS].split(' ')[0] + ' ' + amountOfSubs + '\n'
        lineArray[ConfigType.AMOUNT_OF_LINES] = lineArray[ConfigType.AMOUNT_OF_LINES].split(' ')[0] + ' '+ amountOfLines + '\n'
        # for line in lineArray:
        #     print(line)
    file.close()

    with open(filepath, 'w') as file:
        file.writelines(lineArray)
    file.close()

#genetate input file according to config file
def GenerateInputFile(path = os.path.dirname(os.getcwd()) + '/', filename = 'cdrconfig.txt',
                      command = './GenerateFile'):
    os.chdir(path)
    os.system(command)


def GenerateOutputFile(path = os.path.dirname(os.getcwd()) + '/', command = './GenerateCdr'):
    os.chdir(path)
    os.system(command)

def ParseInputLine(line):
    line = line[0: len(line) - 1]
    cdrDataList = line.split('|')
    Imsi = cdrDataList[0]
    return Imsi,cdrDataList

# @parse line in the output file/s
def ParseOutputLine(line):
    line = line[0 : len(line)-1] # remove '\n' from the end of 'line'
    cdrDataList = line.split(' ')
    result = []
    Imsi = cdrDataList[0][cdrDataList[0].find('=') + 1:len(cdrDataList[0])]
    for cdrData in cdrDataList:
        pos = cdrData.find('=') + 1
        str = cdrData[pos:len(cdrData)]
        # print(str)
        result.append(str)
    return Imsi,result

# @ each list of specific Imsi is sorted by Downlink.
# @ lists ,ust be sorted - so Imsi list created of input can be compared to list created of output
def SortListByDownlink(tup):
    # tuple of Imsi,Date,Downlink,Uplink,Call Duration
    # is sorted by Downlink in an ascending order
    return (sorted(tup, key=lambda cdrDetails: cdrDetails.getDownLink()))

# def SortListByUplink(tup):
#     i = 0
#     while i < len(tup) - 1:
#         j = i
#         while (int(tup[j].Downlink) == int(tup[j + 1].Downlink)):
#             # print(tup[j].Downlink)
#             j = j + 1
#             if j == len(tup) - 1:
#                 break
#         if j > i:
#             tup[i : j + 1] = sorted(tup[i : j + 1], key=lambda cdrDetails: cdrDetails.getUpLink())
#         i = j + 1
#     return tup

#@ strategy design pattern - Dictionary(key = Imsi, value = list of cdrs of that Imsi) is
#@ created from the output file/s. Algorithm is selected according to the output type(Single/Multiple)
class OutputStrategy():
    def BuildDictFromOutputFile(self,path):
        pass

class MultipleOutputStrategy(OutputStrategy):
    def BuildDictFromOutputFile(self,path):
        absPath = path + "/output"
        os.chdir(absPath)
        directory = os.getcwd()
        # print("directory "  + directory)
        onlyTxtFiles = [f for f in listdir(directory) if isfile(join(directory, f)) and f.endswith(".txt")]
        # print(onlyTxtFiles)
        ImsiListDictionary = {}
        ImsikeyList = []
        for file in onlyTxtFiles:
            ImsiList = []
            Imsi = ' '
            with open(file, 'r') as file:
                for line in file:
                    Imsi, CdrData = ParseOutputLine(line)
                    cdrDetails = CdrDetails(CdrData[0], CdrData[1], CdrData[2], CdrData[3], CdrData[4])
                    ImsiList.append(cdrDetails)
            ImsiList = SortListByDownlink(ImsiList)
            ImsiListDictionary[Imsi] = ImsiList
            ImsikeyList.append(Imsi)
        return ImsikeyList, ImsiListDictionary

class SingleOutputStrategy(OutputStrategy):
    def BuildDictFromOutputFile(self,path):
        ImsiListDictionary = {}
        ImsikeyList = []
        absPath = path + "/output"
        filePath = absPath + "/" + SingleOutputFileName
        with open(filePath, 'r') as file:
            for line in file:
                Imsi, CdrData = ParseOutputLine(line)
                cdrDetails = CdrDetails(CdrData[0], CdrData[1], CdrData[2], CdrData[3], CdrData[4])
                if Imsi in ImsiListDictionary.keys():
                    imsiList = ImsiListDictionary[Imsi]
                    imsiList.append(cdrDetails)
                else:
                    imsiList = []
                    imsiList.append(cdrDetails)
                    ImsiListDictionary[Imsi] = imsiList
        for key, value in ImsiListDictionary.items():
            imsiList = value
            imsiList = SortListByDownlink(imsiList)
            ImsiListDictionary[key] = imsiList
            ImsikeyList.append(key)
        return ImsikeyList, ImsiListDictionary

#@ Dictionary(key = Imsi, value = list of cdrs of that Imsi) is
#@ created from the output file/s.
def BuildDictFromOutputFile(path , outputType):
    if outputType == "MultipleOutput" :
        outputStrategy = MultipleOutputStrategy()
    else: # outputType == "SingeOutput"
        outputStrategy = SingleOutputStrategy()

    ImsikeyList, ImsiListDictionary = outputStrategy.BuildDictFromOutputFile(path)
    return ImsikeyList, ImsiListDictionary

#@ Dictionary(key = Imsi, value = list of cdrs of that Imsi) is
#@ created from the input file/s.
def BuildDictFromInputFile(path = os.path.dirname(os.getcwd()), file = "datafile.txt"):
    absPath = path + "/" + file
    # print("absPath " + absPath)
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
        imsiList = SortListByDownlink(imsiList)
        ImsiListDictionary[key] = imsiList
    return ImsiListDictionary
#@ compare two lists of the same Imsi - list created from the input file and list
#@ created from the output file
def CompareLists(Imsikey,ImsiOutputDictionary, ImsiInputDictionary):
    ImsiInputList = ImsiInputDictionary[str(Imsikey)]
    ImsiOutputList = ImsiOutputDictionary[str(Imsikey)]
    result = True
    CdrDetailsList = []
    for (Inputitem, Outputitem) in zip(ImsiInputList, ImsiOutputList):
        if Inputitem.IMSI != Outputitem.IMSI or Inputitem.Downlink != Outputitem.Downlink:
            print(Inputitem.IMSI + " " + Outputitem.IMSI )
            print(Inputitem.Downlink + " " + Outputitem.Downlink)
            print(Inputitem.Uplink + " " + Outputitem.Uplink)
            return  False
        if Inputitem.Uplink != Outputitem.Uplink:
            result = False
            firstTuple = {Inputitem.IMSI, Inputitem.Date, Inputitem.Downlink, Inputitem.Uplink, Inputitem.Duration}
            secondTuple = {Outputitem.IMSI, Outputitem.Date, Outputitem.Downlink, Outputitem.Uplink,Outputitem.Duration}
            if firstTuple in CdrDetailsList:
                CdrDetailsList.remove(firstTuple)
            else:
                CdrDetailsList.append(firstTuple)
            if secondTuple in CdrDetailsList:
                CdrDetailsList.remove(secondTuple)
            else:
                CdrDetailsList.append(secondTuple)
            continue
        if Inputitem.Date != Outputitem.Date:
            result = False
            firstTuple = {Inputitem.IMSI,Inputitem.Date,Inputitem.Downlink,Inputitem.Uplink,Inputitem.Duration}
            secondTuple = {Outputitem.IMSI,Outputitem.Date,Outputitem.Downlink,Outputitem.Uplink,Outputitem.Duration}
            if firstTuple in CdrDetailsList:
                CdrDetailsList.remove(firstTuple)
            else:
                CdrDetailsList.append(firstTuple)
            if secondTuple in CdrDetailsList:
                CdrDetailsList.remove(secondTuple)
            else:
                CdrDetailsList.append(secondTuple)
            continue
        if Inputitem.Duration != Outputitem.Duration:
            result = False
            firstTuple = {Inputitem.IMSI, Inputitem.Date, Inputitem.Downlink, Inputitem.Uplink, Inputitem.Duration}
            secondTuple = {Outputitem.IMSI, Outputitem.Date, Outputitem.Downlink, Outputitem.Uplink,Outputitem.Duration}
            if firstTuple in CdrDetailsList:
                CdrDetailsList.remove(firstTuple)
            else:
                CdrDetailsList.append(firstTuple)
            if secondTuple in CdrDetailsList:
                CdrDetailsList.remove(secondTuple)
            else:
                CdrDetailsList.append(secondTuple)
    if len(CdrDetailsList) == 0:
        result = True
    # else:
    #     for index in CdrDetailsList:
    #         print(index)
    # print(result)
    return result

#@ compare two dictionaries  - dictionary created from the input file and dictionary
#@ created from the output files
def ComplareDictionaries(ImsikeyList,ImsiOutputDictionary, ImsiInputDictionary):
    for Imsikey in ImsikeyList:
        result = CompareLists(Imsikey, ImsiOutputDictionary, ImsiInputDictionary)
        if result == False:
            return False
    return True