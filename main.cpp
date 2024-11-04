#include "lbm.h"
#include "lbm3D.h"
#include <fstream>


int main(){
    lbm test = lbm(100,50);
    lbm3D test3D = lbm3D(100,60,60);
    //test.compute();
    //test.velocities_for_point(100, 2, 2);
    std::ofstream f1("velocity.dat");
    // std::ofstream f2("velocity_ite.dat");


    // std::ofstream ite10("velocity_10_ite.dat");
    // std::ofstream ite50("velocity_50_ite.dat");
    // std::ofstream ite100("velocity_100_ite.dat");
    // std::ofstream ite500("velocity_500_ite.dat");
    // std::ofstream ite1000("velocity_1000_ite.dat");
    // std::ofstream ite2000("velocity_2000_ite.dat");

    std::ofstream f1_3D("velocity_3D.dat");

    // test.velocities_after(ite10, 10);
    // test.velocities_after(ite50, 50);
    // test.velocities_after(ite100, 100);
    // test.velocities_after(ite500, 500);
    // test.velocities_after(ite1000, 1000);
    // test.velocities_after(ite2000, 2000);


    test.velocities_after(f1, 1000);
    // test.velocities_after_print_for_each_iteration(f2, 100);
    std::cout << test.calculate_drag_coefficient(test.calculate_drag_force(), 1.2) << std::endl; //biore gestosc powietrza
    std::cout << test.calculate_mean_velocity() << std::endl;



    // test3D.velocities_after(f1_3D, 1000);
}