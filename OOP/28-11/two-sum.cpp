#include <vector>
#include <unordered_map>
#include <cassert> // Required for assert
#include <iostream> // Required for cout and endl

using namespace std;

vector<int> twoSum(vector<int>& nums, int target) {
    unordered_map<int, int> numMap; 
    for (int i = 0; i < nums.size(); ++i) {
        int complement = target - nums[i];
        if (numMap.count(complement)) {
            return {numMap[complement], i};
        }   
        numMap[nums[i]] = i;
    }
    return {}; 
}

int main() {
    // Test Case 1: Basic functionality
    vector<int> nums1 = {2, 7, 11, 15};
    int target1 = 9;
    vector<int> result1 = twoSum(nums1, target1);
    assert(result1.size() == 2 && ((result1[0] == 0 && result1[1] == 1) || (result1[0] == 1 && result1[1] == 0)));
    cout << "Test Case 1 Passed" << endl; // Fixed syntax error

    // Test Case 2: No solution
    vector<int> nums2 = {3, 2, 4};
    int target2 = 10;
    vector<int> result2 = twoSum(nums2, target2);
    assert(result2.empty());
    cout << "Test Case 2 Passed" << endl;

    return 0;
}
