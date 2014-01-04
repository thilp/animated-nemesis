#ifndef COURSE_HH
# define COURSE_HH

class Course {
public:
    Course(int id,
           int startPoint,
           int endPoint,
           int startTime,
           int endTime);

private:
    int id_;
    int start_point_;
    int end_point_;
    int start_time_;
    int end_time_;
};

#endif //!COURSE_HH
