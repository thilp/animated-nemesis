#ifndef SOLUTION_HH
# define SOLUTION_HH

# include <algorithm>
# include <array>
# include <list>
# include <unordered_map>
# include <set>
# include <ostream>
# include <structs/course.hh>

# define PROBLEM_MAX_TOTAL_WORKTIME     (7 * 60)
# define PROBLEM_MAX_EFFECTIVE_WORKTIME (5 * 60)

using CoursePtr     = const Course*;
using CourseSeq     = std::list<CoursePtr>;
using SolutionDay   = std::unordered_map<unsigned, CourseSeq>;
using IdSet         = std::set<unsigned>;
using IdList        = std::list<unsigned>;

struct Solution {
    std::array<SolutionDay, 5>  days;

    Solution(const std::vector<Course>& courses);

    unsigned value() const;

    /**
     * Returns a Solution slightly different from *this and with at least the
     * same value.
     */
    Solution mutate() const;

    static IdList intersectEmployees(const SolutionDay&, const SolutionDay&);
    static bool valid(const SolutionDay&);
    bool valid() const;
};

bool operator==(const Solution&, const Solution&);

std::ostream& operator<<(std::ostream&, const Solution&);

#endif //!SOLUTION_HH
