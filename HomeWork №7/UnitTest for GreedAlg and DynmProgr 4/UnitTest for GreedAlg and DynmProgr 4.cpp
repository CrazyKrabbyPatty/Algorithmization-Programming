#include "pch.h"
#include "CppUnitTest.h"
#include "../Greedy Algorithms and Dynamic Programming 4/Greedy Algorithms and Dynamic Programming 4.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestforGreedAlgandDynmProgr4
{
	TEST_CLASS(UnitTestforGreedAlgandDynmProgr4)
	{
	public:
		// ������� ������
        TEST_METHOD(TestMinBanknotes_BasicCases)
        {
            Assert::AreEqual(3, minBanknotes(3, 5));
            Assert::AreEqual(2, minBanknotes(5, 2));
            // ������ � ������
            Assert::AreEqual(5, minBanknotes(0, 5));
            Assert::AreEqual(5, minBanknotes(5, 0));
        }

        // ������������ ������ ������� ������
        TEST_METHOD(TestReadInput_ValidInput)
        {
            // ���������� �������� ������
            stringstream testInput;
            testInput << "15\n3\n2 3 5\n";

            // �������������� cin �� ��� stringstream
            streambuf* origCin = cin.rdbuf();
            cin.rdbuf(testInput.rdbuf());

            int housePrice, numDenominations;
            vector<int> denominations;

            readInput(housePrice, numDenominations, denominations);

            // ��������������� cin
            cin.rdbuf(origCin);

            // ��������� ����������
            Assert::AreEqual(15, housePrice);
            Assert::AreEqual(3, numDenominations);
            Assert::AreEqual(2, denominations[0]);
            Assert::AreEqual(3, denominations[1]);
            Assert::AreEqual(5, denominations[2]);
        }

        // ������ ������������ �����
        TEST_METHOD(TestFindMinBanknotes_ExactMatch)
        {
            vector<int> denominations = { 2, 3, 5 };
            string result;
            findMinBanknotes(15, 3, denominations, result);
            Assert::AreEqual(string("3"), result);
        }

        // ��������� ��������� �������
        TEST_METHOD(TestFindMinBanknotes_MultipleOptions)
        {
            vector<int> denominations = { 2, 3, 5 };
            string result;
            findMinBanknotes(7, 3, denominations, result);
            Assert::AreEqual(string("2"), result); // 2+5 ��� 2+2+3
        }

        // C�����, ����� ������ ����������
        TEST_METHOD(TestFindMinBanknotes_NoSolution)
        {
            vector<int> denominations = { 2, 4 };
            string result;
            findMinBanknotes(3, 2, denominations, result);
            Assert::AreEqual(string("-1"), result);
        }

        // ������ ���� ������� �����
        TEST_METHOD(TestFindMinBanknotes_SingleDenomination)
        {
            vector<int> denominations = { 5 };
            string result;
            findMinBanknotes(15, 1, denominations, result);
            Assert::AreEqual(string("3"), result);
        }

        // ������� �����
        TEST_METHOD(TestFindMinBanknotes_ZeroAmount)
        {
            vector<int> denominations = { 2, 3, 5 };
            string result;
            findMinBanknotes(0, 3, denominations, result);
            Assert::AreEqual(string("-1"), result);
        }

        // ������� ����� ��� �������
        TEST_METHOD(TestFindMinBanknotes_LargeAmount)
        {
            vector<int> denominations = { 3, 7, 10 };
            string result;
            findMinBanknotes(100, 3, denominations, result);
            Assert::AreEqual(string("10"), result); // 10 * 10
        }
	};
}
