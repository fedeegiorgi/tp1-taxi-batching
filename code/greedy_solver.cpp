#include "greedy_solver.h"
#include <chrono>

GreedySolver::GreedySolver() {}

GreedySolver::GreedySolver(TaxiAssignmentInstance &instance) {
    this->_instance = instance;
    this->_objective_value = 0;
    this->_solution_status = 0;
    this->_solution_time = 0;
    this->_solution = TaxiAssignmentSolution(this->_instance.n);

}

void GreedySolver::setInstance(TaxiAssignmentInstance &instance) {
    this->_instance = instance;
}

void GreedySolver::solve() {
    // objetivo: completar los vectores _taxi_assignment y _pax_assignment de _solution tal que
    // _solution.getAssignedPax(i-esimo taxi) y _solution.getAssignedTaxi(j-esimo pax) den solución para todo i y j
    
    // Inicializamos timer.
    std::chrono::time_point<std::chrono::system_clock> start, end;
    start = std::chrono::system_clock::now();

    int n = this->_solution.getN();

    for (int j = 0; j < n; j++) {  // por cada pasajero en orden de columna (o sea orden de solicitud)
        double min = 9999; // infinito
        int min_index = 0;

        for (int i = 0; i < n; i++) { // obtener de la columna j (pax), la posición i (auto) disponible con menos distancia posible
            if (min > this->_instance.dist[i][j] && !(this->_solution.isTaxiAssigned(i))) {
                min = this->_instance.dist[i][j];
                min_index = i;
            }
        }
        std::cout << min_index << std::endl;
        this->_solution.assign(min_index, j); // asignar taxi y pax j
        this->_objective_value += this->_instance.dist[min_index][j];
    }

    // Frenamos timer.
    end = std::chrono::system_clock::now();
    std::chrono::duration<double> duration = end - start;
    
    this->_solution_time = duration.count();
}

double GreedySolver::getObjectiveValue() const {
    return this->_objective_value;
}

TaxiAssignmentSolution GreedySolver::getSolution() const {
    return this->_solution;
}

int GreedySolver::getSolutionStatus() const {
    return this->_solution_status;
}

double GreedySolver::getSolutionTime() const {
    return this->_solution_time;
}


