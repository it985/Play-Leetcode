/// Source : https://leetcode.com/problems/number-of-ways-to-separate-numbers/
/// Author : liuyubobobo
/// Time   : 2021-08-23

#include <iostream>
#include <vector>

using namespace std;


/// RK + DP
/// Time Complexity: O(n^2)
/// Space Complexity: O(n^2)
template<typename T>
class StringHash{

private:
    int n;
    T B, MOD;
    vector<T> h, p;

public:
    StringHash(const string& s, T B = 128, T MOD = 1e9+ 7) :
    n(s.size()), h(n + 1, 0), p(n + 1, 1), B(B), MOD(MOD){

        for(int i = 0; i < n; i ++){
            h[i + 1] = (h[i] * B + s[i]) % MOD;
            p[i + 1] = p[i] * B % MOD;
        }
    }

    T get_hash(int l, int r){
        //        assert(l >= 0 && l < n);
        //        assert(r >= 0 && r < n);
        //        return (h[r + 1] - h[l] * p[r - l + 1] % MOD + MOD) % MOD;

        // 对于有符号类型，以下代码更快
        T res = (h[r + 1] - h[l] * p[r - l + 1]) % MOD;
        return res < 0 ? res + MOD : res;
    }
};

class Solution {

private:
    const int MOD = 1e9 + 7;
    StringHash<long long> *hash;

public:
    int numberOfCombinations(string num) {

        int n = num.size();
        hash = new StringHash<long long>(num);
        vector<vector<long long>> dp(n + 1, vector<long long>(n, 0)); // (len, start)
        vector<vector<long long>> presum(n + 1, vector<long long>(n, 0));

        dp[n][0] = num[0] != '0';
        presum[n][0] = dp[n][0];
        for(int len = n - 1; len >= 1; len --){
            dp[len][n - len] = num[n - len] != '0';
            for(int start = n - len - 1; start >= 0; start --){
                if(num[start] == '0') continue;
                dp[len][start] = presum[len + 1][start + len];
                if(start + len + len <= n && less_or_equal(num, start, start + len, len))
                    dp[len][start] += dp[len][start + len];
                dp[len][start] %= MOD;
            }

            for(int i = 0; i < n; i ++)
                presum[len][i] = (dp[len][i] + presum[len + 1][i]) % MOD;
        }

        return presum[1][0];
    }

private:
    bool less_or_equal(const string& num, int start1, int start2, int len){
        if(hash->get_hash(start1, start1 + len - 1) == hash->get_hash(start2, start2 + len - 1))
            return true;

        for(int k = 0; k < len; k ++){
            if(num[start1 + k] < num[start2 + k]) return true;
            else if(num[start1 + k] > num[start2 + k]) return false;
        }

        return true;
    }
};


int main() {

    cout << Solution().numberOfCombinations("327") << endl;
    // 2

    cout << Solution().numberOfCombinations("094") << endl;
    // 0

    cout << Solution().numberOfCombinations("0") << endl;
    // 0

    cout << Solution().numberOfCombinations("9999999999999") << endl;
    // 101

    cout << Solution().numberOfCombinations("11111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111") << endl;
    // 755568658

    return 0;
}