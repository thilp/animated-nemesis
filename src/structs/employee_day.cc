#include <algorithm>
#include <structs/employee_day.hh>

bool EmployeeDay::addCourse(const Course& c) {
    auto it = std::find_if(courses_.begin(), courses_.end(),
                           [&c](const Course& e){ return e < c; });
    if (*it > c) { courses_.insert(it, c); return true; }
    else { return false; }
}
