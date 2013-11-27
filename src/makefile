all: remodel

remodel: stringutil.o parser.o
	g++ stringutil.o parser.o -o remodel

stringutil.o: stringutil.cpp
	g++ -c -Wall -pedantic stringutil.cpp

parser.o: parser.cpp
	g++ -c -Wall -pedantic parser.cpp

md5diff.o: md5diff.cpp
	g++ -c -Wall md5diff.cpp -lcrypto

clean:
	rm -rf *o remodel

