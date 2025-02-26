#include "EquationParser.hpp" 
#include "EquationSolver.hpp" 

int main(int argc, char* argv[]) {
    
    try {
        
        if (argc != 2)
            throw (invalid_argument("Invalid argument: There should be two arguments."));

        EquationParser Parser;
        string equation = argv[1];
        unordered_map<int, double> coefficientPowerPair = Parser.execute(equation);

        EquationSolver equationSolver(coefficientPowerPair);
        equationSolver.execute();

    }
    catch (exception &e) {
        cout << e.what() << endl;
    }
}