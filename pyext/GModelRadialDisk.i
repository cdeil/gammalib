/***************************************************************************
 *        GModelRadialDisk.i  -  Radial disk source model class            *
 * ----------------------------------------------------------------------- *
 *  copyright (C) 2011 by Christoph Deil                                   *
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
 * @file GModelRadialDisk.i
 * @brief Radial disk model class Python interface definition
 * @author C. Deil
 */
%{
/* Put headers and other declarations here that are needed for compilation */
#include "GModelRadialDisk.hpp"
#include "GTools.hpp"
%}

/**************************************************************************
 * @class GModelRadialDisk
 *
 * @brief Disk source model class
 *
 * This class implements the spatial component of the factorised source
 * model for a disk source, i.e. constant surface brightness within some
 * radius and no emission outside.
 ***************************************************************************/
class GModelRadialDisk : public GModelRadial {

public:
    // Constructors and destructors
    GModelRadialDisk(void);
    explicit GModelRadialDisk(const GSkyDir& dir, const double& radius);
    explicit GModelRadialDisk(const GXmlElement& xml);
    GModelRadialDisk(const GModelRadialDisk& model);
    virtual ~GModelRadialDisk(void);

    // Implemented pure virtual methods
    virtual void              clear(void);
    virtual GModelRadialDisk* clone(void) const;
    virtual std::string       type(void) const;
    virtual double            eval(const double& theta) const;
    virtual double            eval_gradients(const double& theta) const;
    virtual GSkyDir           mc(GRan& ran) const;
    virtual double            theta_max(void) const;
    virtual void              read(const GXmlElement& xml);
    virtual void              write(GXmlElement& xml) const;

    // Other methods
    double radius(void) const;
    void   radius(const double& radius);
};


/***********************************************************************//**
 * @brief GModelRadialDisk class extension
 *
 * The eval() and eval_gradients() methods are required here to force swig
 * to build also the interface for these methods. I guess that it is a swig
 * bug that these interfaces are not built automatically.
 ***************************************************************************/
%extend GModelRadialDisk {
    GModelRadialDisk copy() {
        return (*self);
    }
    double eval(const GSkyDir& srcDir) const {
        return self->GModelRadial::eval(srcDir);
    }
    double eval_gradients(const GSkyDir& srcDir) const {
        return self->GModelRadial::eval_gradients(srcDir);
    }
};
