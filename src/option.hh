#ifndef OPTION_HH
# define OPTION_HH

# include <exception>

namespace Utils {

    class OptionException: public std::exception {
        virtual const char* what() const noexcept override;
    };

    template <class T>
    class Option {
    public:
        Option();
        Option(const T& value);
        Option(const Option<T>&);

        bool        defined() const;
        const T&    get() const throw (OptionException);
        const T&    getOrElse(const T& e) const;

    private:
        const T*    value_;
    };
}

# include <option.hxx>

#endif //!OPTION_HH
