#include "tetra.h"

#include <iostream>
#include <Eigen/LU>

namespace tetra
{

    double volume(Element e)
    {
        Eigen::Matrix4d intr;

        (intr << 1, e(0, 0), e(0, 1), e(0, 2),
                 1, e(1, 0), e(1, 1), e(1, 2),
                 1, e(2, 0), e(2, 1), e(2, 2),
                 1, e(3, 0), e(3, 1), e(3, 2))
            .finished();

        return 1 / 6.0 * intr.determinant();
    }

    Eigen::Matrix<double, 6, 12> B(Element e)
    {
        // auto ai = ai(e);
        // auto bi = bi(e);
        // auto ci = ci(e);
        // auto di = di(e);

        Eigen::Matrix<double, 6, 12> r;
        // (intr << 
        //         )
        return r;
    }

    double abcd_ijkl(Element e, int abcd, int ijkl)
    {
        if (abcd > 3 || abcd < 0 || ijkl < 0 || ijkl > 3)
        {
            printf("abcd_ijkl invalid params\n");
            exit(-1);
        }

        Eigen::Matrix3d intr;

        const auto rowReset = 4;
        // starting row to use. Changes based on ijkl
        auto i = (ijkl + 1) % rowReset;

        (intr << e((i + 0) % rowReset,0), e((i + 0) % rowReset,1), e((i + 0) % rowReset,2),
                 e((i + 1) % rowReset,0), e((i + 1) % rowReset,1), e((i + 1) % rowReset,2),
                 e((i + 2) % rowReset,0), e((i + 2) % rowReset,1), e((i + 2) % rowReset,2)).finished();

        // if not a, clear out a col
        if (abcd > 0) {
            auto clearedCol = abcd - 1;
            intr(0,clearedCol) = 1;
            intr(1,clearedCol) = 1;
            intr(2,clearedCol) = 1;
        }

        std::cout << "TMP: \n" << intr << "\n";

        auto res = intr.determinant();

        // if j or l, invert
        if (ijkl == 1 || ijkl == 3) {
            res = -1 * res;
        }

        // if not A, invert
        if (abcd > 0) {
            res = -1 * res;
        }
        return res;
    }

    void test_tetra()
    {
        printf("Testing Tetra Math\n");

        Element e;

        (e << 
        0, 0, 0,
        20, 0, 0,
        0, 30, 0,
        0, 0, 40
        ).finished();

        std::cout << "E:\n" << e << "\n";
        
        //Matches textbook!
        // for (int abc = 0; abc < 4; abc++)
        // {
        //     for (int ijkl = 0; ijkl < 4; ijkl++)
        //     {
        //         std::cout << abc << ijkl << ":\n" << abcd_ijkl(e,abc,ijkl) << "\n";
        //     }
        // }
        



    }
}