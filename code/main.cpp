#include "taxi_assignment_instance.h"
#include "taxi_assignment_solution.h"
#include "checker.h"
#include "greedy_solver.h"
#include "taxi_assignment_batching_solver.h"

#include <iostream>
#include <fstream>
#include <vector>

struct Result {
    int n;
    double greedy_obj_val;
    double greedy_time;
    double batching_obj_val;
    double batching_time;
};

void exportToCSV(const std::vector<Result>& results, const std::string& filename) {
    std::ofstream file(filename);

    // Check if the file was opened successfully
    if (!file) {
        std::cerr << "Error opening the file." << std::endl;
        return;
    }

    // Write the column headers to the file
    file << "n,greedy_obj_val,greedy_time,batching_obj_val,batching_time\n";

    // Write the results to the file
    for (const auto& result : results) {
        file << result.n << "," << result.greedy_obj_val << "," << result.greedy_time << ","
             << result.batching_obj_val << "," << result.batching_time << "\n";
    }

    // Close the file
    file.close();

    std::cout << "Results exported to " << filename << " successfully." << std::endl;
}

int main(int argc, char** argv) {

    std::vector<Result> results;

    for (int i = 0; i < 10; i++) {
        std::string filename = "input/small_" + std::to_string(i) + ".csv";
        TaxiAssignmentInstance instance(filename);

        GreedySolver solver(instance);
        solver.solve();

        BatchingSolver solver_2(instance);
        solver_2.solve();

        results.push_back({instance.n, solver.getObjectiveValue(), solver.getSolutionTime(), solver_2.getObjectiveValue(), solver_2.getSolutionTime()});
    }

    for (int i = 0; i < 10; i++) {
        std::string filename = "input/medium_" + std::to_string(i) + ".csv";
        TaxiAssignmentInstance instance(filename);

        GreedySolver solver(instance);
        solver.solve();

        BatchingSolver solver_2(instance);
        solver_2.solve();

        results.push_back({instance.n, solver.getObjectiveValue(), solver.getSolutionTime(), solver_2.getObjectiveValue(), solver_2.getSolutionTime()});
    }

    for (int i = 0; i < 10; i++) {
        std::string filename = "input/large_" + std::to_string(i) + ".csv";
        TaxiAssignmentInstance instance(filename);

        GreedySolver solver(instance);
        solver.solve();

        BatchingSolver solver_2(instance);
        solver_2.solve();

        results.push_back({instance.n, solver.getObjectiveValue(), solver.getSolutionTime(), solver_2.getObjectiveValue(), solver_2.getSolutionTime()});
    }

        for (int i = 0; i < 10; i++) {
        std::string filename = "input/xl_" + std::to_string(i) + ".csv";
        TaxiAssignmentInstance instance(filename);

        GreedySolver solver(instance);
        solver.solve();

        BatchingSolver solver_2(instance);
        solver_2.solve();

        results.push_back({instance.n, solver.getObjectiveValue(), solver.getSolutionTime(), solver_2.getObjectiveValue(), solver_2.getSolutionTime()});
    }

    exportToCSV(results, "results.csv");

    // std::string filename = "input/xl_3.csv";

    // TaxiAssignmentInstance instance(filename);
    // std::cout << filename << std::endl;

    // GreedySolver solver(instance);

    // solver.solve();

    // std::cout << solver.getSolution() << std::endl;
    // std::cout << solver.getSolutionTime() << std::endl;
    // std::cout << solver.getObjectiveValue() << std::endl;

    // std::cout << "" << std::endl;

    // BatchingSolver solver_2(instance);

    // solver_2.solve();

    // std::cout << solver_2.getSolution() << std::endl;
    // std::cout << solver_2.getObjectiveValue() / 10.0 << std::endl;
    // std::cout << solver_2.getSolutionTime() << std::endl;

    return 0;
}