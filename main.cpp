#include "Parser.hpp" 
#include "Solver.hpp" 

int main(int argc, char* argv[]) {
    
    try {
        
        if (argc != 2)
            throw (invalid_argument("Invalid argument: There should be two arguments."));

        Parser Parser;
        string equation = argv[1];
        unordered_map<int, double> coefficientPowerPair = Parser.execute(equation);

        Solver Solver(coefficientPowerPair);
        Solver.execute();

    }
    catch (exception &e) {
        cout << e.what() << endl;
    }
}