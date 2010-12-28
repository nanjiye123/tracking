//Copyright 2010 Thomas A Caswell
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
// 
//If you modify this Program, or any covered work, by linking or
//combining it with IPP (or a modified version of that library),
//containing parts covered by the terms of End User License Agreement
//for the Intel(R) Software Development Products, the licensors of
//this Program grant you additional permission to convey the resulting
//work.
//
//If you modify this Program, or any covered work, by linking or
//combining it with FreeImage (or a modified version of that library),
//containing parts covered by the terms of End User License Agreement
//for FreeImage Public License, the licensors of
//this Program grant you additional permission to convey the resulting
//work.

#ifndef IMAGE_SERIES
#define IMAGE_SERIES

#include "image_base.h"
#include "mm_md_parser.h"
namespace utilities
{


class Image_series:public Image_base
{
public:
  Image_series(const std::string & base_name,int padding);
  ~Image_series();
  void select_plane(unsigned int plane);
  const WORD * get_plane_pixels();
  Md_store * get_plane_md() ;
  Tuple<unsigned int,2> get_plane_dims();
  WORD get_plate_scan_step();
private:
  
  std::string base_name_;
  unsigned int cur_plane_;
  
  bool image_open_;
  
  fipMultiPage src_;
  fipImage image_;
  Mm_md_parser mm_md_p_;
 
  int padding_;
  
};

std::string format_name(const std::string & base_name,unsigned int plane,int padding);  
}


  
  
#endif