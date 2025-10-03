#include <iostream>
#include "satsolver.h"

void print_model(const std::vector<LitState>& model) {
    std::cout << "SAT Model: ";
    for (size_t i = 1; i < model.size(); ++i) {
        if (model[i] == LitState::TRUE) {
            std::cout << i << " ";
        } else {
            std::cout << "-" << i << " ";
        }
    }
    std::cout << std::endl;
}

int main() {
    SatSolver solver;

    // Example problem in CNF: (x1 v -x2 v x3) AND (-x1 v x2)
    // Variables are 1, 2, 3. Negation is -.
    solver.add_clause({1, -2, 3});
    solver.add_clause({-1, 2});
    
    bool result = solver.solve();

    if (result) {
        std::cout << "Result: SATISFIABLE" << std::endl;
        print_model(solver.get_model());
    } else {
        std::cout << "Result: UNSATISFIABLE" << std::endl;
    }

    return 0;
}