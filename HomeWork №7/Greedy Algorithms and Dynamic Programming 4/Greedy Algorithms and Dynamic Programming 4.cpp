#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <sstream>
#include <string>

using namespace std;

// Функция для определения минимального количества банкнот
// Если один из аргументов 0, возвращает ненулевой
int minBanknotes(int a, int b) {
    if (a == 0 || b == 0) {
        return (a > b) ? a : b;
    }
    return (a < b) ? a : b;
}

// Функция чтения входных данных
void readInput(int& housePrice, int& numDenominations, vector<int>& denominations) {
    string line;

    // Читаем стоимость дома
    getline(cin, line);
    housePrice = stoi(line);

    // Читаем количество номиналов
    getline(cin, line);
    numDenominations = stoi(line);

    // Читаем строку с номиналами и разбиваем на числа
    getline(cin, line);
    istringstream iss(line);
    denominations.resize(numDenominations);
    for (int i = 0; i < numDenominations; ++i) {
        iss >> denominations[i];
    }
}

// Основная функция для поиска минимального количества банкнот
void findMinBanknotes(int housePrice, int numDenominations, const vector<int>& denominations, string& result) {
    int minBanknotesNeeded = -1;

    // Два массива для динамического рещения
    vector<int> prevDP(housePrice + 1, 0);
    vector<int> currentDP(housePrice + 1, 0);

    // Перебираем все номиналы купюр
    for (int i = 0; i < numDenominations; ++i) {
        // Для каждой возможной суммы от 0 до housePrice
        for (int amount = 0; amount <= housePrice; ++amount) {
            // Выбираем минимальное между текущим и предыдущим значением
            currentDP[amount] = minBanknotes(currentDP[amount], prevDP[amount]);
            // Если можно использовать текущую купюру для этой суммы
            if (amount - denominations[i] >= 0 &&
                (currentDP[amount - denominations[i]] > 0 || amount % denominations[i] == 0)) {
                // Обновляем минимальное количество купюр
                currentDP[amount] = minBanknotes(currentDP[amount], currentDP[amount - denominations[i]] + 1);
            }
        }
        prevDP = currentDP; // Переходим к следующей итерации
        currentDP.assign(housePrice + 1, 0); // Сбрасываем текущую строку
    }

    // Если нашли решение
    if (prevDP[housePrice] > 0) {
        minBanknotesNeeded = prevDP[housePrice];
    }

    result = to_string(minBanknotesNeeded); // Записываем результат
}

int main() {
    int housePrice, numDenominations;
    vector<int> denominations;

    // Читаем входные данные
    readInput(housePrice, numDenominations, denominations);

    string result;

    // Ищем минимальное количество банкнот
    findMinBanknotes(housePrice, numDenominations, denominations, result);

    // Вывод в консоль
    cout << result << endl;

    return 0;
}