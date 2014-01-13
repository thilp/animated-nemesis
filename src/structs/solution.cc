#ifdef DEBUG
# include <iostream>
#endif //DEBUG
#include <cassert>
#include <numeric>
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

static bool checkCourseSeq(const CourseSeq& cs) {
    auto it = cs.cbegin();
    if (it == cs.cend()) { return true; }

    const int startTime = (*it)->getStartTime();

    int lastPoint = (*it)->getEndPoint();
    int lastTime  = (*it)->getEndTime();

    int effectiveWorkTime = lastTime - startTime;

    for (++it; it != cs.cend(); ++it) {
        if (   (*it)->getStartPoint() != lastPoint
            || (*it)->getStartTime() < lastTime)
        {
#ifdef DEBUG
            std::cerr << "checkCourseSeq: ";
            if ((*it)->getStartPoint() != lastPoint) {
                std::cerr << "incompatible places: " << lastPoint
                    << " -> " << (*it)->getStartPoint();
            }
            else {
                std::cerr << "incompatible timing: " << lastTime
                    << " !> " << (*it)->getStartTime();
            }
            std::cerr << std::endl;
#endif //DEBUG
            return false;
        }
        lastPoint = (*it)->getEndPoint();
        lastTime  = (*it)->getEndTime();
        effectiveWorkTime += lastTime - (*it)->getStartTime();
        if (effectiveWorkTime > PROBLEM_MAX_EFFECTIVE_WORKTIME) {
#ifdef DEBUG
            std::cerr << "checkCourseSeq: more than 5 hours of effective work in a day" << std::endl;
#endif //DEBUG
            return false; // more than 5 hours of effective work in a day
        }
    }

    if (lastTime - startTime > PROBLEM_MAX_TOTAL_WORKTIME) {
#ifdef DEBUG
        std::cerr << "checkCourseSeq: more than 7 hours of total work in a day" << std::endl;
#endif //DEBUG
        return false; // more than 7 hours of work in a day
    }

    return true;
}

static int computeTotalWorkTime(const CourseSeq& cs) {
    return cs.back()->getEndTime() - cs.front()->getStartTime();
}

static int computeEffectiveWorkTime(const CourseSeq& cs) {
    int acc = 0;
    for (CoursePtr cptr: cs) {
        acc += cptr->getEndTime() - cptr->getStartTime();
    }
    return acc;
}

// Simulates:
//      cs.insert(it, cptr); return checkCourseSeq(cs);
// without really performing any insertion.
// WARNING: Assume that checkCourseSeq(cs) == true
static bool courseWouldFitInSeq(const CourseSeq& cs,
                                CourseSeq::const_iterator it,
                                const CoursePtr cptr)
{
    assert(checkCourseSeq(cs));
    if (it != cs.cbegin()) {
        --it;
        if (!(**it < *cptr)) {
            return false; // predecessor is not compatible with *it
        }
        ++it;
    }
    if (it != cs.cend() && !(*cptr < **it)) {
        return false; // successor is not compatible with *it
    }

    int cptr_duration = cptr->getEndTime() - cptr->getStartTime();

    int totalWorkTime = computeTotalWorkTime(cs) + cptr_duration;
    if (totalWorkTime > PROBLEM_MAX_TOTAL_WORKTIME) { return false; }

    int effectiveWorkTime = computeEffectiveWorkTime(cs) + cptr_duration;
    if (effectiveWorkTime > PROBLEM_MAX_EFFECTIVE_WORKTIME) { return false; }

    return true;
}

static void transferCourse(CoursePtr c, CourseSeq& from, CourseSeq& to) {
    from.remove(c);
    to.insert(
        std::find_if(to.begin(), to.end(),
                     [&c](CoursePtr o){ return *c < *o; }),
        c
    );
}

static void transferCourseAt(CoursePtr c, CourseSeq& from,
                             CourseSeq& to, CourseSeq::iterator at)
{
    from.remove(c);
    to.insert(at, c);
}

