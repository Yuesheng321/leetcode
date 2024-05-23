#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

/*
nums 表示整数组成的非空数组
*/
class Solution
{
public:
    vector<int> plusOne(vector<int> nums)
    {
        int n = nums.size();
        // 从后往前遍历到下标地1位
        bool flag = true;
        nums[n - 1]++;
        for (int i = n - 1; i > 0; --i)
        {
            if(nums[i] / 10) {
                // 计算进位：直接将进位添加到i-1位上
                nums[i - 1] += nums[i] / 10;
                flag = false;
            } 
            // 计算地i位实际值（去掉进位后的）
            nums[i] = nums[i] % 10;
            if(flag) {
                return nums;
            }
           
        }
        // 考虑第0位：存在进位
        if (nums[0] / 10)
        {
            nums[0] = nums[0] % 10;
            nums.insert(nums.begin(), 1);
        }
        return nums;
    }
};



int main()
{
    vector<int> nums = {1, 9, 9};
    vector<int> res = Solution().plusOne(nums);
    for(int val : res) {
        cout << val << endl;
    }
}