#ifndef LEXER_HH
# define LEXER_HH

# include <fstream>
# include <string>

namespace Lexical {


    enum TokenType {
        NUM,
        TIMESEP,
        END_OF_LINE,
        END_OF_FILE,
        OTHER,
        _IGNORABLE,
    };


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
    };


    class Lexer {
    public:
        Lexer(std::istream& is);

        Token& lookup() const;
        Token& consume();

    private:
        bool    fillBuffer();
        void    getNextToken();
        bool    ensureIsReadable();

    private:
        std::istream&   input_stream_;
        _MutableToken   next_token_;
        std::string&    buff_;
        size_t          buff_size_;
        int             buff_offset_;
    };


} //namespace Lexical

#endif //!LEXER_HH
