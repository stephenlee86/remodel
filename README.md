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
