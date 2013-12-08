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

You should store the dependencies on disk in a special directory called .remodel/, so that remodel will not re-execute any commands unless a dependency has been violated. 

Approach
--------
The remodel takes a 4-step approach:
  - Parse the grammar - The grammar is parsed and saved in hash map with the target as key and value as the production statement called the 'node'. 
  - Check for cyclic paths in the grammar - Checks for cycles in the graph as there could be statements such that remodel could run in loops. The program exists if there are cycles in the graph. i.e a is dependent on b and b is dependent on a. Since, one can specify many targets and dependency, a split on the target and dependency is done for additional cyclic checks. For e.g 1) a, b <- c, d 2) c <- e 3) e <- a 
  - Create a vector of tree for all roots - The DEFAULT root may contain multiple targets. Thus it creates a tree for each of the root specified in the grammar. In case the user specifies its own root 'remodel baz', it takes the users root and creates a tree
  - Execute all the trees and its child in threads - For each tree (root targets), a thread is spawned to execute the sequence. For a given tree, all independent statements are executed in parallel. Since, in a given level all statements are independent of each other, we use this information to execute the command and move up each level. Starting with the leaf nodes and executing them in parallel using threads, it is moved up each level till the last root target is executed. MD5 checksum constraint is used to check if there is a change in the dependency for every level, and decide whether to execute the statements. An additional constraint of 'file being present' is used for executing the command. It may happen that another root  running in parallel may have created an output. So, this check ensures that the execution of other target file if a target file is deleted before the execution of the statement. 

Build
-----
The makefile for remodel is present inside the src folder. The remodel requires openssl library for computing md5 checksum. 

Checkout the src code and run make. This should generate remodel as ouput.  

Run
---
remodel also takes two parameters as input
  - the root
  - makefile fiename 

The first will compile only the target mentioned in the parameter. If the second parameter i.e. the filename is specified then it will read the grammar from that file.

remodel by default takes input a file called remodel_makefile. This can be found inside the src folder. This 'Makefile' should be in the same folder as remodel. In order to compile the files using remodel, ensure that the labels/targets reflect the relative path to the dependency. For example, if the dependencies are inside test_cases folder and remodel is up one folder then following will be 'remodel_makefile':

<code>
DEFAULT <- test_cases/baz, test_cases/cow <br/>
test_cases/baz <- test_cases/foo.o, test_cases/bar.o: "g++ test_cases/foo.o test_cases/bar.o -o test_cases/baz"<br/>
test_cases/foo.o <- test_cases/foo.cpp : "g++ -c test_cases/foo.cpp -o test_cases/foo.o"<br/>
test_cases/bar.o <- test_cases/bar.cpp: "g++ -c test_cases/bar.cpp -o test_cases/bar.o"<br/>
test_cases/cow <- test_cases/moo.o, test_cases/zoo.o: "g++ test_cases/zoo.o test_cases/moo.o -o test_cases/cow"<br/>
test_cases/moo.o <- test_cases/moo.cpp : "g++ -c test_cases/moo.cpp -o test_cases/moo.o"<br/>
test_cases/zoo.o <- test_cases/zoo.cpp: "g++ -c test_cases/zoo.cpp -o test_cases/zoo.o"<br/>
</code>


If the dependencies are present in the same folder as remodel executable, no relative path is needed. 

An example that builds the program baz from two source files, foo.cpp and bar.cpp is present inside the src folder

<code>
DEFAULT <- baz <br/>
baz <- foo.o, bar.o: "g++ foo.o bar.o -o baz"<br/>
foo.o <- foo.cpp : "g++ -c foo.cpp -o foo.o"<br/>
bar.o <- bar.cpp: "g++ -c bar.cpp -o bar.o"<br/>
</code>

Testing
-------
Case 1: Using the defuault option
---------------------------------
If inside the src folder type:
<code>
./remodel 
</code>
This should compile output for test_cases/baz and test_cases/cow. Two executables will be created inside the test_cases folder namely cow and baz. 

Case 2: Compiling only a specific target
----------------------------------------
If inside the src folder:
<code>
./remodel test_cases/baz 
</code>
This should compile output for only baz

Case 3: Compiling only a specific target with a user defined makefile
---------------------------------------------------------------------
If inside the src folder:
<code>
./remodel test_cases/baz remodel_makefile
</code>
This should compile output for only baz

Case 4: Check for cycles in the grammar
---------------------------------------
Check for cycles:
<code>
./remodel DEFAULT cyclic_remodel_makefile
</code>

Note: There are two remodel_makefile, one inside the src folder and the other inside test_cases. These two makefiles are present depending on where remodel is executed. In test_cases folder, since dependencies are in the same folder, the target doesn't have relative path appended in the target. 

