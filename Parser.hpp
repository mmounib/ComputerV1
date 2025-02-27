
#ifndef Parser_H
#define Parser_H

#include <string>
#include <unordered_map>
#include <map>
#include <sstream>
#include <iostream>
#include <vector>
#define PLUS '+'
#define MINUS '-'
#define MULTIPLY '*'
#define DIVIDE '/'
#define EQUAL '='
#define TRUE_SIDE true
#define FALSE_SIDE false

using namespace std;
class Parser {

    public:

        Parser();
        unordered_map<int, double> execute(const string &equation);

    private:

        unordered_map<int, double> coefficientPowerPair;
        void trimEquation(const string &equation, string &leftSide, string &rightSide);
        vector<string> splitByDelimiter(const string& expr, char delim);
        void expressionParser(string &expression, bool &isRight);
        void sideParsing(const string &equation, bool isRight);
        string trimmer(const string& s);
        void rightSideParsing(const string &rightSide);
        double returnedExpressionSign(string &expression, bool &isRight);
        pair<int, double> getExpressionValues(vector<string> &elements, double &sign);

};

#endif 