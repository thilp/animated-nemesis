#include <parsical/parser_exception.hh>

namespace Parsical {

    static const char* ttypeToString(Lexical::TokenType ttype) {
        switch (ttype) {
        case Lexical::NUM:          return "number";
        case Lexical::TIMESEP:      return "time separator";
        case Lexical::END_OF_LINE:  return "end of line";
        case Lexical::END_OF_FILE:  return "end of file";
        case Lexical::OTHER:        return "alphabetical sequence";
        case Lexical::_IGNORABLE:   return "(ignorable character sequence)";
        default:                    return "(unknown)";
        }
    }

    ParserException::ParserException(Lexical::Token got,
                                     Lexical::TokenType expected)
    {
        sprintf(str_, "parser: got %s \"%s\" but expected %s",
                ttypeToString(got.type), got.str.c_str(),
                ttypeToString(expected));
    }

    ParserException::ParserException(Lexical::Token got,
                                     Lexical::TokenType expected,
                                     const char* when)
    {
        sprintf(str_, "parser: got %s \"%s\" but expected %s when parsing %s",
                ttypeToString(got.type), got.str.c_str(),
                ttypeToString(expected),
                when);
    }

    const char* ParserException::what() const noexcept {
        return const_cast<const char*>(str_);
    }

}
