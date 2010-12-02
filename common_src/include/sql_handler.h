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

#ifndef SQL_HANDLER
#define SQL_HANDLER

#include<string>

// forward definition of sqlite3 class do get around include the header for sqlite3 in
// a lot of my code.
struct sqlite3;


namespace utilities
{
class Md_store;

/**
   Enumeration for functions that maps to the tables in the database
 */
typedef enum F_TYPE{
  F_NOFUNCTION =0,
  F_IDEN ,
  F_TRACKING,
  F_MSD,
}F_TYPE
    
/**
   Class to wrap around the sqlite3 interface to deal with making connections to
   data basese, cleaning up after them etc.  Will have both functions do to 
   specific things, ie add a computation, and a function that eats a string.
 */
class SQL_handler
{
public:
  /**
     Constructor.  Assumes a very specific database layout, see
     external documentation
   */
  SQL_handler();
  /**
     Destructor
   */
  ~SQL_handler();
  
  
  /**
     Opens the data base connection
     @param [in] db_name the full path of data base file. 
  */
  void open_connection(const std::string& db_name);
 
  /**
     Closes the connection
   */
  void close_connection();
  
  /**
     Adds an entry to the comps table, open a transaction, and return the comp_key

     @param [in] dset_key the key of the data set the function is
     working on 
     @param [out] comp_key the key of the computation,
     taken from the database 
     @param [in] f_type the type of computation being done.  The guts
     of this object need to know to handle the meta-data for each
     function.
     @return the computation key
   */
  int start_comp(int dset_key,
		 int & comp_key,
		 F_TYPE f_type
		 )
  /**
     Adds the function specific meta-data to the table
   */
  void add_mdata(const Md_store & md_store);
  
  /**
     Commits the transactions
   */
  void commit();
  /**
     Rolls back the transaction
   */
  void rollback();
  
private:
  /**
     Pointer to the data base object
   */
  sqlite3 * db_;
  
  /**
     Flag if the connection is open
   */
  bool conn_open_;
  /**
     Flag if there is an open transaction
   */
  bool trans_open_;
  /**
     Type of the current transaction
   */
  F_TYPE trans_type_;
  
};

}


#endif
