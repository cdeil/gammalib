/***************************************************************************
 *           GModelRadial.i  -  Abstract radial model base class           *
 * ----------------------------------------------------------------------- *
 *  copyright (C) 2011 by Jurgen Knodlseder                                *
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
 * @file GModelRadial.i
 * @brief Abstract radial model base class Python interface
 * @author J. Knodlseder
 */
%{
/* Put headers and other declarations here that are needed for compilation */
#include "GModelRadial.hpp"
%}


/***********************************************************************//**
 * @class GModelRadial
 *
 * @brief Abstract radial model base class
 ***************************************************************************/
class GModelRadial : public GModelSpatial {

public:
    // Constructors and destructors
    GModelRadial(void);
    GModelRadial(const GModelRadial& model);
    explicit GModelRadial(const GXmlElement& xml);
    virtual ~GModelRadial(void);

    // Pure virtual methods
    virtual void          clear(void) = 0;
    virtual GModelRadial* clone(void) const = 0;
    virtual std::string   type(void) const = 0;
    virtual double        eval(const double& theta) const = 0;
    virtual double        eval_gradients(const double& theta) const = 0;
    virtual GSkyDir       mc(GRan& ran) const = 0;
    virtual double        theta_max(void) const = 0;

    // Implemented virtual methods
    virtual double        eval(const GSkyDir& srcDir) const;
    virtual double        eval_gradients(const GSkyDir& srcDir) const;
    virtual void          read(const GXmlElement& xml);
    virtual void          write(GXmlElement& xml) const;

    // Other methods
    int                   size(void) const;
    double                ra(void) const;
    double                dec(void) const;
    GSkyDir               dir(void) const;
    void                  dir(const GSkyDir& dir);
};


/***********************************************************************//**
 * @brief GModelRadial class extension
 ***************************************************************************/
%extend GModelRadial {
};
