#include <bits/stdc++.h>

namespace ttl
{
    template <typename T, typename Op = std::plus<T>, typename Inv = std::negate<T>>
    class FenwickTree
    {
    private: 
        std::vector<T> tree; 
        Op op; 
        Inv inv; 

    public: 
        FenwickTree(int n, Op op = Op(), Inv inv = Inv()) : 
            tree(n + 1, T()), op(op), inv(inv) {} 

        /**
         * @brief Updates the Fenwick tree at index with the given value.
         */
        void update(int index, T value)
        {
            while (index < tree.size()) 
            {
                tree[index] = op(tree[index], value); 
                index += index & -index; 
            }
        } 

        /**
         * @brief Updates the Fenwick tree in the range [left, right] with the given value.
         */
        void range_update(int left, int right, T value)
        {
            update(left, value); 
            update(right + 1, inv(value)); 
        }

        /**
         * @brief Queries the Fenwick tree for the cumulative value up to the given index.
         */
        T query(int index)
        {
            T result = T(); 
            while (index > 0) 
            {
                result = op(result, tree[index]); 
                index -= index & -index; 
            }
            return result; 
        } 
        
        /**
         * @brief Queries the Fenwick tree for the cumulative value in the range [left, right].
         */
        T range_query(int left, int right)
        {
            return op(query(right), inv(query(left - 1))); 
        }
    }; 
}