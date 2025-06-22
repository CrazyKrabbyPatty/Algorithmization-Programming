#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Проверяет, можно ли назначить вершине vertex цвет color
bool isSafe(int vertex, int color, const vector<vector<int>>& graph,
    const vector<int>& colors) {
    // Проверяем всех соседей вершины
    for (int i = 0; i < graph.size(); ++i) {
        // Если есть связь с вершиной i и цвет совпадает - конфликт
        if (graph[vertex][i] == 1 && colors[i] == color) {
            return false;
        }
    }
    return true;
}

// Рекурсивная функция для раскраски графа
bool graphColoringUtil(int vertex, int k, const vector<vector<int>>& graph,
    vector<int>& colors) {

    // Все вершины раскрашены - решение найдено
    if (vertex == graph.size()) {
        return true;
    }

    // Пробуем все возможные цвета от 1 до k
    for (int color = 1; color <= k; ++color) {

        // Если цвет подходит для текущей вершины
        if (isSafe(vertex, color, graph, colors)) {
            colors[vertex] = color; // Ставим цвет

            // Рекурсивно раскрашиваем оставшиеся вершины
            if (graphColoringUtil(vertex + 1, k, graph, colors)) {
                return true;
            }

            // Сбрасываем цвет, если решение не найдено
            colors[vertex] = 0; // backtrack
        }
    }

    return false;
}

// Функция раскраски графа
bool graphColoring(int n, int k, const vector<vector<int>>& graph,
    vector<int>& colors) {
    colors.assign(n, 0); // Инициализируем массив цветов нулями
    return graphColoringUtil(0, k, graph, colors); // Начинаем с вершины 0
}

int main() {
    int n, k;
    cin >> n >> k; // Считаем количество вершин и цветов

    // Читаем матрицу смежности графа
    vector<vector<int>> graph(n, vector<int>(n));
    for (int i = 0; i < n; ++i) {
        string row;
        cin >> row;
        for (int j = 0; j < n; ++j) {
            graph[i][j] = row[j] - '0'; // Преобразуем символ в число
        } 
    }

    vector<int> colors; // Массив для хранения цветов вершин
    if (graphColoring(n, k, graph, colors)) {
        cout << "YES" << endl;

        // Выводим цвета вершин
        for (int color : colors) {
            cout << color << " ";
        }
        cout << endl;
    }
    else {
        cout << "NO" << endl;
    }

    return 0;
}