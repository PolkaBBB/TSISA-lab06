#include <iostream>
#include <vector>
#include <algorithm>

// объявляем переменную, которая будет отвечать за размер нашего графа-матрицы
const int N = 10;
// метод, который печатает наш граф-матрицу
void Print_Graf(const std::vector<std::vector<int>>& Graf)
{
    // "бежим" по всем строчкам и столбцам графа-матрицы:
    for (const auto& x : Graf) {
        for (const auto& y : x) {
            // если встречаем обозначение "пути нет", то заменяем его знаком "-" для удобства чтения
            if (y == INT_MAX) 
                std::cout << "-" << "  ";
            else
            // иначе, если такого обозначения не встречается, то просто записываем расстояние между соответствующими вершинами
                std::cout << y << "  "; 
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

// метод, возвращающий критический путь между начальной и конечной вершинами 
int Search_of_Critical_Path(std::vector<std::vector<int>>& Graf)
{
    // "бежим" по всему графу-матрице и смотрим конкретные строки и столбцы "K":
    for (int k = 0; k < N; k++) {
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
            {
                // ставим условия, чтобы путь между двумя просматриваемыми вершинами "существовал" и
                // чтобы эти две вершины графа были различны, то есть не рассматриваем пути вершимы от 
                // самой себя до себя
                if ((i != j)&&(Graf[i][k] != INT_MAX)&&(Graf[k][j] != INT_MAX))
                {
                    // ищем как бы "пустые/несуществующие" места между вершинами:
                    if (Graf[i][j] == INT_MAX)
                        // если все условия выполнены, то с каждым разом складываем найденные пути
                        // и записываем их в "пустые" места
                        Graf[i][j] = Graf[i][k] + Graf[k][j];
                    else
                        // иначе нужно посмотреть, какой путь больше: тот, который получится сложением или тот, который
                        // представлен на данный момент
                        Graf[i][j] = std::max(Graf[i][j], Graf[i][k] + Graf[k][j]);
                }
            }
    }
    // возвращаем наибольший путь между вершинами "0-начало" и "9-конец"
    return Graf[0][9];
}

int main()
{
    // создаём наш граф в виде матрицы
    // столбцы слева-направо: путь между вершинами [1][1], [1][2], [1][3],... 
    // допустим, путь от 1-1 = 0, 1-2 = 2 и т. д.
    // строчки сверху-вниз: путь между вершинами [1][1], [2][1], [3][1],... 
    // допустим, путь от 1-1 = 0, 2-1 = INT_MAX и т. д.
    std::vector<std::vector<int>> Graf =
    {
        // обозначение "INT_MAX" означает, что из такой-то вершины в такую-то пути не существует
        {0,2,INT_MAX,5,INT_MAX,INT_MAX,INT_MAX,INT_MAX,INT_MAX,INT_MAX},
        {INT_MAX,0,3,INT_MAX,INT_MAX,INT_MAX,INT_MAX,INT_MAX,INT_MAX,INT_MAX},
        {INT_MAX,INT_MAX,0,INT_MAX,INT_MAX,INT_MAX,2,INT_MAX,INT_MAX,INT_MAX},
        {INT_MAX,INT_MAX,INT_MAX,0,3,3,INT_MAX,INT_MAX,INT_MAX,INT_MAX},
        {INT_MAX,INT_MAX,INT_MAX,INT_MAX,0,INT_MAX,INT_MAX,2,INT_MAX,INT_MAX},
        {INT_MAX,INT_MAX,INT_MAX,INT_MAX,INT_MAX,0,INT_MAX,INT_MAX,5,INT_MAX},
        {INT_MAX,INT_MAX,INT_MAX,INT_MAX,INT_MAX,INT_MAX,0,3,INT_MAX,INT_MAX},
        {INT_MAX,INT_MAX,INT_MAX,INT_MAX,INT_MAX,INT_MAX,INT_MAX,0,3,INT_MAX},
        {INT_MAX,INT_MAX,INT_MAX,INT_MAX,INT_MAX,INT_MAX,INT_MAX,INT_MAX,0,4},
        {INT_MAX,INT_MAX,INT_MAX,INT_MAX,INT_MAX,INT_MAX,INT_MAX,INT_MAX,INT_MAX,0}
    };
    // печатаем изначальный граф
    Print_Graf(Graf);
    // ищем критический путь
    int critical_path = Search_of_Critical_Path(Graf);
    // печатаем уже изменённый граф
    Print_Graf(Graf);
    std::cout << "Critical path: " << critical_path << std::endl;
}