//*
static void factorSolutionDay(SolutionDay& map) {
    // Select 2 random employees of the day.
    size_t  map_size = map.size();
#ifdef DEBUG
    auto _debug_a = ((rand() << 30) ^ (rand() << 15) ^ rand()) % map_size;
    auto _debug_b = ((rand() << 30) ^ (rand() << 15) ^ rand()) % map_size;
    std::cerr << "(factorSolutionDay: chose employees #" << _debug_a
        << " and #" << _debug_b << ")" << std::endl;
    auto map_it_a = map.begin(); std::advance(map_it_a, _debug_a);
    auto map_it_b = map.begin(); std::advance(map_it_b, _debug_b);
#else
    auto map_it_a = map.begin(); std::advance(map_it_a, ((rand() << 30) ^ (rand() << 15) ^ rand()) % map_size);
    auto map_it_b = map.begin(); std::advance(map_it_b, ((rand() << 30) ^ (rand() << 15) ^ rand()) % map_size);
#endif //DEBUG

    // Walk their courses to find "holes" in first's planning that could
    // be filled by courses in the second's.
    CourseSeq::iterator list_it_a = map_it_a->second.begin();
    CourseSeq::iterator list_it_b = map_it_b->second.begin();
    while (list_it_b != map_it_b->second.end()) {
        while (list_it_a != map_it_a->second.end()
               && *(*list_it_a) < *(*list_it_b))
        {
            ++list_it_a;
        }

        if (courseWouldFitInSeq(map_it_a->second,
                                map_it_a->second.cend(),
                                *list_it_b))
        {
            // transfer the first B at the end of the list of A
            transferCourseAt(*list_it_b,
                             map_it_b->second,
                             map_it_a->second,
                             map_it_a->second.end());

            // Did we just change an extremity?
            if (   list_it_a == map_it_a->second.end()
                   || list_it_a == map_it_a->second.begin()
                   || list_it_b == map_it_b->second.begin()
                   || list_it_b == map_it_b->second.end())
            {
                // TODO
            }
            return;
        }

        ++list_it_b;
    }
}//*/

Solution Solution::mutate() const {
#ifdef DEBUG
    std::cerr << "(Solution::mutate)" << std::endl;
#endif //DEBUG
    Solution msol{*this};
    //if (rand() % 2) { // re-arrange in a day
        Utils::Day d = static_cast<Utils::Day>(rand() % 5);
        //if (rand() % 2) { // find adjacent courses
            factorSolutionDay(msol.days[d]);
        //}
        //else {
        //}
    //}
    //else {
    //}
#ifdef DEBUG
    std::cerr << "(end of Solution::mutate) new fitness: "
        << msol.value() << std::endl;
    std::cerr << "(end of Solution::mutate) new solution: "
        << msol << std::endl;
#endif //DEBUG
    return msol;
}

bool operator==(const Solution& a, const Solution& b) {
    return a.days == b.days;
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

static std::ostream& operator<<(std::ostream& os, const CourseSeq& cs) {
    os << "[ ";
    for (auto it = cs.cbegin(); it != cs.cend(); ++it) {
        if (it != cs.cbegin()) { os << ", "; }
        os << **it;
    }
    return os << " ]";
}

static std::ostream& operator<<(std::ostream& os, const SolutionDay& d) {
    os << "{ ";
    for (auto p = d.cbegin(); p != d.cend(); ++p) {
        if (p != d.cbegin()) { os << ", "; }
        os << p->first << ":" << p->second;
    }
    return os << " }";
}

std::ostream& operator<<(std::ostream& os, const Solution& s) {
    os << "{ ";
    unsigned i = 0;
    for (const SolutionDay& d: s.days) {
        if (i != 0) { os << ", "; }
        os << i++ + 1 << ":" << d;
    }
    return os << " }";
}
