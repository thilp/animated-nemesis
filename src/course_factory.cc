#include <cstring>
#include <course_factory.hh>

Course& CourseFactory::makeCourse(int id,
                                  const char* startPoint,
                                  const char* endPoint,
                                  int startTime,
                                  int endTime)
{
    int sp = -1;
    {
        auto it = map_.find(startPoint);
        if (it == map_.end()) {
            sp = base_pointID_;
            map_[startPoint] = base_pointID_++;
            vect_.push_back(startPoint);
        }
        else sp = it->second;
    }

    int ep = -1;
    {
        auto it = map_.find(endPoint);
        if (it == map_.end()) {
            ep = base_pointID_;
            map_[endPoint] = base_pointID_++;
            vect_.push_back(endPoint);
        }
        else ep = it->second;
    }

    return *(new Course(id, sp, ep, startTime, endTime));
}

const std::string& CourseFactory::idToPoint(int id) const
{
    return *(new std::string(vect_.at(id)));
}
