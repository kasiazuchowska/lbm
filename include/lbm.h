#include <vector>
#include <iostream>
#include <fstream>

class lbm{
private:
    std::vector<std::vector<std::vector<std::vector<double>>>> df;  
    std::vector<std::vector<double>> U, V, R;
    std::vector<std::vector<bool>> f;
    int Lx;
    int Ly;
    
    const int ex[9] = {0, 1, 0, -1, 0, 1, -1, -1, 1};
    const int ey[9] = {0, 0, 1, 0, -1, 1, 1, -1, -1};
    const int inv[9] = {0, 3, 4, 1, 2, 7, 8, 5, 6};
    const double w[9] = {4./9., 1./9., 1./9., 1./9., 1./9., 1./36., 1./36., 1./36., 1./36.};
    
    

    const double fx = 0.000014; // sila zewnetrzna moze jako argument
    const double tau = 1.;

    int c;
public:
    lbm(int Lx, int Ly);
    void macro();
    void collision();
    void transport();
    void compute();
    void velocities_for_point(int iterations, int x=0, int y=0);
    void velocities_after(std::ofstream& f, int iterations);
    void velocities_after_print_for_each_iteration(std::ofstream& f, int iterations);
};