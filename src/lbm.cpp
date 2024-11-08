#include "lbm.h"

lbm::lbm(int Lx, int Ly) : df(2, std::vector<std::vector<std::vector<double>>>(
                            Lx, std::vector<std::vector<double>>(
                            Ly, std::vector<double>(9, 0)))),
                            U(Lx, std::vector<double>(Ly,0)),
                            V(Lx, std::vector<double>(Ly,0)),
                            R(Lx, std::vector<double>(Ly,0)),
                            f(Lx, std::vector<bool>(Ly,0)),
                            Lx(Lx), Ly(Ly), c(1){
    
    //inicjalizacja df
    for(int i = 0; i < Lx; i++)
        for(int j = 0; j < Ly; j++)
            for(int k = 0; k < 9; k++){
                df[0][i][j][k] = df[1][i][j][k] = w[k];
                // std::cout << i << " " << j << " " << k << " " << df[0][i][j][k] << std::endl;
            }
                
    
    //warunki brzegowe
    for(int i = 0; i < Lx; i++)
        f[i][0] = f[i][Ly-1] = 1;

    //rysuj kolko
    double R = (double)Ly/5;
    for(int i = 0; i < Lx; i++)
        for(int j = 0; j < Ly; j++)
            if((i-Lx/2) * (i-Lx/2) + (j-Ly/2) * (j-Ly/2) < R*R)
                f[i][j] = 1;
}



void lbm::macro(){
    for(int i = 0; i < Lx; i++)
        for(int j = 0; j < Ly; j++)
            if(f[i][j] == 0){
                double rho = 0, ux = 0, uy = 0;
                for(int k = 0; k < 9; k++){
                    //std::cout << i << " " << j << " " << k << " " << df[0][i][j][k] * ex[k]<< std::endl;
                    //std:: cout << c << std::endl;
                    rho += df[c][i][j][k];
                    ux += df[c][i][j][k] * ex[k];
                    uy += df[c][i][j][k] * ey[k];
                }
                //std::cout << i << " " << j << " " << ux << std::endl;
                ux /= rho;
                uy /= rho;
                //std::cout << i << " " << j << " " << ux << std::endl;
                U[i][j] = ux;
                V[i][j] = uy;
                R[i][j] = rho;
            }
}

void lbm::collision(){
    double rho = 0, ux = 0, uy = 0;
    for(int i = 0; i < Lx; i++)
        for(int j = 0; j < Ly; j++)
            if(f[i][j] == 0){
                ux = U[i][j];
                uy = V[i][j];
                rho = R[i][j];

                ux += fx * tau / rho;
                //std::cout << i << " " << j << " " << ux << std::endl;
                double feq;
                for(int k = 0; k < 9; k++){
                    feq = w[k] * rho * (1. - (3./2.) * (ux*ux + uy*uy) + 3. * (ex[k]*ux + ey[k]*uy) + (9./2.) * (ex[k]*ux + ey[k]*uy) * (ex[k]*ux + ey[k]*uy));
                    df[c][i][j][k] -= (1./tau) * (df[c][i][j][k] - feq);
                }
            }
}

void lbm::transport(){
    for(int i = 0; i < Lx; i++)
        for(int j = 0; j < Ly; j++)
            if(f[i][j] == 0){
                for(int k = 0; k < 9; k++){
                    int ip = (i + ex[k] + Lx) % (Lx);
                    int jp = (j + ey[k]);

                    if(f[ip][jp] == 1)
                        df[1-c][i][j][inv[k]] = df[c][i][j][k];
                    else
                        df[1-c][ip][jp][k] = df[c][i][j][k];
                }
            }
}

void lbm::compute(){
    c = 1 - c;
    macro();
    collision();
    transport();
}

double lbm::calculate_drag_force(){
    double F_D = 0.;

    for (int i = 0; i < Lx; ++i) {
        for (int j = 0; j < Ly; ++j) {
            if(f[i][j] == 0){
                for(int k = 0; k < 9; k++){
                    int ip = (i + ex[k] + Lx) % (Lx);
                    int jp = (j + ey[k]);

                    if(f[ip][jp] == 1 && jp != 0 && jp != (Ly-1)){ //exclude top and bottom
                        // std::cout << fabs(df[1-c][ip][jp][inv[k]] - df[c][i][j][k])<< std::endl;
                        F_D += fabs(df[1-c][ip][jp][inv[k]] - df[c][i][j][k]);
                    }
                        
                }
            }
        }
    }

    return F_D;
}

double lbm::calculate_drag_coefficient(double force, double rho){
    double R = (double)Ly/5;
    double A = 2*R; //M_PI*R*R; //przekroj ciala
    double mean_velocity = calculate_mean_velocity();

    return (2.0 * force) / (rho * mean_velocity * mean_velocity * A);

}

double lbm::calculate_mean_velocity(){
    double res_sum = 0;
    double res_count = 0;
    int i = 2;

    for(int j = 0; j < Ly; j++)
        if(f[i][j] == 0){
            res_sum += U[i][j];
            res_sum += V[i][j];
            res_count ++;
        }
    
    return res_sum/res_count/2; // /2 bo dwie skladowe
}

double lbm::calculate_reynolds(){
    double mean_velocity = calculate_mean_velocity();
    double L = 40; //2*R
    double viscosity = (2*tau-1)/6;

    return mean_velocity*L/viscosity;
}

void lbm::velocities_for_point(int iterations, int x, int y){
    for(int i = 0; i < iterations; i++){
        compute();
        std::cout << i << " " << U[x][y] << " " << V[x][y] << std::endl;
    }      
}

void lbm::velocities_after(std::ofstream& f, int iterations){
    for(int i = 0; i < iterations; i++)compute();

    for(int i = 0; i < Lx ; i++){
        for(int j = 0; j < Ly; j++){
            f << i << " " << j << " " << U[i][j] << " " << V[i][j] << std::endl;
        }
        f << std::endl;
    }        
}

void lbm::velocities_after_print_for_each_iteration(std::ofstream& f, int iterations){
    for(int ite = 0; ite < iterations; ite++){
        compute();
        f << "Iteration " << ite << std::endl;
        for(int i = 0; i < Lx ; i++){
            for(int j = 0; j < Ly; j++){
                f << i << " " << j << " " << U[i][j] << " " << V[i][j] << std::endl;
            }
            f << std::endl;
        }
        f << std::endl;
        f << std::endl;
    }          
}