#include "lbm.h"
#include <fstream>


int main(){
    lbm test = lbm(100,50);
    //test.compute();
    //test.velocities_for_point(100, 2, 2);
    std::ofstream f1("velocity.dat");
    std::ofstream f2("velocity_ite.dat");
    // test.velocities_after(f1, 1000);
    test.velocities_after_print_for_each_iteration(f2, 100);
}