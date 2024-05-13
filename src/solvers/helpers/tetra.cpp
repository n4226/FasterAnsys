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

    Eigen::Matrix<double, 12, 12> K(Element e, double youngs_modulus, double poissons_ratio)
    {
        auto b = B(e);
        return volume(e) * b.transpose() * D(e, youngs_modulus, poissons_ratio) * b;
    }

    Eigen::Matrix<double, 6, 12> B(Element e)
    {
        auto bi = abcd_ijkl(e, 1, 0);
        auto bj = abcd_ijkl(e, 1, 1);
        auto bk = abcd_ijkl(e, 1, 2);
        auto bl = abcd_ijkl(e, 1, 3);

        auto ci = abcd_ijkl(e, 2, 0);
        auto cj = abcd_ijkl(e, 2, 1);
        auto ck = abcd_ijkl(e, 2, 2);
        auto cl = abcd_ijkl(e, 2, 3);

        auto di = abcd_ijkl(e, 3, 0);
        auto dj = abcd_ijkl(e, 3, 1);
        auto dk = abcd_ijkl(e, 3, 2);
        auto dl = abcd_ijkl(e, 3, 3);

        Eigen::Matrix<double, 6, 12> r;
        (r << bi, 0, 0, bj, 0, 0, bk, 0, 0, bl, 0, 0,
              0, ci, 0, 0, cj, 0, 0, ck, 0, 0, cl, 0,
              0, 0, di, 0, 0, dj, 0, 0, dk, 0, 0, dl,
              ci, bi, 0, cj, bj, 0, ck, bk, 0, cl, bl, 0,
              0, di, ci, 0, dj, cj, 0, dk, ck, 0, dl, cl,
              di, 0, bi, dj, 0, bj, dk, 0, bk, dl, 0, bl
        ).finished();

        return 1/6.0 * 1/volume(e) * r;
    }

    Eigen::Matrix<double, 6, 6> D(Element e, double youngs_modulus, double poissons_ratio)
    {
        double v = poissons_ratio;
        double vFunc = (1 - 2 * v) / 2;

        auto coefficient = youngs_modulus / ((1 + v) * (1 - 2 * v));

        Eigen::Matrix<double, 6, 6> r;


        (r << 1 - v, v, v, 0, 0, 0,
              v, 1 - v, v, 0, 0, 0,
              v, v, 1 - v, 0, 0, 0,
              0, 0, 0, vFunc, 0 ,0,
              0, 0, 0, 0, vFunc, 0,
              0, 0, 0, 0, 0, vFunc
        ).finished();

        r = coefficient * r;

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

        // std::cout << "TMP: \n" << intr << "\n";

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

        if (0) { // Example near equation 8.10

            Element e;

            (e << 0, 0, 0,
             20, 0, 0,
             0, 30, 0,
             0, 0, 40)
                .finished();

            std::cout << "E:\n"
                      << e << "\n";

            // Matches textbook!
             for (int abc = 0; abc < 4; abc++)
             {
                 for (int ijkl = 0; ijkl < 4; ijkl++)
                 {
                     std::cout << abc << ijkl << ":\n" << abcd_ijkl(e,abc,ijkl) << "\n";
                 }
             }
        }

        if (1) { //Example 11.1 -- Matched -- pretty confident

        Element e;

            (e << 0, 0, 0,
             0.10, 0, 0,
             0, 0.15, 0,
             0, 0, 0.20)
                .finished();

            std::cout << "E:\n"
                      << e << "\n";

            double E = 207E9;
            double v = 0.3;

            std::cout << "B:\n" << B(e) << "\n";
            std::cout << "D:\n" << D(e,E,v) << "\n";

            std::cout << "k:\n" << K(e,E,v) << "\n";

        }
    }
}