#include "batching_solver_v2.h"

BatchingSolver_v2::BatchingSolver_v2() {}

BatchingSolver_v2::BatchingSolver_v2(TaxiAssignmentInstance &instance) {
    this->_instance = instance;
    this->_objective_value = 0;
    this->_solution_status = 0;
    this->_solution_time = 0;
    this->_solution = TaxiAssignmentSolution(this->_instance.n);

    _create_network(instance);
}

void BatchingSolver_v2::setInstance(TaxiAssignmentInstance &instance) {
    this->_instance = instance;
}

void BatchingSolver_v2::solve() {

    // Inicializamos timer.
    std::chrono::time_point<std::chrono::system_clock> start, end;
    start = std::chrono::system_clock::now();

    this->_solution_status = this->_min_cost_flow.Solve();
    this->_objective_value = this->_min_cost_flow.OptimalCost();
    
    if (this->_solution_status == operations_research::MinCostFlow::OPTIMAL) {
        for (std::size_t i = 0; i < this->_min_cost_flow.NumArcs(); ++i) {
            // Can ignore arcs leading out of source or into sink.
            if (this->_min_cost_flow.Tail(i) != this->_source && this->_min_cost_flow.Head(i) != this->_sink) {
                // Arcs in the solution have a flow value of 1. Their start and end
                // nodes give an assignment of worker to task.
                if (this->_min_cost_flow.Flow(i) > 0) {
                    this->_solution.assign(this->_min_cost_flow.Tail(i)-1, this->_min_cost_flow.Head(i) - this->_solution.getN()-1);
                }
            }
        }
    } else {
        LOG(INFO) << "Solving the min cost flow problem failed.";
        LOG(INFO) << "Solver status: " << this->_solution_status;
    }

    // Frenamos timer.
    end = std::chrono::system_clock::now();
    std::chrono::duration<double> duration = end - start;
    
    this->_solution_time = duration.count();

    // prints de chequeo

    // std::cout << this->_start_nodes.size() << std::endl;
    // std::cout << this->_end_nodes.size() << std::endl;
    // std::cout << this->_capacities.size() << std::endl;
    // std::cout << this->_unit_costs.size() << std::endl;

    // printVector(_start_nodes);
    // printVector(_end_nodes);
    // printVector(_capacities);
    // printVector(_unit_costs);
}

double BatchingSolver_v2::getObjectiveValue() const {
    return this->_objective_value;
}

TaxiAssignmentSolution BatchingSolver_v2::getSolution() const {
    return this->_solution;
}

int BatchingSolver_v2::getSolutionStatus() const {
    return this->_solution_status;
}

double BatchingSolver_v2::getSolutionTime() const {
    return this->_solution_time;
}

void BatchingSolver_v2::_create_network(TaxiAssignmentInstance &instance) {
    int n = instance.n;
    
    this->_start_nodes = _set_start_nodes(instance.n);
    this->_end_nodes = _set_end_nodes(instance.n);
    this->_capacities = _set_capacities(instance.n);
    this->_unit_costs = _set_costs(instance.dist, instance.n);

    this->_source = 0;
    this->_sink = 2 * instance.n + 1;
    this->_supplies = _set_supplies(instance.n);

    // Add each arc.
    for (int i = 0; i < this->_start_nodes.size(); ++i) {
        int arc = this->_min_cost_flow.AddArcWithCapacityAndUnitCost(this->_start_nodes[i], this->_end_nodes[i], this->_capacities[i], this->_unit_costs[i]);
    }

    // Add node supplies.
    for (int i = 0; i < this->_supplies.size(); ++i) {
        this->_min_cost_flow.SetNodeSupply(i, this->_supplies[i]);
    }
}

std::vector<int64_t> BatchingSolver_v2::_set_start_nodes(int n) {
    std::vector<int64_t> ret;
    
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
    for (int i = n+1; i < 2*n+1; i++) {
        ret.push_back(i);
    }

    return ret;
}

std::vector<int64_t> BatchingSolver_v2::_set_end_nodes(int n) {
    std::vector<int64_t> ret;

    for(int i = 1; i < n+1; i++){
        ret.push_back(i);
    }

    for(int i = n+1; i < 2*n+1; i++){
        for(int j = 0; j < n; j++)
            ret.push_back(n+1+j);
    }

    for(int i = 0; i < n; i++){
        ret.push_back(2*n+1);
    }

    return ret;
}

std::vector<int64_t> BatchingSolver_v2::_set_capacities(int n) {
    std::vector<int64_t> ret;

    for (int i = 0; i < (2*n+n*n); i++){
        ret.push_back(1);
    }

    return ret;
}

std::vector<int64_t> BatchingSolver_v2::_set_costs(std::vector<std::vector<double>> matrix, int n) {
    std::vector<int64_t> flattened = std::vector<int64_t>(n, 0);
    for (int fila = 0; fila < n; fila++){
        int index = 0;
        for (index; index < n; index++){
            int costo = (matrix[fila][index]*10 + this->_instance.pax_trip_dist[index]*10) / this->_instance.pax_tot_fare[index];
            flattened.push_back(costo);
        }
    }
    for (int j = 0; j < n; j++){
        flattened.push_back(0);
    }
    return flattened;
}

std::vector<int64_t> BatchingSolver_v2::_set_supplies(int n) {
    std::vector<int64_t> supplies = std::vector<int64_t>((2*n+2), 0);

    supplies[0] = n;
    supplies[2*n+1] = -n;

    return supplies;
}

// para debugging --------------------------------------------------------------------------------------
void BatchingSolver_v2::printVector(const std::vector<int64_t>& vec) {
    std::cout << "[";
    for (size_t i = 0; i < vec.size(); ++i) {
        std::cout << vec[i];
        if (i != vec.size() - 1) {
            std::cout << ", ";
        }
    }
    std::cout << "]" << std::endl;
}