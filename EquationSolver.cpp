#include "EquationSolver.hpp"



EquationSolver::EquationSolver(const std::unordered_map<int, double>& coefficientPowerPair) : coefficientPowerPair(coefficientPowerPair) {

    this->DegreeOfEquation = 0;
    for (const auto& [key, value] : coefficientPowerPair) {
        if (key > this->DegreeOfEquation)
            this->DegreeOfEquation = key;
    }

}

void EquationSolver::execute() {
    
    this->printReducedForm();
    this->printPolynomialDegree();
    this->polyEquationSolver();

}

void EquationSolver::polyEquationSolver() {

    if (this->DegreeOfEquation == 0) {
        if (this->coefficientPowerPair[0] == 0)
            cout << "All real numbers are solutions." << endl;
        else
            cout << "No solution." << endl;
    }
    else if (this->DegreeOfEquation == 1)
        this->firstDegreeSolver();
    else if (this->DegreeOfEquation == 2)
        this->secondDegreeSolver();
    else
        throw invalid_argument("The polynomial degree is stricly greater than 2, I can't solve.");

}

void EquationSolver::printPolynomialDegree() {
    cout << "Polynomial degree: " << this->DegreeOfEquation << endl;
}

void EquationSolver::printReducedForm() {

    std::cout << "Reduced form: ";
    string sign;
    for (int i = 0; i <= this->DegreeOfEquation; i++) {
        if (i == 0) {
            if (this->coefficientPowerPair[i] < 0)
                sign = "-";
        }
        else {
            if (this->coefficientPowerPair[i] < 0)
                sign = " - ";
            else
                sign = " + ";
        }
        cout << sign << abs(coefficientPowerPair[i]) << " * X^" << i;
    }
    std::cout << " = 0" << std::endl;
}


void EquationSolver::firstDegreeSolver() {

    cout << "The solution is:" << endl;
    double equationSolution = (-1 * this->coefficientPowerPair[0]) / this->coefficientPowerPair[1];
    cout << equationSolution << endl;

}

double  EquationSolver::squareRoot(double &val) {
    if (val < 0)
        return (-1);
    double beg = 0, end = val, fl = 0.0000001, middle = (beg + end) / 2;

    while (end - beg > fl) {
        middle = (beg + end) / 2;
        if (middle * middle > val)
            end = middle;
        else if (middle * middle < val)
            beg = middle;
        else 
            return (middle);
    }

    return ((beg + end) / 2);
}

void EquationSolver::secondDegreeSolver() {

    double a = this->coefficientPowerPair[DegreeOfEquation];
    double b = this->coefficientPowerPair[DegreeOfEquation - 1];
    double c = this->coefficientPowerPair[DegreeOfEquation - 2];
    double discriminant = (b * b) - (4 * a * c);

    if (discriminant == 0) {
        cout << "The solution is: " << endl;
        double equationSolution = (-b) / (2 * a);
        cout << "One real root: X = " << equationSolution << endl;

    }
    else if (discriminant > 0) {
        double Solution_1 = (-b + this->squareRoot(discriminant)) / (2 * a);
        double Solution_2 = (-b - this->squareRoot(discriminant)) / (2 * a);

        cout << "Discriminant is strictly positive, the two solutions are: " << endl;
        cout << Solution_2 << endl;
        cout << Solution_1 << endl;
    }
    else {
        cout << "Discriminant is strictly negative, the two complex solutions are:" << endl;
        discriminant *= -1;
        cout << (b * -1) / (2 * a) << " - i * " << this->squareRoot(discriminant) / (2 * a) << endl;
        cout << (b * -1) / (2 * a) << " + i * " << this->squareRoot(discriminant) / (2 * a) << endl; 
    }
    
}
