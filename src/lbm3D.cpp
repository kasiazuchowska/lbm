#include "lbm3D.h"

lbm3D::lbm3D(int Lx, int Ly, int Lz) : df(2, std::vector<std::vector<std::vector<std::vector<double>>>>(
                            Lx, std::vector<std::vector<std::vector<double>>>(
                            Ly, std::vector<std::vector<double>>(
                            Lz, std::vector<double>(15, 0))))),
                            UX(Lx, std::vector<std::vector<double>>(
                            Ly, std::vector<double>(Lz,0))),
                            UY(Lx, std::vector<std::vector<double>>(
                            Ly, std::vector<double>(Lz,0))),
                            UZ(Lx, std::vector<std::vector<double>>(
                            Ly, std::vector<double>(Lz,0))),
                            R(Lx, std::vector<std::vector<double>>(
                            Ly, std::vector<double>(Lz,0))),
                            f(Lx, std::vector<std::vector<bool>>(
                            Ly, std::vector<bool>(Lz,0))),
                            Lx(Lx), Ly(Ly), Lz(Lz), c(1){
    
    //inicjalizacja df
    for(int i = 0; i < Lx; i++)
        for(int j = 0; j < Ly; j++)
            for(int k = 0; k < Lz; k++)
                for(int l = 0; l < 15; l++){
                    df[0][i][j][k][l] = df[1][i][j][k][l] = w[l];
                // std::cout << i << " " << j << " " << k << " " << df[0][i][j][k] << std::endl;
                }
                
    
    //warunki brzegowe
    for(int i = 0; i < Lx; i++){
        for(int j =0; j < Lz; j++)
            f[i][0][j] = f[i][Ly-1][j] = 1;
        
        for(int j =0; j < Lz; j++)
            f[i][j][0] = f[i][j][Lz-1] = 1;
    }
        

        

    //rysuj kolko
    double R = (double)Ly/5;
    for(int i = 0; i < Lx; i++)
        for(int j = 0; j < Ly; j++)
            for(int k = 0; k < Lz; k++)
                if((i-Lx/2) * (i-Lx/2) + (j-Ly/2) * (j-Ly/2) + (k-Lz/2) * (k-Lz/2) < R*R)
                    f[i][j][k] = 1;


    // for(int i = 0; i < Lx ; i++){
    //     for(int j = 0; j < Ly; j++){
    //         for(int k = 0; k < Lz; k++){
    //             f << i << " " << j << " " << k << " " << UX[i][j][k] << " " << UY[i][j][k] << " " << UZ[i][j][k] << std::endl;
    //         }
    //         f << std::endl;
    //     }    
    //     f << std::endl;
    // }
}



void lbm3D::macro(){
    for(int i = 0; i < Lx; i++)
        for(int j = 0; j < Ly; j++)
            for(int k = 0; k < Lz; k++)
                if(f[i][j][k] == 0){
                    double rho = 0, ux = 0, uy = 0, uz = 0;
                    for(int l = 0; l < 15; l++){
                        //std::cout << i << " " << j << " " << k << " " << df[0][i][j][k] * ex[k]<< std::endl;
                        //std:: cout << c << std::endl;
                        rho += df[c][i][j][k][l];
                        ux += df[c][i][j][k][l] * ex[l];
                        uy += df[c][i][j][k][l] * ey[l];
                        uz += df[c][i][j][k][l] * ez[l];
                    }
                    //std::cout << i << " " << j << " " << ux << std::endl;
                    ux /= rho;
                    uy /= rho;
                    uz /= rho;
                    //std::cout << i << " " << j << " " << ux << std::endl;
                    UX[i][j][k] = ux;
                    UY[i][j][k] = uy;
                    UZ[i][j][k] = uz;
                    R[i][j][k] = rho;
                }
}

void lbm3D::collision(){
    double rho = 0, ux = 0, uy = 0, uz = 0;
    for(int i = 0; i < Lx; i++)
        for(int j = 0; j < Ly; j++)
            for(int k = 0; k < Lz; k++)
                if(f[i][j][k] == 0){
                    ux = UX[i][j][k];
                    uy = UY[i][j][k];
                    uz = UZ[i][j][k];
                    rho = R[i][j][k];

                    ux += fx * tau / rho;
                    //std::cout << i << " " << j << " " << ux << std::endl;
                    double feq;
                    for(int l = 0; l < 15; l++){
                        feq=w[l] * rho * (1.0f - (3.0f/2.0f) * (ux*ux + uy*uy + uz*uz) + 3.0f * (ex[l] * ux + ey[l]*uy + ez[l]*uz) +(9.0f/2.0f)* (ex[l] * ux + ey[l]*uy + ez[l]*uz) * (ex[l] * ux + ey[l]*uy + ez[l]*uz));
                        df[c][i][j][k][l] -= (1./tau) * (df[c][i][j][k][l] - feq);
                    }
                }
}

void lbm3D::transport(){
    for(int i = 0; i < Lx; i++)
        for(int j = 0; j < Ly; j++)
            for(int k = 0; k < Lz; k++)
                if(f[i][j][k] == 0){
                    for(int l = 0; l < 15; l++){
                        int ip = (i + ex[l] + Lx) % (Lx);
                        int jp = (j + ey[l]);
                        int kp = (k + ez[l]);

                        if(f[ip][jp][kp] == 1)
                            df[1-c][i][j][k][inv[l]] = df[c][i][j][k][l];
                        else
                            df[1-c][ip][jp][kp][l] = df[c][i][j][k][l];
                    }
                }
}

void lbm3D::compute(){
    c = 1 - c;
    macro();
    collision();
    transport();
}

void lbm3D::velocities_after(std::ofstream& f, int iterations){
    for(int i = 0; i < iterations; i++)compute();

    for(int i = 0; i < Lx ; i++){
        for(int j = 0; j < Ly; j++){
            for(int k = 0; k < Lz; k++){
                f << i << " " << j << " " << k << " " << UX[i][j][k] << " " << UY[i][j][k] << " " << UZ[i][j][k] << std::endl;
            }
            f << std::endl;
        }    
        f << std::endl;
    }        
}
