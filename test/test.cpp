#include <iostream>
#include <iomanip>
#include <cmath>

#include "coscalc.hpp"


using namespace coscalc;
using namespace std;
int main(int argc,char* argv[])
{
  if(argc!=5)
    {
      std::cerr<<"Usage:"<<argv[0]<<" z H0 Omega w"<<std::endl;
      return -1;
    }
  double z=atof(argv[1]);
  double H0=atof(argv[2]);
  double Omega_m=atof(argv[3]);
  double w=atof(argv[4]);
  
  using u=unit<unit_system::SI>;
  //cosmic_calculator cc(lcdm_cp<unit_system::SI>());
  double Omega_rad=4.165e-5/pow(H0/100.0,2.0);
  cosmic_calculator cc(cosmic_param(2.99792458E8*u::m/u::s,H0*u::km/u::s/u::Mpc,Omega_m,1-Omega_m-Omega_rad,0,Omega_rad,w));
  double d=cc.calc_dl(z)/u::Mpc;
  cout<<setprecision(10);
  cout<<cc.calc_dl(z)<<" cm"<<endl;
  cout<<d<<" Mpc"<<endl;
  double m=5.0*std::log10(d)-5;
  cout<<m<<endl;
}
