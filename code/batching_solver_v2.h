#ifndef BATCHING_SOLVER_V2_H
#define BATCHING_SOLVER_V2_H

#include <cstdint>
#include <vector>
#include <iostream>
#include "taxi_assignment_instance.h"
#include "taxi_assignment_solution.h"
#include "ortools/graph/min_cost_flow.h"


class BatchingSolver_v2
{
	public:
        BatchingSolver_v2();
        BatchingSolver_v2(TaxiAssignmentInstance &instance);

        void setInstance(TaxiAssignmentInstance &instance);
        void solve();

        double getObjectiveValue() const;
        TaxiAssignmentSolution getSolution() const;
        int getSolutionStatus() const;
        double getSolutionTime() const;

        // Para debuggear
        void printVector(const std::vector<int64_t>& vec);
        
	private:
        // Estructuras de datos para el grafo
        std::vector<int64_t> _start_nodes;
        std::vector<int64_t> _end_nodes;
        std::vector<int64_t> _capacities;
        std::vector<int64_t> _unit_costs;
        std::vector<int64_t> _supplies;
        int64_t _source;
        int64_t _sink;
        
        // Interfaz para la solucion del problema costo mínimo flujo máximo
        void _create_network(TaxiAssignmentInstance &instance);
        operations_research::SimpleMinCostFlow _min_cost_flow;
        
        // Métodos para la conformación del grafo para la solución
        std::vector<int64_t> _set_start_nodes(int n);
        std::vector<int64_t> _set_end_nodes(int n);
        std::vector<int64_t> _set_capacities(int n);
        std::vector<int64_t> _set_costs(std::vector<std::vector<double>> matrix, int n);
        std::vector<int64_t> _set_supplies(int n);

        // Instance, problem and results attributes
        TaxiAssignmentInstance _instance;
        TaxiAssignmentSolution _solution;
        double _objective_value;
        int _solution_status;
        double _solution_time;

};

#endif