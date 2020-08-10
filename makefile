CFLAGS= -lpthread -std=c++14  -pedantic -Werror -fpermissive -Wall -c

all: GenerateFile

GenerateFile:GenerateFile.o FileGenerator.o
		g++ -o GenerateFile GenerateFile.o FileGenerator.o


GenerateFile.o: GenerateFile.cpp
		g++ $(CFLAGS) GenerateFile.cpp



FileGenerator.o: FileGenerator.cpp
			g++ $(CFLAGS)  FileGenerator.cpp


clean:
	rm -f *.o
	rm GenerateFile
