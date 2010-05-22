/***************************************************************************
 *              GEventAtom.hpp  -  Event atom abstract base class          *
 * ----------------------------------------------------------------------- *
 *  copyright (C) 2009-2010 by Jurgen Knodlseder                           *
 * ----------------------------------------------------------------------- *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/
/**
 * @file GEventAtom.hpp
 * @brief GEventAtom abstract base class interface definition.
 * @author J. Knodlseder
 */

#ifndef GEVENTATOM_HPP
#define GEVENTATOM_HPP

/* __ Includes ___________________________________________________________ */
#include "GEvent.hpp"
#include "GTime.hpp"
#include "GEnergy.hpp"
#include "GSkyDir.hpp"
#include "GModels.hpp"
#include "GVector.hpp"


/***********************************************************************//**
 * @class GEventAtom
 *
 * @brief Abstract interface for the event atom class
 ***************************************************************************/
class GEventAtom : public GEvent {

    // Friend classes
    friend class GEvents;

    // I/O friends
    friend std::ostream& operator<< (std::ostream& os, const GEventAtom& atom);

public:
    // Constructors and destructors
    GEventAtom();
    GEventAtom(const GEventAtom& atom);
    virtual ~GEventAtom();

    // Operators
    virtual GEventAtom& operator= (const GEventAtom& atom);

    // Virtual methods
    virtual double model(GModels& models) = 0;
    virtual double model(GModels& models, GVector* gradient) = 0;

    // Implemented methods
    double   counts(void) const { return 1.0; }
    GSkyDir* dir(void) { return &m_dir; }
    GEnergy* energy(void) { return &m_energy; }
    GTime*   time(void) { return &m_time; }
    bool     isatom(void) const { return true; }
    bool     isbin(void) const { return false; }
    
protected:
    // Protected methods
    void                init_members(void);
    void                copy_members(const GEventAtom& atom);
    void                free_members(void);
    virtual GEventAtom* clone(void) const = 0;

    // Protected data area
    GTime   m_time;                //!< Event time
	GEnergy m_energy;              //!< Event energy
    GSkyDir m_dir;                 //!< Arrivial direction

private:
};

#endif /* GEVENTATOM_HPP */
