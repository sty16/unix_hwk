#include<iostream>
#include<vector>

using namespace std;

struct node {
    int v[3];
    node(int a, int b, int c){
        v[0] = a;
        v[1] = b;
        v[2] = c; 
    }
    bool operator == (const node& rhs) {
        for(int i = 0; i < 3; ++i) {
            if(v[i] != rhs.v[i]) return false;
        }
        return true;
    }
};

class Solution {
public :
    int vol[3];
    int cnt = 0x3f3f3f3f;
    vector<node> path;
    vector<node> ans;
    vector<node> findMinOperations(int a, int b, int c) {
        vol[0] = a;
        vol[1] = b;
        vol[2] = c;
        node initial(8, 0, 0);
        path.push_back(initial);
        dfs(initial, 0);
        return ans;
    }

    void dfs(node cur, int d) {
        int num = 0;
        for(int i = 0; i < 3; ++i) {
            if(cur.v[i] == 4) ++num;
        }
        if(num == 2) {
            if(d < cnt) {
                ans.assign(path.begin(), path.end());
                cnt = d;
                return;
            }
        }
        for(int i = 0; i < 3; ++i) {
            for(int j = 0; j < 3; ++j) {
                if(i == j || cur.v[i] == 0 || cur.v[j] == vol[j]) continue;
                int water = min(vol[j] - cur.v[j], cur.v[i]);
                cur.v[i] -= water;
                cur.v[j] += water;
                bool isVis = false;
                for(int k = 0; k < path.size(); ++k) {
                    if(cur == path[k]) isVis = true;
                }
                if(!isVis) {
                    path.push_back(cur);
                    dfs(cur, d+1);
                    path.pop_back();
                }
                cur.v[i] += water;
                cur.v[j] -= water;
            }
        }
    }
};


int main() {
    Solution so;
    vector<node> ans = so.findMinOperations(8, 5, 3);
    for(auto tmp : ans) {
        cout << tmp.v[0] << " " << tmp.v[1] << " " << tmp.v[2] << endl;
    }
    cout << "最少次数为：" << (int)ans.size() - 1 << endl; 

}

