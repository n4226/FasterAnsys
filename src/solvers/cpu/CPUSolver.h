#include "../Solver.h"

class CPUSolver: public Solver
{
public:
    using Solver::Solver;

    virtual void solve(const unvpp::Mesh& mesh) override;

};