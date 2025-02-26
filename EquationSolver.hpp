#ifndef EQUATIONSOLVER_HPP
#define EQUATIONSOLVER_HPP

#include <unordered_map>
#include <iostream>

using namespace std;
class EquationSolver {
private:
    int DegreeOfEquation;
    std::unordered_map<int, double> coefficientPowerPair;

    void printPolynomialDegree();
    void firstDegreeSolver();
    void secondDegreeSolver();
    void polyEquationSolver();
    double squareRoot(double &val);
    void printReducedForm();

public:

    EquationSolver(const std::unordered_map<int, double>& coefficientPowerPair);
    void execute();

};;

#endif