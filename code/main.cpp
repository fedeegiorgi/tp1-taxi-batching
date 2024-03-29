#include "taxi_assignment_instance.h"
#include "taxi_assignment_solution.h"
#include "checker.h"
#include "greedy_solver.h"
#include "taxi_assignment_batching_solver.h"
#include "batching_solver_v2.h"
#include "batching_solver_v3.h"

#include <iostream>
#include <fstream>
#include <vector>

// <strategy>_cost = suma de la distancias para recoger a los pasajeros.
// <strategy>_time = tiempo de ejecución de la asignación.
// <strategy>_relative_dist = promedio de la relación entre distancia de recogida y del viaje para cada asignación de la instancia.
// <strategy>_benefit = promedio de los rendimientos económicos sobre distancia recorrida de los vehiculos.

struct Result {
    int n;
    double greedy_cost;
    double greedy_time;
    double greedy_relative_dist;
    double greedy_benefit;
    double batching_cost;
    double batching_time;
    double batching_relative_dist;
    double batching_benefit;
    double alternative_cost;
    double alternative_time;
    double alternative_relative_dist;
    double alternative_benefit;
    double alternative2_cost;
    double alternative2_time;
    double alternative2_relative_dist;
    double alternative2_benefit;
};

void exportToCSV(const std::vector<Result>& results, const std::string& filename) {
    std::ofstream file(filename);

    // Chequeamos que el archivo se abra correctamente.
    if (!file) {
        std::cerr << "Error abriendo el archivo." << std::endl;
        return;
    }

    // Seteamos los headers para las columnas
    file << "n,greedy_cost,greedy_time,greedy_relative_dist,greedy_benefit,batching_cost,batching_time,batching_relative_dist,batching_benefit,alternative_cost,alternative_time,alternative_relative_dist,alternative_benefit,alternative2_cost,alternative2_time,alternative2_relative_dist,alternative2_benefit\n";

    // Escribimos el resultado para una asignación dada.
    for (const auto& result : results) {
        file << result.n << "," << result.greedy_cost << "," << result.greedy_time << "," << result.greedy_relative_dist << "," << result.greedy_benefit << ","
             << result.batching_cost << "," << result.batching_time << "," << result.batching_relative_dist << "," << result.batching_benefit << ","
             << result.alternative_cost << "," << result.alternative_time << "," << result.alternative_relative_dist << "," << result.alternative_benefit << ","
             << result.alternative2_cost << "," << result.alternative2_time << "," << result.alternative2_relative_dist << "," << result.alternative2_benefit <<"\n";
    }

    // Cierre del archivo.
    file.close();

    std::cout << "Los resultados fueron exportados a " << filename << " satisfactoriamente." << std::endl;
}

