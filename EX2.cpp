#include <iostream>
#include <vector>
#include <unordered_set>

class IGraph {
public:
    virtual ~IGraph() { std::cout << "DEAD" << std::endl; }
    IGraph() {};
    IGraph(IGraph* _oth) {};
    virtual void AddEdge(int from, int to) = 0; // Метод принимает вершины начала и конца ребра и добавляет ребро
    virtual int VerticesCount() const = 0; // Метод должен считать текущее количество вершин
    virtual void GetNextVertices(int vertex, std::vector<int>& vertices) const = 0; // Для конкретной вершины метод выводит в вектор “вершины” все вершины, в которые можно дойти по ребру из данной
   // virtual void GetPrevVertices(int vertex, std::vector<int>& vertices) const = 0; // Для конкретной вершины метод выводит в вектор “вершины” все вершины, из которых можно дойти по ребру в данную
};

class ListGraph : IGraph { 
    std::vector<int> vert;
    std::vector<std::shared_ptr<std::vector<int>>> edges;
    int from;
    int to;
public:
    void clear() {
        vert.clear();
        edges.clear();
    }
    void AddEdge(int from, int to) {
        vert.clear();
        vert.emplace_back(from);
        vert.emplace_back(to);
        auto edge = std::make_shared<std::vector<int>>(vert);
        edges.emplace_back(edge);
    }
    
    int VerticesCount() const{
        std::unordered_set<int> vertices;
        for (int i = 0; i < edges.size(); ++i) {
            auto n = *edges[i];
            if (!vertices.contains(n[0])) {
                vertices.insert(n[0]);
            }
            if (!vertices.contains(n[1])) {
                vertices.insert(n[1]);
            }
        }
        return vertices.size();
    }

    void view() {
        std::cout << "Vertices: " << VerticesCount() << std::endl;

        for (int i = 1; i <= VerticesCount(); ++i) {
            std::vector<int> v;
            std::cout << std::endl;
            std::cout << i;
            GetNextVertices(i, v);
        }
    }

    void GetNextVertices(int vertex, std::vector<int>& vertices) const {
        for (int i = 0; i < edges.size(); ++i) {
            std::vector<int> n;
            if (*edges[i].get()->begin() == vertex) {
                if ((i + 1) < edges.size() - 1 && *edges[i + 1].get()->begin() == vertex) {
                    ++i;
                }
                auto v = *edges[i].get();
                int s = v[1];
                int f = v[0];
                vertices.emplace_back(s);
                std::cout << "->" << s;
                if (i < edges.size() - 1) {
                    n = *edges[i + 1].get();
                    if (n[0] >= v[0] || n[0]>= v[1]) { //Разобраться с условиями
                       GetNextVertices(s, vertices);
                    }
                    else {
                       GetNextVertices(f, vertices);
                    }
                }
                break;
            }
            if (i == edges.size() - 1) {
                std::cout << std::endl;
            }
        }
    }

    //void GetPrevVertices(int vertex, std::vector<int>& vertices) const {

    //}

    ListGraph(int inFrom, int inTo) {
        AddEdge(inFrom, inTo);
    }
};

class MatrixGraph : IGraph {

};


int main() {
    int from = 0;
    int to = 0;
    std::string command;
    ListGraph graph(from,to);
    graph.clear();
    do {
        /*std::cout << "Enter command (add, list, matrix, stop): ";
        std::cin >> command;
        if (command == "add") {
            std::cout << "Enter start point: ";
            std::cin >> from;
            std::cout << "Enter end point: ";
            std::cin >> to;
            graph.AddEdge(from, to);
        }
        if (command == "list") {
            graph.view();
        }*/
        graph.AddEdge(1, 2);
        graph.AddEdge(2, 3);
        graph.AddEdge(3, 5);
        graph.AddEdge(3, 1);
        graph.AddEdge(5, 4);
        graph.view();
        /*if (command == "matrix") {

        }
        if (command == "next") {
            int vertex;
            std::cout << "Enter vertex: ";
            std::cin >> vertex;
            std::vector<int> vertices;
            graph.GetNextVertices(vertex, vertices);
            if (vertices.empty()) {
                std::cout << "Vertex not found" << std::endl;
            }
            else {
                std::cout << vertex << " -> ";
            }
            for (int i = 0; !vertices.empty() && i < vertices.size(); ++i) {
                std::cout << vertices[i];
                if (i != vertices.size() - 1) {
                    std::cout << " -> ";
                }
            }
        }*/
        command = "stop";
    } while (command != "stop");
    
    return 0;
}
