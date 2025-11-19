#include <iostream>
#include <vector>
using namespace std;

int findUnique(vector<int> &nums);

vector<int> logs = {2, 5, 1, 1, 4, 5, 2, 4, 112};

int main()
{
    cout << findUnique(logs) << endl;
    return 0;
}

int findUnique(vector<int> &nums)
{
    int unique_id = 0;
    for (int num : nums)
    {
        unique_id = unique_id ^ num;
    }
    return unique_id;
}
