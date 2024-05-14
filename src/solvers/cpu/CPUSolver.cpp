#include "CPUSolver.h"

#include <iostream>

#include <Eigen/LU>
#include <Eigen/Dense>

#include "../helpers/tetra.h"

SolverResults CPUSolver::solve(const unvpp::Mesh &mesh, Eigen::Matrix<double, Eigen::Dynamic, 1> f, Eigen::Matrix<double, Eigen::Dynamic, 1> constand_displacements)
{
   printf("Hello CPU\n");

   double E = 200E9;
   double v = 0.3;

    // Eigen::MatrixXd verts = Eigen::MatrixXd(8,3);

    std::vector<tetra::Element> elements;
    std::vector<std::array<int,4>> vert_maps;
    std::vector<Eigen::Matrix<double,12,12>> ks;
    std::vector<Eigen::Matrix<double,6,12>> bs;
    std::vector<Eigen::Matrix<double,6,6>> ds;
    elements.resize(mesh.elements()->size());
    ks.resize(mesh.elements()->size());
    bs.resize(mesh.elements()->size());
    ds.resize(mesh.elements()->size());
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
        bs[i] = tetra::B(elements[i]); 
        ds[i] = tetra::D(elements[i], E, v); 
    }
    

    // Fill big K matrix
    // N*N mat where N = # vets * DOF per vertex
    Eigen::MatrixXd K = Eigen::MatrixXd::Zero(mesh.vertices().size() * 3,mesh.vertices().size() * 3);
    Eigen::MatrixXd B = Eigen::MatrixXd::Zero(mesh.vertices().size() * 3,mesh.vertices().size() * 3);
    Eigen::MatrixXd D = Eigen::MatrixXd::Zero(mesh.vertices().size() * 3,mesh.vertices().size() * 3);

    for (size_t e = 0; e < elements.size(); e++)
    {
        // if (e>0) break;
        for (size_t i = 0; i < 12; i++)
        {
            for (size_t j = 0; j < 12; j++)
            {
                auto vi = i / 3;
                auto i_offset = (i % 3);
                auto vj = j / 3;
                auto j_offset = (j % 3);

                auto global_vi = vert_maps[e][vi];
                auto global_vj = vert_maps[e][vj];

                // printf("i: %d, vi: %d, i_offset: %d, global_vi: %d\n",i, vi, i_offset, global_vi);

                K(global_vi * 3 + i_offset,global_vj * 3 + j_offset) += ks[e](i,j);
                if (i < 6)
                    B(global_vi * 3 + i_offset,global_vj * 3 + j_offset) += bs[e](i,j);
                if (i < 6 && j < 6)
                    D(global_vi * 3 + i_offset,global_vj * 3 + j_offset) += ds[e](i,j);
            }
            
        }
         
    }

    //Make F
    // Eigen::Matrix<double, mesh.verticies().size(),1> F;

    SolverResults res{};

    // Make K invertable
    auto F = f;
    res.disp = constand_displacements;

    if (res.disp.size() != F.size()) {
        printf("Major Problem\n");
        exit(-1);
    }

    double max = K.maxCoeff();

    auto beta = max * 1E9;
    
    std::cout << "og K:\n" << K << "\n";

    std::cout << "max:\n" << max << "\n";
    std::cout << "beta:\n" << beta << "\n";

    for (size_t i = 0; i < res.disp.size(); i++)
    {
        if (res.disp(i,0) == 1) {
            //known to be zero
            K(i,i) = beta;
            F(i,0) = 0;
        }
    }

    //solve equation
    res.disp = K.inverse() * F;
    std::cout << "K:\n" << K << "\n";
    std::cout << "`K:\n" << K.inverse() << "\n";
    
    std::cout << "Found K\n";

    //find strain
    res.strain = B * res.disp;
    //find stress 
    res.stress = D * res.strain;

    std::cout << "Disp:\n" << res.disp << "\n";
    std::cout << "Strain:\n" << res.strain << "\n";
    std::cout << "Stress:\n" << res.stress << "\n";
    std::cout << "Found Everything\n";


    return res;
}