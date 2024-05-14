#include "../Solver.h"

class CUDASolver: public Solver
{
public:
    using Solver::Solver;

    virtual SolverResults solve(const unvpp::Mesh& mesh,  Eigen::Matrix<double, Eigen::Dynamic, 1> F, Eigen::Matrix<double, Eigen::Dynamic, 1> constand_displacements) override;

};