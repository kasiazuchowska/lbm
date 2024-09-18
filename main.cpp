#include "lbm.h"
#include <fstream>


void run_diffrent_iterations(){
    
}

int main(){
    lbm test = lbm(10000,50);
    //test.compute();
    //test.velocities_for_point(100, 2, 2);
    std::ofstream f1("velocity.dat");
    test.velocities_after(f1, 1000);
}