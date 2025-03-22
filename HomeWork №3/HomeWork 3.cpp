#include <iostream>
#include <random>
#include <chrono>

// Вариант 12
// Сортировка Расчёской 
// Сортировка Шелла
// Быстрая сортировка 

std::vector<int> array;
const int ARRAY_SIZE = 50000;

void generateArray() {
    array.clear();
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(10, 1000000);

    for (int i = 0; i < ARRAY_SIZE; i++) {
        array.push_back(dist(gen));
    }
}

template <typename Func, typename... Args>
auto measure_execution_time(Func&& func, Args&&... args) {
    auto start_time = std::chrono::high_resolution_clock::now();
    std::forward<Func>(func)(std::forward<Args>(args)...);
    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
    return duration.count();
}

void CombSorting(std::vector<int>& array) {
    int n = array.size();
    int step = n - 1;
    while (step > 1) {
        step = step / 1.3;
        int i = 0;
        while (i + step < n) {
            if (array[i] > array[i + step]) {
                std::swap(array[i], array[i + step]);
            }
            else {
                i++;
            }
        }
    }
}

void ShellSorting(std::vector<int>& array) {
    int n = array.size();
    int step = n / 2;

    while (step > 0) {
        for (int i = step; i < n; i++) {
            int temp = array[i];
            int j = i;
            while (j >= step && array[j - step] > temp) {
                array[j] = array[j - step];
                j -= step;
            }
            array[j] = temp;
        }
        step /= 2;
    }
}

int partition(std::vector<int>& array, int low, int high) {
    int pivot = array[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        if (array[j] < pivot) {
            i++;
            std::swap(array[i], array[j]);
        }
    }
    std::swap(array[i + 1], array[high]);
    return (i + 1);
}

void QuickSort(std::vector<int>& array, int low, int high) {
    if (low < high) {
        int pi = partition(array, low, high);

        QuickSort(array, low, pi - 1);
        QuickSort(array, pi + 1, high);
    }
}

int main()
{
    setlocale(LC_ALL, "ru");

    generateArray();
    double CombSorting_Time = measure_execution_time(CombSorting, array);

    generateArray();
    double ShellSorting_Time = measure_execution_time(ShellSorting, array);

    generateArray();
    double QuickSort_Time = measure_execution_time(QuickSort, array, 0, array.size() - 1);

    std::cout << "Время выполнения Расчески: " << CombSorting_Time << "мс" << std::endl;
    std::cout << "Время выполнения Шелла: " << ShellSorting_Time << "мс" << std::endl;
    std::cout << "Время выполнения быстрой сортировки: " << QuickSort_Time << "мс" << std::endl;


}
