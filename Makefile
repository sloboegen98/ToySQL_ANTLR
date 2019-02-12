CC = g++
LIBPATH = -L/usr/local/lib
LINK = -lantlr4-runtime
INCLUDE = -I/usr/local/include/antlr4-runtime 

all: parser

#antlr:
#	antlr4 ToySQL.g4 -Dlanguage=Cpp -no-visitor -no-listener

parser:
	$(CC) ToySQL*.cpp main.cpp Query.cpp $(INCLUDE) $(LINK) $(LIBPATH) -std=c++17 -o parsertestexe

clean:
	rm -rf *.o