/***************************************************************************
 *        GModelTemporalConst.cpp  -  Temporal constant model class        *
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
 * @file GModelTemporalConst.cpp
 * @brief Constant temporal model class interface implementation
 * @author J. Knoedlseder
 */

/* __ Includes ___________________________________________________________ */
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#include "GTools.hpp"
#include "GException.hpp"
#include "GModelTemporalConst.hpp"
#include "GModelTemporalRegistry.hpp"

/* __ Constants __________________________________________________________ */

/* __ Globals ____________________________________________________________ */
const GModelTemporalConst    g_temporal_const_seed;
const GModelTemporalRegistry g_temporal_const_registry(&g_temporal_const_seed);

/* __ Method name definitions ____________________________________________ */

/* __ Macros _____________________________________________________________ */

/* __ Coding definitions _________________________________________________ */

/* __ Debug definitions __________________________________________________ */


/*==========================================================================
 =                                                                         =
 =                        Constructors/destructors                         =
 =                                                                         =
 ==========================================================================*/

/***********************************************************************//**
 * @brief Void constructor
 ***************************************************************************/
GModelTemporalConst::GModelTemporalConst(void) : GModelTemporal()
{
    // Initialise members
    init_members();

    // Return
    return;
}


/***********************************************************************//**
 * @brief Copy constructor
 *
 * @param[in] model Constant temporal model
 ***************************************************************************/
GModelTemporalConst::GModelTemporalConst(const GModelTemporalConst& model) 
                                         : GModelTemporal(model)
{
    // Initialise members
    init_members();

    // Copy members
    copy_members(model);

    // Return
    return;
}


/***********************************************************************//**
 * @brief Destructor
 ***************************************************************************/
GModelTemporalConst::~GModelTemporalConst(void)
{
    // Free members
    free_members();

    // Return
    return;
}


/*==========================================================================
 =                                                                         =
 =                                Operators                                =
 =                                                                         =
 ==========================================================================*/

/***********************************************************************//**
 * @brief Assignment operator
 *
 * @param[in] model Constant temporal model
 ***************************************************************************/
GModelTemporalConst& GModelTemporalConst::operator= (const GModelTemporalConst& model)
{
    // Execute only if object is not identical
    if (this != &model) {

        // Copy base class members
        this->GModelTemporal::operator=(model);

        // Free members
        free_members();

        // Initialise members
        init_members();

        // Copy members
        copy_members(model);

    } // endif: object was not identical

    // Return
    return *this;
}


/*==========================================================================
 =                                                                         =
 =                            Public methods                               =
 =                                                                         =
 ==========================================================================*/

/***********************************************************************//**
 * @brief Clear instance
***************************************************************************/
void GModelTemporalConst::clear(void)
{
    // Free class members (base and derived classes, derived class first)
    free_members();
    this->GModelTemporal::free_members();

    // Initialise members
    this->GModelTemporal::init_members();
    init_members();

    // Return
    return;
}


/***********************************************************************//**
 * @brief Clone instance
***************************************************************************/
GModelTemporalConst* GModelTemporalConst::clone(void) const
{
    return new GModelTemporalConst(*this);
}


/***********************************************************************//**
 * @brief Evaluate function
 *
 * @param[in] srcTime True photon arrival time (not used).
 *
 * This method implements the temporal component of a constant model. It
 * simply returns the normalization constant (which typically is set to 1).
 ***************************************************************************/
double GModelTemporalConst::eval(const GTime& srcTime) const
{
    // Compute function value
    double value = norm();

    // Return
    return value;
}


/***********************************************************************//**
 * @brief Evaluate function and gradients
 *
 * @param[in] srcTime True photon arrival time (not used).
 *
 * The temporal model is defined as
 * \f[I(E)=norm\f]
 * where
 * \f$norm=n_s n_v\f$ is the normalization of the function.
 * Note that the normalization is factorised into a scaling factor and a
 * value and that the method is expected to return the gradient with respect
 * to the parameter value \f$n_v\f$.
 *
 * The partial derivative of the normalization value is given by
 * \f[dI/dn_v=n_s\f]
 ***************************************************************************/
