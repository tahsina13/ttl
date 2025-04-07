#include <bits/stdc++.h>

namespace ttl
{
    /**
     * @brief Computes the prefix function (pi) for a given string.
     * 
     * The prefix function for a string s is an array pi where pi[i] is the length of the longest proper prefix of s[0..i]
     * which is also a suffix of s[0..i].
     * 
     * @param s The input string.
     * @return A vector containing the prefix function values.
     */
    std::vector<int> compute_pi(const std::string &s) {
        std::vector<int> pi (s.size()); 
        int b = 0; 
        for (int i = 1; i < s.size(); i++) {
            while (b > 0 && s[b] != s[i]) {
                b = pi[b - 1];  
            } 
            if (s[b] == s[i]) {
                b++; 
            } 
            pi[i] = b; 
        }    
        return pi; 
    }

    /**
     * @brief Knuth-Morris-Pratt (KMP) algorithm for substring search.
     * 
     * @param s The string to search in.
     * @param t The substring to search for.
     * @return A vector of starting indices where the substring occurs in the string.
     */
    std::vector<int> kmp(const std::string &s, const std::string &t) {
        std::vector<int> pi = compute_pi(t); 
        std::vector<int> occ; 
        for (int i = 0, l = 0; i < s.size();) {
            while (l < t.size() && i + l < s.size() && t[l] == s[i + l]) {
                l++; 
            }  
            if (l == t.size()) {
                occ.push_back(i); 
            } 
            if (l > 0) {
                i += l - pi[l - 1]; 
                l = pi[l - 1]; 
            } else {
                i++; 
            }
        }
        return occ; 
    }
}
