#include <iostream>
#include <fstream>
#include <vector>

#include "Matriz.h" 
#include "EnterosInf.h" // propios o los de las estructuras de datos de clase

using namespace std;

EntInf monedas(int i, int j, vector<pair<int,int>> const& v, Matriz<EntInf>& m) {
    if (j < 0)
        return Infinito;
    
    if (m[i][j] == -1) {
        if (j == 0)
            m[i][j] = 0;
        else if (i == 0)
            m[i][j] = Infinito;
        else {
            int maxUso = min(v[i-1].second, j / v[i-1].first);
            EntInf minMon = Infinito;
            for (int k = 0; k <= maxUso; k++) {
                minMon = min(minMon, monedas(i-1, j - k*(v[i-1].first), v, m) + k);
            }
            m[i][j] = minMon;
        }
    }

    return m[i][j];
}

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    int N, P;

    cin >> N;

    if (!cin)
        return false;

    vector<pair<int,int>> v(N);

    for (int i = 0; i < N; i++)
        cin >> v[i].first;

    for (int i = 0; i < N; i++)
        cin >> v[i].second;

    cin >> P;

    Matriz<EntInf> m(N+1, P+1, -1);

    EntInf sol = monedas(N, P, v, m);

    if (sol == Infinito)
        cout << "NO\n";
    else
        cout << "SI " << sol << '\n';
    

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
