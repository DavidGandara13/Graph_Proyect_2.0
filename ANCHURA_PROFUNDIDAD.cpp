#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>
#include <stack>
#include <unordered_map>

using namespace std;

unordered_map<string, vector<string>> listaAdyacencia;

void agregarArista(const string& nodoOrigen, const string& nodoDestino) {
    listaAdyacencia[nodoOrigen].push_back(nodoDestino);
}

bool BFS(const string& nodoInicial, const string& nodoFinal) {
    queue<string> cola;
    unordered_set<string> visitados;

    cola.push(nodoInicial);
    visitados.insert(nodoInicial);

    while (!cola.empty()) {
        string nodoActual = cola.front();
        cola.pop();
        cout << nodoActual << " ";

        // Si se alcanza el nodo final, terminar el BFS
        if (nodoActual == nodoFinal) {
            return true;
        }

        // Obtener nodos adyacentes y agregarlos a la cola si no han sido visitados
        for (const auto& vecino : listaAdyacencia[nodoActual]) {
            if (visitados.find(vecino) == visitados.end()) {
                cola.push(vecino);
                visitados.insert(vecino);
            }
        }
    }

    // Si no se encuentra el nodo final, devolver false
    return false;
}

bool DFS(const string& nodoInicial, const string& nodoFinal) {
    stack<string> pila;
    unordered_set<string> visitados;

    pila.push(nodoInicial);
    visitados.insert(nodoInicial);

    while (!pila.empty()) {
        string nodoActual = pila.top();
        pila.pop();
        cout << nodoActual << " ";

        // Si se alcanza el nodo final, terminar el DFS
        if (nodoActual == nodoFinal) {
            return true;
        }

        // Obtener nodos adyacentes y agregarlos a la pila si no han sido visitados
        for (const auto& vecino : listaAdyacencia[nodoActual]) {
            if (visitados.find(vecino) == visitados.end()) {
                pila.push(vecino);
                visitados.insert(vecino);
            }
        }
    }

    // Si no se encuentra el nodo final, devolver false
    return false;
}



int main(){

	
	
	agregarArista("Rochester", "SF");
	agregarArista("Rochester", "Minneapolis");
	agregarArista("Rochester", "Lacrosse");
	agregarArista("Rochester", "Dubuque");
	agregarArista("SF", "Fargo");
	agregarArista("Fargo", "GF");
	agregarArista("Fargo", "St.Cloud");
	agregarArista("GF", "IF");
	agregarArista("GF", "Bemidji");
	agregarArista("IF", "Duluth");
	agregarArista("Bemidji", "Duluth");
	agregarArista("Minneapolis", "Duluth");
	agregarArista("Bemidji", "St.Cloud");
	agregarArista("Minneapolis", "St.Cloud");
	agregarArista("IF", "Bemidji");
	agregarArista("Minneapolis", "Wausau");
	agregarArista("Minneapolis", "Lacrosse");
	agregarArista("Madison", "Lacrosse");
	agregarArista("GB", "Wausau");
	agregarArista("GB", "Lacrosse");
	agregarArista("GB", "Milwaukee");
	agregarArista("Dubuque", "Rockford");
	agregarArista("Madison", "Rockford");
	agregarArista("Madison", "Milwaukee");
	agregarArista("Chicago", "Rockford");
	agregarArista("Chicago", "Milwaukee");

    
	cout << "Recorrido en anchura desde el nodo Rochester hasta el nodo Wuasau: "<<endl;
	if (BFS("Rochester" , "Wausau")) {
        cout <<endl<< "Se encontro un camino hasta el nodo Wuasau" << endl;
    } else {
        cout <<endl<< "No se encontro un camino hasta el nodo Wuasau "  << endl;
    }
    
    cout<<endl<<endl;
    
    cout << "Recorrido en profundidad desde el nodo Rochester hasta el nodo Wuasau: "<<endl;
	if (DFS("Rochester" , "Wausau")) {
        cout <<endl<< "Se encontro un camino hasta el nodo Wuasau" << endl;
    } else {
        cout <<endl<< "No se encontro un camino hasta el nodo Wuasau "  << endl;
    }
    
        
    return 0;
}









	


