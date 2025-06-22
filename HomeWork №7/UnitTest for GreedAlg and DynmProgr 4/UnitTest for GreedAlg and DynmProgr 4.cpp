#include "pch.h"
#include "CppUnitTest.h"
#include "../Greedy Algorithms and Dynamic Programming 4/Greedy Algorithms and Dynamic Programming 4.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestforGreedAlgandDynmProgr4
{
	TEST_CLASS(UnitTestforGreedAlgandDynmProgr4)
	{
	public:
		// Базовые случаи
        TEST_METHOD(TestMinBanknotes_BasicCases)
        {
            Assert::AreEqual(3, minBanknotes(3, 5));
            Assert::AreEqual(2, minBanknotes(5, 2));
            // случаи с нулями
            Assert::AreEqual(5, minBanknotes(0, 5));
            Assert::AreEqual(5, minBanknotes(5, 0));
        }

        // Корректность чтения входных данных
        TEST_METHOD(TestReadInput_ValidInput)
        {
            // Подготовка тестовых данных
            stringstream testInput;
            testInput << "15\n3\n2 3 5\n";

            // Перенаправляем cin на наш stringstream
            streambuf* origCin = cin.rdbuf();
            cin.rdbuf(testInput.rdbuf());

            int housePrice, numDenominations;
            vector<int> denominations;

            readInput(housePrice, numDenominations, denominations);

            // Восстанавливаем cin
            cin.rdbuf(origCin);

            // Проверяем результаты
            Assert::AreEqual(15, housePrice);
            Assert::AreEqual(3, numDenominations);
            Assert::AreEqual(2, denominations[0]);
            Assert::AreEqual(3, denominations[1]);
            Assert::AreEqual(5, denominations[2]);
        }

        // Точное соответствие суммы
        TEST_METHOD(TestFindMinBanknotes_ExactMatch)
        {
            vector<int> denominations = { 2, 3, 5 };
            string result;
            findMinBanknotes(15, 3, denominations, result);
            Assert::AreEqual(string("3"), result);
        }

        // Несколько вариантов размена
        TEST_METHOD(TestFindMinBanknotes_MultipleOptions)
        {
            vector<int> denominations = { 2, 3, 5 };
            string result;
            findMinBanknotes(7, 3, denominations, result);
            Assert::AreEqual(string("2"), result); // 2+5 или 2+2+3
        }

        // Cлучай, когда размен невозможен
        TEST_METHOD(TestFindMinBanknotes_NoSolution)
        {
            vector<int> denominations = { 2, 4 };
            string result;
            findMinBanknotes(3, 2, denominations, result);
            Assert::AreEqual(string("-1"), result);
        }

        // Только один номинал купюр
        TEST_METHOD(TestFindMinBanknotes_SingleDenomination)
        {
            vector<int> denominations = { 5 };
            string result;
            findMinBanknotes(15, 1, denominations, result);
            Assert::AreEqual(string("3"), result);
        }

        // Нулевая сумма
        TEST_METHOD(TestFindMinBanknotes_ZeroAmount)
        {
            vector<int> denominations = { 2, 3, 5 };
            string result;
            findMinBanknotes(0, 3, denominations, result);
            Assert::AreEqual(string("-1"), result);
        }

        // Большая сумма для размена
        TEST_METHOD(TestFindMinBanknotes_LargeAmount)
        {
            vector<int> denominations = { 3, 7, 10 };
            string result;
            findMinBanknotes(100, 3, denominations, result);
            Assert::AreEqual(string("10"), result); // 10 * 10
        }
	};
}
