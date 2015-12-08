#include <iostream>
#include <cmath>

#include "coscalc.hpp"


using namespace coscalc;
using namespace std;
int main()
{
  using u=unit<unit_system::SI>;
  cosmic_calculator cc(lcdm_cp<unit_system::SI>());
  cout<<cc.calc_dl(1000)/u::Mpc<<endl;
}
