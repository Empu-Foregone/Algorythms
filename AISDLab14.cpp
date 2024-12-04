#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Функція для знаходження максимального призу з можливістю руху по діагоналі
void findMaxPrizePath(vector<vector<int>>& grid) {
    int n = grid.size();
    int m = grid[0].size();
    
    // Створення матриці для збереження максимальної суми для кожної клітинки
    vector<vector<int>> dp(n, vector<int>(m, 0));
    
    // Заповнюємо першу клітинку
    dp[0][0] = grid[0][0];
    
    // Заповнюємо перший рядок
    for (int j = 1; j < m; ++j) {
        dp[0][j] = dp[0][j-1] + grid[0][j];
    }
    
    // Заповнюємо перший стовпчик
    for (int i = 1; i < n; ++i) {
        dp[i][0] = dp[i-1][0] + grid[i][0];
    }
    
    // Заповнюємо решту матриці з можливістю руху по діагоналі
    for (int i = 1; i < n; ++i) {
        for (int j = 1; j < m; ++j) {
            dp[i][j] = grid[i][j] + max({dp[i-1][j], dp[i][j-1], dp[i-1][j-1]});
        }
    }
    
    // Виведення максимальної суми (призу)
    cout << "Максимальний приз: " << dp[n-1][m-1] << endl;

    // Відновлення шляху
    vector<pair<int, int>> path;
    int i = n - 1, j = m - 1;
    while (i > 0 || j > 0) {
        path.push_back({i, j});
        if (i == 0) {
            --j;
        } else if (j == 0) {
            --i;
        } else {
            // Перевірка, чи йти по діагоналі, чи з верхнього або лівого напрямку
            if (dp[i-1][j-1] >= dp[i-1][j] && dp[i-1][j-1] >= dp[i][j-1]) {
                --i;
                --j;
            } else if (dp[i-1][j] >= dp[i][j-1]) {
                --i;
            } else {
                --j;
            }
        }
    }
    path.push_back({0, 0});
    
    // Позначаємо шлях на шахівниці
    for (const auto& p : path) {
        grid[p.first][p.second] = 9; // 9 позначає шлях мандрівника
    }

    // Виведення шахівниці з позначеним шляхом
    cout << "Шахівниця з позначеним шляхом:\n";
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (grid[i][j] == 9) {
                cout << " * ";  // Шлях мандрівника позначається зірочкою
            } else {
                cout << " " << grid[i][j] << " ";
            }
        }
        cout << endl;
    }
    
    // Виведення шляху
    cout << "Шлях проходження:\n";
    for (int k = path.size() - 1; k >= 0; --k) {
        cout << "(" << path[k].first + 1 << ", " << path[k].second + 1 << ")";
        if (k > 0) cout << " -> ";
    }
    cout << endl;
}

int main() {
    // Опис шахівниці (середовище)
    vector<vector<int>> grid = {
        {3, -1, 4, 3, -2, -3, 4, 5},
        {-1, 2, -2, 1, 6, 2, -3, 3},
        {2, -1, 4, 3, -1, 2, -1, 3},
        {1, -2, 5, 6, 3, -4, -4, 6},
        {-2, 4, -2, 4, -5, 1, -3, -4},
        {-3, -2, -1, -5, 3, 1, -3, -3},
        {-2, -3, -2, 3, -2, 3, -2, -3},
        {2, -1, -2, -3, -2, -2, 4, 3}
    };

    // Викликаємо функцію для знаходження максимального призу та шляху
    findMaxPrizePath(grid);

    return 0;
}
