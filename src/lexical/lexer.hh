#ifndef LEXER_HH
# define LEXER_HH

# include <fstream>
# include <string>
# include <lexical/token.hh>

namespace Lexical {

    class Lexer {
    public:
        Lexer(std::istream& is);

        bool    done() const;
        Token&  lookup() const;
        Token&  consume();

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
