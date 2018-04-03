/* 
   Problem introduction:
   
   You are given a primitive calculator that can perform the following three operations with the current number
   x: multiply x by 2, multiply x by 3, or add 1 to x. Your goal is given a positive integer n, find the
   minimum number of operations needed to obtain the number n starting from the number 1.
   
   Example:
   
   Input
      96234
   
   Output 
      14
      1 3 9 10 11 22 66 198 594 1782 5346 16038 16039 32078 96234

*/


#include <iostream>
#include <vector>
#include <algorithm>
 
using std::vector;  
 
vector<int> optimal_sequence(int n) {
    std::vector<int> MinNumOps;
    std::vector<int> sequence;
    int tempValue, i;
    MinNumOps.push_back(0);
    MinNumOps.push_back(0);
 
    for (i = 2; i <= n; i++) {
        MinNumOps.push_back(i);
        if (i % 3 == 0 && MinNumOps[i / 3] < MinNumOps[i - 1]) {
            MinNumOps[i] = MinNumOps[i / 3] + 1;
        }
        else if (i % 2 == 0 && MinNumOps[i / 2] < MinNumOps[i - 1]) {
            MinNumOps[i] = MinNumOps[i / 2] + 1;
        }
        else MinNumOps[i] = MinNumOps[i - 1] + 1;
    }
 
    for (sequence.push_back(n); n != 1;) {
        if (n % 3 == 0) {
            tempValue = n / 3;
            if (MinNumOps[tempValue] == MinNumOps[n] - 1) {
                n = tempValue;
                sequence.push_back(n);
            }
        }
        if (n % 2 == 0) {
            tempValue = n / 2;
            if (MinNumOps[tempValue] == MinNumOps[n] - 1) {
                n = tempValue;
                sequence.push_back(n);
            }
        }
        tempValue = n - 1;
        if (MinNumOps[tempValue] == MinNumOps[n] - 1) {
            n = tempValue;
            sequence.push_back(n);
        }
    }
    reverse(sequence.begin(), sequence.end());
    return sequence;
}
 
int main() {
    int n;
    std::cin >> n; // For example, 238
    vector<int> sequence = optimal_sequence(n);
    std::cout << sequence.size() - 1 << std::endl;
    for (size_t i = 0; i < sequence.size(); ++i) {
        std::cout << sequence[i] << " ";
    }
    system("pause");
    return 0;
}
