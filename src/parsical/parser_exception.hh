#ifdef TOKEN_HH
# ifndef PARSER_EXCEPTION_HH
#  define PARSER_EXCEPTION_HH

# include <exception>

namespace Parsical {

    class ParserException: public std::exception {
    public:
        ParserException(Lexical::Token      got,
                        Lexical::TokenType  expected);

        ParserException(Lexical::Token      got,
                        Lexical::TokenType  expected,
                        const char*         when);

        virtual const char* what() const noexcept override;

    private:
        char str_[128];
    };

}

# endif //!PARSER_EXCEPTION_HH
#else
# include <lexical/token.hh>
#endif //TOKEN_HH
