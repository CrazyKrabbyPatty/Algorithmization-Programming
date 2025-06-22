#include <iostream>
#include <vector>
#include <string>

using namespace std;

// ���������, ����� �� ��������� ������� vertex ���� color
bool isSafe(int vertex, int color, const vector<vector<int>>& graph,
    const vector<int>& colors) {
    // ��������� ���� ������� �������
    for (int i = 0; i < graph.size(); ++i) {
        // ���� ���� ����� � �������� i � ���� ��������� - ��������
        if (graph[vertex][i] == 1 && colors[i] == color) {
            return false;
        }
    }
    return true;
}

// ����������� ������� ��� ��������� �����
bool graphColoringUtil(int vertex, int k, const vector<vector<int>>& graph,
    vector<int>& colors) {

    // ��� ������� ���������� - ������� �������
    if (vertex == graph.size()) {
        return true;
    }

    // ������� ��� ��������� ����� �� 1 �� k
    for (int color = 1; color <= k; ++color) {

        // ���� ���� �������� ��� ������� �������
        if (isSafe(vertex, color, graph, colors)) {
            colors[vertex] = color; // ������ ����

            // ���������� ������������ ���������� �������
            if (graphColoringUtil(vertex + 1, k, graph, colors)) {
                return true;
            }

            // ���������� ����, ���� ������� �� �������
            colors[vertex] = 0; // backtrack
        }
    }

    return false;
}

// ������� ��������� �����
bool graphColoring(int n, int k, const vector<vector<int>>& graph,
    vector<int>& colors) {
    colors.assign(n, 0); // �������������� ������ ������ ������
    return graphColoringUtil(0, k, graph, colors); // �������� � ������� 0
}

int main() {
    int n, k;
    cin >> n >> k; // ������� ���������� ������ � ������

    // ������ ������� ��������� �����
    vector<vector<int>> graph(n, vector<int>(n));
    for (int i = 0; i < n; ++i) {
        string row;
        cin >> row;
        for (int j = 0; j < n; ++j) {
            graph[i][j] = row[j] - '0'; // ����������� ������ � �����
        } 
    }

    vector<int> colors; // ������ ��� �������� ������ ������
    if (graphColoring(n, k, graph, colors)) {
        cout << "YES" << endl;

        // ������� ����� ������
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