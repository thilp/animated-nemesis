#include <structs/employee.hh>

unsigned int Employee::base_id_ = 0;

Employee::Employee()
    : id_{base_id_++}
    , days_{{
        EmployeeDay{Utils::MON},
        EmployeeDay{Utils::TUE},
        EmployeeDay{Utils::WED},
        EmployeeDay{Utils::THU},
        EmployeeDay{Utils::FRI}
    }}
{
}
