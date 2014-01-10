#include <option.hh>

namespace Utils {

    const char* OptionException::what() const noexcept {
        return "Forced access to an undefined option value";
    }

} //namespace Utils
