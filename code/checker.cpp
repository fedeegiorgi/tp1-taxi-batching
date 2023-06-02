#include "checker.h"

TaxiAssignmentChecker::TaxiAssignmentChecker() :_feasibility_status(std::vector<bool>(3,false)) {}

bool TaxiAssignmentChecker::checkFeasibility(const TaxiAssignmentInstance &instance, const TaxiAssignmentSolution &solution) {
    bool ret = false;

    return ret;
}

// Función para calcular el rendimiento económico por km dada una instancia y su solución de asignación.
// Rendimiento dado por el promedio del ratio: tarifa total / (distancia recogida + distancia de viaje) para cada pasajero dada su asignación

double TaxiAssignmentChecker::getSolutionBenefit(const TaxiAssignmentInstance &instance, const TaxiAssignmentSolution &solution) {
    double ret = 0.0;
    int casos_anomalos = 0;
    for (int i = 0; i < instance.n; i++) {
        // obetenemos el pasajero j asignado al taxi i
        // -1 pues estan numerados del 1 al 10 para que no se confunda en batching con 0 que es el nodo source(s).
        int j = solution.getAssignedPax(i)-1; 
        // Calculo del ratio rendimiento para el pasajero j y el i-esimo taxi
        double rendm_km = instance.pax_tot_fare[j] / (instance.pax_trip_dist[j] + instance.dist[i][j]); 
        // Si el rendimiento da infinito es porque el denominador da 0 pues dist_ij = 0 y trip_j = 0
        // Se considera como caso anómalo y no se suma al promedio
        if (rendm_km > 3000) {
            casos_anomalos += 1;
        } else {
            ret += rendm_km;
        }
    }
    // Promedio del rendimiento global dada la asignación de n pasajeros y n taxis
    return ret/(instance.n - casos_anomalos); 
}

// Función para calcular la relación entre las distancias de recogidas y las distancias de los viajes dada una instancia y su solución de asignación.
// Esta métrica se calcula como el promedio del ratio: distancia recogida / distancia de viaje para cada pasajero dada su asignación
double TaxiAssignmentChecker::getAvgRelativeDistance(const TaxiAssignmentInstance &instance, const TaxiAssignmentSolution &solution) {
    double ret = 0.0;

    for (int i = 0; i < instance.n; i++) {
        // obetenemos el pasajero j asignado al taxi i
        // -1 pues estan numerados del 1 al 10 para que no se confunda en batching con 0 que es el nodo source(s).
        int j = solution.getAssignedPax(i)-1;

        double dist;
        // verificamos que las tarifas no sean 0 o negativas para que esté bien definida la métrica
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

// Función para calcular el costo en términos de distancia hasta recogida dada una instancia y su solución de asignación.
double TaxiAssignmentChecker::getSolutionCost(const TaxiAssignmentInstance &instance, const TaxiAssignmentSolution &solution) {
    double ret = 0.0;
    
    for (int i = 0; i < instance.n; i++) {
        // obetenemos el pasajero j asignado al taxi i
        // -1 pues estan numerados del 1 al 10 para que no se confunda en batching con 0 que es el nodo source(s).
        int j = solution.getAssignedPax(i)-1; 
        // sumamos las distancias
        ret += instance.dist[i][j];
    }

    return ret;
}