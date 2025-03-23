#include "pch.h"
#include "CppUnitTest.h"
#include "../HomeWork 3 For 17.03.2025/HomeWork 3 For 17.03.2025.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{
	TEST_CLASS(UnitTest)
	{
	public:

        TEST_METHOD(TestCombSorting)
        {
            std::vector<int> array = { 5, 3, 8, 4, 6 };
            std::vector<int> expected = { 3, 4, 5, 6, 8 };

            CombSorting(array);

            Assert::IsTrue(array == expected);
        }

        TEST_METHOD(TestShellSorting)
        {
            std::vector<int> array = { 5, 3, 8, 4, 6 };
            std::vector<int> expected = { 3, 4, 5, 6, 8 };

            ShellSorting(array);

            Assert::IsTrue(array == expected);
        }

        TEST_METHOD(TestQuickSort)
        {
            std::vector<int> array = { 5, 3, 8, 4, 6 };
            std::vector<int> expected = { 3, 4, 5, 6, 8 };

            QuickSort(array, 0, array.size() - 1);

            Assert::IsTrue(array == expected);
        }
	};
}
