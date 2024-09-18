#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <queue>
#include <climits>

#include "Matriz.h"

using namespace std;

struct Nodo {
    int sol;
    vector<bool> marcas;
    int k;
    int calEstimada; // estimación, prioridad
    bool operator<(Nodo const& otro) const {
        return otro.calEstimada > calEstimada;
    }
};


// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    int n, m;

    cin >> n >> m;

    vector<int> carros(n), caminos(m);
    Matriz<int> cal(n,m);

    for (int i = 0; i < n; i++)
        cin >> carros[i];

    for (int i = 0; i < m; i++)
        cin >> caminos[i];

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cin >> cal[i][j];

    int calMejor;
    Nodo Y;

    vector<int> calcEst(n+1, 0);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (cal[i][j] > calcEst[i])
                calcEst[i] = cal[i][j];
        }
    }

    for (int i = n-1; i >= 0; i--) {
        calcEst[i] += calcEst[i+1]; 
    }

    Y.marcas = vector<bool>(m,false);
    Y.sol = 0;
    Y.k = -1;
    Y.calEstimada = calcEst[0];
    priority_queue<Nodo> cola;
    cola.push(Y);
    calMejor = 0;
    while (!cola.empty() && cola.top().calEstimada > calMejor) {
        Y = cola.top(); cola.pop();
        Nodo X(Y);
        ++X.k;
        //Uso el carro
        for (int i = 0; i < m; i++) {
            if (!X.marcas[i] && carros[X.k] <= caminos[i]) {
                X.sol = Y.sol + cal[X.k][i];
                X.marcas[i] = true;
                X.calEstimada = X.sol + calcEst[X.k+1];
                if (X.calEstimada > calMejor) {
                    if (X.k == n-1)
                        calMejor = X.sol;
                    else cola.push(X);
                }
                X.marcas[i] = false;
            }
        }
        //No lo uso
        X.sol = Y.sol;
        X.calEstimada = X.sol + calcEst[X.k+1];
        if (X.calEstimada > calMejor) {
            if (X.k == n-1)
                calMejor = X.sol;
            else cola.push(X);
        }
    }

    cout << calMejor << '\n';
}

int main() {
   // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
   std::ifstream in("casos.txt");
   auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif
   
    int numCasos;
    cin >> numCasos;
    for (int i = 0; i < numCasos; i++)
        resuelveCaso();

   // para dejar todo como estaba al principio
#ifndef DOMJUDGE
   std::cin.rdbuf(cinbuf);
   system("PAUSE");
#endif
   return 0;
}
