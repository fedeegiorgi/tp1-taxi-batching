#include "taxi_assignment_instance.h"
#include "taxi_assignment_solution.h"
#include "checker.h"
#include "greedy_solver.h"
#include "taxi_assignment_batching_solver.h"
#include "batching_solver_v2.h"

#include <iostream>
#include <fstream>
#include <vector>

struct Result {
    int n;
    double greedy_obj_val;
    double greedy_time;
    double greedy_solution_cost;
    double batching_obj_val;
    double batching_time;
    double batching_solution_cost;
    double batching_2_obj_val;
    double batching_2_time;
    double batching_2_solution_cost;
};

void exportToCSV(const std::vector<Result>& results, const std::string& filename) {
    std::ofstream file(filename);

    // Check if the file was opened successfully
    if (!file) {
        std::cerr << "Error abriendo el archivo." << std::endl;
        return;
    }

    // Write the column headers to the file
    file << "n,greedy_obj_val,greedy_time,greedy_solution_cost,batching_obj_val,batching_time,batching_solution_cost,batching_2_obj_val,batching_2_time,batching_2_solution_cost\n";

    // Write the results to the file
    for (const auto& result : results) {
        file << result.n << "," << result.greedy_obj_val << "," << result.greedy_time << "," << result.greedy_solution_cost << ","
             << result.batching_obj_val << "," << result.batching_time << "," << result.batching_solution_cost << ","
             << result.batching_2_obj_val << "," << result.batching_2_time << "," << result.batching_2_solution_cost << "\n";
    }

    // Close the file
    file.close();

    std::cout << "Los resultados fueron exportados a " << filename << " satisfactoriamente." << std::endl;
}

int main(int argc, char** argv) {

    std::vector<Result> results;

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

        results.push_back({instance.n, greedy_solver.getObjectiveValue(), greedy_solver.getSolutionTime(), greedy_checker.getSolutionCost(instance, greedy_solver.getSolution()), batching_solver.getObjectiveValue(), batching_solver.getSolutionTime(), batching_checker.getSolutionCost(instance, batching_solver.getSolution()), batching_2_solver.getObjectiveValue(), batching_2_solver.getSolutionTime(), batching_2_checker.getSolutionCost(instance, batching_2_solver.getSolution())});
    }

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

        results.push_back({instance.n, greedy_solver.getObjectiveValue(), greedy_solver.getSolutionTime(), greedy_checker.getSolutionCost(instance, greedy_solver.getSolution()), batching_solver.getObjectiveValue(), batching_solver.getSolutionTime(), batching_checker.getSolutionCost(instance, batching_solver.getSolution()), batching_2_solver.getObjectiveValue(), batching_2_solver.getSolutionTime(), batching_2_checker.getSolutionCost(instance, batching_2_solver.getSolution())});
    }

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

        results.push_back({instance.n, greedy_solver.getObjectiveValue(), greedy_solver.getSolutionTime(), greedy_checker.getSolutionCost(instance, greedy_solver.getSolution()), batching_solver.getObjectiveValue(), batching_solver.getSolutionTime(), batching_checker.getSolutionCost(instance, batching_solver.getSolution()), batching_2_solver.getObjectiveValue(), batching_2_solver.getSolutionTime(), batching_2_checker.getSolutionCost(instance, batching_2_solver.getSolution())});
    }

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

        results.push_back({instance.n, greedy_solver.getObjectiveValue(), greedy_solver.getSolutionTime(), greedy_checker.getSolutionCost(instance, greedy_solver.getSolution()), batching_solver.getObjectiveValue(), batching_solver.getSolutionTime(), batching_checker.getSolutionCost(instance, batching_solver.getSolution()), batching_2_solver.getObjectiveValue(), batching_2_solver.getSolutionTime(), batching_2_checker.getSolutionCost(instance, batching_2_solver.getSolution())});
    }

    exportToCSV(results, "results.csv");

    // std::string filename = "input/small_1.csv";

    // TaxiAssignmentInstance instance(filename);
    // std::cout << filename << std::endl;

    // GreedySolver greedy_solver(instance);
    // TaxiAssignmentChecker greedy_checker;

    // greedy_solver.solve();

    // std::cout << greedy_solver.getSolution() << std::endl;
    // std::cout << greedy_solver.getSolutionTime() << std::endl;
    // std::cout << greedy_solver.getObjectiveValue() << std::endl;
    // std::cout << greedy_checker.getSolutionCost(instance, greedy_solver.getSolution()) << std::endl;

    // std::cout << "" << std::endl;

    // BatchingSolver batching_solver(instance);
    // TaxiAssignmentChecker batching_checker;

    // batching_solver.solve();

    // std::cout << batching_solver.getSolution() << std::endl;
    // std::cout << batching_solver.getObjectiveValue() / 10.0 << std::endl;
    // std::cout << batching_solver.getSolutionTime() << std::endl;
    // std::cout << batching_checker.getSolutionCost(instance, batching_solver.getSolution()) << std::endl;

    // std::cout << "" << std::endl;

    // BatchingSolver_v2 batching_2_solver(instance);
    // TaxiAssignmentChecker batching_2_checker;

    // batching_2_solver.solve();

    // std::cout << batching_2_solver.getSolution() << std::endl;
    // std::cout << batching_2_solver.getObjectiveValue() / 10.0 << std::endl;
    // std::cout << batching_2_solver.getSolutionTime() << std::endl;
    // std::cout << batching_2_checker.getSolutionCost(instance, batching_2_solver.getSolution()) << std::endl;

    return 0;
}