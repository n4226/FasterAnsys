#include "CPUSolver.h"

#include <iostream>

#include <Eigen/LU>
#include <Eigen/Dense>

#include "../helpers/tetra.h"

void CPUSolver::solve(const unvpp::Mesh &mesh, Eigen::Matrix<double, Eigen::Dynamic, 1> F, Eigen::Matrix<double, Eigen::Dynamic, 1> constand_displacements)
{
   printf("Hello CPU\n");

   double E = 200E9;
   double v = 0.3;

    // Eigen::MatrixXd verts = Eigen::MatrixXd(8,3);

    std::vector<tetra::Element> elements;
    std::vector<std::array<int,4>> vert_maps;
    std::vector<Eigen::Matrix<double,12,12>> ks;
    elements.resize(mesh.elements()->size());
    ks.resize(mesh.elements()->size());
    vert_maps.reserve(mesh.elements()->size());
   
    //Split data into Elements
    for (size_t i = 0; i < mesh.elements()->size(); i++)
    {
        auto nodes = mesh.elements()->at(i).vertices_ids();

        for (size_t j = 0; j < 4; j++)
        {
            //populate each vertex
            auto a = mesh.vertices()[nodes[j]];
            auto v = Eigen::Vector3d(a[0],a[1],a[2]);
            elements[i].row(j) = v;
            vert_maps[i][j] = nodes[j];
        }
        
    }
    
    // Generate k matrixes
    for (size_t i = 0; i < elements.size(); i++)
    {
        ks[i] = tetra::K(elements[i], E, v); 
    }
    

    // Fill big K matrix
    // N*N mat where N = # vets * DOF per vertex
    Eigen::MatrixXd K(mesh.vertices().size() * 3,mesh.vertices().size() * 3);

    for (size_t e = 0; e < elements.size(); e++)
    {
        for (size_t i = 0; i < 12; i++)
        {
            for (size_t j = 0; j < 12; j++)
            {
                auto vi = i / 3;
                auto i_offset = (i % 3) * 3;
                auto vj = j / 3;
                auto j_offset = (j % 3) * 3;

                auto global_vi = vert_maps[e][vi];
                auto global_vj = vert_maps[e][vj];

                K(global_vi + i_offset,global_vj + j_offset) = ks[e](i + i_offset,j + j_offset);
            }
            
        }
         
    }

    //Make F
    // Eigen::Matrix<double, mesh.verticies().size(),1> F;

    // Make K invertable


    //solve equation

    //find strain
    
    //find stress 
}