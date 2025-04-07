#include <bits/stdc++.h>

namespace ttl
{
    /**
     * @brief Manacher's algorithm to find all odd_length palindromic substrings in linear time.
     * 
     * @param s The input string.
     * @return A vector containing the length of longest odd-length palindromic substring centered at each character.  
     */
    std::vector<int> compute_manacher_odd(const std::string &s) 
    {
        std::string t = "$" + s + "^"; 
        std::vector<int> p(s.size() + 2, 0); 
        int l = 0, r = 1; 
        for(int i = 1; i <= s.size(); i++)
        {
            p[i] = std::max(0, std::min(r - i, p[l + (r - i)])); 
            while(t[i - p[i]] == t[i + p[i]])
                p[i]++; 
            if(i + p[i] > r)
            {
                l = i - p[i]; 
                r = i + p[i]; 
            }
        }
        return std::vector<int>(p.begin() + 1, p.end() - 1); 
    }

    /**
     * @brief Manacher's algorithm to find all palindromic substrings in linear time.
     * 
     * @param s The input string.
     * @return A vector d where d[2i] = 2d_even[i] + 1 and d[2i + 1] = 2d_odd[i] for all i.
     *        d_even[i] is the length of the longest even-length palindromic substring centered at i.
     *        d_odd[i] is the length of the longest odd-length palindromic substring centered at i.
     */
    std::vector<int> compute_manacher(const std::string &s)
    {
        std::string t; 
        for(char c : s)
            t += "#" + c; 
        auto res = compute_manacher_odd(t + "#"); 
        return std::vector<int>(res.begin() + 1, res.end() - 1); 
    }
}