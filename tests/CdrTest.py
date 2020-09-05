import unittest
import cdrLib
import os

#@ the fucnion creates a scenario from the input parameters and resturns
#@ result which could be True(Pass) or False(Fail)
def TestCdrTestCase(path, filename, outputType, amountOfChunks, amountOfSubs, amountOfLines):
    cdrLib.SetConfigFile(path, filename, outputType, amountOfChunks, amountOfSubs, amountOfLines)
    cdrLib.GenerateInputFile()
    cdrLib.GenerateOutputFile()
    ImsiInputDictionary = cdrLib.BuildDictFromInputFile()
    ImsikeyList, ImsiOutputDictionary = cdrLib.BuildDictFromOutputFile(path,outputType)
    result = cdrLib.ComplareDictionaries(ImsikeyList, ImsiOutputDictionary, ImsiInputDictionary)
    return result

def Test1(path):
    # multithread(amountOfChunks > 1), MultipleOutput, multiImsi(amountOfSubs > 1)
    result  = TestCdrTestCase(path,filename = 'cdrconfig.txt', outputType = 'MultipleOutput',
                    amountOfChunks='5', amountOfSubs = '20', amountOfLines = '10000')
    return result

def Test2(path):
    # multithread(amountOfChunks > 1), MultipleOutput, SingleImsi(amountOfSubs = 1)
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

def Test5(path):
    # signlethread(amountOfChunks = 1), SingleOutput, SingleImsi(amountOfSubs = 1)
    result  = TestCdrTestCase(path,filename = 'cdrconfig.txt', outputType = 'SingleOutput',
                    amountOfChunks='1', amountOfSubs = '1', amountOfLines = '10000')
    return result

def Test6(path):
    # signlethread(amountOfChunks > 1), SingleOutput, SingleImsi(amountOfSubs = 1)
    result  = TestCdrTestCase(path,filename = 'cdrconfig.txt', outputType = 'SingleOutput',
                    amountOfChunks='5', amountOfSubs = '1', amountOfLines = '10000')
    return result

def Test7(path):
    # signlethread(amountOfChunks =  1), SingleOutput, MultipleImsi(amountOfSubs > 1)
    result  = TestCdrTestCase(path,filename = 'cdrconfig.txt', outputType = 'SingleOutput',
                    amountOfChunks='1', amountOfSubs = '20', amountOfLines = '10000')
    return result

def Test8(path):
    # signlethread(amountOfChunks >  1), SingleOutput, MultipleImsi(amountOfSubs > 1)
    result  = TestCdrTestCase(path,filename = 'cdrconfig.txt', outputType = 'SingleOutput',
                    amountOfChunks='5', amountOfSubs = '20', amountOfLines = '10000')
    return result

class TestCdr(unittest.TestCase):
    def RunUnitTests(self):
        print("running tests...,be patient it might take a while")
        path = os.path.dirname(os.getcwd())
        self.assertTrue(Test1(path))
        self.assertTrue(Test2(path))
        self.assertTrue(Test3(path))
        self.assertTrue(Test4(path))
        self.assertTrue(Test5(path))
        self.assertTrue(Test6(path))
        self.assertTrue(Test7(path))
        self.assertTrue(Test8(path))
        print("all tests passed successfully")