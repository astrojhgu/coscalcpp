#include <cmath>
#include <adapt_trapezoid.hpp>
#include <coscalc.hpp>

//using namespace std;

namespace coscalc
{
  cosmic_param::cosmic_param(double _c,double _H0,
			     double _Omega_m,
			     double _Omega_l,
			     double _Omega_k,
			     double _Omega_rad,
			     double _w)
    :c(_c),H0(_H0),Omega_m(_Omega_m),
     Omega_l(_Omega_l),Omega_k(_Omega_k),
     Omega_rad(_Omega_rad),w(_w)
  {
  }

  
  cosmic_calculator::cosmic_calculator(const cosmic_param& _cp)
    :cp(_cp)
  {}

  
  double cosmic_calculator::E(double z,double Omega_m,double Omega_l,double Omega_k,double Omega_rad,double w)const
  {
    double zp1=1+z;
    return std::sqrt(Omega_rad*zp1*zp1*zp1*zp1+Omega_m*zp1*zp1*zp1+Omega_k*zp1*zp1+Omega_l*pow(zp1,3*(1+w)));
  }
  
  double cosmic_calculator::calc_dc(double z)const
  {
    double Omega_m= this->cp.Omega_m;
    double Omega_l= this->cp.Omega_l;
    double Omega_k= this->cp.Omega_k;
    double Omega_rad=this->cp.Omega_rad;
    double w=this->cp.w;
    double c      = this->cp.c;
    double H0     = this->cp.H0;

    return c/H0*adapt_trapezoid([=](double z){return 1.0/E(z,Omega_m,Omega_l,Omega_k,Omega_rad,w);},0.,z,1e-10);
  }

  double cosmic_calculator::calc_dm(double z)const
  {
    double Dh=cp.c/cp.H0;
    double Dc=calc_dc(z);
    if(cp.Omega_k>0)
      {
	return Dh/std::sqrt(cp.Omega_k)*std::sinh(std::sqrt(cp.Omega_k)*Dc/Dh);
      }
    else if(cp.Omega_k<0)
      {
	return Dh/std::sqrt(-cp.Omega_k)*std::sin(std::sqrt(-cp.Omega_k)*Dc/Dh);
      }
    else
      {
	return Dc;
      }
  }

  double cosmic_calculator::calc_da(double z)const
  {
    return calc_dm(z)/(1+z);
  }

  double cosmic_calculator::calc_dl(double z)const
  {
    return calc_dm(z)*(1+z);
  }
}
