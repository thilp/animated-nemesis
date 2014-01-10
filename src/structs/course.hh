#ifndef COURSE_HH
# define COURSE_HH

# include <string>
# include <ostream>

class Course {
public:
    Course() = default; // dummy
    Course(int id,
           int startPoint,
           int endPoint,
           int startTime,
           int endTime);

    int getId() const noexcept { return id_; }
    int getStartPoint() const noexcept { return start_point_; }
    int getEndPoint() const noexcept { return end_point_; }
    int getStartTime() const noexcept { return start_time_; }
    int getEndTime() const noexcept { return end_time_; }

    bool compatibleWith(const Course&) const noexcept;

private:
    int id_;
    int start_point_;
    int end_point_;
    int start_time_;
    int end_time_;
};

/* Display */
std::ostream& operator<<(std::ostream&, const Course&);

/* Time-based comparisons */
bool operator<(const Course&, const Course&);
bool operator>(const Course&, const Course&);

#endif //!COURSE_HH
