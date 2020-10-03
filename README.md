# CDR_Project
The aim of this prject is to get an input file and create an output file.
Cdr = caller data record.
The input file(datafile.txt) contains raw data about  cellular usage of clients/subscribers.
Each client has IMSI whic means "international mobile subscriber idnetitity".
Each line in the file related to a subscriber and gives data about the subscribers.
Each subscriber could appear(and obviuosly appears) more then once.
Each line gives details such as : IMSI,date(dd/mm/yy),downlink(bytes),uplink(bytes),call duration(hh:mm:ss).
Each detail is separated by pipe.
For example : 746397689|29/5/2020|895|611|01:39:29.
This line basically says:
IMSI = 746397689
date = 29/5/2020
downlink = 895
uplink = 611
call duration = 01:39:29

The output file is written in a way that details are understood. In the example above, the line in the output will be:
IMSI=746397689 Date=29/5/2020 Downlink=895 Uplink=611 Duration=01:39:2
output file can appear in the forms: 
1) single file which contains all the cdrs(the name of the file is "SingleFile.txt")

example:(for single  file)
input file: 
617795746|21/12/2020|833|790|00:41:18
832798064|19/7/2020|623|635|05:52:51
410680012|28/6/2020|826|819|00:47:57
617795746|26/6/2020|419|483|01:28:22

output file:
IMSI=617795746 Date=21/12/2020 Downlink=833 Uplink=790 Duration=00:41:18
IMSI=832798064 Date=19/7/2020 Downlink=623 Uplink=635 Duration=05:52:51
IMSI=410680012 Date=28/6/2020 Downlink=826 Uplink=819 Duration=00:47:57
IMSI=617795746 Date=26/6/2020 Downlink=419 Uplink=483 Duration=01:28:22


2) multiple files which are classified by imsi - each file is contains all cdrs of one imsi. files are indexed(1.txt, 2.txt. ...)
example:(for multiple  files)

input file: 
617795746|21/12/2020|833|790|00:41:18
832798064|19/7/2020|623|635|05:52:51
410680012|28/6/2020|826|819|00:47:57
617795746|26/6/2020|419|483|01:28:22

output files:
"1.txt": 
IMSI=617795746 Date=21/12/2020 Downlink=833 Uplink=790 Duration=00:41:18
IMSI=617795746 Date=26/6/2020 Downlink=419 Uplink=483 Duration=01:28:22

"2.txt":
IMSI=832798064 Date=19/7/2020 Downlink=623 Uplink=635 Duration=05:52:51

"3.txt":
IMSI=410680012 Date=28/6/2020 Downlink=826 Uplink=819 Duration=00:47:57



The process of creating the output file of the input file is multi threaded - there are couple of threads  - each thread handles 
a chunk from the file. each thread contains threads which perform tasks in paraller manner(reading from input,parsing input, writing to output)

Things to note:
* This porject works in Linux enviroment.
* If you want to build  - type in commnand line "make" , but you could use the executables which are already built(GenerateCdr && GenerateFile).
* You could simply run the project ("./GenerateCdr")
* If you want to generate the input file you run the executable("./GenerateFile")
* exe file "GenerateFile" generates an input file, whose amount of subscribers is grabbed from "cdrconfig.txt". 
  exe file "GenerateCdr" generates an output file, whose amount of subscribers is grabbed from "cdrconfig.txt".
  so if you modify cdrconfig.txt, please run ./GenerateFile and then ./GenerateCdr cause if two 
  executables don't have the same amount of subscribers - the program "GenerateCdr" is error prone or might crash
* If you modify "cdrconfig.txt", the each line you could modify only the right part of the line -
  the left part must stay as is.
* Output files are in "output" directory
* Imsi and subsscriber are the same(Imsi is a serial number of each subscriber)
  
 coding conventions:
 i_ - input variable
 l_ - local variable 
 m_ - member variable
 o_ - output variable
 n${name_of_variable} - integer
 s${name_of_variable} - string
 
Config file: "cdrconfig.txt"
Example:
INPUT_FILE_NAME datafile.txt
OUTPUT_TYPE SingleOutput
AMOUNT_OF_CHUNKS 5
AMOUNT_OF_SUBS 20
AMOUNT_OF_LINES 10000

Explaination:
INPUT_FILE_NAME    $(name_of_input_file)
OUTPUT_TYPE        $(Single/Multiple output).Single = one output file,Multiple = multiple output files(file for Imsi)
AMOUNT_OF_CHUNKS   $(Amount of chunks all threads should handle - each thread handles a chunk of the file)
AMOUNT_OF_SUBS     $(Amount of subscribers/Imsis) 
AMOUNT_OF_LINES    $(Amount of lines genereted in the input file)

 
 Project Tests:(In "Tests" directory)
 How to run the tests : sh RunTest.sh (in "CDR_Project" directory).
 The project includes tests. The tests are written in Python Language. Each test creates a specific scenario and compares the input file to the output file/s.
 Each test has a very simple chronology: update config file -> generate input file -> generate output file -> compare input and output.
 the test file(CdrTest.py) uses unittest library. 
 The topology of the tests is Simple:
 1)main.py - contains main function which calls function which runs all the tests.
 2)CdrTest.py - contains a class with function which runs all the tests.
 3)CdrLib.py  - library which contains all the functions which are utilized in order to create a scenario and handle it.
 **For the time being there are 8 basic tests, definiltly there are more scenarios to test, might be added later on.**

