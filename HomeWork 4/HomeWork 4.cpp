#include <iostream>
#include <random>
#include <chrono>
#include <vector>
#include <thread>

std::vector<int> array;
const int ARRAY_SIZE = 500000000;

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

void QuickSort_threading(std::vector<int>& array, int num_threads)
{
    int size = array.size();
    int chunkSize = size / num_threads;
    std::vector<std::thread> threads;
    for (int i = 0; i < num_threads; ++i) {
        int start = i * chunkSize;
        int end;
        if (i == num_threads - 1) {
            end = size - 1;
        }
        else {
            end = start + chunkSize - 1;
        }
        threads.emplace_back(QuickSort, std::ref(array), start, end);
    }

    for (auto& thread : threads) {
        thread.join();
    }

    int step = chunkSize;
    while (step < size) {
        for (int i = 0; i < size - step; i += 2 * step) {
            int left = i;
            int mid = i + step;
            int right = std::min(i + 2 * step, size);

            std::inplace_merge(array.begin() + left, array.begin() + mid, array.begin() + right);
        }
        step *= 2;
    }
}

int main()
{
    setlocale(LC_ALL, "ru");

    generateArray();
    double QuickSort_Time = measure_execution_time(QuickSort, array, 0, array.size() - 1);

    std::cout << "Âðåìÿ âûïîëíåíèÿ áûñòðîé ñîðòèðîâêè: " << QuickSort_Time << "ìñ" << std::endl;

}
