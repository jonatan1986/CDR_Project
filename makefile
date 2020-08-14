CFLAGS= -lpthread -std=c++14 -pedantic -Werror -fpermissive -Wall -c

all: GenerateFile  GenerateCdr

GenerateFile:GenerateFile.o FileGenerator.o
		g++ -o GenerateFile GenerateFile.o FileGenerator.o



GenerateCdr:Cdr.o  FileGenerator.o threadManager.o Job.o  eReader.o eWriter.o eParser.o
		g++ -o GenerateCdr Cdr.o FileGenerator.o threadManager.o  Job.o  eReader.o eWriter.o eParser.o -lpthread


GenerateFile.o: GenerateFile.cpp
		g++ $(CFLAGS) GenerateFile.cpp

FileGenerator.o: FileGenerator.cpp
			g++ $(CFLAGS)  FileGenerator.cpp

eReader.o: eReader.cpp
			g++ $(CFLAGS)  eReader.cpp

eWriter.o: eWriter.cpp
			g++ $(CFLAGS)  eWriter.cpp

eParser.o: eParser.cpp
			g++ $(CFLAGS)  eParser.cpp

Job.o: Job.cpp Job.h Factory.h
			g++ $(CFLAGS)  Job.cpp


threadManager.o: threadManager.cpp
			g++ $(CFLAGS)  threadManager.cpp

Cdr.o: Cdr.cpp
			g++ $(CFLAGS)  Cdr.cpp

clean:
	rm -f *.o
	rm GenerateFile
	rm GenerateCdr
