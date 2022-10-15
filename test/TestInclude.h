#pragma once

#include <iostream>
#include <ios>
#include "math/math.h"

// output

template<typename T>
inline void outputSingle(T t) {
    std::cout << t;
}

void output() {}

template<typename T, typename...U>
void output(T t, U...args) {
    outputSingle(t);
    output(args...);
}

// epsilon equal

inline bool testEpsilonEqual(gmq::Float f1, gmq::Float f2, gmq::Float epsilon) {
    return std::abs(f1 - f2) < epsilon;
}

inline bool testEpsilonEqual(const gmq::Vec3 &v1, const gmq::Vec3 &v2, gmq::Float epsilon) {
    return std::abs(v1.x - v2.x) < epsilon && std::abs(v1.y - v2.y) < epsilon && std::abs(v1.z - v2.z) < epsilon;
}

inline bool testEpsilonEqual(const gmq::Vec4 &v1, const gmq::Vec4 &v2, gmq::Float epsilon) {
    return std::abs(v1.w - v2.w) < epsilon
        && std::abs(v1.x - v2.x) < epsilon
        && std::abs(v1.y - v2.y) < epsilon
        && std::abs(v1.z - v2.z) < epsilon;
}

// checking

#define CHECK(expr) if(!(expr)) { \
    output("Error while checking `"#expr"`\n"); \
    output("Line: ", __LINE__, ", File: \"", __FILE__, "\""); return 1; }
#define CHECK_EQU(expr1, expr2) if((expr1) != (expr2)) { \
    output("ERROR: Expression `"#expr1"` and `"#expr2"` are not equal!\n"); \
    output("LHS: ", expr1, "; RHS: ", expr2, "\n"); \
    output("Line: ", __LINE__, ", File: \"", __FILE__, "\""); return 1; }
#define CHECK_EPSILON_EQU(expr1, expr2, epsilon) if(!testEpsilonEqual((expr1), (expr2), (epsilon))) { \
    output("ERROR: Expression `"#expr1"` and `"#expr2"` are not epsilon equal!\n"); \
    output("LHS: ", expr1, "; RHS: ", expr2, "; epsilon: ", epsilon, "\n"); \
    output("Line: ", __LINE__, ", File: \"", __FILE__, "\""); return 1; }
