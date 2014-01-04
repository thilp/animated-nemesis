#include <cstdlib>
#include <fstream>
#include <ostream>
#include <iostream>
#include "lexer.hh"

static void print_usage(std::ostream& os, const char* appname) {
    os << "Usage: " << appname << " <filename>" << std::endl;
}

int main(int argc, char **argv) {
    if (argc < 2) {
        print_usage(std::cerr, argv[0]);
        exit(1);
    }
    std::ifstream is(argv[1]);
    if (!is.good()) {
        std::cerr << "Error: can't read from " << argv[1] << std::endl;
        exit(2);
    }
    Lexical::Lexer lex(is);
}
