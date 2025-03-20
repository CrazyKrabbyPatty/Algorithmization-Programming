#include "pch.h"
#include "CppUnitTest.h"
#include "../Algorithms Practice 1/Algorithms Practice 1.cpp"
#include <thread>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
    TEST_CLASS(CreateArrayTests)
    {
    public:
        TEST_METHOD(CreateArray_HandlesPositiveInput)
        {
            int n = 5;
            std::vector<int> expected = { 0, 1, 2, 3, 4 };

            std::vector<int> result = CreateArray(n);

            Assert::IsTrue(result == expected);
        }

        TEST_METHOD(CreateArray_HandlesNegativeInput)
        {
            int n = -5;
            std::vector<int> expected = { 0, 1, 2, 3, 4 };

            std::vector<int> result = CreateArray(n);

            Assert::IsTrue(result == expected);
        }
    };

    TEST_CLASS(RemoveNumbersFromEndTests)
    {
    public:
        TEST_METHOD(RemoveNumbersFromEnd_HandlesNonEmptyVector)
        {
            std::vector<int> arr = { 1, 2, 3, 4, 5 };

            RemoveNumbersFromEnd(arr);

            Assert::IsTrue(arr.empty());
        }

        TEST_METHOD(RemoveNumbersFromEnd_HandlesEmptyVector)
        {
            std::vector<int> arr;

            RemoveNumbersFromEnd(arr);

            Assert::IsTrue(arr.empty());
        }
    };

    TEST_CLASS(MeasureExecutionTimeTests)
    {
    public:
        TEST_METHOD(MeasureExecutionTime_HandlesFunctionExecution)
        {
            auto dummyFunc = []() { std::this_thread::sleep_for(std::chrono::milliseconds(100)); };

            float execution_time = measure_execution_time(dummyFunc);

            Assert::IsTrue(execution_time > 0);
        }
    };
}

