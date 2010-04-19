//Copyright 2009 Thomas A Caswell
//tcaswell@uchicago.edu
//http://jfi.uchicago.edu/~tcaswell
//
//This program is free software; you can redistribute it and/or modify
//it under the terms of the GNU General Public License as published by
//the Free Software Foundation; either version 3 of the License, or (at
//your option) any later version.
//
//This program is distributed in the hope that it will be useful, but
//WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
//General Public License for more details.
//
//You should have received a copy of the GNU General Public License
//along with this program; if not, see <http://www.gnu.org/licenses>.
//
//Additional permission under GNU GPL version 3 section 7
//
//If you modify this Program, or any covered work, by linking or
//combining it with MATLAB (or a modified version of that library),
//containing parts covered by the terms of MATLAB User License, the
//licensors of this Program grant you additional permission to convey
//the resulting work.

//If you modify this Program, or any covered work, by linking or
//combining it with IPP (or a modified version of that library),
//containing parts covered by the terms of End User License Agreement
//for the Intel(R) Software Development Products, the licensors of
//this Program grant you additional permission to convey the resulting
//work.

#ifndef CORR_GOFR
#define CORR_GOFR

#include <vector>
#include <string>
#include "corr.h"



namespace utilities
{
class Generic_wrapper;
}


namespace tracking
{
/**
   simple g(r) computation
 */
class Corr_gofr:public Corr
{
public:
  // basic inherited stuff
  void compute(const particle *,const std::vector<const particle*> & ) ;
  void out_to_wrapper(utilities::Generic_wrapper & ) const ;

  // special stuff
  /**
     normalize G(r) to the average
   */
  void normalize(std::vector<float> & gofr) const;
  
  /**
     constructor.  The maximum range is taken from particle::max_neighborhood_range_.
     The bins are spaced linearly.  
   */
  Corr_gofr(int bins,float max,const std::string &,int comp_num,int dset,const std::string & fname);
  
  void display() const;
  
  float get_max_range()const
  {
    return max_range_;
  }
  

private:
  // this could be done using a single histogram object, but 
  /**
     gives the number entries in the bin
   */
  std::vector<int> bin_count_;
  /**
     gives the value of the bottom edge of the bin
   */
  std::vector<float> bin_edges_;
  /**
     number of bins
   */
  int n_bins_;
  /**
     maximum range
   */
  float max_range_;

  /**
     name of group for writing out to a wrapper
   */
  std::string name_;

  /**
     count of the number of particles added
   */
  int parts_added_;
  
  /**
     File name of data source
   */
  std::string fname_;
  
  /**
     Data set number
   */
  int dset_;
  /**
     Computation number
   */
  int comp_num_;
  
};

}



#endif
