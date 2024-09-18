#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

#include "Matriz.h" 

using namespace std;

/*

i = películas
j = hora inicio

cine(i,j) = cine(i-1, j) si HoraIni-10 > j
            max(cine(i-1, j), cine(i-1,Fin[i]) + Dur[i])


*/


// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    int N;

    cin >> N;

    if (N == 0)
        return false;

    vector<pair<int,int>> v(N);

    for (int i = 0; i < v.size(); i++) {
        int h, m, dur;
        char c;

        cin >> h >> c >> m >> dur;

        v[i].first = h*60 + m;
        v[i].second = dur;
    }

    vector<int> m(24*60+11, 0);

    sort(v.begin(), v.end(), greater<pair<int,int>>());


    for (int i = 0; i < v.size(); i++) {
        int fin = v[i].first + v[i].second+10;
        for (int j = 24*60; j >= 0; j--) {
            if (j <= v[i].first) {
                m[j] = max(m[j], m[fin] + v[i].second);
            }
        }
    }

    cout << m[0] << '\n';


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
