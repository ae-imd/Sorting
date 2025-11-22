#ifndef __IMD_SORTING_
#define __IMD_SORTING_

#include <functional>
#include <utility>
#include <type_traits>
#include <iterator>
#include <algorithm>

namespace IMD
{
    template <typename InputIt, typename Comparator = std::less<typename std::iterator_traits<InputIt>::value_type>>
    void bubble_sort(InputIt beg, InputIt end, Comparator cmp = Comparator())
    {
        if (beg == end)
            return;
        // cmp = <

        for (auto i = beg; i != std::prev(end); ++i)
        {
            bool flag = false;
            for (auto j = std::next(i); j != end; ++j)
            {
                if (cmp(*j, *i))
                {
                    std::swap(*i, *j);
                    flag = true;
                }
            }
            if (!flag)
                break;
        }
    }

    template <typename InputIt, typename Comparator = std::less<typename std::iterator_traits<InputIt>::value_type>>
    void comb_sort(InputIt beg, InputIt end, Comparator cmp = Comparator())
    {
        if (beg == end)
            return;

        size_t size = std::distance(beg, end);
        size_t gap(std::distance(beg, end));
        double coeff(1.25);
        bool flag(true);

        while (gap > 1 || flag)
        {
            gap = static_cast<size_t>(gap / coeff);
            if (gap == 0)
                gap = 1;

            flag = false;

            for (auto it = beg; it != std::prev(end, gap); ++it)
            {
                auto tmp = std::next(it, gap);
                if (cmp(*tmp, *it))
                {
                    std::iter_swap(tmp, it);
                    flag = true;
                }
            }
        }
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

    template <typename InputIt>
    void counting_sort(InputIt beg, InputIt end)
    {
        static_assert(std::is_integral_v<typename std::iterator_traits<InputIt>::value_type>, "Counting sort requires integer types");

        if (beg == end)
            return;

        auto min_max = std::minmax_element(beg, end);
        auto min_val = *min_max.first;
        auto max_val = *min_max.second;

        size_t size = max_val - min_val + 1;
        size_t *counter = new size_t[size]();
        for (auto it = beg; it != end; ++it)
            ++counter[*it - min_val];

        auto it = beg;
        for (size_t i(0); i < size; ++i)
        {
            std::fill_n(it, counter[i], static_cast<typename std::iterator_traits<InputIt>::value_type>(i + min_val));
            std::advance(it, counter[i]);
        }

        delete[] counter;
    }

}

#endif