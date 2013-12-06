all: clean remodel

remodel: stringutil.o commandutil.o parser.o graph.o production.o md5diff.o remodel.o tree.o
	g++ stringutil.o commandutil.o parser.o graph.o production.o md5diff.o  tree.o remodel.o -o remodel -lcrypto

remodel.o: remodel.cpp
	g++ -c -Wall -pedantic remodel.cpp

parser.o: parser.cpp
	g++ -c -Wall -pedantic parser.cpp

stringutil.o: stringutil.cpp
	g++ -c -Wall -pedantic stringutil.cpp

commandutil.o: commandutil.cpp
	g++ -c -Wall -pedantic -std=c++11 commandutil.cpp

production.o: production.cpp
	g++ -c -Wall -pedantic production.cpp

graph.o: graph.cpp 
	g++ -c -Wall -pedantic graph.cpp

tree.o: tree.cpp
	g++ -c tree.cpp

md5diff.o: md5diff.cpp
	g++ -c -Wall md5diff.cpp -lcrypto

clean:
	rm -f *.o remodel

