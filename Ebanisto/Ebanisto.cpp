#include <iostream>
#include <fstream>
#include <vector>

#include "Matriz.h" 
#include "EnterosInf.h" // propios o los de las estructuras de datos de clase

using namespace std;

/*

i = inicio tabla
j = fin tabla

cortes(i,j) = min (cortes(i,k) + cortes(k,j) + 2*i*j)


*/



// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    int L, N;

    cin >> L >> N;

    if (L == 0 && N == 0)
        return false;

    vector<int> v(N+2);

    v[0] = 0;
    v[N+1] = L;

    for (int i = 1; i <= N; i++)
        cin >> v[i];

    Matriz<EntInf> m(N+2, N+2, 0);

    for (int i = N+2; i >= 0; i--) {
        for (int j = i + 1; j < N+2; j++) {
            m[i][j] = Infinito;
            for (int k = 1; k < v.size(); k++) {
                if (v[k] < v[j] && v[k] > v[i]) {
                    EntInf temp = m[i][k] + m[k][j] + 2*(v[j]-v[i]);
                    if (temp < m[i][j])
                        m[i][j] = temp;
                }
            }
            if (m[i][j] == Infinito)
                m[i][j] = 0;
        }
    }

    cout << m[0][N+1] << '\n';

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
