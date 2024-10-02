#pragma once

#include <vector>
#include <iostream>
#include <fstream>
#include <cmath>

class lbm3D{
private:
    std::vector<std::vector<std::vector<std::vector<std::vector<double>>>>> df;  
    std::vector<std::vector<std::vector<double>>> UX, UY, UZ, R;
    std::vector<std::vector<std::vector<bool>>> f;
    int Lx;
    int Ly;
    int Lz;
    
    const int ex[15] = {0, -1, 0, 0, -1, -1, -1, -1, 1, 0, 0, 1, 1, 1, 1};
    const int ey[15] = {0, 0, -1, 0, -1, -1, 1, 1, 0, 1, 0, 1, 1, -1, -1};
    const int ez[15] = {0, 0, 0, -1, -1, 1, -1, 1, 0, 0, 1, 1, -1, 1, -1};
    const int inv[15] = {0, 8, 9, 10, 11, 12, 13, 14, 1, 2, 3, 4, 5, 6, 7};
    const double w[15] = {2./9., 1./9., 1./9., 1./9., 1./72., 1./72., 1./72., 1./72., 1./9., 1./9., 1./9., 1./72., 1./72., 1./72., 1./72.};
    
    

    const double fx = -0.0000065; // sila zewnetrzna moze jako argument
    const double tau = 1.;

    int c;
public:
    lbm3D(int Lx, int Ly, int Lz);
    void macro();
    void collision();
    void transport();
    void compute();
    // void velocities_for_point(int iterations, int x=0, int y=0);
    void velocities_after(std::ofstream& f, int iterations);
    // void velocities_after_print_for_each_iteration(std::ofstream& f, int iterations);
    // double calculate_drag_force();
    // double calculate_drag_coefficient(double force, double rho);
};