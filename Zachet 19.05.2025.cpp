#include <iostream>
#include <vector>
#include <map>

int temp;

using namespace std;

void show_vector(vector<int>& a)
{
    for (vector<int>::iterator it = a.begin(); it != a.end(); ++it)
        cout << *it << " ";
    cout << endl;
}

void show_dictionary(map<int, int> count_candy) 
{
    for (const auto& [key, value] : count_candy) {
        cout << "Друг " << key << " : " << "Конфеты " << value << endl;
    }
    cout << endl;
}

map<int, int> initialize_dictionary(int m) {
    map<int, int>count_candy;
    for (int guest = 0; m > guest; guest++) {
        count_candy[guest] = 0;
    }
    return count_candy;
}

map<int, int> impudence(int n, vector<int>& a, int m, vector<int>& b, map<int, int>& count_candy) {

    for (int guest = 0; m > guest; guest++) {

        for (int candy_box = 0; n > candy_box; candy_box++) {

            if (a[candy_box] >= b[guest]) {
                a[candy_box] -= b[guest];
                count_candy[guest] += b[guest];
            }
            else if (a[candy_box] > 0) {
                count_candy[guest] += a[candy_box];
                a[candy_box] = 0;
            }
            show_dictionary(count_candy);
        }

    }

    return count_candy;
}

int main()
{
    setlocale(LC_ALL, "ru");

    int n; // количество коробок конфет
    cout << "Введи количество коробок конфет: " << endl;
    cin >> n;

    vector<int> a; // количество конфет в каждой коробке
    cout << "Введите количество конфет в каждой коробке: " << endl;
    
    for (int i = 0; i < n; i++) {
        cin >> temp;
        a.push_back(temp);
    }

    //show_vector(a);

    int m; // количество гостей
    cout << "Введите количество гостей" << endl;
    cin >> m;

    cout << "Введите наглость каждого гостя" << endl;
    vector<int> b;
    for (int i = 0; i < m; i++) {
        cin >> temp;
        b.push_back(temp);
    }

    //show_vector(b);

    map<int, int> count_candy = initialize_dictionary(m);

    impudence(n, a, m, b, count_candy);

    show_dictionary(count_candy);

}