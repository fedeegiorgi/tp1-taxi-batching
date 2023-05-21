#include "taxi_assignment_batching_solver.h"


BatchingSolver::BatchingSolver() {}

BatchingSolver::BatchingSolver(TaxiAssignmentInstance &instance) {
    this->_instance = instance;
    this->_objective_value = 0;
    this->_solution_status = 0;
    this->_solution_time = 0;

    this->_start_nodes = set_start_nodes(instance.n);
    this->_end_nodes = set_end_nodes(instance.n);
    this->_capacities = set_capacities(instance.n);
    this->_unit_costs = set_costs(instance.dist, instance.n);

    this->_source = 0;
    this->_sink = 2 * n + 1;
    this->_supplies = set_supplies(instance.n);
}

void BatchingSolver::setInstance(TaxiAssignmentInstance &instance) {
    this->_instance = instance;
}

void BatchingSolver::solve() {
    // Instantiate a SimpleMinCostFlow solver.
    SimpleMinCostFlow min_cost_flow;

    // Add each arc.
    for (int i = 0; i < this->_start_nodes.size(); ++i) {
        int arc = min_cost_flow.AddArcWithCapacityAndUnitCost(this->_start_nodes[i], this->_end_nodes[i], this->_capacities[i], this->_unit_costs[i]);
    }

    // Add node supplies.
    for (int i = 0; i < this->_supplies.size(); ++i) {
        min_cost_flow.SetNodeSupply(i, this->_supplies[i]);
    }

    this->_objective_value = min_cost_flow.OptimalCost();
    this->_solution_status = min_cost_flow.Solve();
}

double BatchingSolver::getObjectiveValue() const {
    return this->_objective_value;
}

TaxiAssignmentSolution BatchingSolver::getSolution() const {
    return this->_solution;
}

int BatchingSolver::getSolutionStatus() const {
    return this->_solution_status;
}

double BatchingSolver::getSolutionTime() const {
    return this->_solution_time;
}

std::vector<int> set_start_nodes(int n) const {
    std::vector<int> ret;
    
    // seteo 0s para arcos de source a taxis
    for (int i = 0; i < n; i++) {
        ret.push_back(0);
    }

    // seteo start nodes de cada taxi a cada pax
    for (int i = 1; i < n+1; i++) {
        for (int j = 0; j < n; j++) {
            ret.push_back(i);
        }
    }

    // seteo start nodes 
    for (int i = n+1; i < 2*n+1) {
        ret.push_back(i);
    }

    return ret;
}

std::vector<int> set_end_nodes(int n) const {
    std::vector<int> ret = {}

    for(i = 1; i < n+1; i++){
        ret.push_back(i);
    }

    for(i = n+1; i < 2n+1; i++){
        for(j = 0; j < n; j++)
            ret.push_back(i);
    }

    for(i = 0; i < n; i++){
        ret.push_back(21);
    }

    return ret;

}

std::vector<int> set_capacities(int n) const {
    std::vector<int> ret = {}

    for (i=0; i < 2n+n*n; i++){
        ret.push_back(1);
    }

    return ret;
}

std::vector<double> set_costs(std::vector<std::vector<double>> matrix, int n) const {
    std::vector<double> flattened = std::vector<double>(n, 0);
    for (int fila = 0; fila < n; fila++){
        int index = 0;
        for (index; index < n; index++){
            flattened.push_back(matrix[fila][index]);
        }
    }
    for (int j = 0; j < n; j++){
        flattened.push_back(0);
    }
    return flattened;
}

std::vector<int> set_supplies(int n){
    std::vector<int> supplies = std::vector<int>((n+2), 0);
    supplies[0] = n;
    supplies[n+1] = -n;
    return supplies;
}