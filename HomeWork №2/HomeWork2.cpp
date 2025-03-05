#include <iostream>
#include <cmath>
#include <iomanip>

//2 < x < 7
//y = 3x2−2
//y = −x2 + 6

double simpson_rule(double (*f)(double), double a, double b, int n) {
    if (n % 2 == 1) n++; // Делаем n четным
    double h = (b - a) / n;
    double sum = f(a) + f(b);

    for (int i = 1; i < n; i += 2)
        sum += 4 * f(a + i * h);

    for (int i = 2; i < n - 1; i += 2)
        sum += 2 * f(a + i * h);

    return (h / 3) * sum;
}

double function_one(double x) {
    return 3 * pow(x, 2) - 2; // Интегрируемая функция
}

double function_two(double x) {
    return -pow(x, 2) + 6; // Интегрируемая функция
}

int main() {
    setlocale(LC_ALL, "RU");
    double result_one = simpson_rule(function_one, 2, 7, 1000);
    double result_two = simpson_rule(function_two, 2, 7, 1000);
    double result = result_one - result_two;
    std::cout << std::setprecision(20) << "Приближенное значение интеграла: " << result << std::endl;
    return 0;
}