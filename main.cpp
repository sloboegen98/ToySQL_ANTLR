#include <iostream>
#include <vector>
#include <string>
#include <strstream>
#include "antlr4-runtime.h"
#include "ToySQLLexer.h"
#include "ToySQLParser.h"

class MyParserErrorListener: public antlr4::BaseErrorListener {
  virtual void syntaxError(
      antlr4::Recognizer *recognizer,
      antlr4::Token *offendingSymbol,
      size_t line,
      size_t charPositionInLine,
      const std::string &msg,
      std::exception_ptr e) override {
    std::ostrstream s;
    s << "Line(" << line << ":" << charPositionInLine << ") Error(" << msg << ")";
    throw std::invalid_argument(s.str());
  }
};

int main(int argc, char *argv[]) {
    std::ifstream str;
    str.open(argv[1]);
    antlr4::ANTLRInputStream input(str);
    ToySQLLexer lexer(&input);
    antlr4::CommonTokenStream tokens(&lexer);
//
    MyParserErrorListener errorListner;

    tokens.fill();
    // Only if you want to list the tokens
    // for (auto token : tokens.getTokens()) {
    //  std::cout << token->toString() << std::endl;
    // }
    
    ToySQLParser parser(&tokens);
    parser.removeErrorListeners();
    parser.addErrorListener(&errorListner);
    try {
        antlr4::tree::ParseTree* tree = parser.query();
        std::cout << tree->toStringTree(&parser) << std::endl;
        (parser.q).print();
        
        return 0;
    } catch (std::invalid_argument &e) {
        std::cout << e.what() << std::endl;
        return 10;
    }
}