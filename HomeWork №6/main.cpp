// Подключение зависимостей
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <set>
#include <algorithm>
#include <random>
#include <string>

using namespace std;
using namespace sf;

Font font;

int GRID_SIZE = 10; // Размер поля NxN (изменил для изначально для задания варианта)
int CELL_SIZE = 75; // Размер одной ячейки в пикселях
const int WINDOW_SIZE = 750;

// Типы ячеек
enum CellType {
    EMPTY,
    OBSTACLE,
    START,
    END,
    PATH,
    VISITED,
    QUEUED
};

// Структура для представления ячейки
struct Cell {
    int x, y;
    CellType type;
    int f, g, h, weight; // Для алгоритма A*
    Cell* parent;

    Cell(int x, int y) : x(x), y(y), type(EMPTY), f(0), g(INT_MAX), h(0), weight(0), parent(nullptr) {}

    // Перезагрузка оператора == для сравнения ячеек
    bool operator==(const Cell& other) const {
        return x == other.x && y == other.y;
    }

    void updateF() {
        f = g + h;
    }
};

// Функция для вычисления эвристики (манхэттенское расстояние)
int heuristic(const Cell& a, const Cell& b) {
    return abs(a.x - b.x) + abs(a.y - b.y);
}

// Функция для проверки, находится ли ячейка в пределах сетки
bool isValid(int x, int y) {
    return (x >= 0) and (x < GRID_SIZE) and (y >= 0) and (y < GRID_SIZE);
}

pair<pair<int, int>, pair<int, int>> make_grid(vector<vector<Cell>>& grid, bool weighted_grid = false) {
    if (grid.empty()) {
        //Задаём координаты старта и конца, а также поле хардкодом
        int start_x = 0;
        int start_y = 2;
        int end_x = 9;
        int end_y = 9;

        vector<vector<int>> gridtempl = {
            {0, 0, 0, 1, 0, 0, 0, 0, 0, 0},
            {1, 0, 0, 0, 0, 0, 0, 1, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 1, 0, 0, 1, 1, 0, 0, 0},
            {0, 0, 0, 1, 1, 0, 0, 0, 1, 1},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 1, 0, 0, 1, 0},
            {1, 1, 0, 0, 0, 1, 0, 0, 1, 1},
            {1, 0, 1, 0, 0, 1, 1, 0, 0, 0},
            {1, 0, 0, 0, 0, 0, 0, 0, 1, 0}
        };

        // Заполняем поле ячейками
        for (int x = 0; x < GRID_SIZE; x++) {
            vector<Cell> row;
            for (int y = 0; y < GRID_SIZE; y++) {
                Cell cell(x, y);

                // Расчет эвристики
                cell.h = abs(x - end_x) + abs(y - end_y);
                cell.updateF();

                // Если поле - препятствие, то помечаем
                if (gridtempl[y][x]) cell.type = OBSTACLE;

                row.push_back(cell);
            }
            grid.push_back(row);
        }

        // Получаем стартовую и конечное поле по координатам и помечаем их
        Cell* start = &grid[start_x][start_y];
        Cell* end = &grid[end_x][end_y];
        start->type = START;
        start->g = 0;
        end->type = END;

        // Возвращаем позиции старта и конца
        pair<int, int> startp(start_x, start_y);
        pair<int, int> endp(end_x, end_y);
        return make_pair(startp, endp);
    }
    else { // В противном случае поле пересобирается рандомно 
        grid.clear();

        // Используем генераторы
        random_device rd;
        mt19937 gen(rd()); // магия
        uniform_int_distribution<> distrib(0, GRID_SIZE - 1);
        uniform_int_distribution<> wdistr(1, 5);

        int start_x = distrib(gen);
        int start_y = distrib(gen);
        int end_x = distrib(gen);
        int end_y = distrib(gen);

        // Если старт и конец совпали, то перегенерируем конец
        while (start_x == end_x and start_y == end_y) {
            end_x = distrib(gen);
            end_y = distrib(gen);
        }

        // Заполняем поле рандомно
        for (int x = 0; x < GRID_SIZE; x++) {
            vector<Cell> row;
            for (int y = 0; y < GRID_SIZE; y++) {
                Cell cell(x, y);

                // Расчет эвристики
                cell.h = abs(x - end_x) + abs(y - end_y);
                cell.updateF();

                // Если поле с весом, заполнаем поле весом
                if (weighted_grid) cell.weight = wdistr(gen);

                row.push_back(cell);
            }
            grid.push_back(row);
        }

        // Получаем стартовую и конечную клетку
        Cell* start = &grid[start_x][start_y];
        Cell* end = &grid[end_x][end_y];
        start->type = START;
        start->g = 0;
        end->type = END;

        if (weighted_grid) {
            start->weight = 1;
            end->weight = 1;
        }

        // Расставляем препятствия
        int obstacle_count = GRID_SIZE * GRID_SIZE * 0.2;
        for (int i = 0; i < obstacle_count; i++) {
            int x = distrib(gen);
            int y = distrib(gen);
            if (not (grid[x][y] == *start or grid[x][y] == *end)) {
                Cell* cell = &grid[x][y];
                cell->type = OBSTACLE;
                cell->weight = 0;
            }
        }

        // Возвращаем позиции старта и конца
        pair<int, int> startp(start_x, start_y);
        pair<int, int> endp(end_x, end_y);
        return make_pair(startp, endp);
    }
}


