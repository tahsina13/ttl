#include <bits/stdc++.h>

namespace ttl 
{
    /**
     * @brief Computes the Lyndon factorization of a string using Duval's algorithm.
     * 
     * A Lyndon word is a non-empty string that is strictly smaller than all of its non-trivial suffixes.
     * The Lyndon factorization of a string is a unique representation of the string as a concatenation of Lyndon words.
     * 
     * @param s The input string.
     * @return A vector of strings representing the Lyndon factors of the input string.
     */
    std::vector<std::string> lyndon_factorization(const std::string &s) {
        std::vector<std::string> factors; 
        for(int i = 0; i < s.size();) {
            int j = i + 1, k = i; 
            while(j < s.size() && s[k] <= s[j]) {
                if(s[k] < s[j]) k = i; 
                else k++; 
                j++; 
            } 
            while(i <= k) {
                factors.push_back(s.substr(i, j - k)); 
                i += j - k; 
            }
        } 
        return factors; 
    }    
}
