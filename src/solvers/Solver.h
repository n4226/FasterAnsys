
#include <igl/all.h>
#include <unvpp/unvpp.h>

class Solver
{
public:
    Solver() {}
    ~Solver() {}

    virtual void solve(const unvpp::Mesh) = 0;
};