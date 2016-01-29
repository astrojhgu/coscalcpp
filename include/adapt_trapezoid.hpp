#ifndef ADAPT_TRAPEZOID_HPP
#define ADAPT_TRAPEZOID_HPP
#include <list>
#include <utility>
#include <cassert>
#include <iostream>
#include <functional>
#include <cmath>
#include <algorithm>
//#include <iostream>

//using namespace std;

template<typename T>
class interval_sum
{
 public:
  T left_x;
  T ydx;
  bool to_be_refined;
  T err;
  interval_sum(T x1,T x2,bool x3)
    :left_x(x1),ydx(x2),to_be_refined(x3)
    {
    }
};


template <typename fT,typename T>
T adapt_trapezoid(fT fun,
		  T x1,
		  T x2,
		  T err_limit,
		  size_t max_intervals=0)
{
  typedef interval_sum<T> interval;
  
  /*T for interval type,
    bool for state trur for still to be updated,
    false for do not need to be updated
   */
  std::list<interval> interval_list;
  T current_sum=((fun(x1)+fun(x2))/(T)(2)*(x2-x1));
  interval_list.push_back(interval(x1,current_sum,true));
  interval_list.push_back(interval(x2,(T)0.,true));
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
	  //cout<<i1->left_x<<"\t"<<i2->left_x<<endl;
	  //assert(i2->left_x>i1->left_x);
	  if(i1->to_be_refined)
	    {
	      interval new_interval((i1->left_x+i2->left_x)/2,0,true);
	      
	      T sum1,sum2;
	      sum1=(fun(new_interval.left_x)+fun(i1->left_x))/2*(new_interval.left_x-i1->left_x);
	      sum2=(fun(new_interval.left_x)+fun(i2->left_x))/2*(i2->left_x-new_interval.left_x);
	      new_interval.ydx=sum2;
	      T err;
	      err=i1->ydx-sum1-sum2;
	      err/=(sum1+sum2);
	      
	      err=err<0?-err:err;

	      if(err>err_limit||n_intervals<10)
		{
		  i1->ydx=sum1;
		  interval_list.insert(i2,new_interval);
		  n_intervals++;
		  //cout<<n_intervals<<'\n';;
		  if(max_intervals>0&&n_intervals>max_intervals)
		    {
		      std::cerr<<"Warning: Division of the integral interval exceeds 10000, we shall stop here, for the consumption of CPU time. Be care of the result."<<std::endl;
		      int_state=0;
		      goto bk;
		      break;
		    }
		}
	      else
		{
		  i1->to_be_refined=false;
		}
	      int_state=1;
	    }
	}
      
    }
 bk:
  T result=0;
  
  interval_list.sort([](const interval& x1,const interval& x2){
      return std::abs(x1.ydx)<std::abs(x2.ydx);
    }
    );

  result=std::accumulate(interval_list.begin(),interval_list.end(),interval(0,0,false),[](const interval& x1,const interval& x2){return interval(0,x1.ydx+x2.ydx,false);}).ydx;
  //std::cout<<interval_list.size()<<std::endl;
  return result;
}

#endif
//EOF

