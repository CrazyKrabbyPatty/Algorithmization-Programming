#include <iostream>
#include <vector>
#include <climits>
using namespace std;

// –ешение с использованием Ђраздел€й и властвуйї дл€ нахождени€ минимального и максимального числа в массиве
void findMinAndMax(vector<int> const& nums, int low, int high, int& min, int& max)
{
    // если массив содержит только один элемент

    if (low == high) // обычное сравнение
    {
        if (max < nums[low]) { // сравнение 1
            max = nums[low];
        }

        if (min > nums[high]) { // сравнение 2
            min = nums[high];
        }

        return;
    }

    // если массив содержит только два элемента

    if (high - low == 1) // обычное сравнение
    {
        if (nums[low] < nums[high]) // сравнение 1
        {
            if (min > nums[low]) { // сравнение 2
                min = nums[low];
            }

            if (max < nums[high]) { // сравнение 3
                max = nums[high];
            }
        }
        else {
            if (min > nums[high]) { // сравнение 2
                min = nums[high];
            }

            if (max < nums[low]) { // сравнение 3
                max = nums[low];
            }
        }
        return;
    }

    // средний элемент
    int mid = (low + high) / 2;

    // повтор€ем дл€ левого подмассива
    findMinAndMax(nums, low, mid, min, max);

    // повторить дл€ правого подмассива
    findMinAndMax(nums, mid + 1, high, min, max);
}

int main()
{
    vector<int> nums = { 5, 7, 2, 4, 9, 6 };

    // инициализируем минимальный элемент значением INFINITY и
    // максимальный элемент по -INFINITY
    int max = INT_MIN, min = INT_MAX;

    int n = nums.size();
    findMinAndMax(nums, 0, n - 1, min, max);

    cout << "The minimum array element is " << min << endl;
    cout << "The maximum array element is " << max << endl;

    return 0;
}