#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_map>

#include "EnterosInf.h"

using namespace std;

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    int P, N;

   cin >> P >> N;

   if (!cin)
      return false;

    vector<vector<EntInf>> listAdy(P, vector<EntInf>(P, Infinito));
    vector<vector<EntInf>> dist;
    unordered_map<string,int> m;
    int cont = 0;

    for (int i = 0; i < P; i++)
        listAdy[i][i] = 0;

    for (int i = 0; i < N; i++) {
        string p1, p2;
        int i1, i2;

        cin >> p1 >> p2;

        if (!m.count(p1))
            m[p1] = cont++;
        if (!m.count(p2))
            m[p2] = cont++;

        listAdy[m[p1]][m[p2]] = 1;
        listAdy[m[p2]][m[p1]] = 1;
    }

    dist = listAdy;

    for (int k = 0; k < P; ++k) {
        for (int i = 0; i < P; ++i) {
            for (int j = 0; j < P; ++j) {
                EntInf temp = dist[i][k] + dist[k][j];
                if (temp < dist[i][j]) {
                    dist[i][j] = temp;
                    listAdy[i][j] = listAdy[k][j];
                }
            }
        }
    }

    EntInf max = -1;

    for (int i = 0; i < P; i++)
        for (int j = 0; j < P; j++)
            if (dist[i][j] > max)
                max = dist[i][j];

    if (max == Infinito)
        cout << "DESCONECTADA\n";
    else
        cout << max << '\n';

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
