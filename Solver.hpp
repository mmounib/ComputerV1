#ifndef Solver_HPP
#define Solver_HPP

#include <unordered_map>
#include <iostream>

using namespace std;
class Solver {
private:
    int DegreeOfEquation;
    std::unordered_map<int, double> coefficientPowerPair;

    void printPolynomialDegree();
    void firstDegreeSolver();
    void secondDegreeSolver();
    void polySolver();
    double squareRoot(double &val);
    void printReducedForm();

public:

    Solver(const std::unordered_map<int, double>& coefficientPowerPair);
    void execute();

};;

#endif