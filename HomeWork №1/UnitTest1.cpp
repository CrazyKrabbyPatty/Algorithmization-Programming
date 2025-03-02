#include "pch.h"
#include "CppUnitTest.h"
#include "../Algorithms Practice 1/Algorithms Practice 1.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
    TEST_CLASS(UnitTest1)
    {
    public:
        TEST_METHOD(TestNegativeNumberForArray) {
            Assert::IsFalse(CreateArray(-1000000).empty());
        }
        //TEST_METHOD(TestEmptyArray) {
        //    std::vector<int> arr{ 1, 2, 3, 4, 5 };
        //    RemoveNumbersFromEnd(arr);
        //    Assert::IsFalse(arr.empty());
        //}
    };
}