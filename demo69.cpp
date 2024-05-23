#include "./utils/head.h"

/**
 * n的算法平方根最近值
 * 
 * n = 5, left = 0, right = 5
 * 
 * 1. mid = 0 + 5/2 = 2, res = 4 < 5, left = 2 + 1 = 3;
 * 2. mid = 3 + 2/2 = 4, res = 16 > 5, right = 4- 1 = 3;
 * 3. mid = 3 + 0 = 3, res = 9 > 5, right = 2;
*/
class Solution {
    public:
    int mySqrt(int n) {
        int left = 0, right = n, mid;
        long long res;
        while(left <= right) {
            mid = left + ((right - left) >> 1);
            res = mid * mid;
            if(res < n) {
                left = mid + 1;
            } else if(res > n) {
                right = mid - 1;
            } else {
                return mid;
            }
        }
        return right;

    }
};

int main() {
    cout << Solution().mySqrt(5) << endl;
    cout << Solution().mySqrt(9) << endl;
    cout << Solution().mySqrt(10) << endl;
}