#include <algorithm>
#include <structs/employee_day.hh>

bool EmployeeDay::addCourse(const Course& c) {
    auto it = std::find_if(courses_.begin(), courses_.end(),
                           [&c](const Course& e){ return e < c; });
    if (*it > c) { courses_.insert(it, c); return true; }
    else { return false; }
}

std::ostream& EmployeeDay::serialize(std::ostream& os,
                                     const unsigned int emp_id) const
{
    os << emp_id << " " << day_;
    for (const Course& c: courses_) {
        os << " " << c.getId();
    }
    return os << std::endl;
}
