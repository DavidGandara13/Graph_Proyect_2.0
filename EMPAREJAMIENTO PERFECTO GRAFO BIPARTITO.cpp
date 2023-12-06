#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

class BipartiteGraph {
    int leftSetSize, rightSetSize;
    vector<vector<int>> graph;
    vector<int> leftMatch, rightMatch, dist, mate;
    vector<bool> edgeUsed;

public:
    // Constructor que inicializa el grafo bipartito con el tamaño de ambos conjuntos
    BipartiteGraph(int leftSize, int rightSize) {
        leftSetSize = leftSize;
        rightSetSize = rightSize;
        graph.resize(leftSize + 1, vector<int>(rightSize + 1, 0));
    }

    // Función para agregar una arista al grafo bipartito
    void addEdge(int left, int right) {
        graph[left][right] = 1;
    }

    // Métodos de acceso para obtener el tamaño de ambos conjuntos
    int getLeftSetSize() const {
        return leftSetSize;
    }

    int getRightSetSize() const {
        return rightSetSize;
    }

    // Algoritmo de búsqueda en amplitud (BFS) para encontrar rutas aumentantes
    bool bfs() {
        dist.assign(leftSetSize + 1, INT_MAX);
        mate.assign(leftSetSize + 1, 0);

        queue<int> q;

        for (int left = 1; left <= leftSetSize; left++) {
            if (leftMatch[left] == 0) {
                dist[left] = 0;
                q.push(left);
            }
        }

        while (!q.empty()) {
            int left = q.front();
            q.pop();

            if (dist[left] < dist[0]) {
                for (int right = 1; right <= rightSetSize; right++) {
                    if (graph[left][right] && dist[mate[right]] == INT_MAX) {
                        dist[mate[right]] = dist[left] + 1;
                        q.push(mate[right]);
                    }
                }
            }
        }

        return (dist[0] != INT_MAX);
    }

    // Algoritmo de búsqueda en profundidad (DFS) para encontrar rutas aumentantes
    bool dfs(int left) {
        if (left != 0) {
            for (int right = 1; right <= rightSetSize; right++) {
                if (graph[left][right] && dist[mate[right]] == dist[left] + 1 && dfs(mate[right])) {
                    mate[right] = left;
                    leftMatch[left] = right;
                    rightMatch[right] = left;
                    return true;
                }
            }
            dist[left] = INT_MAX;
            return false;
        }
        return true;
    }

    // Algoritmo de Edmonds para encontrar el emparejamiento máximo
    int edmonds() {
        leftMatch.assign(leftSetSize + 1, 0);
        rightMatch.assign(rightSetSize + 1, 0);
        int result = 0;

        while (bfs()) {
            for (int left = 1; left <= leftSetSize; left++) {
                if (leftMatch[left] == 0) {
                    if (dfs(left)) {
                        result++;
                    }
                }
            }
        }

        return result;
    }

// Función para imprimir las parejas obtenidas en el emparejamiento máximo
void printMatching() {
    cout << "\n|Emparejamiento máximo:" << endl;

    edgeUsed.assign(rightSetSize + 1, false); // Reiniciar el vector edgeUsed

    for (int right = 1; right <= rightSetSize; right++) {
        if (rightMatch[right] != 0 && !edgeUsed[right]) {
            int left = rightMatch[right];
            cout << "\t(" << left << " <--> " << right << ")" << endl;
            edgeUsed[right] = true;
            edgeUsed[left] = true; // Marcar también el vértice izquierdo
        }
    }
}


};

int main() {
BipartiteGraph graph(8, 8);

    graph.addEdge(1, 2);
    graph.addEdge(1, 4);
    graph.addEdge(1, 7);
    graph.addEdge(2, 3);
    graph.addEdge(2, 6);
    graph.addEdge(2, 8);
    graph.addEdge(3, 6);
    graph.addEdge(4, 7);
    graph.addEdge(5, 8);
    graph.addEdge(6, 8);
    graph.addEdge(7, 8);
    
    graph.addEdge(2, 1);
    graph.addEdge(4, 1);
    graph.addEdge(7, 1);
    graph.addEdge(3, 2);
    graph.addEdge(6, 2);
    graph.addEdge(8, 2);
    graph.addEdge(6, 3);
    graph.addEdge(7, 4);
    graph.addEdge(8, 5);
    graph.addEdge(8, 6);
    graph.addEdge(8, 7);

    int maxMatching = graph.edmonds();

    cout << "\n|El emparejamiento máximo es: " << maxMatching / 2 << endl;

    if (maxMatching == min(graph.getLeftSetSize(), graph.getRightSetSize())) {
        cout << "|Es un emparejamiento perfecto|\n" << endl;
    } else {
        cout << "|No es un emparejamiento perfecto|\n" << endl;
    }

    graph.printMatching();

    return 0;
}
