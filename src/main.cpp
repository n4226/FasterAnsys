
#include <iostream>

#include "IGLUtils.h"

#include <string>
#include "GUI/GUI.h"

// #include <Eigen/Dense>
// #include "igl/cotmatrix.h"

// #include <igl/readOFF.h>
// #include <igl/opengl/glfw/Viewer.h>
#include <igl/opengl/glfw/Viewer.h>
#include <unvpp/unvpp.h>

void iglTest() {
        // Inline mesh of a cube
  const Eigen::MatrixXd V= (Eigen::MatrixXd(8,3)<<
    0.0,0.0,0.0,
    0.0,0.0,1.0,
    0.0,1.0,0.0,
    0.0,1.0,1.0,
    1.0,0.0,0.0,
    1.0,0.0,1.0,
    1.0,1.0,0.0,
    1.0,1.0,1.0).finished();
  const Eigen::MatrixXi F = (Eigen::MatrixXi(12,3)<<
    0,6,4,
    0,2,6,
    0,3,2,
    0,1,3,
    2,7,6,
    2,3,7,
    4,6,7,
    4,7,5,
    0,4,5,
    0,5,1,
    1,5,7,
    1,7,3).finished();

  // Plot the mesh
  igl::opengl::glfw::Viewer viewer;
  viewer.data().set_mesh(V, F);
  viewer.data().set_face_based(true);
  viewer.launch();
}



void unvTest() {
    unvpp::Mesh mesh = unvpp::read("../cadFiles/TestCube-Static1.unv");
    // unvpp::Mesh mesh = unvpp::read("../cadFiles/TableWoodRedStaticMidPoly3.UNV");

    // print string representation of the mesh system of units
    // if the mesh does not have a system of units, 
    // print the default "repr" representation string "Unknown".
    // Check definition of UnitsSystem in unvpp/unvpp.h file
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

  tetToTry(mesh,V,F);

  // Plot the mesh
  igl::opengl::glfw::Viewer viewer;
  viewer.data().set_mesh(V, F);
  viewer.data().set_face_based(true);
  // viewer.callback_key_down = &key_down;
  viewer.launch(); 
    
}

int main(int argc, char** argv) {

  if (argc < 2) {
    printf("Please provide a file path to the tetrahedral file.\n");
    exit(-1);
  }

  std::string filePath = argv[1];

  auto gui = GUI(filePath);

  gui.start();
}