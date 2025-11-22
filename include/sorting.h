#ifndef __IMD_SORTING_
#define __IMD_SORTING_

#include <functional>
#include <utility>
#include <type_traits>

namespace IMD
{
    template <typename InputIt, typename Comparator = std::less<typename std::iterator_traits<InputIt>::value_type>>
    void bubble_sort(InputIt beg, InputIt end, Comparator cmp = Comparator())
    {
        if (beg == end)
            return;
        // cmp = <

        for (auto i = beg; i != std::prev(end); ++i)
            for (auto j = std::next(i); j != end; ++j)
                if (cmp(*j, *i))
                    std::swap(*i, *j);
    }

}

#endif