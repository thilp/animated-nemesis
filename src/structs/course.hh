#ifndef COURSE_HH
# define COURSE_HH

# include <string>
# include <ostream>
# include <utils/day.hh>

class Course {
public:
    Course() = default; // dummy
    inline constexpr Course(int id,
                            int startPoint, int endPoint,
                            int startTime, int endTime);

    constexpr int getId() const noexcept { return id_; }
    constexpr int getStartPoint() const noexcept { return start_point_; }
    constexpr int getEndPoint() const noexcept { return end_point_; }
    constexpr int getStartTime() const noexcept { return start_time_; }
    constexpr int getEndTime() const noexcept { return end_time_; }

    inline constexpr bool compatibleWith(const Course&) const noexcept;

private:
    const int id_;
    const int start_point_;
    const int end_point_;
    const int start_time_;
    const int end_time_;
};

/* Display */
std::ostream& operator<<(std::ostream&, const Course&);

/* Time- and location-based comparisons */
inline constexpr bool operator==(const Course&, const Course&);
inline constexpr bool operator<(const Course&, const Course&);
inline constexpr bool operator>(const Course&, const Course&);

# include <structs/course.hxx>

#endif //!COURSE_HH
