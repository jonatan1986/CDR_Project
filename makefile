CFLAGS= -lpthread -std=c++14 -pedantic -Werror -fpermissive -Wall -c

all: GenerateFile  GenerateCdr

GenerateFile:GenerateFile.o FileGenerator.o Config.o
		 g++ -o GenerateFile GenerateFile.o FileGenerator.o Config.o



GenerateCdr:Cdr.o  FileGenerator.o TaskManager.o Task.o  eReader.o eWriter.o eParser.o eOutPutFile.o Config.o
		 g++ -o   GenerateCdr  Cdr.o  FileGenerator.o TaskManager.o  Task.o  eReader.o eWriter.o eParser.o  eOutPutFile.o  Config.o -lpthread


Config.o: Config.cpp Config.h
		g++ $(CFLAGS) Config.cpp

GenerateFile.o: GenerateFile.cpp FileGenerator.h Config.h
	   g++ $(CFLAGS) GenerateFile.cpp

FileGenerator.o: FileGenerator.cpp FileGenerator.h Config.h SingleTone.h
		 g++ $(CFLAGS)  FileGenerator.cpp

eReader.o: eReader.cpp  eReader.h SharedResource.h eCdrDetails.h SafeQueue.h SingleTone.h
		 g++ $(CFLAGS)  eReader.cpp

eWriter.o: eWriter.cpp eWriter.h SharedResource.h eCdrDetails.h SafeQueue.h \
	   eOutPutFile.h Factory.h SingleTone.h Config.h SingleTone.h
		 g++ $(CFLAGS)  eWriter.cpp

eParser.o: eParser.cpp  eParser.h SharedResource.h eCdrDetails.h SafeQueue.h SingleTone.h
		 g++ $(CFLAGS)  eParser.cpp

Task.o: Task.cpp Task.h  Factory.h Config.h eWriter.h eParser.h eReader.h \
	 SharedResource.h SingleTone.h
		 g++ $(CFLAGS)  Task.cpp


TaskManager.o: TaskManager.cpp TaskManager.h ThreadPool.h SafeQueue.h Task.h \
Factory.h eWriter.h eParser.h eReader.h SharedResource.h SingleTone.h Config.h
			         g++ $(CFLAGS)  TaskManager.cpp

Cdr.o: Cdr.cpp  FileGenerator.h TaskManager.h Config.h SingleTone.h
			g++ $(CFLAGS)  Cdr.cpp

eOutPutFile.o: eOutPutFile.cpp eOutPutFile.h eCdrDetails.h Config.h SingleTone.h
		  g++ $(CFLAGS)  eOutPutFile.cpp


clean:
	rm -f *.o
	rm GenerateFile
	rm GenerateCdr
