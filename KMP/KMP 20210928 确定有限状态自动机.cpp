// 参考labuladong
class Solution {
public:
    const int R = 256;

    vector<vector<int>> kmp(string pat) {
        int n = pat.size();
        vector<vector<int>> dp(n, vector<int>(R, 0));
        dp[0][pat[0]] = 1;
        int X = 0;
        for (int j = 1; j < n; j++) {
            for (int c = 0; c < R; c++) {
                if (pat[j] == c)
                    dp[j][c] = j + 1;
                else
                    dp[j][c] = dp[X][c];
            }
            X = dp[X][pat[j]]; // 跟 k = next[k] 一个道理，要理解
        }
        return dp;
    }

    int strStr(string txt, string pat) {
        if (txt == "" || pat == "")
            return (txt == pat || pat == "") ? 0 : -1;
        vector<vector<int>> dp = kmp(pat);
        int m = txt.size();
        int n = pat.size();
        int j = 0;
        for (int i = 0; i < m; i++) {
            j = dp[j][txt[i]];
            if (j == n)
                return i - n + 1;
        }
        return -1;
    }
};