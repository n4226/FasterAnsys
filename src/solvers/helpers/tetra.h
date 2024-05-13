#pragma once

#include <Eigen/Core>

namespace tetra {

    // Eigen::MatrixXd N = Eigen::MatrixXd(3,3);

    /*
        In book notation, this containes the verticies as rows in the order i,j,k,l
    */
    using Element = Eigen::Matrix<double, 4, 3>;

    // double u(double x, double y, double z) {

    // } 

    double volume(Element e);

    //As defined in Rao 11.2

    Eigen::Matrix<double, 12, 12> K(Element e, double youngs_modulus, double poissons_ratio);
    Eigen::Matrix<double, 6, 12> B(Element e);
    Eigen::Matrix<double, 6, 6> D(Element e, double youngs_modulus, double poissons_ratio);

    
    // Helper Mats

    /// The ai, aj ..., bi ..., ci, ..., di, ..., matricies discussed in example 3.7 of Rao. Specify which one you want
    double abcd_ijkl(Element e,int abcd, int ijkl);

    void test_tetra();
}
