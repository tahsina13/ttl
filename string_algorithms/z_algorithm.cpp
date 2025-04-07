#include <bits/stdc++.h>
using namespace std; 

namespace ttl
{
    /**
     * @brief Computes the Z-array for a given string.
     * 
     * The Z-array for a string s is an array z where z[i] is the length of the longest substring starting from s[i]
     * which is also a prefix of s.
     * 
     * @param s The input string.
     * @return A vector containing the Z-array values.
     */
    std::vector<int> compute_z_array(const std::string &s) {
        std::vector<int> z(s.size());
        int x = 0, y = 0;
        for (int i = 1; i < s.size(); i++) {
            z[i] = max(0, min(z[i-x], y-i+1));
            while (i+z[i] < s.size() && s[z[i]] == s[i+z[i]]) {
                x = i; y = i+z[i]; z[i]++;
            }
        }
        return z; 
    }
}
