#include<vector>
#include<iostream>
#include<stack>

using namespace std;

class Solution {
public:
    double calculate(string s) {
        vector<string> tokens;
        stack<string> op;
        string nums;
        int n = s.size();
        for(int i = 0; i < n; ++i) {
            char c = s[i];
            if(c == ' ') continue;
            else if(isdigit(c)) {
                nums.push_back(c);
                while(i + 1 < n && isdigit(s[i + 1])) {
                    ++i;
                    nums.push_back(s[i]);
                }
                tokens.push_back(nums);
                nums = "";
            }else if(c == '(') {
                op.push(string(1, c));
            }else if(c == '+' || c == '-' || c == '*' || c == '/') {
                string cur(1, c);
                while(!op.empty() && getPriority(op.top()) >= getPriority(cur)) {
                    tokens.push_back(op.top());
                    op.pop();
                }
                op.push(cur);
            }else if(c == ')') {
                while(!op.empty() && op.top() != "(") {
                    tokens.push_back(op.top());
                    op.pop();
                }
                op.pop();
            }
        }
        while(!op.empty()) {
            tokens.push_back(op.top());
            op.pop();
        }
        double ans = evalRPN(tokens);
        return ans;
    }

    int getPriority(string op) {
        int ans = 0;
        switch(op[0]) {
            case '+' :
                ans = 1; break;
            case '-' :
                ans = 2; break;
            case '/' :
            case '*' :
                ans = 3; break;
        }
        return ans;
    }

    double evalRPN(vector<string>& tokens) {
        stack<double> st;
        for(string &tmp : tokens) {
            if(tmp == "+" || tmp == "-" || tmp == "*" || tmp == "/") {
                double q = 1.0 * st.top();
                st.pop();
                double p = 1.0 * st.top();
                st.pop();
                switch(tmp[0]) {
                    case '+' :
                        st.push(p + q); break;
                    case '-' :
                        st.push(p - q); break;
                    case '*' :
                        st.push(1.0 * p * q); break;
                    case '/' :
                        st.push(1.0 * p / q); break;
                }
            }else{
                st.push(1.0 * stoi(tmp));
            }
        }
        double ans = st.top();
        return ans;
    }
};


int main() {
    //中缀表达式转后缀表达式， 逆波兰达表达式求值
    string s = "((1 + 2) * 3) / 55 * ((3 - 2) / 2) * 44";
    Solution so;
    double ans = so.calculate(s); 
    cout << ans << endl;
}