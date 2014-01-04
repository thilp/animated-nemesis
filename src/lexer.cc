#include <cassert>
#include "lexer.hh"

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


    /* Lexer */

    Lexer::Lexer(std::istream& is)
        : input_stream_(is)
          , next_token_(_IGNORABLE)
          , buff_(*(new std::string))
          , buff_offset_(-1)
    {}

    bool Lexer::fillBuffer()
    {
        if (input_stream_.eof()) return false;

        std::getline(input_stream_, buff_);
        buff_offset_ = 0;
        buff_size_ = buff_.size();
        return true;
    }

    static TokenType charToTokenType(char c)
    {
        if (c >= '0' && c <= '9') {
            return NUM;
        }
        else if (c == ' ' || c == '\t' || c == '\n' || c == '\r') {
            return _IGNORABLE;
        }
        else if (c == ':')          return TIMESEP;
        else if (c == '\n')         return END_OF_LINE;
        else                        return OTHER;
    }

    void Lexer::getNextToken()
    {
        if (buff_offset_ < 0 && !fillBuffer()) {
            next_token_.type = END_OF_FILE;
            return;
        }

        const size_t last_offset = buff_size_ - 1;

        TokenType ttype = _IGNORABLE;
        while (ttype == _IGNORABLE) {
            do {
                ttype = charToTokenType(buff_[buff_offset_]);
            } while (   ttype == _IGNORABLE
                        && static_cast<size_t>(++buff_offset_) <= last_offset);
            if (ttype == _IGNORABLE && !fillBuffer()) {
                next_token_.type = END_OF_FILE;
                return;
            }
        }
        next_token_.type = ttype;

        size_t offset = buff_offset_;
        if (   ttype == TIMESEP || ttype == END_OF_LINE) {
            next_token_.str = "";
        }
        else {
            while (++offset <= last_offset && charToTokenType(buff_[offset]) == ttype);
            next_token_.str = buff_.substr(buff_offset_, offset - buff_offset_);
        }

        buff_offset_ = static_cast<size_t>(buff_offset_) + 1 >= buff_size_
            ? -1
            : buff_offset_ + 1;
    }

    Token& Lexer::lookup() const
    {
        return *(new Token(next_token_));
    }

    Token& Lexer::consume()
    {
        Token* now = new Token(next_token_);
        getNextToken();
        return *now;
    }
}
