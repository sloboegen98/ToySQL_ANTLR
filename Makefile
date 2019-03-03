CC = g++
LIBPATH = -L/usr/local/lib
LINK 	= -lantlr4-runtime
INCLUDE = -I/usr/local/include/antlr4-runtime 
ANTLR 	= java -Xmx500M -cp "/usr/local/lib/antlr-4.7.1-complete.jar:$CLASSPATH" org.antlr.v4.Tool

all: antlr parsertestexe 

parsertestexe: query.o lexer.o parser.o main.o
	$(CC) main.o query.o lexer.o parser.o $(INCLUDE) $(LINK) $(LIBPATH) -std=c++17 -o parsertestexe 

parser.o: ToySQLParser.cpp ToySQLParser.h
	$(CC) ToySQLParser.cpp $(INCLUDE) $(LINK) $(LIBPATH) -std=c++17 -c -o parser.o

lexer.o: ToySQLLexer.cpp ToySQLLexer.h
	$(CC) ToySQLLexer.cpp $(INCLUDE) $(LINK) $(LIBPATH) -std=c++17 -c -o lexer.o

main.o: main.cpp
	$(CC) main.cpp $(INCLUDE) $(LINK) $(LIBPATH) -std=c++17 -c

query.o: Query.cpp Query.h
	$(CC) Query.cpp -c -o query.o

antlr:
	$(ANTLR) ToySQL.g4 -Dlanguage=Cpp -no-listener -visitor

clean:
	rm -rf query.o lexer.o parser.o main.o

.PHONY: all clean
