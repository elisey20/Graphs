#pragma once

#include "exception"
#include "iostream"

class Graph
{
private:
    // матрица смежности
    int **matrix{};
    // размерность матрицы
    int N;

public:
    explicit Graph(int N): N(N) {};
    Graph(int N, int *matrix[]): Graph(N)
    {
        this->matrix = matrix;
    }
    ~Graph()
    {
        for (int i = 0; i < N; i++)
            delete[] matrix[i];
        //delete[] matrix;
    }

    // добавление вершины
    void add_vertex(int count = 1)
    {
        if (count < 1)
            throw std::invalid_argument("[ERR] При добавлении вершин их количество должно быть больше 0");

        int new_N = N + count;
        int *new_matrix[new_N];

        for (int i = 0; i < new_N; i++)
        {
            new_matrix[i] = new int[new_N];

            for (int j = 0; j < new_N; j++)
            {
                if (j < N and i < N)
                    new_matrix[i][j] = matrix[i][j];
                else
                    new_matrix[i][j] = 0;
            }
        }

        for (int i = 0; i < N; i++)
            delete[] matrix[i];
//        delete[] matrix;
        matrix = new int *[new_N];

        N = new_N;
        for (int i = 0; i < N; i++)
            matrix[i] = new_matrix[i];

        std::cout << "[MSG] Добавление вершин(" << count << ") прошло успешно" << std::endl;
    }

    void add_curve(int ver1, int ver2)
    {
        if (ver1 > N or ver2 > N)
            throw std::invalid_argument("[ERR] При добавлении дуги номера вершин не могут быть быльше размерности матрицы");
        else if (ver1 < 1 or ver2 < 1)
            throw std::invalid_argument("[ERR] При добавлении дуги номера вершин не могут быть меньше 1");
        else if (ver1 == ver2)
            throw std::logic_error("[ERR] При добавлении дуги номера вершин должны быть различны");

        matrix[ver1-1][ver2-1] = 1;
        matrix[ver2-1][ver1-1] = 1;

        std::cout << "[MSG] Добавление дуги (" << ver1 << '-' << ver2 << ") прошло успешно" << std::endl;
    }

    void del_vertex(int ver)
    {
        if (ver > N)
            throw std::invalid_argument("[ERR] При удалении вершины её номер не может быть больше размерности матрицы");
        else if (ver < 1)
            throw std::invalid_argument("[ERR] При удалении вершины её номер не может быть меньше 1");

        int new_N = N-1;
        int *new_matrix[new_N];
        ver--;

        for (int i = 0; i < ver; i++)
        {
            new_matrix[i] = new int[new_N];

            for (int j = 0; j < ver; j++)
            {
                new_matrix[i][j] = matrix[i][j];
            }

            for (int j = ver; j < new_N; j++)
            {
                new_matrix[i][j] = matrix[i][j+1];
            }
        }

        for (int i = ver; i < new_N; i++)
        {
            new_matrix[i] = new int[new_N];

            for (int j = 0; j < ver; j++)
            {
                new_matrix[i][j] = matrix[i+1][j];
            }

            for (int j = ver; j < new_N; j++)
            {
                new_matrix[i][j] = matrix[i+1][j+1];
            }
        }

        for (int i = 0; i < N; i++)
            delete[] matrix[i];
//        delete[] matrix;
        matrix = new int *[new_N];

        N = new_N;
        for (int i = 0; i < N; i++)
            matrix[i] = new_matrix[i];

        std::cout << "[MSG] Удаление вершины (" << ++ver << ") прошло успешно" << std::endl;
    }

    void del_curve(int ver1, int ver2)
    {
        matrix[ver1-1][ver2-1] = 0;
        matrix[ver2-1][ver1-1] = 0;

        std::cout << "[MSG] Удаление дуги (" << ver1 << '-' << ver2 << ") прошло успешно" << std::endl;
    }

    void find_vertex(int ver)
    {
        if (ver > N or ver < 1)
            std::cout << "[MSG] Вершина (" << ver << ") не найдена" << std::endl;

        std:: cout << "[MSG] Вершина (" << ver << ") найдена. Смежные с ней вершины: ";

        for (int i = 0; i < N; i++)
        {
            if (matrix[ver-1][i] == 1)
                std::cout << '(' << i+1 << ')' << ' ';
        }

        std::cout << std::endl;
    }

    void find_curve(int ver1, int ver2)
    {
        if (ver1 > N or ver2 > N or ver1 < 1 or ver2 < 1)
            std::cout << "[MSG] Дуга (" << ver1 << '-' << ver2 << ") не найдена" << std::endl;

        if (matrix[ver1-1][ver2-1] == 1)
            std::cout << "[MSG] Дуга (" << ver1 << '-' << ver2 << ") найдена" << std::endl;
        else
            std::cout << "[MSG] Дуга (" << ver1 << '-' << ver2 << ") не найдена" << std::endl;
    }

    void print()
    {

        std::cout << ' ';
        for (int i = 0; i < N; i++)
            std::cout << " -";
        std::cout << std::endl;

        for (int i = 0; i < N; i++)
        {
            std::cout << "| ";
            for (int j = 0; j < N; j++)
                std::cout << matrix[i][j] << ' ';
            std::cout << "|" << std::endl;
        }

        std::cout << ' ';
        for (int i = 0; i < N; i++)
            std::cout << " -";
        std::cout << std::endl;
    }
};