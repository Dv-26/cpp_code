#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

void findNsum(vector<int>& nums, int n, int sum, vector<int>& current, vector<vector<int>>& out, int start, unordered_map <int,int>& hash){
    if(n == 2){
        // for(int i=start; i<nums.size(); i++){
        //     if(hash.find(sum) != hash.end()){
        //         current.push_back(sum);
        //         out.push_back(current);
        //         current.pop_back();
        //         return;
        //     }
        //     hash[nums[i]] = i;
        // }
        int left = start;
        int right = nums.size() - 1;
        while(left < right){
            int lr_sum = nums[left] + nums[right];
            if(lr_sum == sum){
                current.push_back(nums[left]);
                current.push_back(nums[right]);
                out.push_back(current);
                current.pop_back();
                current.pop_back();
                return;
            }
            else if(lr_sum > sum){
                right --;
            }
            else{
                left ++;
            }
        }
    }
    else{
        for(int i = start; i < nums.size() ; i++){
            if(i == start || (i>start && (nums[i] != nums[i+1] || nums[i] != nums[i-1]) )){
                current.push_back(nums[i]);
                findNsum(nums, n-1, sum-nums[i], current, out, i+1, hash);
                current.pop_back();
            }
        }
    }
    return;
}

int main(void){
    vector<int> nums = {-4,-1,-1,0,1,2};
    vector<int> current;
    vector<vector<int>> out;
    unordered_map <int,int> hash;

    findNsum(nums,3,0,current,out,0,hash);

    for(auto p=out.begin();p != out.end();p++){
        for(auto p0= p->begin(); p0 != p->end(); p0++){
            cout << *p0 << " ";
        }
        cout << endl;
    }
    return 0;
}


