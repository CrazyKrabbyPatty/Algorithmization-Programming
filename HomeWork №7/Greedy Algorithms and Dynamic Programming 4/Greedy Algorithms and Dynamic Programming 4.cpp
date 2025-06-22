#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <sstream>
#include <string>

using namespace std;

// ������� ��� ����������� ������������ ���������� �������
// ���� ���� �� ���������� 0, ���������� ���������
int minBanknotes(int a, int b) {
    if (a == 0 || b == 0) {
        return (a > b) ? a : b;
    }
    return (a < b) ? a : b;
}

// ������� ������ ������� ������
void readInput(int& housePrice, int& numDenominations, vector<int>& denominations) {
    string line;

    // ������ ��������� ����
    getline(cin, line);
    housePrice = stoi(line);

    // ������ ���������� ���������
    getline(cin, line);
    numDenominations = stoi(line);

    // ������ ������ � ���������� � ��������� �� �����
    getline(cin, line);
    istringstream iss(line);
    denominations.resize(numDenominations);
    for (int i = 0; i < numDenominations; ++i) {
        iss >> denominations[i];
    }
}

// �������� ������� ��� ������ ������������ ���������� �������
void findMinBanknotes(int housePrice, int numDenominations, const vector<int>& denominations, string& result) {
    int minBanknotesNeeded = -1;

    // ��� ������� ��� ������������� �������
    vector<int> prevDP(housePrice + 1, 0);
    vector<int> currentDP(housePrice + 1, 0);

    // ���������� ��� �������� �����
    for (int i = 0; i < numDenominations; ++i) {
        // ��� ������ ��������� ����� �� 0 �� housePrice
        for (int amount = 0; amount <= housePrice; ++amount) {
            // �������� ����������� ����� ������� � ���������� ���������
            currentDP[amount] = minBanknotes(currentDP[amount], prevDP[amount]);
            // ���� ����� ������������ ������� ������ ��� ���� �����
            if (amount - denominations[i] >= 0 &&
                (currentDP[amount - denominations[i]] > 0 || amount % denominations[i] == 0)) {
                // ��������� ����������� ���������� �����
                currentDP[amount] = minBanknotes(currentDP[amount], currentDP[amount - denominations[i]] + 1);
            }
        }
        prevDP = currentDP; // ��������� � ��������� ��������
        currentDP.assign(housePrice + 1, 0); // ���������� ������� ������
    }

    // ���� ����� �������
    if (prevDP[housePrice] > 0) {
        minBanknotesNeeded = prevDP[housePrice];
    }

    result = to_string(minBanknotesNeeded); // ���������� ���������
}

int main() {
    int housePrice, numDenominations;
    vector<int> denominations;

    // ������ ������� ������
    readInput(housePrice, numDenominations, denominations);

    string result;

    // ���� ����������� ���������� �������
    findMinBanknotes(housePrice, numDenominations, denominations, result);

    // ����� � �������
    cout << result << endl;

    return 0;
}