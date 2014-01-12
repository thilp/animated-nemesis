#ifndef TABU_HH
# define TABU_HH

# include <deque>
# include <vector>
# include <structs/course.hh>
# include <structs/solution.hh>

class Tabu {
public:
    Tabu(unsigned tabu_list_size, const std::vector<Course>& courses);

    unsigned currentBestValue() const { return solution_.value(); }
    Solution currentSolution() const { return solution_; }
    void derive();

private:
    const unsigned              tabu_list_size_;
    Solution                    solution_;
    std::deque<Solution>        tabu_list_;
};

#endif //!TABU_HH
