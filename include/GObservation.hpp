/***************************************************************************
 *           GObservation.hpp  -  Observation abstract base class          *
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
 * @file GObservation.hpp
 * @brief GObservation abstract base class interface definition.
 * @author J. Knodlseder
 */

#ifndef GOBSERVATION_HPP
#define GOBSERVATION_HPP

/* __ Includes ___________________________________________________________ */
#include "GResponse.hpp"
#include "GData.hpp"

/* __ Namespaces _________________________________________________________ */


/***********************************************************************//**
 * @class GObservation
 *
 * @brief Abstract interface for the observation classes.
 ***************************************************************************/
class GObservation {

public:
    // Constructors and destructors
    GObservation();
    GObservation(const GObservation& obs);
    virtual ~GObservation();

    // Operators
    virtual GObservation& operator= (const GObservation& obs);

    // Methods
  
protected:
    // Protected methods
    void    init_members(void);
    void    copy_members(const GObservation& obs);
    void    free_members(void);
    virtual GObservation* clone(void) const = 0;

    // Protected data area
    std::string m_obsname;      //!< Name of observation
    int         m_num_response; //!< Number of associated response functions
	GResponse** m_response;     //!< Pointer to instrument response functions
	GData*      m_data;         //!< Pointer to associated data

private:
};

#endif /* GOBSERVATION_HPP */
