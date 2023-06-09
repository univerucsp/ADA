#include <iostream>
#include <vector>

struct Objeto {
    int peso;
    int beneficio;
};

void resolverProblemaMochila(int capacidadMaxima, const std::vector<Objeto>& objetos, std::vector<int>& X) {
    int n = objetos.size();
    X.resize(n, 0); // Inicializar X con ceros

    int pesoAct = 0;

    while (pesoAct < capacidadMaxima) {
        int mejorObjeto = -1;
        double mejorRelacion = 0.0;

        for (int i = 0; i < n; i++) {
            if (X[i] == 0) {
                double relacion = static_cast<double>(objetos[i].beneficio) / objetos[i].peso;
                if (relacion > mejorRelacion) {
                    mejorRelacion = relacion;
                    mejorObjeto = i;
                }
            }
        }

        if (mejorObjeto == -1) {
            break; // No hay más objetos disponibles
        }

        if (pesoAct + objetos[mejorObjeto].peso <= capacidadMaxima) {
            X[mejorObjeto] = 1;
            pesoAct += objetos[mejorObjeto].peso;
        } else {
            X[mejorObjeto] = (capacidadMaxima - pesoAct) / objetos[mejorObjeto].peso;
            pesoAct = capacidadMaxima;
        }
    }
}

int main() {
    int n, capacidadMaxima;

    // Leer el número de objetos y la capacidad máxima de la mochila
    std::cout << "Ingrese el número de objetos: ";
    std::cin >> n;
    std::cout << "Ingrese la capacidad máxima de la mochila: ";
    std::cin >> capacidadMaxima;

    // Leer los pesos y beneficios de los objetos
    std::vector<Objeto> objetos(n);
    for (int i = 0; i < n; i++) {
        std::cout << "Ingrese el peso y beneficio del objeto " << i + 1 << ": ";
        std::cin >> objetos[i].peso >> objetos[i].beneficio;
    }

    // Resolver el problema de la mochila
    std::vector<int> X;
    resolverProblemaMochila(capacidadMaxima, objetos, X);

    // Mostrar la solución
    std::cout << "Solución: ";
    for (int i = 0; i < n; i++) {
        std::cout << X[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}

