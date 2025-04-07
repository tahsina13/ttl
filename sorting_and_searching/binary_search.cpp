#include <bits/stdc++.h>

namespace ttl
{
    /**
     * @brief Overflow-safe midpoint functor.
     */
    template <typename T>
    struct Midpoint {
        T operator()(T a, T b) const {
            return a + (b - a) / 2;
        }
    };

    /**
     * @brief Searches for the last element in the range (left, right] that does not satisfy the predicate.
     *
     * @param left The left bound of the search range.
     * @param right The right bound of the search range.
     * @param pred The predicate function that returns true for elements that satisfy the condition.
     * @param midpoint A function to calculate the midpoint of the range. Default is std::midpoint.
     */
    template <typename T, typename Predicate, typename Midpoint = Midpoint<T>>
    T lower_bound(
        T left,
        T right,
        Predicate pred,
        Midpoint midpoint = Midpoint()
    ) {
        while (left < right)
        {
            T mid = right - (midpoint(left, right) - left);
            if (pred(mid))
            {
                right = mid - 1;
            }
            else
            {
                left = mid; 
            }
        }
        return right;
    }

    /**
     * @brief Searches for the first element in the range [left, right) that satisfies the predicate.
     *
     * @param left The left bound of the search range.
     * @param right The right bound of the search range.
     * @param pred The predicate function that returns true for elements that satisfy the condition.
     * @param midpoint A function to calculate the midpoint of the range. Default is std::midpoint.
     */
    template <typename T, typename Predicate, typename Midpoint = Midpoint<T>>
    T upper_bound(
        T left,
        T right,
        Predicate pred,
        Midpoint midpoint = Midpoint()
    ) {
        while (left < right)
        {
            T mid = midpoint(left, right);
            if (pred(mid))
            {
                right = mid; 
            }
            else
            {
                left = mid + 1; 
            }
        }
        return left;
    }
}
