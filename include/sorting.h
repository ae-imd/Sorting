#ifndef __IMD_SORTING_
#define __IMD_SORTING_

#include <functional>
#include <utility>
#include <type_traits>
#include <iterator>
#include <algorithm>
#include <stack>

namespace IMD
{
    template <typename InputIt, typename Comparator = std::less<typename std::iterator_traits<InputIt>::value_type>>
    InputIt Hoare_scheme(InputIt beg, InputIt end, Comparator cmp = Comparator())
    {
        if (beg == end || std::next(beg) == end)
            return beg;

        auto size = std::distance(beg, end);
        auto mid = std::next(beg, size / 2);
        auto last = std::prev(end);

        // The median of their three
        if (cmp(*last, *beg))
            std::iter_swap(beg, last);
        if (cmp(*mid, *beg))
            std::iter_swap(beg, mid);
        if (cmp(*last, *mid))
            std::iter_swap(mid, last);

        auto pivot = *mid;
        InputIt left = beg, right = last;

        while (left <= right)
        {
            while (cmp(*left, pivot))
                ++left;
            while (cmp(pivot, *right))
                --right;

            if (left <= right)
            {
                std::iter_swap(left, right);
                ++left;
                --right;
            }
        }

        return right;
    }

    template <typename InputIt, typename Comparator = std::less<typename std::iterator_traits<InputIt>::value_type>>
    InputIt Lomuto_scheme(InputIt beg, InputIt end, Comparator cmp = Comparator())
    {
        if (beg == end || std::next(beg) == end)
            return beg;

        auto last = std::prev(end);
        auto mid = std::next(beg, std::distance(beg, end) / 2);

        // The median of their three
        if (cmp(*last, *beg))
            std::iter_swap(beg, last);
        if (cmp(*mid, *beg))
            std::iter_swap(beg, mid);
        if (cmp(*last, *mid))
            std::iter_swap(mid, last);

        std::iter_swap(mid, last);

        auto pivot = *last;
        InputIt i = beg;

        for (InputIt j = beg; j != last; ++j)
        {
            if (cmp(*j, pivot))
            {
                std::iter_swap(i, j);
                ++i;
            }
        }
        std::iter_swap(i, last);
        return i;
    }

    template <typename InputIt, typename Comparator = std::less<typename std::iterator_traits<InputIt>::value_type>>
    void merge(InputIt beg, InputIt mid, InputIt end, Comparator cmp = Comparator())
    {
        using value_type = typename std::iterator_traits<InputIt>::value_type;

        size_t left_size = std::distance(beg, mid);
        size_t right_size = std::distance(mid, end);
        size_t total_size = left_size + right_size;

        value_type *tmp = new value_type[total_size];

        InputIt it1 = beg, it2 = mid;
        size_t idx = 0;
        while (it1 != mid && it2 != end)
        {
            if (cmp(*it1, *it2))
            {
                tmp[idx] = std::move(*it1);
                ++it1;
            }
            else
            {
                tmp[idx] = std::move(*it2);
                ++it2;
            }
            ++idx;
        }

        while (it1 != mid)
        {
            tmp[idx] = std::move(*it1);
            ++it1;
            ++idx;
        }

        while (it2 != end)
        {
            tmp[idx] = std::move(*it2);
            ++it2;
            ++idx;
        }

        InputIt dest = beg;
        for (size_t i(0); i < total_size; ++i)
        {
            *dest = std::move(tmp[i]);
            ++dest;
        }

        delete[] tmp;
    }

