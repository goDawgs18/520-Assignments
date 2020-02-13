#include "examples.h"
#include <vector>
#include <algorithm>    // std::sort
#include <cmath>
#include <iostream>


void sort_by_magnitude ( std::vector<double> & a ) {
    auto x_mag_less_y_mag = [](double x, double y) { return x*x < y*y; };
    std::sort(a.begin(), a.end(), x_mag_less_y_mag);
}

std::vector<int> primes ( int n ) {
    std::vector<bool> v;
    std::vector<int> nums;
    if (n < 2) {
        return nums;
    }
    v.resize(floor(sqrt(n)) + 1, false);

    for (int i = 2; i < v.size(); i++ ) {
        
        if (v[i] == false) { //have not visited multiple
            nums.push_back(i);
            std::cout << i;
            for (int k = 1; k * i < v.size(); k++ ) {
                v[k*i] = true;
            }
        }
    }
    return nums;
}

std::vector<std::tuple<int,int>> twins(std::vector<int> nums) {
    std::vector<std::tuple<int,int>> v;
    std::sort (nums.begin(), nums.end());
    for (int i = 0; i < nums.size(); i++) {
        if (std::binary_search (nums.begin(), nums.end(), nums[i] + 2)) {
            std::tuple<int, int> x = std::make_tuple(nums[i],nums[i] + 2);
            v.push_back(x);
        }
    }
    return v;
}
