#include <iostream>
#include <vector>

using namespace std;

void printf_nums(vector<int>& nums,int i){
    cout << i << endl;
    for(auto p=nums.begin(); p != nums.end(); p++){
        cout << *p << " " ;
    }
    cout << endl;
}

int partition(vector<int>& nums, int r, int q){
    int pivot = nums[q];
    int i = r;
    for(int j=r; j < q; j++){
        if(nums[j] <= pivot){
            int temp = nums[i];
            nums[i] = nums[j];
            nums[j] = temp;
            i++;
        }
    }
    int temp = nums[q];
    nums[q] = nums[i];
    nums[i] = temp;
    return i;
}

void quick_sort_c(vector<int>& nums, int r, int q){
    if(r >= q){
        return ;
    }
    else{
        int i = partition(nums,r,q);
        quick_sort_c(nums,r,i-1);
        quick_sort_c(nums,i+1,q);
    }
    return;
}


void quicksort(vector<int>& nums){
    quick_sort_c(nums,0,nums.size()-1);
}

int main(void){
    vector<int> nums = {2,3,5,1,4,3};
    quicksort(nums);
    printf_nums(nums,0);
    // int i = partition(nums,0,nums.size()-1);
    // printf_nums(nums,i);
    // i = partition(nums,0,i-1);
    // printf_nums(nums,i);
    // i = partition(nums,i+1,2);
    // printf_nums(nums,i);
    return 0;
}
