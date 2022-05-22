make:	main.cpp func.cpp header.h
	g++ -Wall main.cpp func.cpp -o main
test:	test.cpp func.cpp header.h
	g++ -Wall test.cpp func.cpp -o test
