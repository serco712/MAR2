#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include "Matriz.h" 
#include "EnterosInf.h" // propios o los de las estructuras de datos de clase

using namespace std;


/*
Función recursiva

aibofobia(i,j) = Mínimo de letras que se añaden entre la posición i,j

aibofobia(i,j) = aibofobia(i+1,j-1) si palabra[i] == palabra[j]
                 min(aibofobia(i+1,j) + 1, aibofobia(i,j-1) + 1)

*/

EntInf aibofobia(int i, int j, string const& p, Matriz<EntInf> &m) {
   if (m[i][j] == Infinito) {
      if (i >= j)
         m[i][j] = 0;
      else if (p[i] == p[j])
         m[i][j] = aibofobia(i+1, j-1, p, m);
      else
         m[i][j] = min(aibofobia(i+1,j,p,m) + 1, aibofobia(i,j-1,p,m) + 1);
   }

   return m[i][j];
}

string reconstruir(int i, int j, string const& p, Matriz<EntInf> const& m) {
   if (i > j) return {};
   else if (i == j) return { p[i] };
   else if (p[i] == p[j])
      return p[i] + reconstruir(i+1,j-1,p,m) + p[j];
   else if (m[i][j] == m[i+1][j] + 1)
     return p[i] + reconstruir(i+1,j,p,m) + p[i];
   else
      return p[j] + reconstruir(i,j-1,p,m) + p[j];
}


// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
   string str;

   cin >> str;

   if (!cin)
      return false;

   Matriz<EntInf> m(str.size(), str.size(), Infinito);

   EntInf sol = aibofobia(0, str.size()-1, str, m);

   string pal = reconstruir(0, str.size()-1, str, m);

   cout << sol << ' ' << pal << '\n';

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
