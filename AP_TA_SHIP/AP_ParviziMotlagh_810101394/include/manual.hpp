#ifndef MANUAL_HPP
#define MANUAL_HPP

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <memory>
#include <regex>
#include <algorithm>

using namespace std;

typedef bool (*condition)(int);

const char MANDATORY = '+';
const char OPTIONAL = '?';
const char OR = '|';
const char XOR = '^';
const string MANDATORY_STRING = "+";
const string OPTIONAL_STRING = "?";
const string OR_STRING = "|";
const string XOR_STRING = "^";
const string EQUAL_STRING = "=";
const string END_TREE = "#";
const string END_CONFIGURATION = "##";
const string END_INPUT = "###";
const string DONE = "+++";
const string VALID = "Valid";
const string INVALID = "Invalid";
const string WHITESPACE_CHARS = " \t";
const string FEATURE_REGEX = "\\w+";
const string ADD_SPACE_PATTERN = " $1 ";
const int ZERO_LEVEL = 0;
const int START_OPTIONAL_INDEX = 0;
const int END_OPTIONAL_INDEX = 1;
const int ROOT_INDEX = 0;
const regex ADD_SPACES_AROUND_OPERATORS("([=+|^])");
const string SPACED_OPERATOR_REPLACEMENT = " $1 ";
const regex REMOVE_SPACES_AFTER_QUESTION_MARK("\\?\\s*(\\w+)");
const string QUESTION_MARK_WITH_WORD_REPLACEMENT = "?$1";
const regex CONSOLIDATE_WHITESPACE("\\s+");
const string CONSOLIDATED_SPACE_REPLACEMENT = " ";
const map<int, char> operators = { {0, MANDATORY}, {1, OPTIONAL}, {2, XOR}, {3, OR}};

#endif