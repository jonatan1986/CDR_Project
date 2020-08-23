# CDR_Project
the aim of this prject is to get an input file and create an output file
cdr = caller data record
the input file(datafile.txt) contains raw data about  cellular usage of clients/subscribers.
each client has IMSI whic means "international mobile subscriber idnetitity"
each line in the file related to a subscriber and gives data about the subscribers.
each subscriber could appear(and obviuosly appears) more then once.
each line gives details such as : IMSI,date(dd/mm/yy),downlink(bytes),uplink(bytes),call duration(hh:mm:ss)
each detail is separated by pipe.
for example : 746397689|29/5/2020|895|611|01:39:29
this line basically says:
IMSI = 746397689
date = 29/5/2020
downlink = 895
uplink = 611
call duration = 01:39:29

the output file is written in a way that details are will understood. In the example above, the line in the output will be:
IMSI=746397689 Date=29/5/2020Downlink=895 Uplink=611 Duration= 01:39:2
output file can appear in the forms: 
1) single file which contains all the cdrs(the name of the file is "SingleFile.txt")
2) multiple files which are classified by imsi - each file is contains all cdrs of one imsi. files are indexed(1.txt, 2.txt. ...)

the process of creating the output file of the input file is mutil threaded - there are couple of threads  - each thread handles 
a chunk from the file. each thread contains threads which perform tasks in paraller manner(reading from input,parsing input, writing to output)

things to note:
*if you want to build  - type in commnand line "make" , but you could use the executables.
* you could simply run the project ("./GenerateCdr")
* if you want to generate the input file you run the executable("./GenerateFile")
