#include <iostream>
#include <vector>


int majorityElement(std::vector<int>& nums)
{
    int count = 0;
    int candidate = 0;

    for(int i = 0;i < nums.size() ; i++)
    {
        if(count == 0)
            candidate = nums[i];
        count += (nums[i] == candidate)? 1:-1;
    }

    return candidate;
}

int main(void)
{
    std::vector <int> nums = {1,1,1,3,4,8,9};
    std::cout << majorityElement(nums) << std::endl;
    return 0;
}

