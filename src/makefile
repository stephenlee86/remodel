all: remodel

remodel: stringutil.o parser.o
	g++ stringutil.o parser.o -o remodel

stringutil.o: stringutil.cpp
	g++ -c stringutil.cpp

parser.o: parser.cpp
	g++ -c parser.cpp

md5diff.o: md5diff.cpp
	g++ -c md5diff.cpp -lcrypto

clean:
	rm -rf *o remodel

