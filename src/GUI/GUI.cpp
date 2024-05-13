#include "GUI.h"

#include "../IGLUtils.h"

GUI::GUI(const std::string &cadFIle)
    : cadFile(cadFIle), mesh(unvpp::read(cadFile))
{
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

    Eigen::MatrixXd V;
    Eigen::MatrixXi F;

    tetToTry(mesh, V, F);

    // Plot the mesh
    igl::opengl::glfw::Viewer viewer;
    viewer.data().set_mesh(V, F);
    viewer.data().set_face_based(true);
    // viewer.callback_key_down = &std::bind(&GUI::key_down,this);
    viewer.launch(); 


}

bool GUI::key_down(igl::opengl::glfw::Viewer &viewer, unsigned char key, int modifier)
{
    
    

    return false;
}