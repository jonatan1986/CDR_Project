# This is a sample Python script.

# Press Shift+F10 to execute it or replace it with your code.
# Press Double Shift to search everywhere for classes, files, tool windows, actions, and settings.

#tests
#singlefile - singlethreaded
#singlefile - multithreaded
#multiplefile - singlethreaded
#multiplefile - multithreaded
#emptyFile
#all the tests above - non round number
#if chunk num is bigger than amount of lines
#invalid input
#singleinput
import os
import cdrLib


# Press the green button in the gutter to run the script.
if __name__ == '__main__':
    path = os.path.dirname(os.getcwd()) + '/'
    filename = 'cdrconfig.txt'
    cdrLib.SetConfigFile(path,filename)
    cdrLib.GenerateInputFile()
    cdrLib.GenerateOutputFile()
    cdrLib.BuildDictFromInputFile()

# See PyCharm help at https://www.jetbrains.com/help/pycharm/
