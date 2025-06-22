#include "pch.h"
#include "CppUnitTest.h"
#include "../Divide and Conquer 1/Divide and Conquer 1.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestforDivandCon1
{
	TEST_CLASS(UnitTestforDivandCon1)
	{
	public:
        // Массив из одного элемента
        TEST_METHOD(TestSingleElementArray)
        {
            std::vector<int> nums = { 42 };
            int min = INT_MAX;
            int max = INT_MIN;

            findMinAndMax(nums, 0, nums.size() - 1, min, max);

            Assert::AreEqual(42, min);
            Assert::AreEqual(42, max);
        }

        // Два элемента по возрастанию
        TEST_METHOD(TestTwoElementsAscending)
        {
            std::vector<int> nums = { 3, 7 };
            int min = INT_MAX;
            int max = INT_MIN;

            findMinAndMax(nums, 0, nums.size() - 1, min, max);

            Assert::AreEqual(3, min);
            Assert::AreEqual(7, max);
        }
        
        // Два элемента по убыванию
        TEST_METHOD(TestTwoElementsDescending)
        {
            std::vector<int> nums = { 9, 4 };
            int min = INT_MAX;
            int max = INT_MIN;

            findMinAndMax(nums, 0, nums.size() - 1, min, max);

            Assert::AreEqual(4, min);
            Assert::AreEqual(9, max);
        }
        
        // Чётное количество элементов
        TEST_METHOD(TestEvenNumberOfElements)
        {
            std::vector<int> nums = { 5, 7, 2, 4, 9, 6 };
            int min = INT_MAX;
            int max = INT_MIN;

            findMinAndMax(nums, 0, nums.size() - 1, min, max);

            Assert::AreEqual(2, min);
            Assert::AreEqual(9, max);
        }
        
        // Нечётное количество элементов
        TEST_METHOD(TestOddNumberOfElements)
        {
            std::vector<int> nums = { 8, 3, 5, 1, 10 };
            int min = INT_MAX;
            int max = INT_MIN;

            findMinAndMax(nums, 0, nums.size() - 1, min, max);

            Assert::AreEqual(1, min);
            Assert::AreEqual(10, max);
        }

        // Все элементы одинаковые
        TEST_METHOD(TestAllSameElements)
        {
            std::vector<int> nums = { 5, 5, 5, 5 };
            int min = INT_MAX;
            int max = INT_MIN;

            findMinAndMax(nums, 0, nums.size() - 1, min, max);

            Assert::AreEqual(5, min);
            Assert::AreEqual(5, max);
        }

        // Большой массив с 1000 элементами
        TEST_METHOD(TestLargeArray)
        {
            std::vector<int> nums(1000);
            for (int i = 0; i < 1000; ++i) {
                nums[i] = i + 1;
            }
            nums[500] = -10;
            nums[999] = 2000;

            int min = INT_MAX;
            int max = INT_MIN;

            findMinAndMax(nums, 0, nums.size() - 1, min, max);

            Assert::AreEqual(-10, min);
            Assert::AreEqual(2000, max);
        }
	};
}
