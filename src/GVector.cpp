/***************************************************************************
 *                       GVector.cpp  -  vector class                      *
 * ----------------------------------------------------------------------- *
 *  copyright            : (C) 2006 by Jurgen Knodlseder                   *
 * ----------------------------------------------------------------------- *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

/* __ Includes ___________________________________________________________ */
#include "GVector.hpp"

/* __ Namespaces _________________________________________________________ */
using namespace std;


/*==========================================================================
 =                                                                         =
 =                      GVector constructors/destructors                   =
 =                                                                         =
 ==========================================================================*/

/***************************************************************************
 *                              Constructor                                *
 ***************************************************************************/
GVector::GVector(int num)
{
  // Throw exception if requested vector length is zero
  if (num == 0)
    throw GException::empty("GVector constructor");
	
  // Allocate vector array. Throw exception if allocation failed
  m_data = new double[num];
  if (m_data == NULL)
	throw GException::mem_alloc("GVector constructor", num);
	
  // Store vector size and initialize elements to 0.0
  m_num = num;
  for (int i = 0; i < m_num; ++i)
    m_data[i] = 0.0;
	
  // Return
  return;
}


/***************************************************************************
 *                            Copy constructor                             *
 ***************************************************************************/
GVector::GVector(const GVector& v)
{
  // Allocate vector array. Throw exception if allocation failed
  m_data = new double[v.m_num];
  if (m_data == NULL)
	throw GException::mem_alloc("GVector copy constructor", v.m_num);

  // Store vector size and copy elements
  m_num = v.m_num;
  for (int i = 0; i < m_num; ++i)
    m_data[i] = v.m_data[i];
	
  // Return
  return;
}


/***************************************************************************
 *                               Destructor                                *
 ***************************************************************************/
GVector::~GVector()
{
  // Deallocate only if memory has indeed been allocated
  if (m_data != NULL) delete[] m_data;

  // Return
  return;
}


/*==========================================================================
 =                                                                         =
 =                            GVector operators                            =
 =                                                                         =
 ==========================================================================*/

/***************************************************************************
 *                       GVector assignment operator                       *
 ***************************************************************************/
GVector& GVector::operator= (const GVector& v)
{
  // Assign only if not identical
  if (this != &v) {
  
    // First delete old data if it exists
    if (m_data != NULL) delete [] m_data;
	
    // Allocate vector array. Throw exception if allocation failed
    m_data = new double[v.m_num];
    if (m_data == NULL)
	  throw GException::mem_alloc("GVector assignment operator", v.m_num);

    // Store vector size and copy elements
    m_num = v.m_num;
    for (int i = 0; i < m_num; ++i)
      m_data[i] = v.m_data[i];
  }
  
  // Return vector
  return *this;
}


/*==========================================================================
 =                                                                         =
 =                         GVector member functions                        =
 =                                                                         =
 ==========================================================================*/

/***************************************************************************
 *                   Returns number of non-zeros in vector                 *
 ***************************************************************************/
int GVector::non_zeros() const
{
  // Initialise number of non-zeros
  int non_zeros = 0;
  
  // Gather all non-zero elements
  for (int i = 0; i < m_num; ++i) {
    if (m_data[i] != 0.0)
	  non_zeros++;
  }
  
  // Return number of non-zero elements
  return non_zeros;
}


/*==========================================================================
 =                                                                         =
 =                         GVector private functions                       =
 =                                                                         =
 ==========================================================================*/

/*==========================================================================
 =                                                                         =
 =                              GVector friends                            =
 =                                                                         =
 ==========================================================================*/

/***************************************************************************
 *                          GVector output operator                        *
 ***************************************************************************/
ostream& operator<< (ostream& os, const GVector& v)
{
  for (int i = 0; i < v.m_num; ++i) {
    os << v(i);
	if (i != v.m_num-1)
	  os << ", ";
  }
  return os;
}


/***************************************************************************
 *                           GVector cross product                         *
 ***************************************************************************/
GVector cross(const GVector &a, const GVector &b)
{
  if (a.m_num != b.m_num)
    throw GVector::vector_mismatch("GVector cross product", a.m_num, b.m_num);
  if (a.m_num != 3)
    throw GVector::vector_bad_cross_dim(a.m_num);
  GVector result(3);
  result(0) = a.m_data[1]*b.m_data[2] - a.m_data[2]*b.m_data[1];
  result(1) = a.m_data[2]*b.m_data[0] - a.m_data[0]*b.m_data[2];
  result(2) = a.m_data[0]*b.m_data[1] - a.m_data[1]*b.m_data[0];
  return result;
}


/*==========================================================================
 =                                                                         =
 =                         GVector exception classes                       =
 =                                                                         =
 ==========================================================================*/

/***************************************************************************
 *                          Vector index out of range                      *
 ***************************************************************************/
GVector::out_of_range::out_of_range(string origin, int inx, int elements)
{
  m_origin = origin;
  if (elements > 0) {
    ostringstream s_inx;
    ostringstream s_elements;
    s_inx      << inx;
    s_elements << elements-1;
    m_message = "Vector index (" + s_inx.str() + ") out of range [0," + 
                s_elements.str() + "]";
  }
  else {
    m_message = "Empty vector";
  }
}


/***************************************************************************
 *                          Vector dimensions differ                       *
 ***************************************************************************/
GVector::vector_mismatch::vector_mismatch(string origin, int size1, int size2)
{
  m_origin = origin;
  ostringstream s_size1;
  ostringstream s_size2;
  s_size1 << size1;
  s_size2 << size2;
  m_message = "Vector dimensions differ (" + s_size1.str() + " <-> " + 
              s_size2.str() + ")";
}


/***************************************************************************
 *                   Invalid vector dimension for cross product            *
 ***************************************************************************/
GVector::vector_bad_cross_dim::vector_bad_cross_dim(int elements)
{
  ostringstream s_elements;
  s_elements << elements;
  m_message = "Vector cross product only defined for 3 dimensions but vector size is " + 
              s_elements.str(); 
}
