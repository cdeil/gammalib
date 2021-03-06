/***************************************************************************
 *      GCTAModelRadialProfile.hpp  -  Radial Profile CTA model class      *
 * ----------------------------------------------------------------------- *
 *  copyright (C) 2011 by Juergen Knoedlseder                              *
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
 * @file GCTAModelRadialProfile.hpp
 * @brief Radial Profile model class interface definition
 * @author J. Knoedlseder
 */

#ifndef GCTAMODELRADIALPROFILE_HPP
#define GCTAMODELRADIALPROFILE_HPP

/* __ Includes ___________________________________________________________ */
#include <string>
#include "GTools.hpp"
#include "GModelPar.hpp"
#include "GXmlElement.hpp"
#include "GCTAModelRadial.hpp"
#include "GCTAInstDir.hpp"
#include "GIntegrand.hpp"


/***********************************************************************//**
 * @class GCTAModelRadialProfile
 *
 * @brief Radial Profile CTA model class
 *
 * This class implements the radial profile function
 * \f[f(\theta) = (1 + (\theta/c_0)^{c_1})^{-c_2/c_1}\f]
 * where
 * \f$\theta\f$ is the offset angle (in degrees),
 * \f$c_0\f$ is the width of the profile (width),
 * \f$c_1\f$ is the width of the central plateau (core), and
 * \f$c_2\f$ is the size of the tail (tail).
 * Note that all 3 parameters are positive values.
 ***************************************************************************/
class GCTAModelRadialProfile  : public GCTAModelRadial {

public:
    // Constructors and destructors
    GCTAModelRadialProfile(void);
    explicit GCTAModelRadialProfile(const double& width, const double& core,
                                    const double& tail);
    explicit GCTAModelRadialProfile(const GXmlElement& xml);
    GCTAModelRadialProfile(const GCTAModelRadialProfile& model);
    virtual ~GCTAModelRadialProfile(void);

    // Operators
    virtual GCTAModelRadialProfile& operator= (const GCTAModelRadialProfile& model);

    // Implemented pure virtual methods
    virtual void                    clear(void);
    virtual GCTAModelRadialProfile* clone(void) const;
    virtual std::string             type(void) const { return "Profile"; }
    virtual double                  eval(const double& offset) const;
    virtual double                  eval_gradients(const double& offset) const;
    virtual GCTAInstDir             mc(const GCTAInstDir& dir, GRan& ran) const;
    virtual double                  omega(void) const;
    virtual void                    read(const GXmlElement& xml);
    virtual void                    write(GXmlElement& xml) const;
    virtual std::string             print(void) const;

    // Other methods
    double width(void) const { return m_width.real_value(); }
    double core(void) const { return m_core.real_value(); }
    double tail(void) const { return m_tail.real_value(); }
    void   width(const double& width) { m_width.real_value(width); }
    void   core(const double& core) { m_core.real_value(core); }
    void   tail(const double& tail) { m_tail.real_value(tail); }

protected:
    // Protected methods
    void init_members(void);
    void copy_members(const GCTAModelRadialProfile& model);
    void free_members(void);

    // Radial integration class (used by omega() method). Note that the
    // integration is done in radians
    class integrand : public GIntegrand {
    public:
        integrand(const GCTAModelRadialProfile* model) : m_model(model) { }
        double eval(double x) {
            return (sin(x)*m_model->eval(x*rad2deg));
        }
    private:
        const GCTAModelRadialProfile* m_model;
    };

    // Protected members
    GModelPar m_width;        //!< Width parameter
    GModelPar m_core;         //!< Core parameter
    GModelPar m_tail;         //!< Tail parameter
};

#endif /* GCTAMODELRADIALPROFILE_HPP */
