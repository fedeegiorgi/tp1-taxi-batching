#include "taxi_assignment_instance.h"
#include "taxi_assignment_solution.h"
#include "checker.h"
#include "greedy_solver.h"
#include "taxi_assignment_batching_solver.h"


int main(int argc, char** argv) {

    std::string filename = "input/xl_3.csv";

    TaxiAssignmentInstance instance(filename);
    std::cout << filename << std::endl;

    GreedySolver solver(instance);

    solver.solve();

    std::cout << solver.getSolution() << std::endl;
    std::cout << solver.getSolutionTime() << std::endl;
    std::cout << solver.getObjectiveValue() << std::endl;

    std::cout << "" << std::endl;

    BatchingSolver solver_2(instance);

    solver_2.solve();

    std::cout << solver_2.getSolution() << std::endl;
    std::cout << solver_2.getObjectiveValue() / 10.0 << std::endl;
    std::cout << solver_2.getSolutionTime() << std::endl;

    return 0;
}