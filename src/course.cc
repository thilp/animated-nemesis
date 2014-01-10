#include <cstdio>
#include <course.hh>

Course::Course(int id, int sp, int ep, int st, int et)
    : id_(id)
    , start_point_(sp)
    , end_point_(ep)
    , start_time_(st)
    , end_time_(et)
{}

const char* Course::toString() const noexcept {
    char* str = new char[128];
    sprintf(str, "{%d %d %d %d %d}",
            id_, start_point_, end_point_, start_time_, end_time_);
    return str;
}
