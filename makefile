run: src/main.cpp src/FileReader.o
	g++ -o run src/FileReader.o src/main.cpp

FileReader.o: src/FileReader.h src/FileReader.cpp
	g++ -o src/FileReader.o -c src/FileReader.cpp

clean:
	rm src/*.o
	rm *.o
