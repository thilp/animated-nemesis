#include <cstdlib>
#include <fstream>
#include <ostream>
#include <iostream>
#include <parsical/parser.hh>
#include <parsical/parser_exception.hh>

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

    Parsical::Parser parser(is);
    try {
        Utils::Option<Course> opt = parser.nextCourse();
        while (opt.defined()) {
            std::cout << opt.get().toString() << std::endl;
            opt = parser.nextCourse();
        }
    }
    catch (Parsical::ParserException e) {
        std::cerr << e.what() << std::endl;
        exit(3);
    }
}
