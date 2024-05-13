
#include <igl/opengl/glfw/Viewer.h>
#include <unvpp/unvpp.h>
#include <string>
#include <vector>
#include "solvers/CUDA/CUDASolver.h"
#include "solvers/cpu/CPUSolver.h"

class GUI
{
public:
    GUI(const std::string& cadFIle);
    ~GUI();

    void start();

    static GUI* shared;

    void solve();

private:
    /* data */
    std::string cadFile;

    unvpp::Mesh mesh;

    Solver* solver = 0;

};

    bool key_down(igl::opengl::glfw::Viewer& viewer, unsigned char key, int modifier);
