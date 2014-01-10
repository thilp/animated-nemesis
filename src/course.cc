#include <iostream>
#include <course.hh>

Course::Course(int id, int sp, int ep, int st, int et)
    : id_(id)
    , start_point_(sp)
    , end_point_(ep)
    , start_time_(st)
    , end_time_(et)
{}

std::ostream& operator<<(std::ostream& os, const Course& c) {
    os << "{" << c.getId() << " "
        << c.getStartPoint() << " " << c.getEndPoint() << " "
        << c.getStartTime() << " " << c.getEndTime() << "}";
    return os;
}
