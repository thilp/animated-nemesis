#include <cstdlib>
#include <fstream>
#include <ostream>
#include <iostream>
#include <vector>
#include <parsical/parser.hh>
#include <parsical/parser_exception.hh>
#include <structs/course.hh>

static void print_usage(std::ostream& os, const char* appname) {
    os << "Usage: " << appname << " <filename>" << std::endl;
}

int main(int argc, char **argv) {
    if (argc < 2) {
        print_usage(std::cerr, argv[0]);
        return 1;
    }
    std::ifstream is(argv[1]);
    if (!is.good()) {
        std::cerr << "Error: can't read from " << argv[1] << std::endl;
        return 2;
    }

    Parsical::Parser parser(is);
    auto courses = std::vector<Course>{};
    try {
        while (!parser.done()) { courses.emplace_back(parser.nextCourse()); }
    }
    catch (const Parsical::ParserException& e) {
        std::cerr << e.what() << std::endl;
        return 3;
    }

    for (auto c: courses) { std::cout << c << std::endl; }
}
