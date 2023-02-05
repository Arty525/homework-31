#include <iostream>
#include <vector>

class IGraph {
public:
    virtual ~IGraph() { std::cout << "DEAD" << std::endl; }
    IGraph() {};
    IGraph(IGraph* _oth) {};
    virtual void AddEdge(int from, int to) = 0; // Метод принимает вершины начала и конца ребра и добавляет ребро
   // virtual int VerticesCount() const = 0; // Метод должен считать текущее количество вершин
   // virtual void GetNextVertices(int vertex, std::vector<int>& vertices) const = 0; // Для конкретной вершины метод выводит в вектор “вершины” все вершины, в которые можно дойти по ребру из данной
   // virtual void GetPrevVertices(int vertex, std::vector<int>& vertices) const = 0; // Для конкретной вершины метод выводит в вектор “вершины” все вершины, из которых можно дойти по ребру в данную
};

class ListGraph : IGraph { 
    std::vector<int> vert;
    std::vector<std::shared_ptr<std::vector<int>>> edges;
    int from;
    int to;
public:
    void AddEdge(int from, int to) {
        vert.emplace_back(from);
        vert.emplace_back(to);
        auto edge = std::make_shared<std::vector<int>>(vert);
        edges.emplace_back(edge);
        vert.clear();
    }
    void view() {
        for (int i = 0; i < edges.size(); ++i) {
            auto f = *edges[i];
            std::cout << f[0] << ";" << f[1] << std::endl;
        }
    }

    ListGraph(int inFrom, int inTo) {
        AddEdge(inFrom, inTo);
    }
};

class MatrixGraph : IGraph {

};


int main() {
    int from;
    int to;
    std::cout << "Enter start point: ";
    std::cin >> from;
    std::cout << "Enter end point: ";
    std::cin >> to;

    ListGraph list(from, to);
    list.view();
    
    return 0;
}

//edge.use_counr();
