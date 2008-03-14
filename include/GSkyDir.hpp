/***************************************************************************
 *          GSkyDir.hpp  -  Class that implements a sky direction          *
 * ----------------------------------------------------------------------- *
 *  copyright            : (C) 2008 by Jurgen Knodlseder                   *
 * ----------------------------------------------------------------------- *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/
/**
 * @file GSkyDir.hpp
 * @brief GSkyDir class definition.
 * @author J. Knodlseder
 */

#ifndef GSKYDIR_HPP
#define GSKYDIR_HPP

/* __ Includes ___________________________________________________________ */

/* __ Namespaces _________________________________________________________ */


/***********************************************************************//**
 * @class GSkyDir
 *
 * @brief GSkyDir class interface defintion
 ***************************************************************************/
class GSkyDir {

    // I/O friends
    friend ostream& operator<< (ostream& os, const GSkyDir& dir);

public:
    // Constructors and destructors
    GSkyDir();
    GSkyDir(const GSkyDir& dir);
    virtual ~GSkyDir();

    // Operators
    GSkyDir& operator= (const GSkyDir& dir);

    // Methods
    void   radec(const double& ra, const double& dec);
    void   lb(const double& l, const double& b);
    double l(void);
    double b(void);
    double ra(void);
    double dec(void);

private:
    // Private methods
    void init_members(void);
    void copy_members(const GSkyDir& dir);
    void free_members(void);
    void equ2gal(void);
    void gal2equ(void);

    // Private data area
    int    m_has_lb;     //!< Has galactic coordinates
    int    m_has_radec;  //!< Has equatorial coordinates
    double m_l;          //!< Galactic longitude in radians
    double m_b;          //!< Galactic latitude in radians
    double m_ra;         //!< Right Ascension in radians
    double m_dec;        //!< Declination in radians
};

#endif /* GSKYDIR_HPP */
