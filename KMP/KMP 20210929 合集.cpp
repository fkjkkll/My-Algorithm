// https://www.cnblogs.com/dusf/p/kmp.html
class Solution {
public:
    vector<int> getNext(string pat) {
        vector<int> next(pat.size(), -1);
        int j = 0;
        int k = -1;
        while (j < pat.size() - 1) {
            if (k == -1 || pat[j] == pat[k]) {
                // 改进版
                if (pat[++j] == pat[++k]) // 当前字符跟最大前缀字符串紧跟着的一个字符相等时，要跳过
                    next[j] = next[k];
                else
                    next[j] = k;
                //// 基础版
                //next[++j] == ++k;
            }
            else
                k = next[k];
        }
        return next;
    }

    int strStr(string txt, string pat) {
        if (txt == "" || pat == "")
            return (txt == pat || pat == "") ? 0 : -1;
        int m = txt.size();
        int n = pat.size();
        vector<int> next = getNext(pat);
        int i = 0;
        int j = 0;
        while (i < m && j < n) {
            if (j == -1 || txt[i] == pat[j]) {
                ++i;
                ++j;
            }
            else
                j = next[j];
        }
        return (j == n) ? (i - j) : -1;
    }
};