double GModelTemporalConst::eval_gradients(const GTime& srcTime) const
{
    // Compute function value
    double value = norm();

    // Compute partial derivatives of the parameter values
    double g_norm = (m_norm.isfree()) ? m_norm.scale() : 0.0;

    // Set gradients (circumvent const correctness)
    const_cast<GModelTemporalConst*>(this)->m_norm.gradient(g_norm);

    // Return
    return value;
}


/***********************************************************************//**
 * @brief Returns vector of random event times
 *
 * @param[in] rate Mean event rate (events per second).
 * @param[in] tmin Minimum event time.
 * @param[in] tmax Maximum event time.
 * @param[in] ran Random number generator.
 *
 * This method returns a vector of random event times assuming a constant
 * event rate that is specified by the rate parameter.
 ***************************************************************************/
GTimes GModelTemporalConst::mc(const double& rate, const GTime&  tmin,
                               const GTime&  tmax, GRan& ran) const
{
    // Allocates empty vector of times
    GTimes times;

    // Compute event rate (in events per seconds)
    double lambda = rate * norm();

    // Initialise start and stop times (using MET)
    double time  = tmin.met();
    double tstop = tmax.met();

    // Generate events until maximum event time is exceeded
    while (time <= tstop) {

        // Simulate next event time
        time += ran.exp(lambda);

        // Add time if it is not beyod the stop time
        if (time <= tstop) {
            GTime event;
            event.met(time);
            times.push_back(event);
        }

    } // endwhile: loop until stop time is reached

    // Return vector of times
    return times;
}


/***********************************************************************//**
 * @brief Read model from XML element
 *
 * @param[in] xml XML element.
 *
 * @todo To be implemented.
 ***************************************************************************/
void GModelTemporalConst::read(const GXmlElement& xml)
{
    // Return
    return;
}


/***********************************************************************//**
 * @brief Write model into XML element
 *
 * @param[in] xml XML element.
 *
 * @todo To be implemented.
 ***************************************************************************/
void GModelTemporalConst::write(GXmlElement& xml) const
{
    // Return
    return;
}


/***********************************************************************//**
 * @brief Print constant information
 ***************************************************************************/
std::string GModelTemporalConst::print(void) const
{
    // Initialise result string
    std::string result;

    // Append header
    result.append("=== GModelTemporalConst ===\n");
    result.append(parformat("Number of parameters")+str(size()));
    for (int i = 0; i < size(); ++i) {
        result.append("\n"+m_pars[i]->print());
    }

    // Return result
    return result;
}


/*==========================================================================
 =                                                                         =
 =                            Private methods                              =
 =                                                                         =
 ==========================================================================*/

/***********************************************************************//**
 * @brief Initialise class members
 ***************************************************************************/
void GModelTemporalConst::init_members(void)
{
    // Initialise normalisation parameter
    m_norm.clear();
    m_norm.name("Constant");
    m_norm.unit("(relative value)");
    m_norm.value(1.0);
    m_norm.fix();
    m_norm.gradient(0.0);
    m_norm.hasgrad(true);

    // Set parameter pointer(s)
    m_pars.clear();
    m_pars.push_back(&m_norm);

    // Return
    return;
}


/***********************************************************************//**
 * @brief Copy class members
 *
 * @param[in] model Constant temporal model
 ***************************************************************************/
void GModelTemporalConst::copy_members(const GModelTemporalConst& model)
{
    // Copy members
    m_norm = model.m_norm;

    // Set parameter pointer(s)
    m_pars.clear();
    m_pars.push_back(&m_norm);

    // Return
    return;
}


/***********************************************************************//**
 * @brief Delete class members
 ***************************************************************************/
void GModelTemporalConst::free_members(void)
{
    // Return
    return;
}


/*==========================================================================
 =                                                                         =
 =                                  Friends                                =
 =                                                                         =
 ==========================================================================*/
