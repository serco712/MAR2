#include <iostream>
#include <fstream>
#include <vector>

#include "Matriz.h" 
#include "EnterosInf.h" // propios o los de las estructuras de datos de clase

using namespace std;


/*
Función recursiva

i son los sectores disponibles
j son los puntos que queremos conseguir

dianas(i,j) = dianas(i-1,j) si sector[i] > j
              max(dianas(i-1,j), dianas(i,j-sector[i]) + sector[i]) otherwise


*/


// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
   int V, S;

   cin >> V >> S;

   if (!cin)
      return false;

   vector<int> sectores(S);
   
   for (int i = 0; i < S; i++)
      cin >> sectores[i];
   
   vector<EntInf> m(V+1, Infinito);

   m[0] = 0;

   for (int i = 0; i < S; i++)
      for (int j = 1; j <= V; j++) {
         if (sectores[i] <= j)
            m[j] = min(m[j], m[j-sectores[i]]+1);
      }

   vector<int> sol;

   if (m[V] != Infinito) {
      int j = V, i = S-1;
      while (j > 0) {
         if (sectores[i] <= j && m[j] == m[j-sectores[i]]+1) {
            sol.push_back(sectores[i]);
            j -= sectores[i];
         }
         else
            i--;
      }
   }

   if (sol.empty())
      cout << "Imposible\n";
   else {
      cout << sol.size() << ':';
      for (int i = 0; i < sol.size(); i++)
         cout << ' ' << sol[i];

      cout << '\n';
   }


   
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