int main(int argc, char** argv) {

    std::vector<Result> results;

    // obtención de los resultados para los tamaños de muestra n = 10.
    for (int i = 0; i < 10; i++) {
        std::string filename = "input/small_" + std::to_string(i) + ".csv";
        TaxiAssignmentInstance instance(filename);

        GreedySolver greedy_solver(instance);
        TaxiAssignmentChecker greedy_checker;
        greedy_solver.solve();

        BatchingSolver batching_solver(instance);
        TaxiAssignmentChecker batching_checker;
        batching_solver.solve();

        BatchingSolver_v2 batching_2_solver(instance);
        TaxiAssignmentChecker batching_2_checker;
        batching_2_solver.solve();

        BatchingSolver_v3 batching_3_solver(instance);
        TaxiAssignmentChecker batching_3_checker;
        batching_3_solver.solve();

        results.push_back({instance.n, greedy_solver.getObjectiveValue(), greedy_solver.getSolutionTime(), greedy_checker.getAvgRelativeDistance(instance, greedy_solver.getSolution()),greedy_checker.getSolutionBenefit(instance, greedy_solver.getSolution()), 
                           batching_solver.getObjectiveValue()/10.0, batching_solver.getSolutionTime(), batching_checker.getAvgRelativeDistance(instance, batching_solver.getSolution()),batching_checker.getSolutionBenefit(instance, batching_solver.getSolution()), 
                           batching_2_checker.getSolutionCost(instance, batching_2_solver.getSolution()), batching_2_solver.getSolutionTime(), batching_2_checker.getAvgRelativeDistance(instance, batching_2_solver.getSolution()),batching_2_checker.getSolutionBenefit(instance, batching_2_solver.getSolution()),
                           batching_3_checker.getSolutionCost(instance, batching_3_solver.getSolution()), batching_3_solver.getSolutionTime(), batching_3_checker.getAvgRelativeDistance(instance, batching_3_solver.getSolution()),batching_3_checker.getSolutionBenefit(instance, batching_3_solver.getSolution())});
    }

    // Obtención de los resultados para los tamaños de muestra n = 100.
    for (int i = 0; i < 10; i++) {
        std::string filename = "input/medium_" + std::to_string(i) + ".csv";
        TaxiAssignmentInstance instance(filename);

        GreedySolver greedy_solver(instance);
        TaxiAssignmentChecker greedy_checker;
        greedy_solver.solve();

        BatchingSolver batching_solver(instance);
        TaxiAssignmentChecker batching_checker;
        batching_solver.solve();

        BatchingSolver_v2 batching_2_solver(instance);
        TaxiAssignmentChecker batching_2_checker;
        batching_2_solver.solve();

        BatchingSolver_v3 batching_3_solver(instance);
        TaxiAssignmentChecker batching_3_checker;
        batching_3_solver.solve();

        results.push_back({instance.n, greedy_solver.getObjectiveValue(), greedy_solver.getSolutionTime(), greedy_checker.getAvgRelativeDistance(instance, greedy_solver.getSolution()),greedy_checker.getSolutionBenefit(instance, greedy_solver.getSolution()), 
                           batching_solver.getObjectiveValue()/10.0, batching_solver.getSolutionTime(), batching_checker.getAvgRelativeDistance(instance, batching_solver.getSolution()),batching_checker.getSolutionBenefit(instance, batching_solver.getSolution()), 
                           batching_2_checker.getSolutionCost(instance, batching_2_solver.getSolution()), batching_2_solver.getSolutionTime(), batching_2_checker.getAvgRelativeDistance(instance, batching_2_solver.getSolution()),batching_2_checker.getSolutionBenefit(instance, batching_2_solver.getSolution()),
                           batching_3_checker.getSolutionCost(instance, batching_3_solver.getSolution()), batching_3_solver.getSolutionTime(), batching_3_checker.getAvgRelativeDistance(instance, batching_3_solver.getSolution()),batching_3_checker.getSolutionBenefit(instance, batching_3_solver.getSolution())});
    }

    // Obtención de los resultados para los tamaños de muestra n = 250.
    for (int i = 0; i < 10; i++) {
        std::string filename = "input/large_" + std::to_string(i) + ".csv";
        TaxiAssignmentInstance instance(filename);

        GreedySolver greedy_solver(instance);
        TaxiAssignmentChecker greedy_checker;
        greedy_solver.solve();

        BatchingSolver batching_solver(instance);
        TaxiAssignmentChecker batching_checker;
        batching_solver.solve();

        BatchingSolver_v2 batching_2_solver(instance);
        TaxiAssignmentChecker batching_2_checker;
        batching_2_solver.solve();

        BatchingSolver_v3 batching_3_solver(instance);
        TaxiAssignmentChecker batching_3_checker;
        batching_3_solver.solve();

        results.push_back({instance.n, greedy_solver.getObjectiveValue(), greedy_solver.getSolutionTime(), greedy_checker.getAvgRelativeDistance(instance, greedy_solver.getSolution()),greedy_checker.getSolutionBenefit(instance, greedy_solver.getSolution()), 
                           batching_solver.getObjectiveValue()/10.0, batching_solver.getSolutionTime(), batching_checker.getAvgRelativeDistance(instance, batching_solver.getSolution()),batching_checker.getSolutionBenefit(instance, batching_solver.getSolution()), 
                           batching_2_checker.getSolutionCost(instance, batching_2_solver.getSolution()), batching_2_solver.getSolutionTime(), batching_2_checker.getAvgRelativeDistance(instance, batching_2_solver.getSolution()),batching_2_checker.getSolutionBenefit(instance, batching_2_solver.getSolution()),
                           batching_3_checker.getSolutionCost(instance, batching_3_solver.getSolution()), batching_3_solver.getSolutionTime(), batching_3_checker.getAvgRelativeDistance(instance, batching_3_solver.getSolution()),batching_3_checker.getSolutionBenefit(instance, batching_3_solver.getSolution())});
    }

    // Obtención de los resultados para los tamaños de muestra n = 500.
    for (int i = 0; i < 10; i++) {
        std::string filename = "input/xl_" + std::to_string(i) + ".csv";
        TaxiAssignmentInstance instance(filename);

        GreedySolver greedy_solver(instance);
        TaxiAssignmentChecker greedy_checker;
        greedy_solver.solve();

        BatchingSolver batching_solver(instance);
        TaxiAssignmentChecker batching_checker;
        batching_solver.solve();

        BatchingSolver_v2 batching_2_solver(instance);
        TaxiAssignmentChecker batching_2_checker;
        batching_2_solver.solve();

        BatchingSolver_v3 batching_3_solver(instance);
        TaxiAssignmentChecker batching_3_checker;
        batching_3_solver.solve();

        results.push_back({instance.n, greedy_solver.getObjectiveValue(), greedy_solver.getSolutionTime(), greedy_checker.getAvgRelativeDistance(instance, greedy_solver.getSolution()),greedy_checker.getSolutionBenefit(instance, greedy_solver.getSolution()), 
                           batching_solver.getObjectiveValue()/10.0, batching_solver.getSolutionTime(), batching_checker.getAvgRelativeDistance(instance, batching_solver.getSolution()),batching_checker.getSolutionBenefit(instance, batching_solver.getSolution()), 
                           batching_2_checker.getSolutionCost(instance, batching_2_solver.getSolution()), batching_2_solver.getSolutionTime(), batching_2_checker.getAvgRelativeDistance(instance, batching_2_solver.getSolution()),batching_2_checker.getSolutionBenefit(instance, batching_2_solver.getSolution()),
                           batching_3_checker.getSolutionCost(instance, batching_3_solver.getSolution()), batching_3_solver.getSolutionTime(), batching_3_checker.getAvgRelativeDistance(instance, batching_3_solver.getSolution()),batching_3_checker.getSolutionBenefit(instance, batching_3_solver.getSolution())});
    }

    exportToCSV(results, "results.csv");
    return 0;
}