#include <iostream>
#include <vector>
#include <chrono>
#include <string>

template <typename Func, typename... Args>
auto measure_execution_time(Func&& func, Args&&... args) {
    auto start_time = std::chrono::high_resolution_clock::now();  // Начинаем отсчет времени
    std::forward<Func>(func)(std::forward<Args>(args)...);  // Выполняем переданную функцию
    auto end_time = std::chrono::high_resolution_clock::now();  // Останавливаем отсчет времени
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);  // Вычисляем продолжительность в миллисекундах
    return duration.count();  // Возвращаем результат и время выполнения
}

int Insert()
{
    std::cout << "Введите диапозон :\n";
    int x;
    while (!(std::cin >> x) || std::cin.get() != '\n')
    {
        std::cout << "Error!" <<std:: endl << "Введите числовое значение :";
        std::cin.clear();
        while (std::cin.get() != '\n');
    }
    return x;
}

std::vector<int> CreateArray(int n) {

    if (n <= 0) {
        n = -n;
    }

    std::vector<int> arr;
    for (int i = 0; i < n; i++) {
        arr.push_back(i);
    }
    return arr;
}

void RemoveNumbersFromEnd(std::vector<int>& arr) {
    while (!arr.empty()) {
        arr.pop_back();
    }
}

int main()
{
    setlocale(LC_ALL, "ru");
    int n = Insert();
    std::vector<int> arr = CreateArray(n);
    float execution_time = measure_execution_time(RemoveNumbersFromEnd, arr);
    std::cout << "Время выполнения: " << execution_time << " мс" << std::endl;

}