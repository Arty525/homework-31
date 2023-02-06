#include <iostream>
#include <vector>

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
        std::vector<int> vertices;
        std::vector<int>* n;
        for (int i = 0; i < edges.size(); ++i) {
            auto n = *edges[i];
            if (!vertices.size()) {
                vertices.emplace_back(n[0]);
            }
            bool uniqueBeg = true;
            bool uniqueEnd = true;
            for (int j = 0; j < vertices.size(); ++j) {
                uniqueBeg = n[0] != vertices[j];
                uniqueEnd = n[1] != vertices[j];
            }
            if (uniqueBeg) vertices.emplace_back(n[0]);
            if (uniqueEnd) vertices.emplace_back(n[1]);
        }
        return vertices.size() - 1;
    }

    void view() {
        for (int i = 0; i < edges.size(); ++i) {
            auto f = *edges[i];
            std::cout << f[0] << ";" << f[1] << std::endl;
        }
        std::cout << "Vertices: " << VerticesCount() << std::endl;
    }

    void GetNextVertices(int vertex, std::vector<int>& vertices) const {
        int v;
        for (int i = 0; i < edges.size(); ++i) {
            if (*edges[i]->begin() == vertex) {
                v = i;
                break;
            }
        }
        /*if (v == NULL) {
            std::cout << "Vertex not found" << std::endl;
        }*/
        //for (int i = v; i < edges.size(); ++i) {
            int f = *edges[v].get()->begin();
            int s = *edges[v].get()->end();
            vertices.emplace_back(f);
            vertices.emplace_back(s);
            std::cout << f << "->" << s << "->";
        //}
            GetNextVertices(s, vertices);

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
        std::cout << "Enter command (add, list, matrix, stop): ";
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
        }
        if (command == "matrix") {

        }
        if (command == "next") {
            int vertex;
            std::cout << "Enter vertex: ";
            std::cin >> vertex;
            std::vector<int> vertices;
            graph.GetNextVertices(vertex, vertices);
        }
    } while (command != "stop");
    
    return 0;
}
