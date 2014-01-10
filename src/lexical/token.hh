#ifndef TOKEN_HH
# define TOKEN_HH

# include <string>

// Forward declarations

namespace Lexical {

    enum TokenType {
        NUM,
        TIMESEP,
        END_OF_LINE,
        END_OF_FILE,
        OTHER,
        _IGNORABLE,
    };

    struct _MutableToken;
    struct Token;
}

# include <parsical/parser_exception.hh>

namespace Lexical {

    struct _MutableToken {
        _MutableToken(TokenType);
        _MutableToken(std::string&, TokenType);

        std::string&  str;
        TokenType     type;
    };

    struct Token {
        Token(TokenType);
        Token(const std::string&, TokenType);
        Token(const _MutableToken&);

        const std::string&  str;
        const TokenType     type;

        void ensure(TokenType) const throw (Parsical::ParserException);
    };

}

#endif //!TOKEN_HH
