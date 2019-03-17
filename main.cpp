#include <iostream>
#include <vector>
#include <string>
#include <strstream>

#include "antlr4-runtime.h"
#include "parser/ToySQLLexer.h"
#include "parser/ToySQLParser.h"

#include "parser/MyVisitor.h"
#include "src/Query.h"

int main(int args, char* argv[]) {

    std::ifstream input_string;
    input_string.open(argv[1]);
    antlr4::ANTLRInputStream input(input_string);

    ToySQLLexer lexer(&input);
    antlr4::CommonTokenStream tokens(&lexer);

    ToySQLParser parser(&tokens);

    antlr4::tree::ParseTree *tree = parser.query();

    MyVisitor* visitor = new MyVisitor(); 

    visitor->visit(tree);
    
    Query q = visitor->get();
    q.print();

    return 0;
}