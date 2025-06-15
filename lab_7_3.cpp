#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MAX_RECURSION_DEPTH = 1000; // Максимальная глубина рекурсии
int recursion_depth = 0; // Счётчик глубины рекурсии

bool canPlaceItems(vector<int>& items, vector<int>& containers, int H, int index) {
    // Проверка на превышение глубины рекурсии
    if (recursion_depth > MAX_RECURSION_DEPTH) {
        cout << "Превышена максимальная глубина рекурсии!" << endl;
        return false;
    }
    recursion_depth++;
    
    // Все предметы размещены успешно
    if (index == items.size()) {
        return true;
    }
    
    // Пробуем разместить текущий предмет в каждом контейнере
    for (int i = 0; i < containers.size(); i++) {
        if (containers[i] + items[index] <= H) { // если по высоте проходит
            containers[i] += items[index];
            if (canPlaceItems(items, containers, H, index + 1)) {
                return true;
            }
            // Откатываем изменения 
            containers[i] -= items[index]; // заново
        }
    }
    
    return false;
}

int main() {
    int N, H, M;
    cout << "Введите количество контейнеров (N): ";
    cin >> N;
    cout << "Введите высоту каждого контейнера (H): ";
    cin >> H;
    cout << "Введите количество предметов: ";
    cin >> M;
    
    vector<int> items(M);
    cout << "Введите высоты предметов: ";
    for (int i = 0; i < M; i++) {
        cin >> items[i]; // для каждого
    }
    
    // Сортируем предметы в порядке убывания для оптимизации
    sort(items.begin(), items.end(), greater<int>());
    
    vector<int> containers(N, 0); // Изначально все контейнеры пусты
    
    recursion_depth = 0; // Сброс счётчика перед вызовом
    if (canPlaceItems(items, containers, H, 0)) {
        cout << "Предметы можно разместить в контейнерах!" << endl;
    } else {
        cout << "Предметы нельзя разместить в контейнерах." << endl;
    }
    
    return 0;
}
