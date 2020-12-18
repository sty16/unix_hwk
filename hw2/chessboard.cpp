#include<iostream>
#include<vector>
using namespace std;

struct Point {
    int x, y;
    Point(int _x, int _y) : x(_x), y(_y) {}
};

class Solution {
public:
    vector<vector<char>> board;
    vector<Point> spaces;
    vector<Point> deleted;
    vector<Point> ans;
    vector<vector<int>> dir = {{-2, 0}, {2, 0}, {0, -2}, {0, 2}};
    vector<vector<int>> dir1 = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    void makeBoard() {
        // x 代表当前位置为棋子 o 代表当前位置是空格 # 代表当前位置为非法位置
        board.resize(7, vector<char>(7, 'x'));
        board[3][3] = 'o';
        vector<int> pos = {0, 1, 5, 6};
        for(int i : pos) {
            for(int j : pos) {
                board[i][j] = '#';
            }
        }
    }

    vector<Point> findOptimal(int d_n) {
        spaces.emplace_back(3, 3);
        dfs(d_n);
        return ans;
    }

    void dfs(int d_n){
        if(ans.size() == d_n) return ;
        bool isFinished = true;
        int m = board.size();
        int n = spaces.size();
        for(int i = 0; i < n; ++i) {
            Point p = spaces[i];
            for(int k = 0; k < 4; ++k) {
                int ni = p.x + dir[k][0];
                int nj = p.y + dir[k][1];
                int di = p.x + dir1[k][0];
                int dj = p.y + dir1[k][1];
                if(ni < 0 || ni >= m || nj < 0 || nj >= m || board[ni][nj] != 'x') continue;
                if(di < 0 || di >= m || dj < 0 || dj >= m || board[di][dj] != 'x') continue;
                deleted.emplace_back(di, dj);
                board[di][dj] = 'o'; 
                board[ni][nj] = 'o';
                board[p.x][p.y] = 'x';
                isFinished = false;
                spaces.erase(spaces.begin() + i);
                spaces.emplace_back(di, dj);
                spaces.emplace_back(ni, nj);
                dfs(d_n);
                spaces.pop_back();
                spaces.pop_back();
                spaces.insert(spaces.begin() + i, {p.x, p.y});
                board[di][dj] = 'x';
                board[ni][nj] = 'x';
                board[p.x][p.y] = 'o';
                deleted.pop_back();
            }
        }

        if(isFinished) {
            if(deleted.size() > ans.size()) {
                ans = deleted;
            }
        }
    }

};

int main() {
    // 程序复杂度为n的阶乘， 大概10分钟以上跑出过删除30个点的方法, 通过修改 n_deleted 进行改变
    // 当添加两行两列后，程序复杂度过高。
    Solution so;
    so.makeBoard();
    int n_deleted = 29;
    vector<Point> ans = so.findOptimal(n_deleted);
    cout << "删除29个棋子的顺序" << endl;
    for(auto p : ans) {
        cout << p.x << " " << p.y << endl;
    }
    cout << "程序复杂度为n的阶乘O(n!)， 大概10分钟以上跑出过删除30个点的方法, 通过修改 n_deleted修改" << endl;
    cout << "算法思想类似于八皇后，暴力解法，递归回溯" << endl;
}