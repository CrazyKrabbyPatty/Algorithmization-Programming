#include "pch.h"
#include "CppUnitTest.h"
#include "../HomeWork2/HomeWork2.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		TEST_METHOD(AlmostEqual_N_2)
		{
			double result_one = simpson_rule(function_one, 2, 7, 2);
			double result_two = simpson_rule(function_two, 2, 7, 2);
			double result = result_one - result_two;
			Assert::AreEqual(result, 406.667, 3, L"Значения совпали с точностью до 3-ёх");
		}

		TEST_METHOD(AlmostEqual_N_10)
		{	
			double result_one = simpson_rule(function_one, 2, 7, 10);
			double result_two = simpson_rule(function_two, 2, 7, 10);
			double result = result_one - result_two;
			Assert::AreEqual(result, 406.667, 3, L"Значения совпали с точностью до 3-ёх");
		}

		TEST_METHOD(AlmostEqual_N_100)
		{
			double result_one = simpson_rule(function_one, 2, 7, 100);
			double result_two = simpson_rule(function_two, 2, 7, 100);
			double result = result_one - result_two;
			Assert::AreEqual(result, 406.667, 3, L"Значения совпали с точностью до 3-ёх");
		}
	};
}
