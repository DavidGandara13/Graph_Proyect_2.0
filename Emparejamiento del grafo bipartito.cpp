#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

class Grafobipartido {
public:
    Grafobipartido(int vertices);
    void agregarArista(int u, int v);
    void encontrarEmparejamientobipartido();

private:
    int vertices;
    vector<vector<int>> listaAdyacencia;
    vector<int> pareja;
    vector<bool> visitado;

    bool buscarCaminoAumento(int u);
};

Grafobipartido::Grafobipartido(int vertices) {
    this->vertices = vertices;
    listaAdyacencia.resize(vertices);
    pareja.assign(vertices, -1);
    visitado.assign(vertices, false);
}

void Grafobipartido::agregarArista(int u, int v) {
    listaAdyacencia[u].push_back(v);
    listaAdyacencia[v].push_back(u);
}

bool Grafobipartido::buscarCaminoAumento(int u) {
    for (int i = 0; i < listaAdyacencia[u].size(); ++i) {
        int v = listaAdyacencia[u][i];
        if (!visitado[v]) {
            visitado[v] = true;

            // Si el vértice no está emparejado o se puede encontrar un camino de aumento
            if (pareja[v] == -1 || buscarCaminoAumento(pareja[v])) {
                pareja[v] = u;
                return true;
            }
        }
    }
    return false;
}

void Grafobipartido::encontrarEmparejamientobipartido() {
    // Reiniciar el conjunto de vértices visitados para cada vértice nuevo
    visitado.assign(vertices, false);

    // Intentar encontrar un camino de aumento desde cada vértice del primer conjunto
    for (int i = 0; i < vertices; ++i) {
        if (pareja[i] == -1) {
            buscarCaminoAumento(i);
        }
    }

    // Mostrar el emparejamiento máximo
    cout << "Emparejamiento bipartido:" << endl;
    for (int i = 0; i < vertices; ++i) {
        if (pareja[i] != -1) {
            cout << "(" << pareja[i] << " -> " << i << ")" << endl;
        }
    }
}

int main() {
    Grafobipartido grafo(6);
    grafo.agregarArista(0, 1);
    grafo.agregarArista(0, 2);
    grafo.agregarArista(1, 3);
    grafo.agregarArista(3, 4);
    grafo.agregarArista(2, 4);
    grafo.agregarArista(3, 5);

    grafo.encontrarEmparejamientobipartido();

    return 0;
}


