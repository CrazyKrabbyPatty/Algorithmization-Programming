#include <iostream>
#include <vector>
#include <chrono>
#include <string>

template <typename Func, typename... Args>
auto measure_execution_time(Func&& func, Args&&... args) {
    auto start_time = std::chrono::high_resolution_clock::now();  // Íà÷èíàåì îòñ÷åò âðåìåíè
    std::forward<Func>(func)(std::forward<Args>(args)...);  // Âûïîëíÿåì ïåðåäàííóþ ôóíêöèþ
    auto end_time = std::chrono::high_resolution_clock::now();  // Îñòàíàâëèâàåì îòñ÷åò âðåìåíè
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);  // Âû÷èñëÿåì ïðîäîëæèòåëüíîñòü â ìèëëèñåêóíäàõ
    return duration.count();  // Âîçâðàùàåì ðåçóëüòàò è âðåìÿ âûïîëíåíèÿ
}

int Insert()
{
    std::cout << "Ââåäèòå äèàïîçîí :\n";
    int x;
    while (!(std::cin >> x) or std::cin.get() != '\n')
    {
        std::cout << "Error!" <<std:: endl << "Ââåäèòå ÷èñëîâîå çíà÷åíèå :";
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
    setlocale(LC_ALL, "");
    int n = Insert();
    std::vector<int> arr = CreateArray(n);
    float execution_time = measure_execution_time(RemoveNumbersFromEnd, arr);
    std::cout << "Âðåìÿ âûïîëíåíèÿ: " << execution_time << " ìñ" << std::endl;

}
