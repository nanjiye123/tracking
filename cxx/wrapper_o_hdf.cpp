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
#include <iostream>
#include <sstream>
#include <stdexcept>

#include "wrapper_o_hdf.h"
#include "H5Cpp.h"

//using namespace H5;

using utilities::Wrapper_o_hdf;

using std::string;
using std::set;
using std::vector;
using std::cout;
using std::endl;


using H5::H5File;
using H5::Group;
using H5::DataSpace;
using H5::H5File;
using H5::PredType;
using H5::CompType;
using H5::DataSet;
using H5::DSetCreatPropList;


Wrapper_o_hdf::Wrapper_o_hdf(const string& file_name,set<D_TYPE> d_add):
  part_count_(0),part_open_(false), wrapper_open_(false), frame_open_(false),
  part_index_(-1), frame_max_count_(-1), frame_index_(-1), new_hdf_(true),over_write_(true),
  file_(NULL), file_name_(file_name),
  d_types_add_(d_add),d_types_check_(),d_types_already_(), 
  float_data_(),int_data_(),complex_data_()
{
  // open file
  // open frame000000
  // loop through the data sets and extract the types of data they already have
  // close file
  
  // logic to make sure that there is no over lap between the add and
  // contains sets

  // actions depend on settings of the bools 

  // make sure that all of the types in check are in file already

}


void Wrapper_o_hdf::initialize_wrapper()
{

  
  file_ = new H5File(file_name_,H5F_ACC_RDWR);
  wrapper_open_ = true;
}

void Wrapper_o_hdf::open_frame(int frame,int count)
{
  if(!wrapper_open_)
    throw "wrapper not open";
  
 
  frame_index_ = frame;
  frame_max_count_ = count;
  int_map_   = Data_map();
  float_map_ = Data_map();
  complex_map_=Data_map();
    
  int i_c=0,f_c=0,c_c = 0;
   
  // go through add set and allocate arrays for storing data
  for(set<D_TYPE>::const_iterator it = d_types_add_.begin(); 
      it!=d_types_add_.end();++it)
  { 
    
    switch(v_type(*it))
    {
    case V_INT:
      int_data_.push_back(new int[frame_max_count_]);
      int_map_.set_lookup(*it,i_c++);
      break;
    case V_FLOAT:
      float_data_.push_back(new float[frame_max_count_]);
      float_map_.set_lookup(*it,f_c++);
      break;
    case V_COMPLEX:
      complex_data_.push_back(new complex_t[frame_max_count_]);
      complex_map_.set_lookup(*it,c_c++);
      break;
    case V_ERROR:
      throw "type not registered, wrapper_o_hdf";
    }
  }
  
  // ititialize the tmp_data to something
  

  frame_open_ = true;  
}

void Wrapper_o_hdf::open_particle(int ind)
{
  if(!frame_open_)
    throw "frame not open";
  if(part_open_)
    throw "particle already open";
  
  if(new_hdf_)
  {
    part_index_ = part_count_++;
  }
  else
  {
    part_index_ = ind;
    part_count_++;
  }
  
  if(!(part_count_<frame_max_count_))
    throw "trying to add too many particles to frame";
  
  part_open_ = true;
}

void Wrapper_o_hdf::set_value(utilities::D_TYPE type, float val)
{
  if(!part_open_)
    throw "particle not open";
  // shove data into the proper place in the temp arrays
  float_data_.at(float_map_(type))[part_index_] = val;
}

void Wrapper_o_hdf::set_value(utilities::D_TYPE type, std::complex<float> val)
{
  if(!part_open_)
    throw "particle not open";
  // shove data into the proper place in the temp arrays
  complex_t tmp_val;
  tmp_val.re = val.real();
  tmp_val.im = val.imag();
  complex_data_.at(complex_map_(type))[part_index_] =tmp_val;

}

void Wrapper_o_hdf::set_value(utilities::D_TYPE type, int val)
{
  if(!part_open_)
    throw "particle not open";
  // shove data into the proper place in the temp arrays
  int_data_.at(int_map_(type))[part_index_] = val;
}

       
void Wrapper_o_hdf::close_particle()
{
  part_index_ = -1;
  part_open_ = false;
}

