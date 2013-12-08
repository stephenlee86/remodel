REMODEL CMPSCI 630
==================
Description
-----------
remodel takes a series of dependencies and targets, etc. (grammar below), but unlike make, it uses MD5 hashes to detect new content and provide, together with the dependency chain, a happens-before relation (md5diff(oldA,newA) => everything that depends on A must be rebuilt). It executes all independent (non-conflicting) commands in parallel, using threads or processes.

remodel uses a different grammar than make. Dependencies can appear in any order. If you execute remodel with no arguments, it should start with the pseudo-target DEFAULT. Otherwise, the root is the argument to remodel, as in remodel foo.o.

<code>
program ::= production* <br/>
production ::= target '<-' dependency (':' '"' command '"") <br/>
dependency ::= filename (',' filename)* <br/>
target ::= filename (',' filename)*<br/>
</code>

Here's an example that builds the program baz from two source files, foo.cpp and bar.cpp.

<code>
DEFAULT <- baz <br/>
baz <- foo.o, bar.o: "g++ foo.o bar.o -o baz"<br/>
foo.o <- foo.cpp : "g++ -c foo.cpp -o foo.o"<br/>
bar.o <- bar.cpp: "g++ -c bar.cpp -o bar.o"<br/>
</code>

You should store the dependencies on disk in a special directory called .remodel/, so that remodel will not re-execute any commands unless a dependency has been violated. 

Approach
--------
The remodel takes a 4-step approach:
  - Parse the grammar
  - Check for cyclic paths in the grammar
  - Create a tree for the specified target
  - Execute all the trees and its child in parallel

To RUN
------
The default filename that remodel takes as input is remodel_makefile. This 'Makefile' should be in the same folder as remodel. In order to compile the files, ensure that the labels/targets reflect the relative path to the file. For example, if the class files are inside test_cases folder and remodel is up one folder then following will be 'remodel_makefile':

<code>
DEFAULT <- test_cases/baz, test_cases/cow <br/>
test_cases/baz <- test_cases/foo.o, test_cases/bar.o: "g++ test_cases/foo.o test_cases/bar.o -o test_cases/baz"<br/>
test_cases/foo.o <- test_cases/foo.cpp : "g++ -c test_cases/foo.cpp -o test_cases/foo.o"<br/>
test_cases/bar.o <- test_cases/bar.cpp: "g++ -c test_cases/bar.cpp -o test_cases/bar.o"<br/>
test_cases/cow <- test_cases/moo.o, test_cases/zoo.o: "g++ test_cases/zoo.o test_cases/moo.o -o test_cases/cow"<br/>
test_cases/moo.o <- test_cases/moo.cpp : "g++ -c test_cases/moo.cpp -o test_cases/moo.o"<br/>
test_cases/zoo.o <- test_cases/zoo.cpp: "g++ -c test_cases/zoo.cpp -o test_cases/zoo.o"<br/>
</code>



