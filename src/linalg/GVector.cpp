/***************************************************************************
 *                       GVector.cpp  -  Vector class                      *
 * ----------------------------------------------------------------------- *
 *  copyright (C) 2006-2012 by Juergen Knoedlseder                         *
 * ----------------------------------------------------------------------- *
 *                                                                         *
 *  This program is free software: you can redistribute it and/or modify   *
 *  it under the terms of the GNU General Public License as published by   *
 *  the Free Software Foundation, either version 3 of the License, or      *
 *  (at your option) any later version.                                    *
 *                                                                         *
 *  This program is distributed in the hope that it will be useful,        *
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of         *
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          *
 *  GNU General Public License for more details.                           *
 *                                                                         *
 *  You should have received a copy of the GNU General Public License      *
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.  *
 *                                                                         *
 ***************************************************************************/
/**
 * @file GVector.cpp
 * @brief Vector class implementation
 * @author Juergen Knoedlseder
 */

/* __ Includes ___________________________________________________________ */
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#include "GVector.hpp"
#include "GTools.hpp"


/* __ Method name definitions ____________________________________________ */
#define G_ACCESS                                  "GVector::operator[](int&)"
#define G_CROSS                                      "cross(GVector,GVector)"


/*==========================================================================
 =                                                                         =
 =                         Constructors/destructors                        =
 =                                                                         =
 ==========================================================================*/

/***********************************************************************//**
 * @brief Void vector constructor
 ***************************************************************************/
GVector::GVector(void)
{
    // Initialise class members
    init_members();

    // Return
    return;
}


/***********************************************************************//**
 * @brief Vector constructor
 *
 * @param[in] num Number of elements in vector.
 *
 * Initialises a vector with num elements (all values are set to 0).
 ***************************************************************************/
GVector::GVector(const int& num)
{
    // Initialise class members
    init_members();

    // Store vector size
    m_num = num;

    // Allocate vector (filled with 0)
    alloc_members();

    // Return
    return;
}


/***********************************************************************//**
 * @brief Single element vector constructor
 *
 * @param[in] a Value of first and single vector element.
 *
 * Initialises 1-element vector.
 ***************************************************************************/
GVector::GVector(const double& a)
{
    // Initialise class members
    init_members();

    // Store vector size
    m_num = 1;

    // Allocate vector
    alloc_members();

    // Set value
    m_data[0] = a;

    // Return
    return;
}


/***********************************************************************//**
 * @brief Two elements vector constructor
 *
 * @param[in] a Value of first vector element.
 * @param[in] b Value of second vector element.
 *
 * Initialises 2-elements vector.
 ***************************************************************************/
GVector::GVector(const double& a, const double& b)
{
    // Initialise class members
    init_members();

    // Store vector size
    m_num = 2;

    // Allocate vector
    alloc_members();

    // Set values
    m_data[0] = a;
    m_data[1] = b;

    // Return
    return;
}


/***********************************************************************//**
 * @brief Three elements vector constructor
 *
 * @param[in] a Value of first vector element.
 * @param[in] b Value of second vector element.
 * @param[in] c Value of third vector element.
 *
 * Initialises 3-elements vector.
 ***************************************************************************/
GVector::GVector(const double& a, const double& b, const double& c)
{
    // Initialise class members
    init_members();

    // Store vector size
    m_num = 3;

    // Allocate vector
    alloc_members();

    // Set values
    m_data[0] = a;
    m_data[1] = b;
    m_data[2] = c;

    // Return
    return;
}


/***********************************************************************//**
 * @brief Copy constructor
 *
 * @param[in] v Vector from which class should be instantiated.
 ***************************************************************************/
GVector::GVector(const GVector& v)
{
    // Initialise class members
    init_members();

    // Copy members
    copy_members(v);

    // Return
    return;
}


/***********************************************************************//**
 * @brief Destructor
 ***************************************************************************/
GVector::~GVector(void)
{
    // Free members
    free_members();

    // Return
    return;
}


/*==========================================================================
 =                                                                         =
 =                               Operators                                 =
 =                                                                         =
 ==========================================================================*/

/***********************************************************************//**
 * @brief Assignment operator
 *
 * @param[in] v GVector instance to be assigned
 ***************************************************************************/
GVector& GVector::operator= (const GVector& v)
{
    // Execute only if object is not identical
    if (this != &v) {

        // Free members
        free_members();

        // Initialise private members
        init_members();

        // Copy members
        copy_members(v);

    } // endif: object was not identical

    // Return this object
    return *this;
}


/***********************************************************************//**
 * @brief Vector element access operator
 *
 * @param[in] inx Vector element index to be accessed [0,...,size()-1]
 *
 * @exception GException::out_of_range
 *            Element index is out of range.
 ***************************************************************************/
double& GVector::operator[](const int& inx)
{
    // Compile option: raise an exception if index is out of range
    #if defined(G_RANGE_CHECK)
    if (inx < 0 || inx >= size()) {
        throw GException::out_of_range(G_ACCESS, inx, size()-1);
    }
    #endif

    // Return vector element
    return m_data[inx];
}


