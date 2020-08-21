CFLAGS= -lpthread -std=c++17 -lstdc++fs -pedantic -Werror -fpermissive -Wall -c

all: GenerateFile  GenerateCdr

GenerateFile:GenerateFile.o FileGenerator.o
		 g++ -o GenerateFile GenerateFile.o FileGenerator.o



GenerateCdr:Cdr.o  FileGenerator.o TaskManager.o Task.o  eReader.o eWriter.o eParser.o eOutPutFile.o
		 g++ -o GenerateCdr Cdr.o FileGenerator.o TaskManager.o  Task.o  eReader.o eWriter.o eParser.o  eOutPutFile.o -lpthread


GenerateFile.o: GenerateFile.cpp FileGenerator.h
	   g++ $(CFLAGS) GenerateFile.cpp

FileGenerator.o: FileGenerator.cpp
		 g++ $(CFLAGS)  FileGenerator.cpp

eReader.o: eReader.cpp  eReader.h ThreadArgs.h eCdrDetails.h SafeQueue.h
		 g++ $(CFLAGS)  eReader.cpp

eWriter.o: eWriter.cpp eWriter.h ThreadArgs.h eCdrDetails.h SafeQueue.h \
	   eOutPutFile.h Factory.h SingleTone.h Config.h
		 g++ $(CFLAGS)  eWriter.cpp

eParser.o: eParser.cpp  eParser.h ThreadArgs.h eCdrDetails.h SafeQueue.h
		 g++ $(CFLAGS)  eParser.cpp

Task.o: Task.cpp Task.h  Factory.h Config.h eWriter.h eParser.h eReader.h \
	 ThreadArgs.h SingleTone.h
		 g++ $(CFLAGS)  Task.cpp


TaskManager.o: TaskManager.cpp TaskManager.h ThreadPool.h SafeQueue.h Task.h \
Factory.h eWriter.h eParser.h eReader.h ThreadArgs.h SingleTone.h Config.h
			         g++ $(CFLAGS)  TaskManager.cpp

Cdr.o: Cdr.cpp  FileGenerator.h TaskManager.h Config.h
			g++ $(CFLAGS)  Cdr.cpp

eOutPutFile.o: eOutPutFile.cpp eOutPutFile.h eCdrDetails.h
		  g++ $(CFLAGS)  eOutPutFile.cpp


clean:
	rm -f *.o
	rm GenerateFile
	rm GenerateCdr
