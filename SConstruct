env = Environment(
    CXX = 'g++',
    CPPFLAGS = ['-O0', '-std=c++17', '-Wall', '-g']
)

Execute('java -Xmx500M -cp "/usr/local/lib/antlr-4.7.1-complete.jar:$CLASSPATH" org.antlr.v4.Tool parser/ToySQL.g4 -Dlanguage=Cpp -no-listener -visitor')

antlr = env.File('/usr/local/lib/libantlr4-runtime.so')

parser = env.Object(target = 'parser/parser.o',
                    source = 'parser/ToySQLParser.cpp',
                    LIBS = [antlr],
                    CPPPATH = ['/usr/local/include/antlr4-runtime'])

lexer = env.Object(target = 'parser/lexer.o',
                   source = 'parser/ToySQLLexer.cpp',
                   LIBS = [antlr],
                   CPPPATH = ['/usr/local/include/antlr4-runtime'])

main = env.Object(target = 'main.o',
                  source = 'main.cpp', 
                  LIBS = [antlr],
                  CPPPATH = ['/usr/local/include/antlr4-runtime'])

query = env.Object(target = 'src/query.o',
                   source = 'src/Query.cpp')

parser_obj = File('parser/parser.o')
lexer_obj = File('parser/lexer.o')
query_obj = File('src/query.o')
main_obj = File('main.o')

parsertestexe = Program (target = 'parsertestexe',
                         source = [parser_obj, lexer_obj, query_obj, main_obj], 
                         LIBS = [antlr],
                         CPPPATH = ['/usr/local/include/antlr4-runtime'])