/***********************************************************************//**
 * @brief Vector element access operator (const variant)
 *
 * @param[in] inx Vector element index to be accessed [0,...,size()-1]
 *
 * @exception GException::out_of_range
 *            Element index is out of range.
 ***************************************************************************/
const double& GVector::operator[](const int& inx) const
{
    // Compile option: raise an exception if index is out of range
    #if defined(G_RANGE_CHECK)
    if (inx < 0 || inx >= size()) {
        throw GException::out_of_range(G_ACCESS, inx, size()-1);
    }
    #endif

    // Return vector element
    return m_data[inx];
}


/*==========================================================================
 =                                                                         =
 =                             Public methods                              =
 =                                                                         =
 ==========================================================================*/

/***********************************************************************//**
 * @brief Clear instance
 ***************************************************************************/
void GVector::clear(void)
{
    // Free members
    free_members();

    // Initialise private members
    init_members();
    
    // Return
    return; 
}


/***********************************************************************//**
 * @brief Clone object
 ***************************************************************************/
GVector* GVector::clone(void) const
{
    // Clone this image
    return new GVector(*this);
}


/***********************************************************************//**
 * @brief Returns number of non-zero elements in vector
 ***************************************************************************/
int GVector::non_zeros(void) const
{
    // Initialise number of non-zeros
    int non_zeros = 0;

    // Gather all non-zero elements
    for (int i = 0; i < m_num; ++i) {
        if (m_data[i] != 0.0) {
            non_zeros++;
        }
    }

    // Return number of non-zero elements
    return non_zeros;
}


/***********************************************************************//**
 * @brief Print vector information
 ***************************************************************************/
std::string GVector::print(void) const
{
    // Initialise result string
    std::string result = "(";

    // Put all elements in stream
    for (int i = 0; i < m_num; ++i) {
        result += str((*this)[i]);
        if (i != m_num-1) {
            result += ", ";
        }
    }

    // Append )
    result += ")";

    // Return result
    return result;
}


/*==========================================================================
 =                                                                         =
 =                             Private methods                             =
 =                                                                         =
 ==========================================================================*/

/***********************************************************************//**
 * @brief Initialise class members
 ***************************************************************************/
void GVector::init_members(void)
{
    // Initialise members
    m_num  = 0;
    m_data = NULL;

    // Return
    return;
}


/***********************************************************************//**
 * @brief Allocate vector
 ***************************************************************************/
void GVector::alloc_members(void)
{
    // Continue only if vector has non-zero length
    if (m_num > 0) {

        // Allocate vector and initialize elements to 0
        m_data = new double[m_num];
        for (int i = 0; i < m_num; ++i) {
            m_data[i] = 0.0;
        }

    } // endif: vector had non-zero length

    // Return
    return;
}


/***********************************************************************//**
 * @brief Copy class members
 *
 * @param[in] v Vector from which members should be copied.
 ***************************************************************************/
void GVector::copy_members(const GVector& v)
{
    // Copy attributes
    m_num = v.m_num;

    // Copy elements
    if (m_num > 0) {
        alloc_members();
        for (int i = 0; i <  m_num; ++i) {
            m_data[i] = v.m_data[i];
        }
    }

    // Return
    return;
}


/***********************************************************************//**
 * @brief Delete class members
 ***************************************************************************/
void GVector::free_members(void)
{
    // Free memory
    if (m_data != NULL) delete m_data;

    // Signal free pointers
    m_data = NULL;

    // Return
    return;
}


/*==========================================================================
 =                                                                         =
 =                                 Friends                                 =
 =                                                                         =
 ==========================================================================*/


/***********************************************************************//**
 * @brief GVector cross product
 *
 * @param[in] a First vector for cross product.
 * @param[in] b Second vector for cross product.
 *
 * @exception GException::vector_mismatch
 *            Mismatch between vector size.
 *
 * Computes the cross product between two 3-element vectors (note that the
 * cross product is only defined for 3-element vectors).
 ***************************************************************************/
GVector cross(const GVector &a, const GVector &b)
{
    // Verify that vectors have same dimensions
    if (a.m_num != b.m_num) {
        throw GException::vector_mismatch(G_CROSS, a.m_num, b.m_num);
    }

    // Verify that vectors have 3 elements
    if (a.m_num != 3) {
       throw GException::vector_bad_cross_dim(G_CROSS, a.m_num);
    }

    // Compute cross product
    GVector result(3);
    result.m_data[0] = a.m_data[1]*b.m_data[2] - a.m_data[2]*b.m_data[1];
    result.m_data[1] = a.m_data[2]*b.m_data[0] - a.m_data[0]*b.m_data[2];
    result.m_data[2] = a.m_data[0]*b.m_data[1] - a.m_data[1]*b.m_data[0];

    // Return result
    return result;
}
