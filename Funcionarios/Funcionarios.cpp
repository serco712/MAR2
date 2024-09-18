#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <queue>
#include <limits>
#include <climits>

#include "Matriz.h"

using namespace std;

struct Nodo {
    int sol;
    vector<bool> marcas;
    int k;
    int eficEstimado; // estimación, prioridad
    bool operator<(Nodo const& otro) const {
        return otro.eficEstimado < eficEstimado;
    }
};


// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    int N;

    cin >> N;

    if (N == 0)
        return false;

    Matriz<int> mat(N, N);

    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            cin >> mat[i][j];

    int eficMejor;
    Nodo Y;

    vector<int> calcEst(N+1, INT_MAX);

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (mat[j][i] < calcEst[i])
                calcEst[i] = mat[j][i];
        }
    }

    for (int i = N-2; i >= 0; i--) {
        calcEst[i] += calcEst[i+1]; 
    }

    calcEst[N] = 0;

    Y.marcas = vector<bool>(N,false);
    Y.sol = 0;
    Y.k = -1;
    Y.eficEstimado = calcEst[0];
    priority_queue<Nodo> cola;
    cola.push(Y);
    eficMejor = INT_MAX;
    while (!cola.empty() && cola.top().eficEstimado < eficMejor) {
        Y = cola.top(); cola.pop();
        Nodo X(Y);
        ++X.k;
        for (int i = 0; i < N; i++) {
            if (!X.marcas[i]) {
                X.sol += mat[i][X.k];
                X.marcas[i] = true;
                X.eficEstimado = X.sol + calcEst[X.k+1];
                if (X.eficEstimado < eficMejor) {
                    if (X.k == N-1)
                        eficMejor = X.sol;
                    else cola.push(X);
                }
                X.sol -= mat[i][X.k];
                X.marcas[i] = false;
            }
        }

    }


    cout << eficMejor << '\n';

   return true;
}

int main() {
   // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
   std::ifstream in("casos.txt");
   auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif
   
   while (resuelveCaso());
   
   // para dejar todo como estaba al principio
#ifndef DOMJUDGE
   std::cin.rdbuf(cinbuf);
   system("PAUSE");
#endif
   return 0;
}
