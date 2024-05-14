#pragma once
#include <igl/all.h>
#include <unvpp/unvpp.h>

struct SolverResults
{
    Eigen::MatrixXd disp;
    Eigen::MatrixXd strain;
    Eigen::MatrixXd stress;
};


class Solver
{
public:
    Solver() {}
    ~Solver() {}

    // Constant displacements filled with 1s for constant and 0s for unknown
    virtual SolverResults solve(const unvpp::Mesh& mesh, Eigen::Matrix<double, Eigen::Dynamic, 1> F, Eigen::Matrix<double, Eigen::Dynamic, 1> constand_displacements) = 0;
};