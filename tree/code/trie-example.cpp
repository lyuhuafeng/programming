#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>
#include <set>
using namespace std;

const int ALPHABET_SIZE = 26;

typedef struct trie_node {
    int count;   // 该节点代表的单词的个数
    trie_node *children[ALPHABET_SIZE]; // 各个子节点 
} *trie;

trie_node* create_trie_node() {
    trie_node* node = new trie_node();
    node->count = 0;
    fill_n(node->children, ALPHABET_SIZE, nullptr);
    return node;
}

void trie_insert(trie root, const string &key) {
    trie_node* node = root;
    for (char c : key) {
        int ci = c - 'a';
        if (node->children[ci] == nullptr) {
            node->children[ci] = create_trie_node();
        }
        node = node->children[ci];
    }
    node->count++;
}

/**
 * 查询：不存在：返回0，存在：返回出现的次数
 */ 
int trie_search(trie root, const string& key) {
    trie_node* node = root;
    for (char c : key) {
        int ci = c - 'a';
        if (node->children[ci] == nullptr) {
            return 0;
        }
        node = node->children[ci];
    }
    return node == nullptr ? 0 : node->count;
}

int main() {
    string sentence = "once upon a time there lived a king who loved horses very much one day he asked an artist to draw him a horse the artist said you must wait so the king waited and waited after a year he could not wait any more so he went to the artist";
    stringstream ss(sentence);
    string key;
    set<string> keys;
    trie root = create_trie_node();
    while (ss >> key) {
        keys.insert(key);
        trie_insert(root, key);
    }

    keys.insert("never_happen");
    keys.insert("thaw");
    for (const string &k : keys) {
        int cnt = trie_search(root, k);
        printf("%s : %d\n", k.c_str(), cnt);
    }
    return 0;
}