Color Orange(229, 135, 34, 255);
Color Purple(90, 34, 139, 255);

// Функция отображения сетки
void draw_grid(RenderWindow& window, vector<vector<Cell>>& grid) {
    // Проходимся по каждой клетке сетки
    for (int x = 0; x < grid.size(); x++) {
        for (int y = 0; y < grid.size(); y++) {
            // Создаём прямоугольник с заданными размерами
            RectangleShape cell(Vector2f(CELL_SIZE, CELL_SIZE));
            // Задаём позицию клетки на сцене
            cell.setPosition(x * CELL_SIZE, y * CELL_SIZE);
            // В зависимости от состояния клетки выбираем цвет
            switch (grid[x][y].type) {
            case EMPTY: cell.setFillColor(Color::White); break;
            case OBSTACLE: cell.setFillColor(Color::Black); break;
            case START: cell.setFillColor(Orange); break;
            case END: cell.setFillColor(Color::Cyan); break;
            case PATH: cell.setFillColor(Purple); break;
            case VISITED: cell.setFillColor(Color::Red); break;
            case QUEUED: cell.setFillColor(Color::Green); break;
            }
            // Задаём цвет и толщину контура клетки
            cell.setOutlineColor(Color::Black);
            cell.setOutlineThickness(1);
            // Отрисовываем
            window.draw(cell);

            // Отображение веса клетки (для карты)
            if (grid[x][y].weight != 0) {
                Text weightText;
                weightText.setFont(font);
                weightText.setString(to_string(grid[x][y].weight));
                weightText.setCharacterSize(CELL_SIZE / 2);
                weightText.setFillColor(Color::Black);
                // Центрируем вес клетки
                FloatRect textRect = weightText.getLocalBounds();
                weightText.setOrigin(textRect.left + textRect.width / 2.0f,
                    textRect.top + textRect.height / 2.0f);
                weightText.setPosition(x * CELL_SIZE + CELL_SIZE / 2.0f,
                    y * CELL_SIZE + CELL_SIZE / 2.0f);
                // Отрисовывем вес
                window.draw(weightText);
            }
        }
    }
}

// Функция для сброса сетки
void reset_grid(vector<vector<Cell>>& grid, pair<pair<int, int>, pair<int, int>> st_end_pos) {
    // Координаты конечной точки
    pair<int, int> endp = st_end_pos.second;
    // Проходим по каждой клетке 
    for (int x = 0; x < grid.size(); x++) {
        for (int y = 0; y < grid.size(); y++) {
            Cell* cell = &grid[x][y];
            // Если клетка не является точкой старта и препятствием — обнуляем g
            if (cell->type != START && cell->type != OBSTACLE)
                cell->g = INT_MAX;

            // Используем манхэттенское расстояние до конечной клетки в качестве h
            cell->h = abs(x - endp.first) + abs(y - endp.second);
            cell->updateF();

            // Если клетка не конец, не старт и не препятствие — очищаем
            if (cell->type != END && cell->type != START && cell->type != OBSTACLE)
                cell->type = EMPTY;

            // Удаляем ссылку на родителя для алгоритма поиска пути
            cell->parent = nullptr;
        }
    }
}


