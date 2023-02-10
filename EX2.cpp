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
    int from;
    int to;
    ListGraph* obj;
public:
    std::vector<std::shared_ptr<std::vector<int>>>* ed = new std::vector<std::shared_ptr<std::vector<int>>>(edges);
    ListGraph(const ListGraph& oth) {
        obj = new ListGraph(*oth.obj);
    }
    ListGraph& operator = (const ListGraph& oth) {
        if (this == &oth) {
            return *this;
        }
        if (obj != nullptr) {
            delete obj;
        }
        obj = new ListGraph(*oth.obj);
        return *this;
    }

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

    std::vector<std::shared_ptr<std::vector<int>>> get_edges(){
        return *ed;
    }

    ListGraph(int inFrom, int inTo) {
    };
};

class MatrixGraph : ListGraph {
    std::vector<std::shared_ptr<std::vector<int>>>* edges = new std::vector<std::shared_ptr<std::vector<int>>> (*ed);
public:
    void view() {
        std::cout << " |";
        for (int i = 1; i <= edges->size(); ++i) {
            std::cout << i << " ";
        }
        std::cout << std::endl;
        for (int i = 1; i <= VerticesCount(); ++i) {
            std::cout << i << "|";
            for (int j = 0; j <= edges->size() - 1; ++j) {
                auto e = edges[j];
                if (e[0].get()->begin() == i) { //ПЕРЕДАТЬ ВЕКТОР РЕБЕР В МАТРИЦУ!
                    std::cout << "1";
                }
                else if (e[1] == i) {
                    std::cout << "-1";
                }
                else {
                    std::cout << "0";
                }
                std::cout << std::endl;
            }
        }
    }


    MatrixGraph(int inFrom, int inTo) : ListGraph(inFrom, inTo) {
    }
};


int main() {
    int from = 0;
    int to = 0;
    std::string command;
    std::shared_ptr <ListGraph> list = std::make_shared<ListGraph>(from, to);
    std::shared_ptr <MatrixGraph> matrix = std::make_shared<MatrixGraph>(from,to);

    //list.clear();
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
        list.get()->AddEdge(1, 2);
        list.get()->AddEdge(2, 3);
        list.get()->AddEdge(3, 5);
        list.get()->AddEdge(3, 1);
        list.get()->AddEdge(5, 4);
        list.get()->AddEdge(5, 2);
        list.get()->view();
        for (int i = 1; i <= 5; ++i) {
            std::vector<int> v;
            std::cout << i;
            list.get()->GetPrevVertices(i, v);
            std::cout << std::endl;
        }
        matrix.get()->view();

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
    std::cout << std::endl;
    
    return 0;
}
