#include <iostream>
#include <fstream>
#include <vector>

#include "Matriz.h" 
#include "EnterosInf.h" // propios o los de las estructuras de datos de clase

using namespace std;

/*

resolver(i, j) = resolver(i-1,j) si 3*Prof[i] > j
                 max(resolver(i-1, j), resolver(i-1, j-3*Prof[i]) + Cost[i])

*/

int resolver(int i, int j, vector<pair<int,int>> const& v, Matriz<int> & m) {
   if (m[i][j] == -1) {
      if (i == 0 || j == 0)
         m[i][j] = 0;
      else if (3*v[i-1].first > j)
         m[i][j] = resolver(i-1, j, v, m);
      else 
         m[i][j] = max(resolver(i-1,j,v,m), resolver(i-1,j-3*v[i-1].first,v,m) + v[i-1].second);
   }

   return m[i][j];
}


// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
   int T, N;

   cin >> T;
   
   if (!std::cin)  // fin de la entrada
      return false;

   cin >> N;

   vector<pair<int,int>> v(N);

   for (int i = 0; i < N; i++)
      cin >> v[i].first >> v[i].second;
   
   Matriz<int> m(N+1, T+1, -1);

   int sol = resolver(N,T,v,m);

   vector<bool> elegidos(N, false);
   int cont = 0;

   int j = T;
   for (int i = N; i > 0 && j > 0; i--) {
      if (m[i][j] != m[i-1][j]) {
         elegidos[i-1] = true;
         j -= 3*v[i-1].first;
         cont++;
      }
   }

   cout << sol << '\n' << cont << '\n';

   for (int i = 0; i < N; i++)
      if(elegidos[i])
         cout << v[i].first << ' ' << v[i].second << '\n';

   cout << "---\n";
   
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