int А_star(vector<vector<Cell>>& grid, RenderWindow& window, pair<pair<int, int>, pair<int, int>> st_end_pos) {
    // Компаратор для очереди с приоритетом (чем меньше F, тем выше приоритет)
    auto cmp = [](Cell* a, Cell* b) {
        return (a->f > b->f);
    };
    // Инициализация структур
    priority_queue<Cell*, vector<Cell*>, decltype(cmp)> open_list(cmp);
    set<pair<int, int>> open_list_hash;
    set<pair<int, int>> closed_list;
    // Извлекаем координаты старта и финиша
    pair<int, int> startp = st_end_pos.first;
    pair<int, int> endp = st_end_pos.second;
    // Получаем указатели старта и финиша
    Cell* start = &grid[startp.first][startp.second];
    Cell* end = &grid[endp.first][endp.second];
    // Добавляем стартовую клетку в открытый список
    open_list.push(start);
    open_list_hash.insert(make_pair(start->x, start->y));
    // Возможные направления движения для соседних вершин
    vector<pair<int, int>> destinations = {
        make_pair(-1,0), make_pair(1, 0),
        make_pair(0, -1), make_pair(0, 1)
    };

    cout << "Поиск пути от " << start->x << ';' << start->y << " к " << end->x << ';' << end->y << endl;

    while (!open_list.empty()) {
        // Извлекаем клетку с наименьшим F
        Cell* current = open_list.top();
        open_list.pop();
        // Если достигли конечной точки - строим путь
        if (current->type == END) {
            vector<Cell*> path;
            int weight = 0;
            // Восстанавливаем путь от конца к началу
            while (current != nullptr) {
                path.push_back(&grid[current->x][current->y]);
                current = current->parent;
            }
            // Разворачиваем путь (чтобы был от начала к концу)
            reverse(path.begin(), path.end());
            // Визуализация найденного пути
            for (int i = 0;i < path.size() - 1;i++) {
                Cell* cell = path[i];
                if (cell->type != START) cell->type = PATH;
                weight += cell->weight;
                window.clear(Color::White);
                draw_grid(window, grid);
                window.display();
            }
            if (weight != 0) cout << "Вес пути (без старта и конца): " << weight - 1 << endl;
            cout << "Длина пути (без старта и конца): " << path.size() - 2 << endl << endl;
            return 0;
        }
        // Помечаем текущую клетку как посещённую
        if (current->type != START) current->type = VISITED;
        closed_list.insert(make_pair(current->x, current->y));
        // Проверяем всех соседей
        for (int i = 0; i < destinations.size(); i++) {
            int nx = current->x + destinations[i].first;
            int ny = current->y + destinations[i].second;
            // Если соседняя клетка в пределах сетки
            if (isValid(nx, ny)) {
                Cell* neighbor = &grid[nx][ny];
                auto g = current->g + 1 + neighbor->weight;
                // Если клетка проходима и не является стартом
                if (neighbor->type != OBSTACLE and neighbor->type != START) {
                    // Если клетка ещё не посещалась
                    if (closed_list.find(make_pair(nx, ny)) == closed_list.end()) {
                        // Если нашли более короткий путь
                        if (g < neighbor->g) {
                            // Обновляем показатели
                            neighbor->parent = current;
                            neighbor->g = g;
                            neighbor->h = heuristic(*neighbor, *end);
                            neighbor->updateF();
                            // Если клетка не в открытом списке
                            if (open_list_hash.find(make_pair(nx, ny)) == open_list_hash.end()) {
                                if (neighbor->type != END) neighbor->type = QUEUED;
                                // Добавляем в очередь
                                open_list.push(neighbor);
                                // Помечаем как добавленную
                                open_list_hash.insert(make_pair(nx, ny));
                            }
                        }
                    }
                }
            }
        }
        // Обновляем отображение
        window.clear(Color::White);
        draw_grid(window, grid);
        window.display();
    }
    return 1;
}

int main() {
    // Русская локаль
    setlocale(LC_ALL, "ru");

    // Загружаем шрифт
    if (!font.loadFromFile("arial.ttf")) cout << "can't load font";

    // Выводим функционал в консоль
    cout << endl <<
        "--R - generate new grid (30x30)" << endl <<
        "--F - reset to demo grid (10x10)" << endl <<
        "--G - generate new map (grid with weights, 30x30)" << endl <<
        "--SPACE - launch A* pathfinder" << endl;

    // Инициализируем поле с ячейками и координатами старта и конца
    vector<vector<Cell>> grid;
    pair<pair<int, int>, pair<int, int>> st_end_pos;

    // Заполняем поле картой по умолчанию (10x10) с помощью make_grid()
    st_end_pos = make_grid(grid);

    // Флаг запуска A*
    bool pathfinderStarted = false;

    // Создаём окно
    RenderWindow window(VideoMode(WINDOW_SIZE, WINDOW_SIZE), "A*");

    // Запрещаем удерживать клавиши для повторных событий
    window.setKeyRepeatEnabled(false);

    // Главный цикл для отображения
    while (window.isOpen()) {
        Event event;
        // Обработка событий в очереди
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();

            if (event.type == Event::KeyPressed) {

                // Если R — перейти на поле 30x30 и сгенерировать его заново
                if (event.key.scancode == Keyboard::Scan::R) {
                    if (GRID_SIZE == 10) {
                        GRID_SIZE = 30;
                        CELL_SIZE = 25;
                    }
                    st_end_pos = make_grid(grid);
                }

                // Если G — перейти на поле 30x30 с весами
                if (event.key.scancode == Keyboard::Scan::G) {
                    if (GRID_SIZE == 10) {
                        GRID_SIZE = 30;
                        CELL_SIZE = 25;
                    }
                    st_end_pos = make_grid(grid, true);
                }

                // Если F — вернуться к полю 10x10 с точкой старта и целью по умолчанию
                if (event.key.scancode == Keyboard::Scan::F) {
                    if (GRID_SIZE != 10) {
                        GRID_SIZE = 10;
                        CELL_SIZE = 75;
                        grid.clear();
                        st_end_pos = make_grid(grid);
                    }
                }

                // Если SPACE — запускаем алгоритм А* на поле
                if (event.key.scancode == Keyboard::Scan::Space and not pathfinderStarted) {
                    reset_grid(grid, st_end_pos);
                    pathfinderStarted = true;
                    А_star(grid, window, st_end_pos);
                    pathfinderStarted = false;
                }
            }
        }
        // Чистим экран и перерисовываем поле
        window.clear(Color::White);
        draw_grid(window, grid);
        window.display();
    }
    return 0;
}


