#include "EquationParser.hpp"


EquationParser::EquationParser() {}

unordered_map<int, double> EquationParser::execute(const string &equation) {

    string leftSide, rightSide;

    this->trimEquation(equation, leftSide, rightSide);
    leftSide = (leftSide[0] == '-') ? "0" + leftSide : leftSide;
    rightSide = (rightSide[0] == '-') ? "0" + rightSide : rightSide;
    this->sideParsing(rightSide, TRUE_SIDE);
    this->sideParsing(leftSide, FALSE_SIDE);

    return (this->coefficientPowerPair);
}


double EquationParser::returnedExpressionSign(string &expression, bool &isRight) {

    expression = trimmer(expression);
    if (expression.empty())
        return 0.0;

    double doubleSign = 1.0;
    if (expression[0] == '-') {
        doubleSign = -1.0;
        expression = trimmer(expression.substr(1));
    }
    doubleSign = isRight ? -doubleSign : doubleSign;
    return (doubleSign);

}



pair<int, double> EquationParser::getExpressionValues(vector<string> &elements, double &sign) {

    pair<int, double> powerCoefficient(0, stod(this->trimmer(elements[0])) * sign);

    if (elements.size() > 1) {
        string el = trimmer(elements[1]);
        if (el.substr(0, 2) == "X^") {
            powerCoefficient.first = stoi(el.substr(2));
        }
    }

    return (powerCoefficient);
}

void EquationParser::expressionParser(string &expression, bool &isRight) {

    double sign = this->returnedExpressionSign(expression, isRight);
    vector<string> elements = this->splitByDelimiter(expression, MULTIPLY);
    if (elements.empty())
        return;
    pair<int, double> powerCoefficient = this->getExpressionValues(elements, sign);
    this->coefficientPowerPair[powerCoefficient.first] += powerCoefficient.second;
    
}

void EquationParser::sideParsing(const string &equation, bool isRight) {

    vector<string> expressions = this->splitByDelimiter(equation, PLUS);
    for (string expression: expressions) {
        vector<string> expressionPartsArray = this->splitByDelimiter(expression, MINUS);
        for (size_t i = 0; i < expressionPartsArray.size(); i++) {
            string singleExpressionPart = expressionPartsArray[i];
            if (singleExpressionPart.empty())
                continue;
            if (i > 0)
                singleExpressionPart = "-" + singleExpressionPart;
            this->expressionParser(singleExpressionPart, isRight);
        }
    }

}

vector<string> EquationParser::splitByDelimiter(const string& expr, char delim) {

    vector<string> partsArray;
    stringstream strings(expr);
    string part;
    
    while (getline(strings, part, delim)) {
        partsArray.push_back(part);
    }
    return partsArray;
}

string EquationParser::trimmer(const string& s) {

    size_t pos = s.find_first_not_of(" \t\n\r\f\v");
    if (pos == string::npos)
        return "";
    size_t end = s.find_last_not_of(" \t\n\r\f\v");

    return s.substr(pos, end - pos + 1);

}

void EquationParser::trimEquation(const string &equation, string &leftSide, string &rightSide) {

    size_t pos = equation.find(EQUAL);
    if (pos == string::npos)
        throw invalid_argument("Invalid argument: Equation should have an equal sign");

    leftSide =  trimmer(equation.substr(0, pos));
    rightSide = trimmer(equation.substr(pos + 1));
}