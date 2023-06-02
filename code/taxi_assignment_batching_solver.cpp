#include "taxi_assignment_batching_solver.h"

BatchingSolver::BatchingSolver() {}

BatchingSolver::BatchingSolver(TaxiAssignmentInstance &instance) {
    this->_instance = instance;
    this->_objective_value = 0;
    this->_solution_status = 0;
    this->_solution_time = 0;
    this->_solution = TaxiAssignmentSolution(this->_instance.n);

    _create_network(instance);
}

void BatchingSolver::setInstance(TaxiAssignmentInstance &instance) {
    this->_instance = instance;
}

void BatchingSolver::solve() {

    // Inicializamos timer.
    std::chrono::time_point<std::chrono::high_resolution_clock> start, end;
    start = std::chrono::high_resolution_clock::now();

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
    end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    
    this->_solution_time = duration.count() * 1000;

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

void BatchingSolver::_create_network(TaxiAssignmentInstance &instance) {
    int n = instance.n;

    // Creamos los vectores que representan las conexiones entre nodos (arcos), sus capacidades y sus costos.
    this->_start_nodes = _set_start_nodes(instance.n);
    this->_end_nodes = _set_end_nodes(instance.n);
    this->_capacities = _set_capacities(instance.n);
    this->_unit_costs = _set_costs(instance.dist, instance.n);

    this->_source = 0; // Numeramos al nodo Source como 0.
    this->_sink = 2 * instance.n + 1; // Numeramos al nodo sink como 2n+1.
    this->_supplies = _set_supplies(instance.n); // Creamos el vector de imbalances.

    // Añadimos cada arco.
    for (int i = 0; i < this->_start_nodes.size(); ++i) {
        int arc = this->_min_cost_flow.AddArcWithCapacityAndUnitCost(this->_start_nodes[i], this->_end_nodes[i], this->_capacities[i], this->_unit_costs[i]);
    }

    // Añadimos los imbalances a los nodos.
    for (int i = 0; i < this->_supplies.size(); ++i) {
        this->_min_cost_flow.SetNodeSupply(i, this->_supplies[i]);
    }
}

std::vector<int64_t> BatchingSolver::_set_start_nodes(int n) {
    std::vector<int64_t> ret;
    
    // Seteamos 0s para arcos de source a taxis.
    for (int i = 0; i < n; i++) {
        ret.push_back(0);
    }

    // Seteamos start_nodes de cada taxi a cada pax, es decir, agregamos (n 1_s, n 2_s, ... n n_s).
    for (int64_t i = 1; i < n+1; i++) {
        for (int j = 0; j < n; j++) {
            ret.push_back(i);
        }
    }

    // Seteamos start_nodes de cada pax a sink t, es decir, una vez cada pasajero (n+1, n+2, ..., 2n).
    for (int64_t i = n+1; i < 2*n+1; i++) {
        ret.push_back(i);
    }

    return ret;
}

std::vector<int64_t> BatchingSolver::_set_end_nodes(int n) {
    std::vector<int64_t> ret;

    // Cerramos las conexiones de source a taxis, es decir, una vez cada taxi (1, 2, ..., n).
    for(int64_t i = 1; i < n+1; i++){
        ret.push_back(i);
    }

    // Cerramos las conexiones de los taxis a los pasajeros, es decir, agregamos n veces la secuencia (n+1, n+2, ..., 2n).
    for(int i = n+1; i < 2*n+1; i++){
        for(int64_t j = 0; j < n; j++)
            ret.push_back(n+1+j);
    }

    // Cerramos las conexiones de cada pasajero a sink, es decir, agregamos n veces 2n+1 (sink).
    for(int i = 0; i < n; i++){
        ret.push_back(2*n+1);
    }

    return ret;
}

std::vector<int64_t> BatchingSolver::_set_capacities(int n) {
    std::vector<int64_t> ret = std::vector<int64_t>((2*n+n*n), 1) 
    // Todas las capacidades son 1, inicializo un vector con 2n + n^2 (cantidad de arcos) unos.
    return ret;
}

std::vector<int64_t> BatchingSolver::_set_costs(std::vector<std::vector<double>> matrix, int n) {
    std::vector<int64_t> flattened = std::vector<int64_t>(n, 0); // Inicializo un vector con n ceros pues las conexiones de source a los taxis tienen costo 0.
    for (int fila = 0; fila < n; fila++){
        int index = 0;
        for (index; index < n; index++){
            flattened.push_back(int64_t(matrix[fila][index]*10)); // Multiplicación por 10 para que los costos sean enteros.
        }
    }
    // Agrego a ese vector todos los costos (dist_ij), aplanando la matriz y agregando al vector a medida que lo hago.

    for (int j = 0; j < n; j++){
        flattened.push_back(0);
    }
    // Agrego n ceros mas, pues las conexiones de los pasajeros a sink tienen costo 0.
    return flattened;
}

std::vector<int64_t> BatchingSolver::_set_supplies(int n) {
    std::vector<int64_t> supplies = std::vector<int64_t>((2*n+2), 0);
    // Inicializo un vector de todos 0s que representa los imbalances.
    supplies[0] = int64_t(n); // Al nodo source le asigno n como imbalance.
    supplies[2*n+1] = int64_t(-n); // Al nodo sink le asigno -n como imbalance.
    // Ver informe para entender el porque.
    return supplies;
}

// para debugging --------------------------------------------------------------------------------------
void BatchingSolver::printVector(const std::vector<int64_t>& vec) {
    std::cout << "[";
    for (size_t i = 0; i < vec.size(); ++i) {
        std::cout << vec[i];
        if (i != vec.size() - 1) {
            std::cout << ", ";
        }
    }
    std::cout << "]" << std::endl;
}