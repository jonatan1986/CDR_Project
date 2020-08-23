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
