/***************************************************************************
 *        GModelSpectral.hpp  -  Abstract spectral model base class        *
 * ----------------------------------------------------------------------- *
 *  copyright (C) 2009-2012 by Juergen Knoedlseder                         *
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
 * @file GModelSpectral.hpp
 * @brief Abstract spectral model base class interface definition
 * @author Juergen Knoedlseder
 */

#ifndef GMODELSPECTRAL_HPP
#define GMODELSPECTRAL_HPP

/* __ Includes ___________________________________________________________ */
#include <string>
#include <vector>
#include "GBase.hpp"
#include "GModelPar.hpp"
#include "GEnergy.hpp"
#include "GRan.hpp"
#include "GXmlElement.hpp"


/***********************************************************************//**
 * @class GModelSpectral
 *
 * @brief Abstract spectral model base class
 *
 * This class implements the spectral component of the factorised source
 * model.
 ***************************************************************************/
class GModelSpectral : public GBase {

public:
    // Constructors and destructors
    GModelSpectral(void);
    GModelSpectral(const GModelSpectral& model);
    virtual ~GModelSpectral(void);

    // Operators
    virtual GModelSpectral&  operator=(const GModelSpectral& model);
    virtual GModelPar&       operator[](const int& index);
    virtual const GModelPar& operator[](const int& index) const;
    virtual GModelPar&       operator[](const std::string& name);
    virtual const GModelPar& operator[](const std::string& name) const;

    // Pure virtual methods
    virtual void            clear(void) = 0;
    virtual GModelSpectral* clone(void) const = 0;
    virtual std::string     type(void) const = 0;
    virtual double          eval(const GEnergy& srcEng) const = 0;
    virtual double          eval_gradients(const GEnergy& srcEng) const = 0;
    virtual double          flux(const GEnergy& emin, const GEnergy& emax) const = 0;
    virtual double          eflux(const GEnergy& emin, const GEnergy& emax) const = 0;
    virtual GEnergy         mc(const GEnergy& emin, const GEnergy& emax, GRan& ran) const = 0;
    virtual void            read(const GXmlElement& xml) = 0;
    virtual void            write(GXmlElement& xml) const = 0;
    virtual std::string     print(void) const = 0;

    // Methods
    int size(void) const { return m_pars.size(); }

protected:
    // Protected methods
    void init_members(void);
    void copy_members(const GModelSpectral& model);
    void free_members(void);

    // Proteced members
    std::vector<GModelPar*> m_pars;  //!< Parameter pointers
};

#endif /* GMODELSPECTRAL_HPP */
