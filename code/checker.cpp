#include "checker.h"

TaxiAssignmentChecker::TaxiAssignmentChecker() :_feasibility_status(std::vector<bool>(3,false)) {}

bool TaxiAssignmentChecker::checkFeasibility(const TaxiAssignmentInstance &instance, const TaxiAssignmentSolution &solution) {
    bool ret = false;

    return ret;
}

double TaxiAssignmentChecker::getSolutionCost(const TaxiAssignmentInstance &instance, const TaxiAssignmentSolution &solution) {
    double ret = 0.0;
    
    for (int i = 0; i < instance.n; i++) {
        int j = solution.getAssignedPax(i)-1; // -1 pq estan numerados del 1 al 10 para q no se confunda en batching con 0 que es el nodo source
        double rendm_km = instance.pax_tot_fare[j] / (instance.pax_trip_dist[j] + instance.dist[i][j]);
        ret += rendm_km;
    }

    return ret/instance.n;
}
