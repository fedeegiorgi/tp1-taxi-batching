#include "checker.h"

TaxiAssignmentChecker::TaxiAssignmentChecker() :_feasibility_status(std::vector<bool>(3,false)) {}

bool TaxiAssignmentChecker::checkFeasibility(const TaxiAssignmentInstance &instance, const TaxiAssignmentSolution &solution) {
    bool ret = false;

    return ret;
}

// función para chequear el rendimiento económico por km dada una instancia y su solución de asignación
// rendimiento dado por el promedio del ratio: tarifa total / (distancia recogida + distancia de viaje) para cada pasajero dada su asignación

double TaxiAssignmentChecker::getSolutionBenefit(const TaxiAssignmentInstance &instance, const TaxiAssignmentSolution &solution) {
    double ret = 0.0;
    
    for (int i = 0; i < instance.n; i++) {
        int j = solution.getAssignedPax(i)-1; // -1 pues estan numerados del 1 al 10 para que no se confunda en batching con 0 que es el nodo source.
        double rendm_km = instance.pax_tot_fare[j] / (instance.pax_trip_dist[j] + instance.dist[i][j]); // ratio rendimiento para el pasajero j y el i-esimo taxi
        ret += rendm_km;
    }

    return ret/instance.n; // promedio del rendimiento global dada la asignación de n pasajeros y n taxis
}

// función para chequear el costo en términos de distancia hasta recogida dada una instancia y su solución de asignación

double TaxiAssignmentChecker::getSolutionCost(const TaxiAssignmentInstance &instance, const TaxiAssignmentSolution &solution) {
    double ret = 0.0;
    
    for (int i = 0; i < instance.n; i++) {
        int j = solution.getAssignedPax(i)-1; // -1 pues estan numerados del 1 al 10 para que no se confunda en batching con 0 que es el nodo source.
        ret += instance.dist[i][j];
    }

    return ret;
}