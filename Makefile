make:
	g++  -o recommendation -std=c++11 -g3 main.cpp utils.cpp

clean:
	rm -rf recommendation *.o
