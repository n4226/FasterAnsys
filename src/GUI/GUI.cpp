#include "GUI.h"

#include <imgui.h>
#include "../IGLUtils.h"

GUI* GUI::shared;

GUI::GUI(const std::string &cadFIle)
    : cadFile(cadFIle), mesh(unvpp::read(cadFile))
{
    shared = this;
}

GUI::~GUI()
{
}

void GUI::start()
{
    std::cout << "Units system: " 
              << mesh.unit_system().value_or(unvpp::UnitsSystem()).repr
              << std::endl;

    // print count of mesh vertices
    std::cout << "Vertices count = " 
              << mesh.vertices().size() 
              << std::endl;

    // print count of mesh elements (cells)
    std::cout << "Elements count = " 
              << mesh.elements().value_or(std::vector<unvpp::Element>()).size()
              << std::endl;

    // print group names and element count (like boundary patches or cell zones)
    for (auto& group : mesh.groups().value_or(std::vector<unvpp::Group>())) {
        std::cout << "Group name: " 
                  << group.name() 
                  << " - elements count = " 
                  << group.elements_ids().size()
                  << std::endl;
    }

    

    tetToTry(mesh, V, F);

    set_boundary_conditions();

    // Plot the mesh
    viewer.data().set_mesh(V, F);
    viewer.data().set_face_based(true);
    viewer.callback_key_down = key_down;
    color_find_boundary_conditions();
    // color_boundary_cond();
    viewer.launch(); 


}

void GUI::solve()
{
    if (solver == nullptr)
        // solver = new CUDASolver();
        solver = new CPUSolver();

    auto res = solver->solve(mesh, AppliedForces, fixed_displacements);

    // std::cout << "Disp:\n" << res.strain << "\n";
    // std::cout << "Stress:\n" << res.stress << "\n";

    const double scale = 1E8;

    for (size_t i = 0; i < res.disp.rows(); i+= 3)
    {
        V(i / 3,0) += res.disp(i+0) * scale;
        V(i / 3,1) += res.disp(i+1) * scale;
        V(i / 3,2) += res.disp(i+2) * scale;
    }

    viewer.data().set_mesh(V,F);
    
}

void GUI::set_boundary_conditions()
{
    const double force_to_apply = -10'000;

    fixed_displacements = Eigen::MatrixXd::Zero(mesh.vertices().size() * 3,1);
    AppliedForces = Eigen::MatrixXd::Zero(mesh.vertices().size() * 3,1);

    auto min_height = V.colwise().minCoeff();
    auto max_height = V.colwise().maxCoeff();

    const double tolerenceMult = 0.01; // 1% plus or minus top or bottom to be considered part of it;
    const int chosen_axis = 1; // Y axis

    for (size_t i = 0; i < mesh.vertices().size(); i++)
    {
        auto vert = mesh.vertices()[i];
        if (abs(vert[chosen_axis] - min_height(chosen_axis)) < tolerenceMult) {
            // Constrained

            // Frictionless Support
            fixed_displacements((i * 3 + chosen_axis + 0),0) = 1;

            // Frictional Support
            /*
            fixed_displacements((i * 3),0) = 1;
            fixed_displacements((i * 3) + 1,0) = 1;
            fixed_displacements((i * 3) + 2,0) = 1;
            */
        }

        if (abs(vert[chosen_axis] - max_height(chosen_axis)) < tolerenceMult) {
            // Force Applied
            AppliedForces((i * 3) + chosen_axis + 0,0) = force_to_apply;
        }
    }

    // std::cout << "Forces: \n" << AppliedForces << "\n"; 
    // std::cout << "Fixed Verts: \n" << fixed_displacements << "\n"; 
}

void GUI::color_find_boundary_conditions()
{
    Eigen::MatrixXd C(mesh.vertices().size(),3);
    Eigen::MatrixXd data(mesh.vertices().size(),1);

    for (size_t i = 0; i < mesh.vertices().size(); i++)
    {
        auto vec = Eigen::Vector3d(mesh.vertices()[i][0],mesh.vertices()[i][1],mesh.vertices()[i][2]);
        auto val = std::clamp(vec(2) / 10, 0.0,1.0);

        auto col1 = Eigen::Vector3d(1,0.1,0);
        auto col2 = Eigen::Vector3d(0,0.2,1);

        C.row(i) =  (val * (col2 - col1)) + col1;
        data(i) = vec(1);
    }
    

    // viewer.data().set_colors(C);
    viewer.data().set_data(data);
}

void GUI::color_boundary_cond()
{
    Eigen::MatrixXd C(mesh.vertices().size(),3);
    Eigen::MatrixXd data(mesh.vertices().size(),1);

    for (size_t i = 0; i < mesh.vertices().size(); i++)
    {
        auto vec = Eigen::Vector3d(mesh.vertices()[i][0],mesh.vertices()[i][1],mesh.vertices()[i][2]);
        auto val = std::clamp(vec(2) / 10, 0.0,1.0);

        auto col1 = Eigen::Vector3d(1,0,0);
        auto col2 = Eigen::Vector3d(0,0,1);
        auto col3 = Eigen::Vector3d(0,0.4,0);

        if (AppliedForces(3*i,0) != 0 || AppliedForces(3*i + 1,0) != 0 || AppliedForces(3*i + 2,0) != 0)
            C.row(i) = col1;
        else if (fixed_displacements(3*i,0) != 0 || fixed_displacements(3*i + 1,0) != 0 || fixed_displacements(3*i + 2,0) != 0)
            C.row(i) = col2;
        else
            C.row(i) = col3;
    }
    

    viewer.data().set_colors(C);
    // viewer.data().set_data(data);
}

bool key_down(igl::opengl::glfw::Viewer &viewer, unsigned char key, int modifier)
{
    
    if (key == '1')
    {
        GUI::shared->solve();
    }

    if (key == '1') {
        GUI::shared->color_find_boundary_conditions();
    }
        
    return false;
}