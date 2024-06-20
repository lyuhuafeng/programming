#include <string>
#include <algorithm>
using namespace std;

class Trie {
private:
    bool is_end;
    Trie* children[26];
public:
    Trie() {
        is_end = false;
        fill_n(children, 26, nullptr);
    }
    
    void insert(string word) {
        Trie* node = this;
        for (char c : word) {
            int ci = c - 'a';
            if (node->children[ci] == nullptr) {
                node->children[ci] = new Trie();
            }
            node = node->children[ci];
        }
        node->is_end = true;
    }
    
    bool search(string word) {
        Trie* node = this;
        for (char c : word) {
            if ((node = node->children[c - 'a']) == nullptr) {
                return false;
            }
        }
        return node->is_end;
    }
    
    bool startsWith(string prefix) {
        Trie* node = this;
        for (char c : prefix) {
            if ((node = node->children[c - 'a']) == nullptr) {
                return false;
            }
        }
        return true;
    }
};

int main() {}

/**
 * Your Trie object will be instantiated and called as such:
 * Trie* obj = new Trie();
 * obj->insert(word);
 * bool param_2 = obj->search(word);
 * bool param_3 = obj->startsWith(prefix);
 */