    template <typename InputIt, typename Comparator = std::less<typename std::iterator_traits<InputIt>::value_type>>
    void bubble_sort(InputIt beg, InputIt end, Comparator cmp = Comparator())
    {
        if (beg == end || std::next(beg) == end)
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
        if (beg == end || std::next(beg) == end)
            return;

        size_t size = std::distance(beg, end);
        size_t gap(size);
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
        if (beg == end || std::next(beg) == end)
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
    void Shell_sort(InputIt beg, InputIt end, Comparator cmp = Comparator())
    {
        if (beg == end || std::next(beg) == end)
            return;

        auto size = std::distance(beg, end);

        for (auto gap = size / 2; gap > 0; gap /= 2)
        {
            auto current = std::next(beg, gap);

            for (auto i = gap; i < size; ++i, ++current)
            {
                auto tmp = std::move(*current);
                auto j = current;
                auto j_gap = std::distance(beg, j);

                while (j_gap >= gap && cmp(tmp, *std::prev(j, gap)))
                {
                    *j = std::move(*std::prev(j, gap));
                    j = std::prev(j, gap);
                    j_gap = std::distance(beg, j);
                }

                *j = std::move(tmp);
            }
        }
    }

    template <typename InputIt, typename Comparator = std::less<typename std::iterator_traits<InputIt>::value_type>>
    void Shell_Knuth_sort(InputIt beg, InputIt end, Comparator cmp = Comparator())
    {
        if (beg == end || std::next(beg) == end)
            return;

        auto size = std::distance(beg, end);

        auto gap = static_cast<decltype(size)>(1);
        while (gap < size / 3)
            gap = 3 * gap + 1;

        while (gap > 0)
        {
            auto current = std::next(beg, gap);

            for (auto i = gap; i < size; ++i, ++current)
            {
                auto tmp = std::move(*current);
                auto j = current;
                auto j_gap = std::distance(beg, j);

                while (j_gap >= gap && cmp(tmp, *std::prev(j, gap)))
                {
                    *j = std::move(*std::prev(j, gap));
                    j = std::prev(j, gap);
                    j_gap = std::distance(beg, j);
                }

                *j = std::move(tmp);
            }

            gap /= 3;
        }
    }

    template <typename InputIt, typename Comparator = std::less<typename std::iterator_traits<InputIt>::value_type>>
    void selection_sort(InputIt beg, InputIt end, Comparator cmp = Comparator())
    {
        if (beg == end || std::next(beg) == end)
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

        if (beg == end || std::next(beg) == end)
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

    template <typename InputIt, typename Comparator = std::less<typename std::iterator_traits<InputIt>::value_type>>
    void Hoare_recursive_sort(InputIt beg, InputIt end, Comparator cmp = Comparator())
    {
        if (beg == end || std::next(beg) == end)
            return;

        InputIt it = Hoare_scheme(beg, end, cmp);
        Hoare_recursive_sort(beg, std::next(it), cmp);
        Hoare_recursive_sort(std::next(it), end, cmp);
    }

    template <typename InputIt, typename Comparator = std::less<typename std::iterator_traits<InputIt>::value_type>>
    void Hoare_iterative_sort(InputIt beg, InputIt end, Comparator cmp = Comparator())
    {
        if (beg == end || std::next(beg) == end)
            return;

        std::stack<std::pair<InputIt, InputIt>> st;
        st.emplace(beg, end);
        while (!st.empty())
        {
            auto [left, right] = st.top();
            st.pop();

            if (std::distance(left, right) <= 1)
                continue;

            InputIt it = Hoare_scheme(left, right, cmp);
            st.emplace(left, std::next(it));
            st.emplace(std::next(it), right);
        }
    }

    template <typename InputIt, typename Comparator = std::less<typename std::iterator_traits<InputIt>::value_type>>
    void Lomuto_recursive_sort(InputIt beg, InputIt end, Comparator cmp = Comparator())
    {
        if (beg == end || std::next(beg) == end)
            return;

        InputIt it = Lomuto_scheme(beg, end, cmp);
        Lomuto_recursive_sort(beg, it, cmp);
        Lomuto_recursive_sort(std::next(it), end, cmp);
    }

    template <typename InputIt, typename Comparator = std::less<typename std::iterator_traits<InputIt>::value_type>>
    void Lomuto_iterative_sort(InputIt beg, InputIt end, Comparator cmp = Comparator())
    {
        if (beg == end || std::next(beg) == end)
            return;

        std::stack<std::pair<InputIt, InputIt>> st;
        st.emplace(beg, end);
        while (!st.empty())
        {

            auto [left, right] = st.top();
            st.pop();

            if (std::distance(left, right) <= 1)
                continue;

            InputIt it = Lomuto_scheme(left, right, cmp);
            st.emplace(left, it);
            st.emplace(std::next(it), right);
        }
    }

    template <typename InputIt, typename Comparator = std::less<typename std::iterator_traits<InputIt>::value_type>>
    void merge_recursive_sort(InputIt beg, InputIt end, Comparator cmp = Comparator())
    {
        auto size = std::distance(beg, end);
        if (size <= 1)
            return;

        auto mid = std::next(beg, size / 2);

        merge_recursive_sort(beg, mid, cmp);
        merge_recursive_sort(mid, end, cmp);
        merge(beg, mid, end, cmp);
    }

    template <typename InputIt, typename Comparator = std::less<typename std::iterator_traits<InputIt>::value_type>>
    void merge_iterative_sort(InputIt beg, InputIt end, Comparator cmp = Comparator())
    {
        auto size = std::distance(beg, end);
        if (size <= 1)
            return;

        for (size_t block_size = 1; block_size < size; block_size *= 2)
        {
            auto it = beg;

            while (it != end)
            {
                auto left_beg = it;
                auto left_end = std::next(it, std::min(block_size, static_cast<size_t>(std::distance(it, end))));

                if (left_end == end)
                    break;

                auto right_beg = left_end;
                auto right_end = std::next(right_beg, std::min(block_size, static_cast<size_t>(std::distance(right_beg, end))));

                merge(left_beg, right_beg, right_end, cmp);

                it = right_end;
            }
        }
    }
}

#endif