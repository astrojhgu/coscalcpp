#ifndef ADAPT_TRAPEZOID_HPP
#define ADAPT_TRAPEZOID_HPP
#include <list>
#include <utility>
#include <cassert>
#include <iostream>
#include <functional>
//#include <iostream>

//using namespace std;

template<typename T1,typename T2,typename T3>
class triple
{
 public:
  T1 first;
  T2 second;
  T3 third;
  triple(T1 x1,T2 x2,T3 x3)
    :first(x1),second(x2),third(x3)
    {
    }
};


template<typename T1,typename T2,typename T3>
triple<T1,T2,T3> make_triple(T1 x1,T2 x2,T3 x3)
{
  return triple<T1,T2,T3>(x1,x2,x3);
}


template <typename fT,typename T1,typename T2>
auto adapt_trapezoid(fT fun,
		     T1 x1,
		     T2 x2,
		     decltype(x1+x2) err_limit) -> decltype(fun((x1+x2)))
{
  typedef decltype(x1+x2) T;
  typedef triple<T,T,bool> interval;
  typedef decltype(fun(x1)) resT;
  /*T for interval type,
    bool for state trur for still to be updated,
    false for do not need to be updated
   */
  std::list<interval> interval_list;
  resT current_sum=((fun(x1)+fun(x2))/(T)(2)*(x2-x1));
  interval_list.push_back(make_triple(x1,current_sum,true));
  interval_list.push_back(make_triple(x2,(T)0.,true));
  bool int_state=1;
  size_t n_intervals=1;
  while(int_state)
    {
      //std::cout<<n_intervals<<std::endl;
      int_state=0;
      typename std::list<interval>::iterator i1=interval_list.begin();
      typename std::list<interval>::iterator i2=interval_list.begin();
      i2++;
      for(;i2!=interval_list.end();i1++,i2=i1,i2++)
	{
	  //cout<<i1->first<<"\t"<<i2->first<<endl;
	  //assert(i2->first>i1->first);
	  if(i1->third)
	    {
	      interval new_interval((i1->first+i2->first)/2,0,true);
	      
	      resT sum1,sum2;
	      sum1=(fun(new_interval.first)+fun(i1->first))/2*(new_interval.first-i1->first);
	      sum2=(fun(new_interval.first)+fun(i2->first))/2*(i2->first-new_interval.first);
	      new_interval.second=sum2;
	      resT err;
	      err=i1->second-sum1-sum2;
	      err/=(sum1+sum2);
	      
	      err=err<0?-err:err;

	      if(err>err_limit||n_intervals<10)
		{
		  i1->second=sum1;
		  interval_list.insert(i2,new_interval);
		  n_intervals++;
		  //cout<<n_intervals<<'\n';;
		  if(n_intervals>10000)
		    {
		      std::cerr<<"Warning: Division of the integral interval exceeds 10000, we shall stop here, for the consumption of CPU time. Be care of the result."<<std::endl;
		      int_state=0;
		      goto bk;
		      break;
		    }
		}
	      else
		{
		  i1->third=false;
		}
	      int_state=1;
	    }
	}
      
    }
 bk:
  resT result=0;
  for(typename std::list<interval>::iterator i=interval_list.begin();i!=interval_list.end();i++)
    {
      result+=i->second;
    }
  return result;
}

#endif
//EOF

