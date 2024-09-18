#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>

#include "Matriz.h" 
#include "EnterosInf.h" // propios o los de las estructuras de datos de clase

using namespace std;

/*

i = izquirda
j = derecha


*/

char multiplicar(char x, char y) {
    switch (x)
    {
    case 'a':
        switch (y)
        {
        case 'a':
            return 'b';
        case 'b':
            return 'b';
        case 'c':
            return 'a';
        }
    case 'b':
        switch (y)
        {
        case 'a':
            return 'c';
        case 'b':
            return 'b';
        case 'c':
            return 'a';
        }
    case 'c':
        switch (y)
        {
        case 'a':
            return 'a';
        case 'b':
            return 'c';
        case 'c':
            return 'c';
        }
    }

    return '\0';
}

bool parentesis(string const& str) {
    vector<vector<unordered_map<char,bool>>> m(str.size(), vector<unordered_map<char,bool>>(str.size()));

    for (int i = 0; i < str.size(); i++)
        m[i][i][str[i]] = true;
    


    for (int i = str.size()-1; i >= 0; i--)
        for (int j = 0; j < str.size(); j++) {
            if (i < j) {
                for (int k = i; k < j && !m[i][j]['a']; k++) {
                    m[i][j]['a'] = (m[i][k]['a'] && m[k+1][j]['c']) || (m[i][k]['b'] && m[k+1][j]['c']) || (m[i][k]['c'] && m[k+1][j]['a']);
                }

                for (int k = i; k < j && !m[i][j]['b']; k++) {
                    m[i][j]['b'] = (m[i][k]['a'] && m[k+1][j]['a']) || (m[i][k]['a'] && m[k+1][j]['b']) || (m[i][k]['b'] && m[k+1][j]['b']);
                }

                for (int k = i; k < j && !m[i][j]['c']; k++) {
                    m[i][j]['c'] = (m[i][k]['b'] && m[k+1][j]['a']) || (m[i][k]['c'] && m[k+1][j]['b']) || (m[i][k]['c'] && m[k+1][j]['c']);
                }
            }
        }

    return m[0][str.size()-1]['a'];
}


// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    string str;

    cin >> str;

    if (!cin)
        return false;


    if (parentesis(str))
        cout << "SI\n";
    else
        cout << "NO\n";

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
