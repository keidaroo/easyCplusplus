all: main.cpp
	g++ -std=c++11 main.cpp -o main
	./main
	clang-format -i  -style=file  output.cpp
	g++ -std=c++11 output.cpp -o output
	./output
