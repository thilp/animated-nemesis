#ifndef COURSE_FACTORY_HH
# define COURSE_FACTORY_HH

# include <string>
# include <unordered_map>
# include <vector>
# include "course.hh"

class CourseFactory {
public:
    Course& makeCourse(int id,
                       const char* startPoint,
                       const char* endPoint,
                       int startTime,
                       int endTime);

    const std::string& idToPoint(int id) const;

private:
    int base_pointID_;
    std::unordered_map<const char*, int> map_;
    std::vector<const char*> vect_;
};

#endif //!COURSE_FACTORY_HH
