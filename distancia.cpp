#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
using namespace std;

struct Point {
    int x, y;
};

// Función para calcular la distancia euclidiana entre dos puntos
double distancia(const Point& p1, const Point& p2) {
    return sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2));
}

// Función para encontrar la distancia mínima entre puntos utilizando divide y vencerás
double distancia_minima(vector<Point>& puntos, int izq, int der) {
    // Caso base: si hay menos de 2 puntos, no se puede calcular la distancia mínima
    if (der - izq < 1) {
        return numeric_limits<double>::infinity();
    }

    // Caso base: si hay exactamente 2 puntos, se calcula su distancia directamente
    if (der - izq == 1) {
        return distancia(puntos[izq], puntos[der]);
    }

    // Dividir en subproblemas izquierdo y derecho
    int medio = (izq + der) / 2;
    double distancia_izq = distancia_minima(puntos, izq, medio);
    double distancia_der = distancia_minima(puntos, medio + 1, der);

    // Calcular la distancia mínima entre los puntos que cruzan la línea vertical
    double distancia_cruce = min(distancia_izq, distancia_der);

    // Encontrar los puntos dentro de la franja central
    vector<Point> franja;
    int punto_medio_x = puntos[medio].x;
    for (int i = izq; i <= der; i++) {
        if (abs(puntos[i].x - punto_medio_x) < distancia_cruce) {
            franja.push_back(puntos[i]);
        }
    }

    // Calcular la distancia mínima entre los puntos dentro de la franja
    double minima_distancia_franja = distancia_cruce;
    for (size_t i = 0; i < franja.size(); i++) {
        for (size_t j = i + 1; j < franja.size() && (franja[j].y - franja[i].y) < minima_distancia_franja; j++) {
            double dist = distancia(franja[i], franja[j]);
            minima_distancia_franja = min(minima_distancia_franja, dist);
        }
    }

    // Calcular y retornar la distancia mínima final
    return min(distancia_cruce, minima_distancia_franja);
}

int main() {
    vector<Point> puntos = {{2, 3}, {12, 30}, {40, 50}, {5, 1}, {12, 10}, {3, 4}};
    int n = puntos.size();
    sort(puntos.begin(), puntos.end(), [](const Point& a, const Point& b) {
        return a.x < b.x;
    });

    double minima_distancia = distancia_minima(puntos, 0, n - 1);

    cout << "La distancia mínima entre los puntos es: " << minima_distancia << endl;

    return 0;
}

