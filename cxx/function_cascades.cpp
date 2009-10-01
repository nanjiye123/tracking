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
//see website for additional permissions under GNU GPL version 3 section 7
#include<iostream>

#include "hash_case.h"
#include "hash_shelf.h"
#include "hash_box.h"
#include "particle_base.h"
#include "wrapper_o.h"

using tracking::hash_box;
using tracking::hash_shelf;
using tracking::hash_case;
using tracking::particle_base;

using utilities::Wrapper_out;

using std::set;
using std::vector;
using std::cout;
using std::endl;



void hash_case::output_to_wrapper(Wrapper_out & wrapper) const
{

  wrapper.initialize_wrapper();
  for(vector<hash_shelf*>::const_iterator current_shelf= h_case_.begin();
      current_shelf!=h_case_.end();++current_shelf)				// loop over frames
  {
    (*current_shelf)->output_to_wrapper(wrapper);
  }
  wrapper.finalize_wrapper();


}
void hash_shelf::output_to_wrapper(Wrapper_out & wrapper) const
{
  cout<<"frame "<<plane_number_<<"contains ";
  
  cout<<particle_count_<<"particles"<<endl;
  
  wrapper.open_frame(plane_number_,particle_count_);
  for(vector<hash_box*>::const_iterator current_box = hash_.begin();
      current_box != hash_.end();++current_box)
  {
    (*current_box)->output_to_wrapper(wrapper);
  }
  wrapper.close_frame();
}
void hash_box::output_to_wrapper(Wrapper_out & wrapper) const
{

  for(vector<particle_base*>::const_iterator current_part = contents_.begin();
      current_part!=contents_.end();++current_part)
  {
    wrapper.set_all_values(*current_part);
  }
}







void hash_case::pass_fun_to_part(void(particle_base::*fun)())
{
  vector<hash_shelf*>::iterator myend =  h_case_.end();
  for(vector<hash_shelf*>::iterator it = h_case_.begin();
      it!=myend;++it)
  {
    (*it)->pass_fun_to_part(fun);
    
  }
}
void hash_shelf::pass_fun_to_part(void(particle_base::*fun)())
{
  vector<hash_box*>::iterator myend =  hash_.end();
  for(vector<hash_box*>::iterator it = hash_.begin();
      it!=myend;++it)
  {
    (*it)->pass_fun_to_part(fun);
    
  }
}
void hash_box::pass_fun_to_part(void(particle_base::*fun)())
{
  vector<particle_base*>::iterator myend = contents_.end();
  for(vector<particle_base*>::iterator it = contents_.begin();
      it!=myend;++it)
  {
    ((*it)->*fun)();
  }
}








void hash_case::pass_fun_to_part(void(particle_base::*fun)()const)const
{
  vector<hash_shelf*>::const_iterator myend =  h_case_.end();
  for(vector<hash_shelf*>::const_iterator it = h_case_.begin();
      it!=myend;++it)
  {
    (*it)->pass_fun_to_part(fun);
    
  }
}
void hash_shelf::pass_fun_to_part(void(particle_base::*fun)()const)const
{
  vector<hash_box*>::const_iterator myend =  hash_.end();
  for(vector<hash_box*>::const_iterator it = hash_.begin();
      it!=myend;++it)
  {
    (*it)->pass_fun_to_part(fun);
    
  }
}
void hash_box::pass_fun_to_part(void(particle_base::*fun)()const)const
{
  vector<particle_base*>::const_iterator myend = contents_.end();
  for(vector<particle_base*>::const_iterator it = contents_.begin();
      it!=myend;++it)
  {
    ((*it)->*fun)();
  }
}






void hash_case::pass_fun_to_shelf(void(hash_shelf::*fun)())
{
  vector<hash_shelf*>::iterator myend =  h_case_.end();
  for(vector<hash_shelf*>::iterator it = h_case_.begin();
      it!=myend;++it)
  {
    ((*it)->*fun)();
    
  }
}
void hash_case::pass_fun_to_shelf(void(hash_shelf::*fun)()const)const
{
  vector<hash_shelf*>::const_iterator myend =  h_case_.end();
  for(vector<hash_shelf*>::const_iterator it = h_case_.begin();
      it!=myend;++it)
  {
    ((*it)->*fun)();
    
  }
}
