#include "IGLUtils.h"
#include <iostream>

void tetToTry(const unvpp::Mesh &mesh, Eigen::MatrixXd &V, Eigen::MatrixXi& F)
{

    auto v_count = mesh.vertices().size();
    V = Eigen::MatrixXd(v_count,3);
    int i = 0;
    for (auto v : mesh.vertices()) {
        for (int x = 0; x < 3; x++)
            V.row(i)[x] = v.at(x);
        i++;
    }

    auto elems = mesh.elements().value_or(std::vector<unvpp::Element>());

    F = Eigen::MatrixXi((elems.size()) * 4,3);
    i = 0;

    for (auto elem : elems) {
        if (elem.type() == unvpp::ElementType::Tetra) {
            auto& ids = elem.vertices_ids();

            std::cout << "IDS:\n" << ids[0] << " " << ids[1]<< " " << ids[2]<< " " << ids[3]<< "\n";

           // if (i >= 6 * 4) {break;}

            F.row(i)[0] = ids[2];
            F.row(i)[1] = ids[1];
            F.row(i)[2] = ids[0];

            F.row(i+1)[0] = ids[2];
            F.row(i+1)[1] = ids[3];
            F.row(i+1)[2] = ids[1];

            F.row(i+2)[0] = ids[3];
            F.row(i+2)[1] = ids[2];
            F.row(i+2)[2] = ids[0];

            F.row(i+3)[0] = ids[3];
            F.row(i+3)[1] = ids[0];
            F.row(i+3)[2] = ids[1];


            
        } else {
            printf("ERRROR\n");
        }
        i += 4;
    }

    std::cout << "V: \n" << V << "\n";
    std::cout << "F: \n" << F << "\n";
}
