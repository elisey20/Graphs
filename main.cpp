#include <iostream>
#include "src/graph.h"

const int N = 5;

int main()
{
    //std::system("clear");

    int *matrix[N] = {
            new int[] {0, 1, 1, 0, 0},
            new int[] {1, 0, 0, 1, 0},
            new int[] {1, 0, 0, 0, 1},
            new int[] {0, 1, 0, 0, 1},
            new int[] {0, 0, 1, 1, 0}
    };

    Graph graph(N, matrix);

    try
    {
        graph.add_vertex();
        graph.print();
        graph.add_curve(1, 6);
        graph.print();
        graph.del_vertex(3);
        graph.print();
        graph.del_curve(2, 3);
        graph.print();
        graph.find_vertex(1);
        graph.find_curve(1, 3);
    }
    catch(std::exception &exp)
    {
        std::cout << exp.what() << std::endl;
    }
}
