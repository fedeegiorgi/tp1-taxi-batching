#include "greedy_solver.h"


GreedySolver::GreedySolver() {}

GreedySolver::GreedySolver(TaxiAssignmentInstance &instance) {
    this->_instance = instance;
    this->_objective_value = 0;
    this->_solution_status = 0;
    this->_solution_time = 0;
}

void GreedySolver::setInstance(TaxiAssignmentInstance &instance) {
    this->_instance = instance;
}

void GreedySolver::solve() {
    // prueba: entendiendo como funciona la calse TaxiAssignmentSolution

    // crea objeto solucion con n (cant. pax y taxis) 
    TaxiAssignmentSolution _solution = TaxiAssignmentSolution(this->_instance.n);

    // tenemos para usar:
    // _solution.getN()
    // _solution.assign(i-esimo taxi, j-esimo pax) 
    // _solution.isTaxiAssigned(i-esimo taxi)
    // _solution.isPaxAssigned(j-esimo pax)

    // _instance.dist[i-esimo taxi][j-esimo pax] 

    // objetivo: completar los vectores _taxi_assignment y _pax_assignment de _solution tal que
    // _solution.getAssignedPax(i-esimo taxi) y _solution.getAssignedTaxi(j-esimo pax) den solución para todo i y j


    // idea pseudocodigo algoritmo:
    for (int j = 0; j < _solution.getN(); j++) {  // por cada pasajero en orden de columna (o sea orden de solicitud)
        int auto_a_asignar = getMinDist(j); // obtener de la columna j (pax), la posición i (auto) disponible con menos distancia posible
        _solution.assign[auto_a_asignar, j]; // asignar taxi y pax j
    }

}

// ni idea si es la idea hacer una func auxiliar, supongo q no hay problema
// int getMinDist(int j) {
    // recorre la columna j
        // if min > _instance.dist[i][j] && !(_solution.isTaxiAssigned[i]) // si la dist es menor y ese taxi ya no fue asignado
        //     min = i

    // return i
// }

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


