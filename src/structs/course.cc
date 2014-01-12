#include <iostream>
#include <structs/course.hh>

std::ostream& operator<<(std::ostream& os, const Course& c) {
    os << "{" << c.getId() << " "
        << c.getStartPoint() << " " << c.getEndPoint() << " "
        << c.getStartTime() << " " << c.getEndTime() << "}";
    return os;
}
