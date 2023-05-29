#include "taxi_assignment_instance.h"
#include "taxi_assignment_solution.h"
#include "checker.h"
#include "greedy_solver.h"
#include "taxi_assignment_batching_solver.h"
#include "batching_solver_v2.h"

#include <iostream>
#include <fstream>
#include <vector>

// ObjectiveValue para estrategia Greedy y Batching es la suma de la distancias para recoger a los pasajeros.
// ObjectiveValue para estrategia alternativa de Batching es las sumas de los ratios de la forma: (dist. recogida + dist. viaje) / tarifa total

// strategy_cost = suma de la distancias para recoger a los pasajeros.
// strategy_time = tiempo de ejecución de la asignación.
// strategy_benefit = promedio de los rendimientos económicos sobre distancia recorrida de los vehiculos.

struct Result {
    int n;
    double greedy_cost;
    double greedy_time;
    double greedy_benefit;
    double batching_cost;
    double batching_time;
    double batching_benefit;
    double alternative_cost;
    double alternative_time;
    double alternative_benefit;
};

void exportToCSV(const std::vector<Result>& results, const std::string& filename) {
    std::ofstream file(filename);

    // Chequeamos que el archivo se abra correctamente.
    if (!file) {
        std::cerr << "Error abriendo el archivo." << std::endl;
        return;
    }

    // Seteamos los headers para las columnas
    file << "n,greedy_cost,greedy_time,greedy_benefit,batching_cost,batching_time,batching_benefit,alternative_cost,alternative_time,alternative_benefit\n";

    // Escrimos el resultado para una asignación dada.
    for (const auto& result : results) {
        file << result.n << "," << result.greedy_cost << "," << result.greedy_time << "," << result.greedy_benefit << ","
             << result.batching_cost << "," << result.batching_time << "," << result.batching_benefit << ","
             << result.alternative_cost << "," << result.alternative_time << "," << result.alternative_benefit << "\n";
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

        results.push_back({instance.n, greedy_solver.getObjectiveValue(), greedy_solver.getSolutionTime(), greedy_checker.getSolutionBenefit(instance, greedy_solver.getSolution()), 
                           batching_solver.getObjectiveValue()/10.0, batching_solver.getSolutionTime(), batching_checker.getSolutionBenefit(instance, batching_solver.getSolution()), 
                           batching_2_checker.getSolutionCost(instance, batching_2_solver.getSolution()), batching_2_solver.getSolutionTime(), batching_2_checker.getSolutionBenefit(instance, batching_2_solver.getSolution())});
    }

    // obtención de los resultados para los tamaños de muestra n = 100.
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

        results.push_back({instance.n, greedy_solver.getObjectiveValue(), greedy_solver.getSolutionTime(), greedy_checker.getSolutionBenefit(instance, greedy_solver.getSolution()), 
                           batching_solver.getObjectiveValue()/10.0, batching_solver.getSolutionTime(), batching_checker.getSolutionBenefit(instance, batching_solver.getSolution()), 
                           batching_2_checker.getSolutionCost(instance, batching_2_solver.getSolution()), batching_2_solver.getSolutionTime(), batching_2_checker.getSolutionBenefit(instance, batching_2_solver.getSolution())});
    }

    // obtención de los resultados para los tamaños de muestra n = 250.
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

        results.push_back({instance.n, greedy_solver.getObjectiveValue(), greedy_solver.getSolutionTime(), greedy_checker.getSolutionBenefit(instance, greedy_solver.getSolution()), 
                           batching_solver.getObjectiveValue()/10.0, batching_solver.getSolutionTime(), batching_checker.getSolutionBenefit(instance, batching_solver.getSolution()), 
                           batching_2_checker.getSolutionCost(instance, batching_2_solver.getSolution()), batching_2_solver.getSolutionTime(), batching_2_checker.getSolutionBenefit(instance, batching_2_solver.getSolution())});
    }

    // obtención de los resultados para los tamaños de muestra n = 500.
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

        results.push_back({instance.n, greedy_solver.getObjectiveValue(), greedy_solver.getSolutionTime(), greedy_checker.getSolutionBenefit(instance, greedy_solver.getSolution()), 
                           batching_solver.getObjectiveValue()/10.0, batching_solver.getSolutionTime(), batching_checker.getSolutionBenefit(instance, batching_solver.getSolution()), 
                           batching_2_checker.getSolutionCost(instance, batching_2_solver.getSolution()), batching_2_solver.getSolutionTime(), batching_2_checker.getSolutionBenefit(instance, batching_2_solver.getSolution())});
    }

    exportToCSV(results, "results.csv");

    // ------------------------------------------------------------
    
    // Prints de prueba por archivo
    // La idea es imprimir para cada estrategia:
    // - Asignación
    // - Costo (suma de distancias de recogida) - valor objetivo en batching y Greedy
    // - Tiempo de ejecución de asignación
    // - Medida de beneficio (rendimiento de $ por km)

    // std::string filename = "input/small_1.csv";

    // TaxiAssignmentInstance instance(filename);
    // std::cout << filename << std::endl;

    // GreedySolver greedy_solver(instance);
    // TaxiAssignmentChecker greedy_checker;

    // greedy_solver.solve();

    // std::cout << greedy_solver.getSolution() << std::endl;
    // std::cout << greedy_solver.getObjectiveValue() << std::endl;
    // std::cout << greedy_checker.getSolutionCost(instance, greedy_solver.getSolution()) << std::endl;
    // std::cout << greedy_solver.getSolutionTime() << std::endl;
    // std::cout << greedy_checker.getSolutionBenefit(instance, greedy_solver.getSolution()) << std::endl;

    // std::cout << "" << std::endl;

    // BatchingSolver batching_solver(instance);
    // TaxiAssignmentChecker batching_checker;

    // batching_solver.solve();

    // std::cout << batching_solver.getSolution() << std::endl;
    // std::cout << batching_solver.getObjectiveValue() / 10.0 << std::endl;
    // std::cout << batching_checker.getSolutionCost(instance, batching_solver.getSolution()) << std::endl;
    // std::cout << batching_solver.getSolutionTime() << std::endl;
    // std::cout << batching_checker.getSolutionBenefit(instance, batching_solver.getSolution()) << std::endl;

    // std::cout << "" << std::endl;

    // BatchingSolver_v2 batching_2_solver(instance);
    // TaxiAssignmentChecker batching_2_checker;

    // batching_2_solver.solve();

    // std::cout << batching_2_solver.getSolution() << std::endl;
    // std::cout << batching_2_checker.getSolutionCost(instance, batching_2_solver.getSolution()) << std::endl;
    // std::cout << batching_2_solver.getSolutionTime() << std::endl;
    // std::cout << batching_2_checker.getSolutionBenefit(instance, batching_2_solver.getSolution()) << std::endl;

    return 0;
}