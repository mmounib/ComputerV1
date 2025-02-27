#include "Parser.hpp"

// Constructor for the Parser class
Parser::Parser() {}

// Main function to parse and process the equation
unordered_map<int, double> Parser::execute(const string &equation) {
    string leftSide, rightSide;
    
    // Split equation into left and right sides at '='
    this->trimEquation(equation, leftSide, rightSide);
    
    // Ensure both sides start with a number
    leftSide = (leftSide[0] == '-') ? "0" + leftSide : leftSide;
    rightSide = (rightSide[0] == '-') ? "0" + rightSide : rightSide;
    
    // Process right side (values moved to the left by negating)
    this->sideParsing(rightSide, TRUE_SIDE);
    // Process left side
    this->sideParsing(leftSide, FALSE_SIDE);

    return this->coefficientPowerPair;
}

// Determines the sign of the expression based on its position (left or right side)
double Parser::returnedExpressionSign(string &expression, bool &isRight) {
    expression = trimmer(expression); // Remove whitespace
    if (expression.empty())
        return 0.0;

    double sign = 1.0;
    if (expression[0] == '-') { // If expression starts with '-', invert sign
        sign = -1.0;
        expression = trimmer(expression.substr(1));
    }
    
    // If it's on the right side, negate the sign
    return isRight ? -sign : sign;
}

// Extracts coefficient and exponent values from an expression
pair<int, double> Parser::getExpressionValues(vector<string> &elements, double &sign) {
    // Convert first element to coefficient, apply sign
    pair<int, double> powerCoefficient(0, stod(trimmer(elements[0])) * sign);
    
    // Check if there is a power term (e.g., X^2)
    if (elements.size() > 1) {
        string el = trimmer(elements[1]);
        if (el.substr(0, 2) == "X^") {
            powerCoefficient.first = stoi(el.substr(2)); // Extract exponent value
        }
    }
    return powerCoefficient;
}

// Parses a single term in the equation
void Parser::expressionParser(string &expression, bool &isRight) {
    double sign = this->returnedExpressionSign(expression, isRight);
    
    // Split by '*' to handle cases like "3*X^2"
    vector<string> elements = this->splitByDelimiter(expression, MULTIPLY);
    if (elements.empty()) return;
    
    // Extract power and coefficient
    pair<int, double> powerCoefficient = this->getExpressionValues(elements, sign);
    
    // Store result in the map (accumulate if the same exponent appears multiple times)
    this->coefficientPowerPair[powerCoefficient.first] += powerCoefficient.second;
}

// Parses one side of the equation (left or right)
void Parser::sideParsing(const string &equation, bool isRight) {
    // Split by '+' first
    vector<string> expressions = this->splitByDelimiter(equation, PLUS);
    
    for (string expression : expressions) {
        // Split by '-' to handle negative terms
        vector<string> expressionPartsArray = this->splitByDelimiter(expression, MINUS);
        
        for (size_t i = 0; i < expressionPartsArray.size(); i++) {
            string singleExpressionPart = expressionPartsArray[i];
            if (singleExpressionPart.empty()) continue;
            
            // If term follows a '-', prepend a '-'
            if (i > 0) singleExpressionPart = "-" + singleExpressionPart;
            
            // Parse the individual term
            this->expressionParser(singleExpressionPart, isRight);
        }
    }
}

// Splits a string by a given delimiter
vector<string> Parser::splitByDelimiter(const string& expr, char delim) {
    vector<string> partsArray;
    stringstream strings(expr);
    string part;
    
    while (getline(strings, part, delim)) {
        partsArray.push_back(part);
    }
    return partsArray;
}

// Removes leading and trailing whitespace from a string
string Parser::trimmer(const string& s) {
    size_t pos = s.find_first_not_of(" \t\n\r\f\v");
    if (pos == string::npos) return "";
    size_t end = s.find_last_not_of(" \t\n\r\f\v");
    return s.substr(pos, end - pos + 1);
}

// Splits the equation into left and right sides at '='
void Parser::trimEquation(const string &equation, string &leftSide, string &rightSide) {
    size_t pos = equation.find(EQUAL);
    if (pos == string::npos)
        throw invalid_argument("Invalid argument: Equation should have an equal sign");
    
    leftSide = trimmer(equation.substr(0, pos));
    rightSide = trimmer(equation.substr(pos + 1));
}
