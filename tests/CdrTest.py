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
    print("final result " + str(result))
    return result

class TestCdr(unittest.TestCase):
    def RunUnitTests(self):
        path = os.path.dirname(os.getcwd())
        result = TestCdrTestCase(path,'cdrconfig.txt', 'MultipleOutput', '5', '20', '10000')
        print("final result " + str(result))
        self.assertTrue(result)
        # self.assertAlmostEqual(TestCdrTestCase(),True)
        # self.assertAlmostEqual(TestCdrTestCase(),True)
        # self.assertAlmostEqual(TestCdrTestCase(),True)


