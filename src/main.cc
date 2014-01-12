#define _POSIX_SOURCE //for sigaction

#include <cassert>
#include <csignal>
#include <cstdlib>
#include <fstream>
#include <ostream>
#include <iostream>
#include <vector>
#include <parsical/parser.hh>
#include <parsical/parser_exception.hh>
#include <structs/course.hh>
#include <tabu.hh>

# define PRINT_EACH_NTH 10

static void print_usage(std::ostream& os, const char* appname) {
    os << "Usage: " << appname << " <filename>" << std::endl;
}

static bool search_run = true;

void signal_handler(int) {
    search_run = false;
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

    Parsical::Parser parser{is};
    auto courses = std::vector<Course>{};
    try {
        while (!parser.done()) { courses.emplace_back(parser.nextCourse()); }
    }
    catch (const Parsical::ParserException& e) {
        std::cerr << e.what() << std::endl;
        return 3;
    }

    struct sigaction ssigaction;
    ssigaction.sa_handler = &signal_handler;
    sigemptyset(&ssigaction.sa_mask);
    ssigaction.sa_flags = 0;
    sigaction(SIGINT, &ssigaction, nullptr);

    Tabu search{10, courses};
    assert(search.currentSolution().valid());
    return 33;

    unsigned long rounds = 0;
    while (search_run) {
        if (rounds % PRINT_EACH_NTH == 0) {
            std::cout << "Current best value for round " << rounds
                << " is: " << search.currentBestValue() << std::endl;
        }
        search.derive();
        rounds += 1;
    }
}
