CC = g++
CFLAGS = -std=c++17 -g

LIBPATH = -L/usr/local/lib
LINK 	= -lantlr4-runtime
INCLUDE = -I/usr/local/include/antlr4-runtime 
ANTLR 	= java -Xmx500M -cp "/usr/local/lib/antlr-4.7.1-complete.jar:$CLASSPATH" org.antlr.v4.Tool

all: antlr parsertestexe 

parsertestexe: src/query.o parser/lexer.o parser/parser.o main.o
	$(CC) $^ $(INCLUDE) $(LINK) $(LIBPATH) $(CFLAGS) -o $@

parser/parser.o: parser/ToySQLParser.cpp
	$(CC) $^ $(INCLUDE) $(LINK) $(LIBPATH) $(CFLAGS) -c -o $@

parser/lexer.o: parser/ToySQLLexer.cpp 
	$(CC) $^ $(INCLUDE) $(LINK) $(LIBPATH) $(CFLAGS) -c -o $@

main.o: main.cpp
	$(CC) $^ $(INCLUDE) $(LINK) $(LIBPATH) $(CFLAGS) -c

src/query.o: src/Query.cpp 
	$(CC) $^ $(CFLAGS) -c -o $@

antlr: parser/ToySQL.g4 
	$(ANTLR) $^ -Dlanguage=Cpp -no-listener -visitor

test:	
	cd tests/ && ./run.sh	

clean:
	rm -f parsertestexe 
	rm -f query.o lexer.o parser.o main.o 

.PHONY: all clean
