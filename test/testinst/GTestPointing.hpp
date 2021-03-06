/***************************************************************************
 *          GTestPointing.hpp  -  Test pointing class                      *
 * ----------------------------------------------------------------------- *
 *  copyright (C) 2012 by Jean-Baptiste Cayrou                             *
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
 
#ifndef GTestPOINTING_HPP
#define GTestPOINTING_HPP

/* __ Includes ___________________________________________________________ */
#include "GPointing.hpp"


class GTestPointing : public GPointing {

public:
    // Constructors and destructors
    GTestPointing(void){
        init_members();
        return;
    }
    
    GTestPointing(const GTestPointing& pnt) 
    {
        init_members();
        copy_members(pnt);
        return;
    }
    
    virtual ~GTestPointing(void){
        free_members();
        return;
    }

    // Operators
    GTestPointing& operator= (const GTestPointing& pnt){
        // Execute only if object is not identical
        if (this != &pnt) {

            // Copy base class members
            this->GPointing::operator=(pnt);

            // Free members
            free_members();

            // Initialise private members
            init_members();

            // Copy members
            copy_members(pnt);

        } // endif: object was not identical

    // Return this object
        return *this;
    }

    // Methods
    void clear(void){
        // Free members
        free_members();
        this->GPointing::free_members();

        // Initialise private members
        this->GPointing::init_members();
        init_members();
        
        return;
    }
    
    GTestPointing*  clone(void) const{ return new GTestPointing(*this);}
    const GSkyDir& dir(void) const { return m_dir; }
    std::string    print(void) const{return "=== GTestPointing ===";}

protected:
    // Protected methods
    void init_members(void){
        m_dir.clear();
        return;
    }
    void copy_members(const GTestPointing& pnt){
        m_dir = pnt.m_dir;
        return;
    }
    void free_members(void){ return; }

    // Protected members
    GSkyDir m_dir;  //!< Pointing direction
};

#endif /* GTestPOINTING_HPP */
