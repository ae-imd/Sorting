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

    template <typename InputIt, typename Comparator = std::less<typename std::iterator_traits<InputIt>::value_type>>
    void insertion_sort(InputIt beg, InputIt end, Comparator cmp = Comparator())
    {
        if (beg == end)
            return;
        // cmp = <

        for (auto i = std::next(beg); i != end; ++i)
        {
            auto key = std::move(*i);
            auto j = i;

            while (j != beg && cmp(key, *std::prev(j)))
            {
                *j = std::move(*std::prev(j));
                --j;
            }

            *j = std::move(key);
        }
    }

    template <typename InputIt, typename Comparator = std::less<typename std::iterator_traits<InputIt>::value_type>>
    void selection_sort(InputIt beg, InputIt end, Comparator cmp = Comparator())
    {
        if (beg == end)
            return;
        // cmp = <

        for (auto i = beg; i != end; ++i)
        {
            auto min_it = i;
            for (auto j = std::next(i); j != end; ++j)
                if (cmp(*j, *min_it))
                    min_it = j;

            if (min_it != i)
                std::iter_swap(i, min_it);
        }
    }

}

#endif