#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>

// виды рекурсии прямая(сама себя), косвенная(через другую рекурсию)

using namespace std;
using namespace sf;  // пространство имен для библиотеки SFML

// Структура для представления отрезка
struct Segment {
    double start;
    double end;
};

// Рекурсивная функция для генерации множества Кантора
void cantorSet(vector<Segment>& segments, double start, double end, int n, int& counter, int maxDepth) {
    counter++; // повышаем глубину рекурсии

    if (counter > maxDepth) {
        cout << "Превышена максимальная глубина рекурсии!" << endl;
        return;
    }

    if (n == 0) { // вывод n=0
        segments.push_back({start, end});
        return;
    }

    double length = end - start;
    double third1 = start + length / 3.0;  // параметры длины на 2/3 меньше, чем у предыдущего
    double third2 = end - length / 3.0;

    cantorSet(segments, start, third1, n - 1, counter, maxDepth);
    cantorSet(segments, third2, end, n - 1, counter, maxDepth); // реализация отрезков n-1 и тд
}

int main() {
    int n, maxDepth = 1000; // параметры
    cout << "Введите количество итераций для множества Кантора: ";
    cin >> n;

    vector<Segment> segments;
    int recursionCounter = 0;
    cantorSet(segments, 0.0, 1.0, n, recursionCounter, maxDepth); // генерация сегментов

    // Создаем окно для графического вывода
    RenderWindow window(VideoMode(800, 600), "Множество Кантора");
    window.setFramerateLimit(60);

    // Основной цикл отрисовки
    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();
        }

        window.clear(Color::White);

        // Рисуем отрезки множества Кантора
        float y_pos = 50.f;
        float level_height = 50.f; // расположение
        float scale = 700.f; // Масштаб

        for (int level = 0; level <= n; level++) {
            // Находим все отрезки текущего уровня
            vector<Segment> current_level;
            int temp_counter = 0;
            cantorSet(current_level, 0.0, 1.0, level, temp_counter, maxDepth);

            // Рисуем отрезки текущего уровня
            for (auto& segment : current_level) {
                RectangleShape line(Vector2f((segment.end - segment.start) * scale, 5.f));
                line.setPosition(50 + segment.start * scale, y_pos);
                line.setFillColor(Color::Black);
                window.draw(line);
            }

            y_pos += level_height; // на уровень ниже
        }

        window.display();
    }

    return 0;
}
