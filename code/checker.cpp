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
    int casos_anomalos = 0;
    for (int i = 0; i < instance.n; i++) {
        int j = solution.getAssignedPax(i)-1; // -1 pues estan numerados del 1 al 10 para que no se confunda en batching con 0 que es el nodo source.
        double rendm_km = instance.pax_tot_fare[j] / (instance.pax_trip_dist[j] + instance.dist[i][j]); // ratio rendimiento para el pasajero j y el i-esimo taxi
        // si el rendimiento da infinito es porque el denominador da 0 pues dist_ij = 0 y trip_j = 0, no suma al promedio
        if (rendm_km > 3000) {
            casos_anomalos += 1;
        } else {
            ret += rendm_km;
        }
    }

    return ret/(instance.n - casos_anomalos); // promedio del rendimiento global dada la asignación de n pasajeros y n taxis
}

double TaxiAssignmentChecker::getSolutionBenefit_2(const TaxiAssignmentInstance &instance, const TaxiAssignmentSolution &solution) {
    double ret = 0.0;
    
    for (int i = 0; i < instance.n; i++) {
        int j = solution.getAssignedPax(i)-1; // -1 pues estan numerados del 1 al 10 para que no se confunda en batching con 0 que es el nodo source.
        double rendm_km;
        if (instance.pax_tot_fare[j] < 0) {
            // rendm_km = instance.pax_tot_fare[j] / (instance.pax_trip_dist[j] + instance.dist[i][j]);
            rendm_km = (instance.dist[i][j]*10 + instance.pax_trip_dist[j]*10) / (instance.pax_tot_fare[j]*-1);
        } else if (instance.pax_tot_fare[j] == 0) {
            rendm_km = (instance.dist[i][j]*10 + instance.pax_trip_dist[j]*10) / 1;
        } else {
            rendm_km = (instance.dist[i][j]*10 + instance.pax_trip_dist[j]*10) / instance.pax_tot_fare[j];
        }
         // ratio rendimiento para el pasajero j y el i-esimo taxi
        ret += rendm_km;
    }

    return ret/instance.n; // promedio del rendimiento global dada la asignación de n pasajeros y n taxis
}

double TaxiAssignmentChecker::getAvgRelativeDistance(const TaxiAssignmentInstance &instance, const TaxiAssignmentSolution &solution) {
    double ret = 0.0;

    for (int i = 0; i < instance.n; i++) {
        int j = solution.getAssignedPax(i)-1;
        double dist;
        if (instance.pax_trip_dist[j] < 0) {
            dist = (instance.dist[i][j] / abs(instance.pax_trip_dist[j])) * 10;
        } else if (instance.pax_trip_dist[j] == 0) {
            dist = (instance.dist[i][j] / 1) * 10;
        } else {
            dist = (instance.dist[i][j] / instance.pax_trip_dist[j]) * 10;
        }

        ret += dist;
    }

    return ret/instance.n;
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