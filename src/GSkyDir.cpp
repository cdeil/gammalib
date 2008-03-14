/***************************************************************************
 *          GSkyDir.cpp  -  Class that implements a sky direction          *
 * ----------------------------------------------------------------------- *
 *  copyright            : (C) 2008 by Jurgen Knodlseder                   *
 * ----------------------------------------------------------------------- *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 * ----------------------------------------------------------------------- *
 ***************************************************************************/

/* __ Includes ___________________________________________________________ */
#include "GException.hpp"
#include "GTools.hpp"
#include "GSkyDir.hpp"

/* __ Namespaces _________________________________________________________ */

/* __ Method name definitions ____________________________________________ */

/* __ Macros _____________________________________________________________ */

/* __ Coding definitions _________________________________________________ */

/* __ Debug definitions __________________________________________________ */



/*==========================================================================
 =                                                                         =
 =                      GSkyDir constructors/destructors                   =
 =                                                                         =
 ==========================================================================*/

/***********************************************************************//**
 * @brief Constructor
 ***************************************************************************/
GSkyDir::GSkyDir()
{
    // Initialise class members for clean destruction
    init_members();

    // Return
    return;
}


/***********************************************************************//**
 * @brief Copy constructor
 *
 * @param[in] dir Sky direction from which class should be instantiated.
 ***************************************************************************/
GSkyDir::GSkyDir(const GSkyDir& dir)
{
    // Initialise class members for clean destruction
    init_members();

    // Copy members
    copy_members(dir);

    // Return
    return;
}


/***********************************************************************//**
 * @brief Destructor
 ***************************************************************************/
GSkyDir::~GSkyDir()
{
    // Free members
    free_members();

    // Return
    return;
}


/*==========================================================================
 =                                                                         =
 =                             GSkyDir operators                           =
 =                                                                         =
 ==========================================================================*/

/***********************************************************************//**
 * @brief Assignment operator
 ***************************************************************************/
GSkyDir& GSkyDir::operator= (const GSkyDir& dir)
{
    // Execute only if object is not identical
    if (this != &dir) {

        // Free members
        free_members();

        // Initialise private members for clean destruction
        init_members();

        // Copy members
        copy_members(dir);

    } // endif: object was not identical

    // Return this object
    return *this;
}


/*==========================================================================
 =                                                                         =
 =                          GSkyDir public methods                         =
 =                                                                         =
 ==========================================================================*/

/***********************************************************************//**
 * @brief Set equatorial sky direction
 *
 * @param[in] ra Right Ascension in radians.
 * @param[in] dec Declination in radians.
 ***************************************************************************/
void GSkyDir::radec(const double& ra, const double& dec)
{
    // Set attributes
    m_has_lb    = 0;
    m_has_radec = 1;

    // Set direction
    m_ra  = ra;
    m_dec = dec;
    
    // Return
    return;
}


/***********************************************************************//**
 * @brief Set galactic sky direction
 *
 * @param[in] l Galactic longitude in radians.
 * @param[in] b Galactic latitude in radians.
 ***************************************************************************/
void GSkyDir::lb(const double& l, const double& b)
{
    // Set attributes
    m_has_lb    = 1;
    m_has_radec = 0;

    // Set direction
    m_l = l;
    m_b = b;
    
    // Return
    return;
}


/***********************************************************************//**
 * @brief Returns galactic longitude in radians
 ***************************************************************************/
double GSkyDir::l(void)
{
    // If we have no galactic coordinates then get them now
    if (!m_has_lb && m_has_radec)
        equ2gal();
    
    // Return galactic longitude
    return m_l;
}


/***********************************************************************//**
 * @brief Returns galactic latitude in radians
 ***************************************************************************/
double GSkyDir::b(void)
{
    // If we have no galactic coordinates then get them now
    if (!m_has_lb && m_has_radec)
        equ2gal();
    
    // Return galactic latitude
    return m_b;
}


/***********************************************************************//**
 * @brief Returns Right Ascension in radians
 ***************************************************************************/
double GSkyDir::ra(void)
{
    // If we have no equatorial coordinates then get them now
    if (!m_has_radec && m_has_lb)
        gal2equ();
    
    // Return Right Ascension
    return m_ra;
}


/***********************************************************************//**
 * @brief Returns Declination in radians
 ***************************************************************************/
double GSkyDir::dec(void)
{
    // If we have no equatorial coordinates then get them now
    if (!m_has_radec && m_has_lb)
        gal2equ();
    
    // Return Declination
    return m_dec;
}


/*==========================================================================
 =                                                                         =
 =                          GSkyDir private methods                        =
 =                                                                         =
 ==========================================================================*/

/***********************************************************************//**
 * @brief Initialise class members
 ***************************************************************************/
void GSkyDir::init_members(void)
{
    // Initialise members
    m_has_lb    = 0;
    m_has_radec = 0;
    m_l         = 0.0;
    m_b         = 0.0;
    m_ra        = 0.0;
    m_dec       = 0.0;

    // Return
    return;
}


/***********************************************************************//**
 * @brief Copy class members
 *
 * @param[in] dir Sky direction from which members should be copied
 ***************************************************************************/
void GSkyDir::copy_members(const GSkyDir& dir)
{
    // Copy attributes
    m_has_lb    = dir.m_has_lb;
    m_has_radec = dir.m_has_radec;
    m_l         = dir.m_l;
    m_b         = dir.m_b;
    m_ra        = dir.m_ra;
    m_dec       = dir.m_dec;

    // Return
    return;
}


/***********************************************************************//**
 * @brief Delete class members
 ***************************************************************************/
void GSkyDir::free_members(void)
{
    // Free memory

    // Signal free pointers

    // Return
    return;
}


/***********************************************************************//**
 * @brief Convert equatorial to galactic coordinates
 *
 * @todo Needs to be implemented
 ***************************************************************************/
void GSkyDir::equ2gal(void)
{
    // Return
    return;
}


/***********************************************************************//**
 * @brief Convert galactic to equatorial coordinates
 *
 * @todo Needs to be implemented
 ***************************************************************************/
void GSkyDir::gal2equ(void)
{
    // Return
    return;
}


/*==========================================================================
 =                                                                         =
 =                              GSkyDir friends                            =
 =                                                                         =
 ==========================================================================*/

/***********************************************************************//**
 * @brief Output operator
 *
 * @param[in] os Output stream
 * @param[in] column Sky direction to put in output stream
 ***************************************************************************/
ostream& operator<< (ostream& os, const GSkyDir& dir)
{
    // Create coordinate system dependent output
    if (dir.m_has_lb)
        os << "(l,b)=(" << dir.m_l*rad2deg << "," << dir.m_b*rad2deg << ")";
    else if (dir.m_has_radec)
        os << "(RA,Dec)=(" << dir.m_ra*rad2deg << "," << dir.m_dec*rad2deg << ")";

    // Return output stream
    return os;
}


/*==========================================================================
 =                                                                         =
 =                      Other functions used by GSkyDir                    =
 =                                                                         =
 ==========================================================================*/
