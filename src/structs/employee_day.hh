#ifndef EMPLOYEE_DAY_HH
# define EMPLOYEE_DAY_HH

# include <list>
# include <ostream>
# include <utils/day.hh>
# include <structs/course.hh>

class EmployeeDay {
public:
    inline EmployeeDay(Utils::Day); // "empty" ctor

    inline Utils::Day               getDay()        const noexcept;
    inline const std::list<Course>& getCourses()    const noexcept;

    bool addCourse(const Course&);

    std::ostream& serialize(std::ostream&, unsigned employee_id) const;

private:
    const Utils::Day    day_;
    std::list<Course>   courses_;
};

# include <structs/employee_day.hxx>

#endif //!EMPLOYEE_DAY_HH
