#include <iostream>
#include <fstream>
#include <vector>

#include "Matriz.h" 
#include "EnterosInf.h" // propios o los de las estructuras de datos de clase

using namespace std;

/*
Recurrencia

j es el tamaño de la cometa
i es hasta qué cordel usamos


                 esPosible(i-1,j) si j < Long[i]
esPosible(i, j) = 
                 esPosible(i-1,j) || cometas(i-1,j-C[i]) otherwise

*/

bool esPosible(int N, int L, vector<pair<int,int>> &C) {
   vector<bool> v(L+1,false);
   v[0] = true;
   for (int i = 0; i < N; i++) {
      for (int j = L; j > 0; j--) {
         if (j >= C[i].first) {
            v[j] = v[j] || v[j-C[i].first];
         }
      }
   }

   return v[L];
}

/*
Recurrencia

j es el tamaño de la cometa
i es hasta qué cordel usamos

matematico(i, j) =   matematico(i-1,j) si j < Long[i]
                     matematico(i-1,j-Long[i]) + matematico(i-1, j)
*/

long long int matematico(int N, int L, vector<pair<int,int>> &C) {
   vector<long long int> v(L+1, 0);
   v[0] = 1;
   for (int i = 0; i < N; i++) {
      for (int j = L; j > 0; j--) {
         if (j >= C[i].first) {
            v[j] += v[j-C[i].first];
         }
      }
   }

   return v[L];
}

/*
Recurrencia

j es el tamaño de la cometa
i es hasta qué cordel usamos

ingeniero(i, j) =    ingeniero(i-1,j) si j < C¡Long[i]
                     min(ingeniero(i-1,j-Long[i]) + 1, ingeniero(i-1, j)) otherwise
*/


EntInf ingeniero(int N, int L, vector<pair<int,int>> &C) {
   vector<EntInf> v(L+1, Infinito);
   v[0] = 0;

   for (int i = 0; i < N; i++) {
      for (int j = L; j > 0; j--) {
         if (j >= C[i].first) {
            v[j] = min(v[j], v[j-C[i].first] + 1);
         }
      }
   }

   return v[L];
}

/*
Recurrencia

j es el tamaño de la cometa
i es hasta qué cordel usamos

economista(i, j) =    economista(i-1,j) si j < Long[i]
                      min(economista(i-1,j-Long[i]) + Coste[i], economista(i-1, j)) otherwise
*/

EntInf economista(int N, int L, vector<pair<int,int>> &C) {
   vector<EntInf> v(L+1, Infinito);
   v[0] = 0;

   for (int i = 0; i < N; i++) {
      for (int j = L; j > 0; j--) {
         if (j >= C[i].first) {
            v[j] = min(v[j], v[j-C[i].first] + C[i].second);
         }
      }
   }

   return v[L];
}


// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
   int N, L;
   
   // leer los datos de la entrada
   std::cin >> N >> L;
   
   if (!std::cin)  // fin de la entrada
      return false;

   vector<pair<int,int>> C(N);


   for (int i = 0; i < N; i++)
      cin >> C[i].first >> C[i].second;

   if (esPosible(N, L, C)) {
      long long int solMat = matematico(N, L, C);
      EntInf solIng = ingeniero(N, L, C);
      EntInf solEc = economista(N, L, C);

      cout << "SI " << solMat << ' ' << solIng << ' ' << solEc << '\n';
   }
   else {
      cout << "NO\n";
   }

   // escribir sol
   
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
