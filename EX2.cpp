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
    virtual void GetPrevVertices(int vertex, std::vector<int>& vertices) const = 0; // Для конкретной вершины метод выводит в вектор “вершины” все вершины, из которых можно дойти по ребру в данную
};

class ListGraph : IGraph {
    std::vector<int> vert;
    std::vector<std::shared_ptr<std::vector<int>>> edges;
    std::vector<std::shared_ptr<std::vector<int>>>* ed = new std::vector<std::shared_ptr<std::vector<int>>>;
    int from;
    int to;
public:
    void AddEdge(int from, int to) {
        vert.clear();
        vert.emplace_back(from);
        vert.emplace_back(to);
        auto edge = std::make_shared<std::vector<int>>(vert);
        edges.emplace_back(edge);
        std::cout << "Added edge " << from << "->" << to << std::endl;
    }

    int VerticesCount() const {
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
        std::cout << "List:" << std::endl;
        for (int i = 1; i <= VerticesCount(); ++i) {
            std::vector<int> v;
            std::cout << i;
            GetNextVertices(i, v);
            std::cout << std::endl;
        }
    }

    void GetNextVertices(int vertex, std::vector<int>& vertices) const {
        for (int i = 0; i <= edges.size() - 1; ++i) {
            std::vector<int> n = *edges[i].get();
            if (n[0] == vertex) {
                vertices.emplace_back(n[1]);
            }
        }
        if (!vertices.empty()) {
            for (int i = 0; i <= vertices.size() - 1; ++i) {
                if (i <= vertices.size() - 1) {
                    std::cout << "->";
                }
                std::cout << vertices[i];
            }
        }
    }

    void GetPrevVertices(int vertex, std::vector<int>& vertices) const {
        for (int i = 0; i <= edges.size() - 1; ++i) {
            std::vector<int> n = *edges[i].get();
            if (n[1] == vertex) {
                vertices.emplace_back(n[0]);
            }
        }
        if (!vertices.empty()) {
            for (int i = 0; i <= vertices.size() - 1; ++i) {
                if (i <= vertices.size() - 1) {
                    std::cout << "<-";
                }
                std::cout << vertices[i];
            }
        }
    }
    std::vector<std::shared_ptr<std::vector<int>>> get_edges() {
        *ed = edges;
        return *ed;
    }

    ListGraph(int inFrom, int inTo) {
    };
};

class MatrixGraph : ListGraph {
public:
    void view(std::vector<std::shared_ptr<std::vector<int>>> edges, int vertices) {
        std::cout << "Matrix:" << std::endl;
        std::cout << " | ";
        for (int i = 1; i <= edges.size(); ++i) {
            std::cout << i << " ";
        }
        std::cout << std::endl;

        for (int i = 1; i <= vertices; ++i) {
            std::cout << i << "|";
            for (int j = 0; j <= edges.size() - 1; ++j) {
                auto e = *edges[j];
                if (e[0] == i) {
                    std::cout << " 1";
                }
                else if (e[1] == i) {
                    std::cout << "-1";
                }
                else {
                    std::cout << " 0";
                }
                
            }
            std::cout << std::endl;
        }
    }

    

    MatrixGraph(int inFrom, int inTo) : ListGraph(inFrom, inTo) {
    }
};


int main() {
    int from = 0;
    int to = 0;
    std::string command;
    ListGraph list(from, to);
    MatrixGraph matrix(from, to);
    std::cout << "Commands:" << std::endl;
    std::cout << "add - adds a new edge;" << std::endl;
    std::cout << "next - displays next vertices for this vertex;" << std::endl;
    std::cout << "prev - displays previous vertices for this vertex;" << std::endl;
    std::cout << "list - displays the graph in the form of adjacency lists;" << std::endl;
    std::cout << "matrix - displays the graph as an adjacency matrix;" << std::endl;
    std::cout << "test - automatically builds a graph and outputs list and matrix commands;" << std::endl;
    std::cout << "stop - stops the program." << std::endl;
    do {
        std::cout << "Enter command: ";
        std::cin >> command;
        if (command == "add") {
            std::cout << "Enter start point: ";
            std::cin >> from;
            std::cout << "Enter end point: ";
            std::cin >> to;
            list.AddEdge(from, to);
        }
        if (command == "list") {
            list.view();
        }
        if (command == "test") {
            list.AddEdge(1, 2);
            list.AddEdge(2, 3);
            list.AddEdge(3, 5);
            list.AddEdge(3, 1);
            list.AddEdge(5, 4);
            list.AddEdge(5, 2);
            list.view();
            std::cout << "Get previous vertex" << std::endl;
            for (int i = 1; i <= 5; ++i) {
                std::vector<int> v;
                std::cout << i;
                list.GetPrevVertices(i, v);
                std::cout << std::endl;
            }

            matrix.view(list.get_edges(), list.VerticesCount());
        }

        if (command == "matrix") {
            matrix.view(list.get_edges(), list.VerticesCount());
        }
        if (command == "next") {
            int vertex;
            std::cout << "Enter vertex: ";
            std::cin >> vertex;
            std::vector<int> vertices;
            std::cout << vertex;
            list.GetNextVertices(vertex, vertices);
            if (vertices.empty()) {
                std::cout << "Vertex not found" << std::endl;
            }
            std::wcout << std::endl;
        }
        if (command == "prev") {
            int vertex;
            std::cout << "Enter vertex: ";
            std::cin >> vertex;
            std::vector<int> vertices;
            std::cout << vertex;
            list.GetPrevVertices(vertex, vertices);
            if (vertices.empty()) {
                std::cout << "Vertex not found" << std::endl;
            }
            std::cout << std::endl;
        }
    } while (command != "stop");
    std::cout << std::endl;
    return 0;
}
