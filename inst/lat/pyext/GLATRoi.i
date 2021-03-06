/***************************************************************************
 *               GLATRoi.i  -  LAT region of interest class                *
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
 * @file GLATRoi.i
 * @brief GLATRoi class python bindings
 * @author J. Knodlseder
 */
%{
/* Put headers and other declarations here that are needed for compilation */
#include "GLATRoi.hpp"
%}


/***********************************************************************//**
 * @class GLATRoi
 *
 * @brief Python bindings for the LAT region of interest class
 ***************************************************************************/
class GLATRoi : public GRoi {
public:
    // Constructors and destructors
    GLATRoi(void);
    GLATRoi(const GLATRoi& roi);
    virtual ~GLATRoi(void);

    // Implemented pure virtual base class methods
    void        clear(void);
    GLATRoi*    clone(void) const;

    // Other methods
    GLATInstDir centre(void) const { return m_centre; }
    double      radius(void) const { return m_radius; }
    void        centre(const GLATInstDir& centre) { m_centre=centre; return; }
    void        radius(const double& radius) { m_radius=radius; return; }
};


/***********************************************************************//**
 * @brief GLATRoi class extension
 ***************************************************************************/
%extend GLATRoi {
    GLATRoi copy() {
        return (*self);
    }
};


/***********************************************************************//**
 * @brief GLATRoi type casts
 ***************************************************************************/
%inline %{
    GLATRoi* cast_GLATRoi(GRoi* roi) {
        return dynamic_cast<GLATRoi*>(roi);
    }
%}
