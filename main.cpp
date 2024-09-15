#include "lbm.h"
#include <fstream>

int main(){
    lbm test = lbm(100,50);
    //test.compute();
    //test.velocities_for_point(100, 2, 2);
    std::ofstream f1("velocity.dat");
    test.velocities_after(f1, 1000);
}