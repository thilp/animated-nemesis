#include <iostream>
#include <structs/course.hh>

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

bool operator<(const Course& a, const Course& b) {
    if (a.getEndTime() == b.getStartTime()) {
        return a.getEndPoint() == b.getStartPoint();
    }
    else { return a.getEndTime() < b.getStartTime(); }
}

bool operator>(const Course& a, const Course& b) {
    if (a.getStartTime() == b.getEndTime()) {
        return a.getStartPoint() == b.getEndPoint();
    }
    else { return a.getStartTime() > b.getEndTime(); }
}

bool Course::compatibleWith(const Course& o) const noexcept {
    return (*this < o) || (*this > o);
}
