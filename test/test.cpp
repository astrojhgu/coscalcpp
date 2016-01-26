#include <iostream>
#include <cmath>

#include "coscalc.hpp"


using namespace coscalc;
using namespace std;
int main(int argc,char* argv[])
{
  double z=atof(argv[1]);
  double H0=atof(argv[2]);
  double Omega_m=atof(argv[3]);
  double w=atof(argv[4]);
  
  using u=unit<unit_system::SI>;
  //cosmic_calculator cc(lcdm_cp<unit_system::SI>());
  cosmic_calculator cc(cosmic_param(2.99792458E8*u::m/u::s,H0*u::km/u::s/u::Mpc,Omega_m,1-Omega_m,0,0,w));
  double d=cc.calc_dl(z)/u::pc;
  cout<<cc.calc_dl(z)<<endl;
  cout<<d<<endl;
  double m=5.0*std::log10(d)-5;
  cout<<m<<endl;
}
