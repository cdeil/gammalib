/***************************************************************************
 *            GLATInstDir.cpp  -  LAT instrument direction class           *
 * ----------------------------------------------------------------------- *
 *  copyright (C) 2010-2011 by Jurgen Knodlseder                           *
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
 * @file GLATInstDir.cpp
 * @brief GLATInstDir class implementation.
 * @author J. Knodlseder
 */

/* __ Includes ___________________________________________________________ */
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#include "GLATInstDir.hpp"
#include "GTools.hpp"

/* __ Method name definitions ____________________________________________ */

/* __ Macros _____________________________________________________________ */

/* __ Coding definitions _________________________________________________ */

/* __ Debug definitions __________________________________________________ */

/* __ Prototypes _________________________________________________________ */

/*==========================================================================
 =                                                                         =
 =                         Constructors/destructors                        =
 =                                                                         =
 ==========================================================================*/

/***********************************************************************//**
 * @brief Void constructor
 ***************************************************************************/
GLATInstDir::GLATInstDir(void) : GInstDir()
{
    // Initialise class members
    init_members();

    // Return
    return;
}


/***********************************************************************//**
 * @brief GSkyDir constructor
 *
 * @param[in] dir Sky direction.
 *
 * Construct LAT instrument direction from sky direction.
 ***************************************************************************/
GLATInstDir::GLATInstDir(const GSkyDir& dir) : GInstDir()
{
    // Initialise class members
    init_members();

    // Assign sky direction
    m_dir = dir;

    // Return
    return;
}


/***********************************************************************//**
 * @brief Copy constructor
 *
 * @param[in] dir Instrument direction.
 ***************************************************************************/
GLATInstDir::GLATInstDir(const GLATInstDir& dir) : GInstDir(dir)
{
    // Initialise class members
    init_members();

    // Copy members
    copy_members(dir);

    // Return
    return;
}


/***********************************************************************//**
 * @brief Destructor
 ***************************************************************************/
GLATInstDir::~GLATInstDir(void)
{
    // Free members
    free_members();

    // Return
    return;
}


/*==========================================================================
 =                                                                         =
 =                                Operators                                =
 =                                                                         =
 ==========================================================================*/

/***********************************************************************//**
 * @brief Assignment operator
 *
 * @param[in] dir Instrument direction.
 ***************************************************************************/
GLATInstDir& GLATInstDir::operator= (const GLATInstDir& dir)
{
    // Execute only if object is not identical
    if (this != &dir) {

        // Copy base class members
        this->GInstDir::operator=(dir);

        // Free members
        free_members();

        // Initialise private members
        init_members();

        // Copy members
        copy_members(dir);

    } // endif: object was not identical

    // Return this object
    return *this;
}


/*==========================================================================
 =                                                                         =
 =                              Public methods                             =
 =                                                                         =
 ==========================================================================*/

/***********************************************************************//**
 * @brief Clear instance
 ***************************************************************************/
void GLATInstDir::clear(void)
{
    // Free members
    free_members();
    this->GInstDir::free_members();

    // Initialise private members
    this->GInstDir::init_members();
    init_members();

    // Return
    return;
}


/***********************************************************************//**
 * @brief Clone instance
 ***************************************************************************/
GLATInstDir* GLATInstDir::clone(void) const
{
    return new GLATInstDir(*this);
}


/***********************************************************************//**
 * @brief Compute angular distance between instrument directions in radians
 *
 * @param[in] dir Instrument direction.
 ***************************************************************************/
double GLATInstDir::dist(const GLATInstDir& dir) const
{
    // Assign sky direction from instrument direction
    GSkyDir sky;
    double  ra  = dir.ra();
    double  dec = dir.dec();
    sky.radec(ra,dec);

    // Compute distance
    double dist = m_dir.dist(sky);

    // Return distance
    return dist;
}


/***********************************************************************//**
 * @brief Compute angular distance between instrument directions in degrees
 *
 * @param[in] dir Instrument direction.
 ***************************************************************************/
double GLATInstDir::dist_deg(const GLATInstDir& dir) const
{
    // Return distance in degrees
    return (dist(dir) * rad2deg);
}


/***********************************************************************//**
 * @brief Print instrument direction information
 ***************************************************************************/
std::string GLATInstDir::print(void) const
{
    // Initialise result string
    std::string result;

    // Append instrument direction
    result.append("RA="+str(ra_deg())+", DEC="+str(dec_deg()));

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
void GLATInstDir::init_members(void)
{
    // Initialise members
    m_dir.clear();

    // Return
    return;
}


/***********************************************************************//**
 * @brief Copy class members
 *
 * @param[in] dir Instrument direction.
 ***************************************************************************/
void GLATInstDir::copy_members(const GLATInstDir& dir)
{
    // Copy attributes
    m_dir = dir.m_dir;

    // Return
    return;
}


/***********************************************************************//**
 * @brief Delete class members
 ***************************************************************************/
void GLATInstDir::free_members(void)
{
    // Return
    return;
}


/*==========================================================================
 =                                                                         =
 =                                 Friends                                 =
 =                                                                         =
 ==========================================================================*/
