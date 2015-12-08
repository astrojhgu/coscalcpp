#ifndef COSCALC_HPP
#define COSCALC_HPP

namespace coscalc
{
  enum class unit_system
  {
    SI,CGS
  };

  template <unit_system us>
  class unit
  {};

  template <>
  class unit<unit_system::SI>
  {
  public:
    static constexpr double m=1.;
    static constexpr double km=1000;
    static constexpr double cm=1./100.;
    static constexpr double pc=3.0857E16*m;
    static constexpr double kpc=pc*1000;
    static constexpr double Mpc=kpc*1000;

    static constexpr double kg=1.;
    static constexpr double g=1./1000.;

    static constexpr double s=1.;
  };

  template <>
  class unit<unit_system::CGS>
  {
  public:
    static constexpr double m=100;
    static constexpr double km=1000*m;
    static constexpr double cm=1.;
    static constexpr double pc=3.0857E16*m;
    static constexpr double kpc=pc*1000;
    static constexpr double Mpc=kpc*1000;


    static constexpr double kg=1000;
    static constexpr double g=1000.;

    static constexpr double s=1;
  };

  struct cosmic_param
  {
  public:
    const double c;
    const double H0;
    const double Omega_m;
    const double Omega_l;
    const double Omega_k;

  public:
    cosmic_param(double _c,double _H0,
		 double _Omega_m,
		 double _Omega_l,
		 double _Omega_k);
  };

  template <unit_system us>
  cosmic_param lcdm_cp()
  {
    using u=unit<us>;
    return cosmic_param(2.99792458E8*u::m/u::s,71*u::km/u::s/u::Mpc,
			.27,.73,0.0);
  }

  class cosmic_calculator
  {
  private:
    const cosmic_param cp;
  public:
    cosmic_calculator(const cosmic_param& _cp);

  public:
    double calc_dc(double z)const;
    double calc_dm(double z)const;
    double calc_da(double z)const;
    double calc_dl(double z)const;
    
  private:
    double E(double z,double Omega_m,double Omega_l,double Omega_k)const;
  };
}

#endif
