#ifndef PARSER_HH
# define PARSER_HH

# include <exception>
# include <fstream>
# include <utils/option.hh>
# include <lexical/lexer.hh>
# include <course.hh>
# include <course_factory.hh>

namespace Parsical {

    class Parser {
    public:
        Parser(std::istream& is);
        Course nextCourse() throw (ParserException);
        bool done() const noexcept { return lexer_.done(); }

    private:
        Lexical::Lexer  lexer_;
        CourseFactory   factory_;
    };

} // namespace Parsical

#endif //!PARSER_HH
