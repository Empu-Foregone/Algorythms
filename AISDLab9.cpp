#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Структура для зберігання інтервалів
struct Interval {
    int start;  // Початковий час
    int end;    // Кінцевий час
};

// Функція для порівняння інтервалів за кінцевими точками
bool compare(const Interval &a, const Interval &b) {
    return a.end < b.end;  // Сортуємо за кінцевим часом
}

// Процедура для жадібного вибору максимального числа інтервалів
void greedySelection(vector<Interval> &intervals) {
    // Сортуємо інтервали за кінцевими точками
    sort(intervals.begin(), intervals.end(), compare);
    
    // Вибір інтервалів
    int count = 1;  // Перший інтервал завжди можна вибрати
    int lastEnd = intervals[0].end;  // Кінець першого інтервалу
    
    cout << "Вибрані інтервали:" << endl;
    cout << "(" << intervals[0].start << ", " << intervals[0].end << ")" << endl;  // Вивести перший інтервал
    
    // Пройдемо по всіх інтервалах і вибираємо ті, що не перекриваються
    for (size_t i = 1; i < intervals.size(); i++) {
        if (intervals[i].start >= lastEnd) {
            // Якщо поточний інтервал не перекривається з попереднім
            cout << "(" << intervals[i].start << ", " << intervals[i].end << ")" << endl;
            lastEnd = intervals[i].end;  // Оновлюємо кінцевий час
            count++;  // Збільшуємо кількість вибраних інтервалів
        }
    }
    
    cout << "Максимальна кількість заявок, які можна виконати: " << count << endl;
}

int main() {
    // Вхідні інтервали (si, fi)
    vector<Interval> intervals = {
        {2, 5}, {3, 6}, {4, 7}, {7, 9}, {9, 11},
        {11, 15}, {13, 17}, {15, 16}, {8, 11},
        {6, 9}, {5, 9}, {10, 13}, {1, 4}
    };
    
    // Викликаємо жадібний алгоритм
    greedySelection(intervals);
    
    return 0;
}
