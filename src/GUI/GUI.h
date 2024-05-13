
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

    void set_boundary_conditions();

    //Debuf

    void color_find_boundary_conditions();
    void color_boundary_cond();

private:
    /* data */
    std::string cadFile;

    unvpp::Mesh mesh;

    igl::opengl::glfw::Viewer viewer;
    Eigen::MatrixXd V;
    Eigen::MatrixXi F;


    //boundary conditions
    Eigen::MatrixXd AppliedForces;
    Eigen::MatrixXd fixed_displacements;

    Solver* solver = 0;

};

    bool key_down(igl::opengl::glfw::Viewer& viewer, unsigned char key, int modifier);
