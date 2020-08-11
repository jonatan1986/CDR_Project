CFLAGS= -lpthread -std=c++14  -pedantic -Werror -fpermissive -Wall -c

all: GenerateFile  GenerateCdr

GenerateFile:GenerateFile.o FileGenerator.o
		g++ -o GenerateFile GenerateFile.o FileGenerator.o



GenerateCdr:Cdr.o  FileGenerator.o threadManager.o Job.o  eReader.o eWriter.o eParser.o
		g++ -o GenerateCdr Cdr.o FileGenerator.o threadManager.o  Job.o  eReader.o eWriter.o eParser.o -lpthread


GenerateFile.o:
		g++ $(CFLAGS) GenerateFile.cpp

FileGenerator.o:
			g++ $(CFLAGS)  FileGenerator.cpp

eReader.o:
			g++ $(CFLAGS)  eReader.cpp

eWriter.o:
			g++ $(CFLAGS)  eWriter.cpp

eParser.o:
			g++ $(CFLAGS)  eParser.cpp

Job.o:
			g++ $(CFLAGS)  Job.cpp


threadManager.o:
			g++ $(CFLAGS)  threadManager.cpp

Cdr.o:
			g++ $(CFLAGS)  Cdr.cpp

clean:
	rm -f *.o
	rm GenerateFile
	rm GenerateCdr
