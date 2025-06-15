#include <iostream>
#include <vector>
#include <string>

using namespace std;

int recursion_counter = 0;
const int MAX_RECURSION_DEPTH = 1000;

// Функция для проверки наличия слова в словаре
bool contains(const vector<string> dict, const string word) {
    for (const string w : dict) { // проходимся по словарю
        if (w == word) {
            return true;
        }
    }
    return false;
}

bool wordBreak(const string s, const vector<string> wordDict) { // можно ли составить строку из слов словаря
    recursion_counter++;
    if (recursion_counter > MAX_RECURSION_DEPTH) {
        cout << "Превышена максимальная глубина рекурсии!" << endl;
        return false;
    }

    // Если строка пустая - значит успешно разбили всю строку
    if (s.empty()) {
        return true;
    }

    // Проверяем все возможные префиксы
    for (int i = 1; i <= s.length(); i++) {
        string prefix = s.substr(0, i); // вариации слова
        
        // Если префикс есть в словаре, рекурсивно проверяем оставшуюся часть
        if (contains(wordDict, prefix) && wordBreak(s.substr(i), wordDict)) {
            return true;
        }
    }

    return false;
}

int main() {
    string s;
    cout << "Введите строку: ";
    cin >> s;

    vector<string> dict;
    cout << "Введите количество слов в словаре: ";
    int n;
    cin >> n;
    
    cout << "Введите слова словаря:" << endl;
    for (int i = 0; i < n; i++) {
        string word;
        cin >> word;
        dict.push_back(word);
    }

    recursion_counter = 0;
    bool result = wordBreak(s, dict);

    cout << "Результат: " << (result ? "true" : "false") << endl;
    cout << "Глубина рекурсии: " << recursion_counter << endl;

    return 0;
}
