#ifndef EMPLOYEE_DAY_HXX
# define EMPLOYEE_DAY_HXX

# include <structs/employee_day.hh>

EmployeeDay::EmployeeDay(Utils::Day d)
    : day_{d}
{
}

Utils::Day EmployeeDay::getDay() const noexcept {
    return day_;
}

const std::list<Course>& EmployeeDay::getCourses() const noexcept {
    return courses_;
}

#endif //!EMPLOYEE_DAY_HXX
