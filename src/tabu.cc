#include <cassert>
#include <algorithm>
#include <tabu.hh>

Tabu::Tabu(const unsigned tabu_list_size,
           const std::vector<Course>& courses)
    : tabu_list_size_{tabu_list_size}
    , solution_{courses}
    , tabu_list_{tabu_list_size, solution_}
{
}

void Tabu::derive() {
    assert(tabu_list_.size() == tabu_list_size_);
    Solution old{solution_};
    do {
        solution_ = old.mutate();
    } while (std::any_of(tabu_list_.cbegin(), tabu_list_.cend(),
                         [this](const Solution& s){ return s == solution_; }));
    tabu_list_.push_back(solution_);
    tabu_list_.pop_front();
}
