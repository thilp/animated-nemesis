#ifndef OPTION_HXX
# define OPTION_HXX

# include <option.hh>

namespace Utils {

    template <class T>
    Option<T>::Option()
        : value_(nullptr)
    {}

    template <class T>
    Option<T>::Option(const T& value)
        : value_(&value)
    {}

    template <class T>
    Option<T>::Option(const Option<T>& o)
        : value_(o.value_)
    {}

    template <class T>
    bool Option<T>::defined() const { return value_ != nullptr; }

    template <class T>
    const T& Option<T>::get() const throw (OptionException) {
        if (defined()) return *value_;
        else throw OptionException();
    }

    template <class T>
    const T& Option<T>::getOrElse(const T& e) const {
        if (defined()) return *value_;
        else return e;
    }

}

#endif //!OPTION_HXX