void Wrapper_o_hdf::close_frame()
{
  // make sure the particle is closed
  if(frame_open_)
  {
    if(part_open_)
    {
      close_particle();
    }
    if(part_count_ != frame_max_count_)
      throw "not enough particles added";
    no
    
    string frame_name_ = format_name(frame_index_);
    Group* group_ = new Group(file_->openGroup(frame_name_));
    
    // shove into file
    
    // for complex data types
    CompType ctype(sizeof(complex_t));
    ctype.insertMember("re",HOFFSET(complex_t,re),PredType::NATIVE_FLOAT);
    ctype.insertMember("im",HOFFSET(complex_t,im),PredType::NATIVE_FLOAT);
    
    // set up property lists for data sets
    hsize_t csize = 400;
    
    float fillvalue_f = 0;
    DSetCreatPropList plist_f;
    plist_f.setFillValue(PredType::NATIVE_FLOAT,&fillvalue_f);
    //     plist_f.setChunk(1,&csize);
    //     plist_f.setDeflate(9);
    

    int fillvalue_i = 0;
    DSetCreatPropList plist_i;
    plist_i.setFillValue(PredType::NATIVE_INT,&fillvalue_i);
    //     plist_i.setChunk(1,&csize);
    //     plist_i.setDeflate(9);
    
    csize = csize/2;
    complex_t fillvalue_c;
    fillvalue_c.im = 0;
    fillvalue_c.re = 0;
    DSetCreatPropList plist_c;
    plist_c.setFillValue(ctype,&fillvalue_c);
    // plist_c.setChunk(1,&csize);
    //     plist_c.setDeflate(9);

    hsize_t dim [] = {frame_max_count_};
    DataSpace space(1,dim);
    
    
    for(set<D_TYPE>::const_iterator it = d_types_add_.begin(); 
	it!=d_types_add_.end();++it)
    {
      DataSet * dset = NULL;
      //     int * tmp_ptr_i = NULL;
      //       float * tmp_ptr_f = NULL;
      
      switch(v_type(*it))
      {
	// integer data
      case V_INT:
	// 	cout<<*it<<':'<<DT2str_s(*it)<<endl;
	// 	cout<<int_map_(*it)<<endl;
	// 	cout<<int_data_.size()<<endl;
	// 	tmp_ptr_i = int_data_.at(int_map_(*it));
	// 	for(int j = 0;j<frame_max_count_;++j)
	// 	  cout<<tmp_ptr_i[j]<<'\t';
	// 	cout<<endl;

 	dset = new DataSet(group_->createDataSet(DT2str_s(*it),PredType::NATIVE_INT,space,plist_i));
	dset->write(int_data_.at(int_map_(*it)),PredType::NATIVE_INT);
	break;
	// float data
      case V_FLOAT:
	// 	cout<<*it<<':'<<DT2str_s(*it)<<endl;
	// 	cout<<float_map_(*it)<<endl;
	// 	cout<<float_data_.size()<<endl;
	//  	tmp_ptr_f = float_data_.at(float_map_(*it));
	//  	for(int j = 0;j<frame_max_count_;++j)
	//  	  cout<<tmp_ptr_f[j]<<'\t';
	//  	cout<<endl;
	
	dset = new DataSet(group_->createDataSet(DT2str_s(*it),PredType::NATIVE_FLOAT,space,plist_f));
	dset->write(float_data_.at(float_map_(*it)),PredType::NATIVE_FLOAT);
	break;
	// complex data
      case V_COMPLEX:
	dset = new DataSet(group_->createDataSet(DT2str_s(*it),ctype,space,plist_c));
	dset->write(complex_data_.at(complex_map_(*it)),ctype);
	
	break;
      default:
	throw "should not have hit default";
      }
      
      
      delete dset;
      
    }

    
    delete group_;
    group_ = NULL;
 
    // clean up
    for(vector<int*>::iterator it = int_data_.begin();
	it != int_data_.end();++it)
      delete [] *it;
    int_data_.clear();
    
    for(vector<float*>::iterator it = float_data_.begin();
	it != float_data_.end();++it)
      delete [] *it;
    float_data_.clear();
    
    for(vector<complex_t*>::iterator it = complex_data_.begin();
	it != complex_data_.end();++it)
      delete [] *it;
    complex_data_.clear();
    
    
    frame_open_ = false;

    
  }
}

  
void Wrapper_o_hdf::finalize_wrapper()
{
  if(wrapper_open_)
  {
    if(frame_open_)
    {
      close_frame();
    }
    delete file_;
    file_ = NULL;
    wrapper_open_ = false;
  }
}

       
void Wrapper_o_hdf::reset_wrapper(params * param)
{
  throw "not implemented";
}

       
void Wrapper_o_hdf::print()const
{
 throw "not implemented";
} 


Wrapper_o_hdf::~Wrapper_o_hdf()
{
  // clean up temporary arrays
  finalize_wrapper();
  
}


string Wrapper_o_hdf::format_name(int in)const
{
  std::ostringstream o;
  o.width(6);
  o.fill('0');
  o<<std::right<<in;
  return  "frame" + o.str();
}

  
