#pragma once
#include <igl/all.h>
#include <unvpp/unvpp.h>

class Solver
{
public:
    Solver() {}
    ~Solver() {}

    // Constant displacements filled with 1s for constant and 0s for unknown
    virtual void solve(const unvpp::Mesh& mesh, Eigen::Matrix<double, Eigen::Dynamic, 1> F, Eigen::Matrix<double, Eigen::Dynamic, 1> constand_displacements) = 0;
};