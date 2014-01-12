#ifndef EMPLOYEE_HXX
# define EMPLOYEE_HXX

# include <structs/employee.hh>

unsigned int Employee::getId() const noexcept { return id_; }

Week&       Employee::days()  noexcept { return days_; }
const Week& Employee::cdays() const noexcept { return days_; }

#endif //!EMPLOYEE_HXX
