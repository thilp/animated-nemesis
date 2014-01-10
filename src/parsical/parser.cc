#include <cstdlib>
#include <parsical/parser.hh>

namespace Parsical {

    Parser::Parser(std::istream& is)
        : lexer_(is), factory_()
    {}

    static int parseTime(Lexical::Lexer& l) throw (ParserException) {
        Lexical::Token tok_h = l.consume();
        if (tok_h.type != Lexical::NUM)
            throw ParserException(tok_h, Lexical::NUM, "hour");
        Lexical::Token tok_sep = l.consume();
        if (tok_sep.type != Lexical::TIMESEP)
            throw ParserException(tok_sep, Lexical::TIMESEP);
        Lexical::Token tok_m = l.consume();
        if (tok_m.type != Lexical::NUM)
            throw ParserException(tok_m, Lexical::NUM, "minute");
        return atoi(tok_h.str.c_str()) * 60 + atoi(tok_m.str.c_str());
    }

    Utils::Option<Course>   Parser::nextCourse() throw (ParserException) {
        if (lexer_.done()) { return Utils::Option<Course>(); }

        Lexical::Token tok_id = lexer_.consume();
        if (tok_id.type != Lexical::NUM)
            throw ParserException(tok_id, Lexical::NUM, "id");

        Lexical::Token tok_start_p = lexer_.consume();
        if (tok_start_p.type != Lexical::OTHER)
            throw ParserException(tok_start_p, Lexical::OTHER, "departure place");

        Lexical::Token tok_end_p = lexer_.consume();
        if (tok_end_p.type != Lexical::OTHER)
            throw ParserException(tok_end_p, Lexical::OTHER, "arrival place");

        int start_t = parseTime(lexer_);
        int end_t = parseTime(lexer_);
        return factory_.makeCourse(atoi(tok_id.str.c_str()),
                                   tok_start_p.str.c_str(),
                                   tok_end_p.str.c_str(),
                                   start_t,
                                   end_t);
    }

}
