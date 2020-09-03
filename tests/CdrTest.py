import unittest
import cdrLib
import os

def TestCdrTestCase(path, filename, outputType, amountOfChunks, amountOfSubs, amountOfLines):
    cdrLib.SetConfigFile(path, filename, outputType, amountOfChunks, amountOfSubs, amountOfLines)
    cdrLib.GenerateInputFile()
    cdrLib.GenerateOutputFile()
    ImsiInputDictionary = cdrLib.BuildDictFromInputFile()
    ImsikeyList, ImsiOutputDictionary = cdrLib.BuildDictFromOutputFile()
    result = cdrLib.ComplareDictionaries(ImsikeyList, ImsiOutputDictionary, ImsiInputDictionary)
    return result

def Test1(path):
    # multithread(amountOfChunks > 1), multiOutPut, multiImsi(amountOfSubs > 1)
    result  = TestCdrTestCase(path,filename = 'cdrconfig.txt', outputType = 'MultipleOutput',
                    amountOfChunks='5', amountOfSubs = '20', amountOfLines = '10000')
    return result

def Test2(path):
    # multithread(amountOfChunks > 1), multiOutPut, SingleImsi(amountOfSubs = 1)
    result  = TestCdrTestCase(path,filename = 'cdrconfig.txt', outputType = 'MultipleOutput',
                    amountOfChunks='5', amountOfSubs = '1', amountOfLines = '10000')
    return result


def Test3(path):
    # signlethread(amountOfChunks = 1), MultipleOutput, multiImsi(amountOfSubs > 1)
    result  = TestCdrTestCase(path,filename = 'cdrconfig.txt', outputType = 'MultipleOutput',
                    amountOfChunks='1', amountOfSubs = '20', amountOfLines = '10000')
    return result

def Test4(path):
    # signlethread(amountOfChunks = 1), MultipleOutput, SingleImsi(amountOfSubs = 1)
    result  = TestCdrTestCase(path,filename = 'cdrconfig.txt', outputType = 'MultipleOutput',
                    amountOfChunks='1', amountOfSubs = '1', amountOfLines = '10000')
    return result

class TestCdr(unittest.TestCase):
    def RunUnitTests(self):
        path = os.path.dirname(os.getcwd())
        self.assertTrue(Test1(path))
        self.assertTrue(Test2(path))
        self.assertTrue(Test3(path))
        self.assertTrue(Test4(path))
