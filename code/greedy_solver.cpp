#include "greedy_solver.h"
#include <chrono>

GreedySolver::GreedySolver() {}

GreedySolver::GreedySolver(TaxiAssignmentInstance &instance) {
    this->_instance = instance;
    this->_objective_value = 0;
    this->_solution_status = 0;
    this->_solution_time = 0;

    // Inicializamos un objeto solución que luego será modificado por el método "solve" al momento de resolver el problema para la instancia dada.
    this->_solution = TaxiAssignmentSolution(this->_instance.n); 
}

void GreedySolver::setInstance(TaxiAssignmentInstance &instance) {
    this->_instance = instance;
}

void GreedySolver::solve() {
    // Objetivo: completar los vectores _taxi_assignment y _pax_assignment de _solution tal que:
    // _solution.getAssignedPax(i-esimo taxi) y _solution.getAssignedTaxi(j-esimo pax) den solución para todo i y j.
    
    // Inicializamos timer.
    std::chrono::time_point<std::chrono::high_resolution_clock> start, end;
    start = std::chrono::high_resolution_clock::now();

    int n = this->_solution.getN(); // n = cantidad de pasajeros = cantidad de taxis.

    for (int j = 0; j < n; j++) {  // Por cada pasajero en orden de columna (o sea orden de solicitud).
        double min = 9999; // Infinito.
        int min_index = 0;

        for (int i = 0; i < n; i++) { // Obtener de la columna j (pax), la posición i (auto) disponible con menos distancia posible.
            if (min > this->_instance.dist[i][j] && !(this->_solution.isTaxiAssigned(i))) {
                min = this->_instance.dist[i][j];
                min_index = i;
            }
        }
        this->_solution.assign(min_index, j); // Asignar taxi i al pax j.
        this->_objective_value += this->_instance.dist[min_index][j]; // Sumamos al valor objetivo que es la distancia total, la distancia de el taxi seleccionado al pasajero.
    }

    // Frenamos timer.
    end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    
    this->_solution_time = duration.count() * 1000; // Asignamos al tiempo que tardamos en dar la solución lo que nos marca el timer.
    this->_solution_status = 1; // Marcamos que el problema fue resuelto.
}

double GreedySolver::getObjectiveValue() const {
    return this->_objective_value; // Devolvemos el objective value construido en el solve.
}

TaxiAssignmentSolution GreedySolver::getSolution() const {
    return this->_solution; // Devolvemos la solucion construida en el solve.
}

int GreedySolver::getSolutionStatus() const {
    return this->_solution_status; // Devolvemos el estado de la instancia, 1 si fue resuelta, 0 si no.
}

double GreedySolver::getSolutionTime() const {
    return this->_solution_time; // Devolvemos el tiempo que tardo en correrse el solve.
}


