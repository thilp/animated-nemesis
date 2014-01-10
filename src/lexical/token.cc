#include <lexical/token.hh>

namespace Lexical {

    /* _MutableToken */

    _MutableToken::_MutableToken(TokenType ttype)
        : str(*(new std::string)), type(ttype)
    {}

    _MutableToken::_MutableToken(std::string& string,
                                 TokenType ttype)
        : str(string), type(ttype)
    {}


    /* Token */

    Token::Token(TokenType ttype)
        : str(*(new std::string)), type(ttype)
    {}

    Token::Token(const std::string& string, TokenType ttype)
        : str(string), type(ttype)
    {}

    Token::Token(const _MutableToken& mtoken)
        : str(mtoken.str), type(mtoken.type)
    {}

    void Token::ensure(TokenType ttype) const throw (Parsical::ParserException) {
        if (type != ttype) throw Parsical::ParserException(*this, ttype);
    }

}
