#include<iostream>
#include<sstream>
#include<string>
#include<cstring>
#include<vector>
#include<unordered_set>
using namespace std;


class Trie{
    struct TrieNode {
        int path, end;
        TrieNode* next[26];
        TrieNode(int _path, int _end) : path(_path), end(_end) {
            memset(next, 0, sizeof(next));
        };
        ~TrieNode() {
            for(int i = 0; i < 26; ++i) {
                if(next[i] != nullptr) {
                    delete next[i];
                    next[i] = nullptr;
                }
            }
        }
    };

private :
    TrieNode *root;

public :
    Trie() {
        root = new TrieNode(0, 0);
    }

    void insert(string &word) {
        TrieNode *cur = root;
        for(char c : word) {
            int idx = c - 'a';
            if(cur->next[idx] == nullptr) {
                cur->next[idx] = new TrieNode(0, 0);
            }
            cur = cur->next[idx];
            ++cur->path;
        }
        ++cur->end;
    }

    bool search(string &word) {
        TrieNode *cur = root;
        for(char c : word) {
            int idx = c - 'a';
            if(cur->next[idx] == nullptr) {
                return false;
            }
            cur = cur->next[idx];
        }
        return cur->end > 0;
    }

    void deleteWord(string& word) {
        if(search(word)) {
            TrieNode *cur = root;
            int n = word.size();
            for(char c : word) {
                int idx = c - 'a';
                --cur->next[idx]->path;
                if(!cur->next[idx]->path) {
                    delete cur->next[idx];
                    cur->next[idx] = nullptr;
                    return;
                }
                cur = cur->next[idx];
            }
            --cur->end;
        }
    }
    
    bool startsWith(string& prefix) {
        TrieNode *cur = root;
        for(char c : prefix) {
            int idx = c - 'a';
            if(cur->next[idx] == nullptr) {
                return false;
            }
            cur = cur->next[idx];
        }
        return true;
    }
};


int main() {
    string s = "   sdf sdf we  tr  qw rwe  adsf w3rq afdsga fga adfgsfad gsfdgsdf sdfgsdf sgdfsdfg gfsdgsdf sfdgsfdg sfdgsdf sgdfgsd gsdfsdg asdfasd asdfasd asdfas asdfasd asdfasd tes tes adf   adfa";
    vector<string> words;
    int n = s.size();
    int i = 0, j = 0;
    while(i < n) {
        if(s[i] == ' ') {
            ++i;
            continue;
        }else {
            int j = i + 1;
            while(j < n && s[j] != ' ') ++j;
            words.push_back(s.substr(i, j - i));
            i = j;
        }
    }
    Trie trie;
    int m = words.size();
    unordered_set<string> ans;
    for(int i = 0; i < m; ++i) {
        if(trie.search(words[i])) {
            ans.insert(words[i]);
        }else {
            trie.insert(words[i]);
        }
    }
    trie.deleteWord(words[0]);
    for(string tmp : ans) {
        cout << tmp << endl;
    }
}