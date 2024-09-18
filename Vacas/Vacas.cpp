#include <iostream>
#include <fstream>
#include <vector>

#include "Matriz.h" 
#include "EnterosInf.h" // propios o los de las estructuras de datos de clase

using namespace std;

/*

i = izquirda
j = derecha


*/
int devoradora(int i, int j, vector<int> const& v, Matriz<int>& m);

int amiga(int i, int j, vector<int> const& v, Matriz<int>& m) {
    if (i > j)
        return 0;
    else if (i == j)
        return v[i];
    else if (m[i][j] != -1)
        return m[i][j];
    else
        m[i][j] = max(devoradora(i+1,j,v,m) + v[i]
                        , devoradora(i,j-1,v,m) + v[j]);

    return m[i][j];
}

int devoradora(int i, int j, vector<int> const& v, Matriz<int>& m) {
    if (v[i] > v[j])
        return amiga(i+1,j, v, m);
    else
        return amiga(i,j-1, v, m);
}


// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    int N;

    cin >> N;

    if (N == 0)
        return false;

    vector<int> v(N);

    for (int i = 0; i < N; i++)
        cin >> v[i];

    Matriz<int> m(N,N,-1);

    cout << amiga(0,N-1,v,m) << '\n'; 

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
