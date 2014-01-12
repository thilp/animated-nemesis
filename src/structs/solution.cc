#include <cstdlib>
#include <future>
#include <iterator>
#include <thread>
#include <unordered_set>
#include <utility>
#include <utils/day.hh>
#include <structs/solution.hh>

Solution::Solution(const std::vector<Course>& courses) {
    unsigned i = 0;
    for (unsigned d = Utils::MON; d <= Utils::FRI; ++d) {
        for (const Course& c: courses) {
            days[d][i++] = CourseSeq(1, &c);
        }
    }
}

unsigned Solution::value() const {
    std::unordered_set<unsigned> set;
    for (const SolutionDay& d: days) {
        auto dcend = d.cend();
        for (auto it = d.cbegin(); it != dcend; ++it) {
            set.insert(it->first);
        }
    }
    return set.size();
}

/*
static void factorSolutionDay(SolutionDay& map) {
    // Select 2 random employees of the day.
    size_t  map_size = map.size();
    auto a = map.begin(); std::advance(a, rand() % map_size);
    auto b = map.begin(); std::advance(b, rand() % map_size);
    auto map_end = map.cend();

    // Walk their courses to find "holes" in the first's planning that could
    // be filled by courses in the second's.
    while (b != map_end) {
        while (a != map_end && *a->second < *b->second) { a.next(); }
        if (a == map_end) { // don't care about extremities
            break;
        }
        else {
        }
        b.next();
    }
}//*/

static void transferCourse(CoursePtr c, CourseSeq& from, CourseSeq& to) {
    from.remove(c);
    to.insert(
        std::find_if(to.begin(), to.end(),
                     [&c](CoursePtr o){ return *c < *o; }),
        c
    );
}

Solution Solution::mutate() const {
    Solution msol{*this};
    if (rand() % 2) { // re-arrange in a day
        Utils::Day d = static_cast<Utils::Day>(rand() % 5);
        if (rand() % 2) { // find adjacent courses
            //factorSolutionDay(msol.days[d]);
        }
        else {
        }
    }
    else {
    }
    return msol;
}

bool operator==(const Solution& a, const Solution& b) {
    return a.days == b.days;
}

static bool checkCourseSeq(const CourseSeq& cs) {
    auto it = cs.cbegin();
    if (it == cs.cend()) { return true; }
    int lastPoint = (*it)->getEndPoint();
    int lastTime  = (*it)->getEndTime();
    for (++it; it != cs.cend(); ++it) {
        if (   (*it)->getStartPoint() != lastPoint
            || (*it)->getStartTime() < lastTime)
        {
            return false;
        }
        lastPoint = (*it)->getEndPoint();
        lastTime  = (*it)->getEndTime();
    }
    return true;
}

bool Solution::valid(const SolutionDay& d) {
    std::list<std::future<bool>> list;
    for (auto p: d) {
        list.emplace(
            list.end(),
            std::async(std::launch::async,
                       checkCourseSeq,
                       p.second)
        );
    }
    return std::all_of(
        list.cbegin(), list.cend(),
        [](const std::future<bool>& f){
            return const_cast<std::future<bool>&>(f).get();
        }
    );
}

IdList Solution::intersectEmployees(const SolutionDay& a, const SolutionDay& b) {
    auto f = [](const SolutionDay& s, IdSet& set) {
        for (auto p: s) { set.insert(p.first); }
    };
    IdSet set_a{};
    IdSet set_b{};
    IdList l_final{};
    std::thread ta{f, std::cref(a), std::ref(set_a)};
    f(b, set_b);
    ta.join();
    std::set_intersection(set_a.cbegin(), set_a.cend(),
                          set_b.cbegin(), set_b.cend(),
                          l_final.begin());
    return l_final;
}

bool Solution::valid() const {
    auto sda = days.cbegin();
    if (!valid(*sda)) return false;

    auto sdb = days.cbegin() + 1;
    IdList intersection;
    while (sdb != days.cend()) {
        if (!valid(*sdb)) return false;
        intersection = intersectEmployees(*sda, *sdb);
        for (unsigned id: intersection) {
            if (   sda->at(id).back()->getEndPoint()
                != sdb->at(id).front()->getStartPoint())
            {
                return false;
            }
        }
        ++sda;
        ++sdb;
    }
    return true;
}
