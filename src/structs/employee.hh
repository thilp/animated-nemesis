#ifndef EMPLOYEE_HH
# define EMPLOYEE_HH

# include <array>
# include <structs/employee_day.hh>

using Week = std::array<EmployeeDay, 5>;

class Employee {
public:
    Employee();

    inline unsigned int getId() const noexcept;
    inline Week&        days() noexcept;

private:
    const unsigned int  id_;
    Week                days_;

    static unsigned int base_id_;
};

# include <structs/employee.hxx>

#endif //!EMPLOYEE_HH
