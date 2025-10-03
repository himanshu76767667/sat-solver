#ifndef SATSOLVER_H
#define SATSOLVER_H

#include <vector>
#include <iostream>

// Represents the state of a literal
enum class LitState { TRUE, FALSE, UNASSIGNED };

class SatSolver {
public:
    // Constructor
    SatSolver();

    // Adds a clause to the formula. Variables are represented as integers (e.g., 1 for x1, -1 for not x1).
    void add_clause(const std::vector<int>& clause);

    // Main function to solve the SAT problem.
    bool solve();

    // Returns the satisfying model if the formula is SAT.
    const std::vector<LitState>& get_model() const;

private:
    // --- Core Data Structures ---
    int num_vars;
    std::vector<std::vector<int>> clauses;
    std::vector<LitState> assignments;

    // --- CDCL & Optimization Data Structures ---
    std::vector<std::vector<int>> watch_lists; // For two-watched-literals
    std::vector<int> decision_level;            // Tracks the level of each assignment
    std::vector<int> antecedent;                // Stores the clause that implied an assignment (for conflict analysis)

    // --- Private Helper Methods ---

    // Initializes solver state before solving.
    void initialize();
    
    // Core DPLL/CDCL loop logic.
    bool search();

    // Implements unit propagation, using the two-watched-literals scheme.
    // Returns the index of a conflicting clause, or -1 if no conflict.
    int unit_propagation();

    // Selects the next variable to branch on using an adaptive heuristic (e.g., VSIDS).
    int pick_branching_variable();

    // Analyzes a conflict to produce a learned clause and determine the backtrack level.
    // This is the heart of Conflict-Driven Clause Learning (CDCL).
    std::vector<int> analyze_conflict(int conflict_clause_idx);
    
    // Performs non-chronological backtracking to a specified decision level.
    void backtrack(int level);
};

#endif // SATSOLVER_H