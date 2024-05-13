#include "../Solver.h"

class CUDASolver: public Solver
{
public:
    using Solver::Solver;

    virtual void solve(const unvpp::Mesh& mesh) override;

};