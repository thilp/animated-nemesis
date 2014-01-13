#ifndef COURSE_HXX
# define COURSE_HXX

# include <structs/course.hh>

constexpr Course::Course(int id, int sp, int ep, int st, int et)
    : id_(id)
    , start_point_(sp)
    , end_point_(ep)
    , start_time_(st)
    , end_time_(et)
{}

constexpr bool operator<(const Course& a, const Course& b) {
    return a.getEndPoint() == b.getStartPoint()
        && a.getEndTime() < b.getStartTime();
}

constexpr bool operator>(const Course& a, const Course& b) {
    return a.getStartPoint() == b.getEndPoint()
        && a.getStartTime() > b.getEndTime();
}

constexpr bool Course::compatibleWith(const Course& o) const noexcept {
    return (*this < o) || (*this > o);
}

constexpr bool operator==(const Course& a, const Course& b) {
    return a.getStartPoint()    == b.getStartPoint()
        && a.getEndPoint()      == b.getEndPoint()
        && a.getStartTime()     == b.getStartTime()
        && a.getEndTime()       == b.getEndTime();
}

#endif //!COURSE_HXX
