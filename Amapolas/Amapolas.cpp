#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

/*
i es la letra de la primera palabra
j es la letra de la segunda palabra 

amapola(i,j) = amapola(i+1,j+1) + 1 si str1[i] == str1[j]
               max(amapola(i+1, j), amapola(i,j+1))


*/


int amapola(int i, int j, string const& str1, string const& str2,
                vector<vector<int>>& amap) {
    if (i >= str1.size() || j >= str2.size())
            return 0;
    else if (amap[i][j] == -1) {
        if (str1[i] == str2[j])
            amap[i][j] = amapola(i+1, j+1, str1, str2, amap) + 1;
        else
            amap[i][j] = max(amapola(i+1,j,str1,str2,amap), amapola(i, j+1, str1, str2,amap));
    }

    return amap[i][j];
}

void reconstruir(int i, int j, string const& str1, string const& str2, 
                    vector<vector<int>> const& amap, string& sol) {
    if (i >= str1.length() || j >= str2.length()) {
        return;
    }
    else if (str1[i] == str2[j]) {
        sol.push_back(str1[i]);
        reconstruir(i+1,j+1, str1, str2, amap, sol);
    }
    else if (amap[i][j] == amap[i][j+1])
        reconstruir(i,j+1, str1, str2, amap, sol);
    else
        reconstruir(i+1,j, str1, str2, amap, sol);
}

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    string str1, str2;

    cin >> str1 >> str2;

    if (!cin)
        return false;

    vector<vector<int>> amap(str1.length()+1, vector<int>(str2.length()+1, -1)); 

    amapola(0,0,str1,str2,amap);

    string sol;

    reconstruir(0,0,str1,str2,amap,sol);

    cout << sol << '\n';
    

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
