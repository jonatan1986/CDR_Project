CFLAGS= -lpthread -std=c++14 -pedantic -Werror -fpermissive -Wall -c

all: GenerateFile  GenerateCdr

GenerateFile:GenerateFile.o FileGenerator.o
		g++ -o GenerateFile GenerateFile.o FileGenerator.o



GenerateCdr:Cdr.o  FileGenerator.o threadManager.o Job.o  eReader.o eWriter.o eParser.o
		g++ -o GenerateCdr Cdr.o FileGenerator.o threadManager.o  Job.o  eReader.o eWriter.o eParser.o -lpthread


GenerateFile.o: GenerateFile.cpp FileGenerator.h
		g++ $(CFLAGS) GenerateFile.cpp

FileGenerator.o: FileGenerator.cpp
			g++ $(CFLAGS)  FileGenerator.cpp

eReader.o: eReader.cpp  eReader.h ThreadArgs.h eCdrDetails.h SafeQueue.h
			g++ $(CFLAGS)  eReader.cpp

eWriter.o: eWriter.cpp eWriter.h ThreadArgs.h eCdrDetails.h SafeQueue.h  eOutPutFile.h Factory.h SingleTone.h
			g++ $(CFLAGS)  eWriter.cpp

eParser.o: eParser.cpp  eParser.h ThreadArgs.h eCdrDetails.h SafeQueue.h
			g++ $(CFLAGS)  eParser.cpp

Job.o: Job.cpp Job.h  Factory.h eWriter.h eParser.h eReader.h ThreadArgs.h SingleTone.h
			g++ $(CFLAGS)  Job.cpp


threadManager.o: threadManager.cpp threadManager.h ThreadPool.h SafeQueue.h Job.h  Factory.h eWriter.h eParser.h eReader.h ThreadArgs.h SingleTone.h
			g++ $(CFLAGS)  threadManager.cpp

Cdr.o: Cdr.cpp  FileGenerator.h threadManager.h
			g++ $(CFLAGS)  Cdr.cpp

clean:
	rm -f *.o
	rm GenerateFile
	rm GenerateCdr
