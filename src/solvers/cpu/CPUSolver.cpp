#include "CPUSolver.h"

#include <iostream>

#include <Eigen/LU>

#include "../helpers/tetra.h"

void CPUSolver::solve(const unvpp::Mesh &mesh)
{
   printf("Hello CPU\n");

    Eigen::MatrixXd verts = Eigen::MatrixXd(8,3);
   
   tetra::test_tetra();

    //Split data into Elements

    // Generate k matrixes

    // Fill big K matrix

    // Make K invertable

    //solve equation

    //find strain
    
    //find stress 
}