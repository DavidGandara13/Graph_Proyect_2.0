#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

class Grafo {
public:
    Grafo(int vertices);
    void agregarArista(int u, int v);
    void encontrarPareoMaximo();

private:
    int vertices;
    vector<vector<int>> listaAdyacencia;
    vector<int> pareja;
    vector<bool> visitado;

    bool buscarPareo(int u);
};

Grafo::Grafo(int vertices) {
    this->vertices = vertices;
    listaAdyacencia.resize(vertices);
    pareja.assign(vertices, -1);
    visitado.assign(vertices, false);
}

void Grafo::agregarArista(int u, int v) {
    listaAdyacencia[u].push_back(v);
    listaAdyacencia[v].push_back(u);
}

bool Grafo::buscarPareo(int u) {
    for (int i = 0; i < listaAdyacencia[u].size(); ++i) {
        int v = listaAdyacencia[u][i];
        if (!visitado[v]) {
            visitado[v] = true;

            // Si el vértice no está emparejado o se puede encontrar un camino de aumento
            if (pareja[v] == -1 || buscarPareo(pareja[v])) {
                pareja[v] = u;
                return true;
            }
        }
    }
    return false;
}

void Grafo::encontrarPareoMaximo() {
    for (int i = 0; i < vertices; ++i) {
        // Reiniciar el conjunto de vértices visitados para cada vértice nuevo
        visitado.assign(vertices, false);
        // Intentar encontrar un camino de aumento desde el vértice actual
        buscarPareo(i);
    }

    // Mostrar el pareo máximo
    cout << "Pareo Maximo:" << endl;
    for (int i = 0; i < vertices; ++i) {
        if (pareja[i] != -1) {
            cout << "(" << pareja[i] << " -> " << i << ")" << endl;
        }
    }
}

int main() {
    Grafo grafo(6);
    grafo.agregarArista(0, 1);
    grafo.agregarArista(0, 2);
    grafo.agregarArista(1, 3);
    grafo.agregarArista(3, 4);
	grafo.agregarArista(2, 4);
    grafo.agregarArista(3, 5);

    grafo.encontrarPareoMaximo();

    return 0;
}

