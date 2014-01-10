#ifndef PARSER_HH
# define PARSER_HH

# include <exception>
# include <fstream>
# include <option.hh>
# include <lexical/lexer.hh>
# include <course.hh>
# include <course_factory.hh>

namespace Parsical {

    class Parser {
    public:
        Parser(std::istream& is);
        Utils::Option<Course> nextCourse() throw (ParserException);

    private:
        Lexical::Lexer  lexer_;
        CourseFactory   factory_;
    };

} // namespace Parsical

#endif //!PARSER_HH
