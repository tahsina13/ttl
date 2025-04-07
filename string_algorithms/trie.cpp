#include <bits/stdc++.h>

namespace ttl
{
    class Trie
    {
    private:
        struct TrieNode
        {
            int depth;
            int slink;
            std::vector<int> patterns;
            std::map<int, int> children;

            TrieNode(int depth) : depth(depth), slink(-1) {}
        };

        int num_patterns;
        std::vector<TrieNode> nodes;

    public:
        Trie() : num_patterns(0), nodes{TrieNode(0)} {}

        const TrieNode &operator[](int index) const
        {
            return nodes[index];
        }

        size_t size() const
        {
            return nodes.size();
        }

        /**
         * @brief Adds a string to the trie.
         */
        void add(const std::string &s)
        {
            int curr = 0;
            for (char ch : s)
            {
                if (!nodes[curr].children.count(ch))
                {
                    nodes[curr].children[ch] = nodes.size();
                    nodes.emplace_back(nodes[curr].depth + 1);
                }
                curr = nodes[curr].children[ch];
            }
            nodes[curr].patterns.push_back(num_patterns++);
        }

        /**
         * @brief Links the trie nodes to nodes with longest partial match.
         */
        void link()
        {
            std::queue<int> q;
            nodes[0].slink = 0;
            for (const auto &p : nodes[0].children)
            {
                nodes[p.second].slink = 0;
                q.push(p.second);
            }
            while (!q.empty())
            {
                int v = q.front();
                q.pop();
                for (const auto &p : nodes[v].children)
                {
                    auto &[c, u] = p;
                    int l = nodes[v].slink;
                    while (l > 0 && !nodes[l].children.count(c))
                        l = nodes[l].slink;
                    if (nodes[l].children.count(c))
                        l = nodes[l].children[c];
                    nodes[u].slink = l;
                    q.push(u);
                }
            }
        }

        friend std::ostream &operator<<(std::ostream &os, const Trie &trie)
        {
            for (int i = 0; i < trie.size(); i++)
            {
                os << "Node " << i << ":\n";
                os << "  Depth: " << trie.nodes[i].depth << "\n";
                os << "  Slink: " << trie.nodes[i].slink << "\n";
                os << "  Patterns: ";
                for (int j : trie.nodes[i].patterns)
                    os << j << " ";
                os << "\n  Children:\n";
                for (const auto &p : trie.nodes[i].children)
                    os << "    " << char(p.first) << ": " << p.second << "\n";
            }
            return os;
        }
    };

    /**
     * @brief Counts the occurrences of patterns in the trie within the string s. Assumes the trie has been linked. 
     * 
     * @param trie The Trie object containing the patterns.
     * @param s The string to search for patterns.
     * @return A map where keys are pattern indices and values are their counts.
     */
    std::map<int, int> get_counts(const Trie &trie, const std::string &s)
    {
        // Find initial frequencies of each trie node. 
        std::vector<int> freq(trie.size(), 0);
        int curr = 0;
        for (int i = 0; i < s.size(); i++)
        {
            while (curr > 0 && !trie[curr].children.count(s[i]))
                curr = trie[curr].slink;
            if (trie[curr].children.count(s[i]))
                curr = trie[curr].children.at(s[i]);
            freq[curr]++;
        }
        // Traverse trie nodes bottom up to find the frequencies.
        std::priority_queue<std::pair<int, int>> pq;
        std::vector<bool> vis(trie.size(), false);
        for (int i = 0; i < trie.size(); i++)
        {
            if (freq[i] > 0)
                pq.emplace(trie[i].depth, i);
        }
        while (!pq.empty())
        {
            int v = pq.top().second;
            pq.pop();
            if (vis[v])
                continue;
            vis[v] = true;
            int l = trie[v].slink;
            if (l > 0 && !vis[l])
            {
                freq[l] += freq[v];
                pq.emplace(trie[l].depth, l);
            }
        }
        // Find counts of patterns using the frequencies of their trie nodes.
        std::map<int, int> cnt;
        for (int i = 0; i < trie.size(); i++)
        {
            if (freq[i] > 0)
            {
                for (int pat : trie[i].patterns)
                    cnt[pat] += freq[i];
            }
        }
        return cnt; 
    }

    /**
     * @brief Finds the first positions of patterns in the trie within the string s. Assumes the trie has been linked. 
     * 
     * @param trie The Trie object containing the patterns.
     * @param s The string to search for patterns.
     * @return A map where keys are pattern indices and values are their first starting positions.
     */
    std::map<int, int> get_positions(const Trie &trie, const std::string &s)
    {
        // Find initial first occurrences of each trie node.
        std::vector<int> occ(trie.size(), s.size()); 
        int curr = 0;
        for (int i = 0; i < s.size(); i++)
        {
            while (curr > 0 && !trie[curr].children.count(s[i]))
                curr = trie[curr].slink;
            if (trie[curr].children.count(s[i]))
                curr = trie[curr].children.at(s[i]);
            occ[curr] = std::min(occ[curr], i); 
        }
        // Traverse trie nodes bottom up to find the first occurrences.
        std::priority_queue<std::pair<int, int>> pq;
        std::vector<bool> vis(trie.size(), false); 
        for (int i = 0; i < trie.size(); i++)
        {
            if (occ[i] < s.size())
                pq.emplace(trie[i].depth, i);
        }
        while (!pq.empty())
        {
            int v = pq.top().second; 
            pq.pop(); 
            if (vis[v])
                continue; 
            vis[v] = true; 
            int l = trie[v].slink; 
            if (l > 0 && !vis[l])
            {
                occ[l] = std::min(occ[l], occ[v]); 
                pq.emplace(trie[l].depth, l); 
            }
        }
        // Find first positions of patterns using the first occurrences of their trie nodes.
        std::map<int, int> pos; 
        for (int i = 0; i < trie.size(); i++)
        {
            if (occ[i] < s.size())
            {
                for (int p : trie[i].patterns)
                    pos[p] = occ[i] - trie[i].depth + 1;
            }
        }
        return pos; 
    }
}