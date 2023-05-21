#ifndef TAXI_ASSIGNMENT_BATCHING_SOLVER_H
#define TAXI_ASSIGNMENT_BATCHING_SOLVER_H

#include <cstdint>
#include <vector>
#include <iostream>
#include "taxi_assignment_instance.h"
#include "taxi_assignment_solution.h"
#include "ortools/graph/min_cost_flow.h"


class BatchingSolver
{
	public:
        BatchingSolver();
        BatchingSolver(TaxiAssignmentInstance &instance);

        void setInstance(TaxiAssignmentInstance &instance);
        void solve();

        double getObjectiveValue() const;
        TaxiAssignmentSolution getSolution() const;
        int getSolutionStatus() const;
        double getSolutionTime() const;
        
        
	
	private:
        // Completar con lo que sea necesario.
        std::vector<int> _start_nodes;
        std::vector<int> _end_nodes;
        std::vector<int> _capacities;
        std::vector<int> _unit_costs;
        int _source;
        int _sink;
        std::vector<int> _supplies;

        std::vector<int> set_start_nodes(int n) const;
        std::vector<int> set_end_nodes(int n) const;
        std::vector<int> set_capacities(int n);
        std::vector<int> set_costs(std::vector<std::vector<double>> matrix, int n) const;

        // Instance, problem and results attributes
        TaxiAssignmentInstance _instance;
        TaxiAssignmentSolution _solution;
        double _objective_value;
        int _solution_status;
        double _solution_time;

};

#endif