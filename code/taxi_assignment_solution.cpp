#include "taxi_assignment_solution.h"

TaxiAssignmentSolution::TaxiAssignmentSolution() {}

TaxiAssignmentSolution::TaxiAssignmentSolution(int n) {
    this->_n = n;
    this->_taxi_assignment = std::vector<int>(n, -1);
    this->_pax_assignment = std::vector<int>(n, -1);
}

int TaxiAssignmentSolution::getN() const {
    return this->_n;
}

void TaxiAssignmentSolution::assign(int taxi, int pax) {
    this->_taxi_assignment[taxi] = pax+1; 
    this->_pax_assignment[pax] = taxi+1;
    // Agregamos +1 para que los taxis y pax empiecen su numeracion en 1 y no 0 y evitar conflictos con el nodo source (0) en la estrategia de batching.
}

bool TaxiAssignmentSolution::isTaxiAssigned(int taxi) const {
    return this->_taxi_assignment[taxi] != -1;
}

bool TaxiAssignmentSolution::isPaxAssigned(int pax) const {
    return this->_pax_assignment[pax] != -1;
}

int TaxiAssignmentSolution::getAssignedPax(int taxi) const {
    return this->_taxi_assignment[taxi];
}

int TaxiAssignmentSolution::getAssignedTaxi(int pax) const {
    return this->_pax_assignment[pax];
}

std::ostream& operator<<(std::ostream& os, const TaxiAssignmentSolution& solution) {
    os << "taxis: ";
    for (int i = 0; i < solution.getN(); i++)
        os << solution.getAssignedPax(i) << " ";
    os << std::endl;
    os << "paxs: ";
    for (int i = 0; i < solution.getN(); i++)
        os << solution.getAssignedTaxi(i) << " ";
    os << std::endl;
    os << "taxi \t --> \t pax" << std::endl;
    for (int i = 0; i < solution.getN(); i++) {
        os << i+1 << " \t --> \t" << solution.getAssignedPax(i) << std::endl; 
        // Agregamos +1 para que los taxis y pax empiecen su numeracion en 1 y no 0 y evitar conflictos con el nodo source (0) en la estrategia de batching.
    }

    return os;
}

