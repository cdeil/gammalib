/***************************************************************************
 *            GCOMObservation.cpp  -  COMPTEL Observation class            *
 * ----------------------------------------------------------------------- *
 *  copyright (C) 2012 by Juergen Knoedlseder                              *
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
 * @file GCOMObservation.cpp
 * @brief COMPTEL observation class implementation
 * @author Juergen Knoedlseder
 */

/* __ Includes ___________________________________________________________ */
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#include <typeinfo> 
#include "GObservationRegistry.hpp"
#include "GException.hpp"
#include "GFits.hpp"
#include "GTools.hpp"
#include "GCOMObservation.hpp"
#include "GCOMEventCube.hpp"
#include "GCOMSupport.hpp"

/* __ Globals ____________________________________________________________ */
const GCOMObservation      g_obs_com_seed;
const GObservationRegistry g_obs_com_registry(&g_obs_com_seed);

/* __ Method name definitions ____________________________________________ */
#define G_RESPONSE                    "GCOMObservation::response(GResponse&)"
#define G_READ                          "GCOMObservation::read(GXmlElement&)"
#define G_WRITE                        "GCOMObservation::write(GXmlElement&)"

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
 *
 * Creates empty class instance.
 ***************************************************************************/
GCOMObservation::GCOMObservation(void) : GObservation()
{
    // Initialise members
    init_members();

    // Return
    return;
}


/***********************************************************************//**
 * @brief Instrument constructor
 *
 * @param[in] drename Event cube name.
 * @param[in] drbname Background cube name.
 * @param[in] drgname Geometry cube name.
 * @param[in] drxname Exposure map name.
 *
 * Creates COMPTEL observation by loading the relevant FITS files.
 ***************************************************************************/
GCOMObservation::GCOMObservation(const std::string& drename,
                                 const std::string& drbname,
                                 const std::string& drgname,
                                 const std::string& drxname) : GObservation()
{
    // Initialise members
    init_members();

    // Load observation
    load(drename, drbname, drgname, drxname);

    // Return
    return;
}


/***********************************************************************//**
 * @brief Copy constructor
 *
 * @param[in] obs COMPTEL observation.
 *
 * Creates class instance by copying an existing COMPTEL observation.
 ***************************************************************************/
GCOMObservation::GCOMObservation(const GCOMObservation& obs) : GObservation(obs)
{
    // Initialise members
    init_members();

    // Copy members
    copy_members(obs);

    // Return
    return;
}


/***********************************************************************//**
 * @brief Destructor
 ***************************************************************************/
GCOMObservation::~GCOMObservation(void)
{
    // Free members
    free_members();

    // Return
    return;
}


/*==========================================================================
 =                                                                         =
 =                               Operators                                 =
 =                                                                         =
 ==========================================================================*/

/***********************************************************************//**
 * @brief Assignment operator
 *
 * @param[in] obs COMPTEL observation.
 *
 * Assign COMPTEL observation to this object.
 ***************************************************************************/
GCOMObservation& GCOMObservation::operator= (const GCOMObservation& obs)
{
    // Execute only if object is not identical
    if (this != &obs) {

        // Copy base class members
        this->GObservation::operator=(obs);

        // Free members
        free_members();

        // Initialise members
        init_members();

        // Copy members
        copy_members(obs);

    } // endif: object was not identical

    // Return this object
    return *this;
}


/*==========================================================================
 =                                                                         =
 =                              Public methods                             =
 =                                                                         =
 ==========================================================================*/

/***********************************************************************//**
 * @brief Clear instance
 ***************************************************************************/
void GCOMObservation::clear(void)
{
    // Free members
    free_members();
    this->GObservation::free_members();

    // Initialise members
    this->GObservation::init_members();
    init_members();

    // Return
    return;
}


/***********************************************************************//**
 * @brief Clone instance
***************************************************************************/
GCOMObservation* GCOMObservation::clone(void) const
{
    return new GCOMObservation(*this);
}


/***********************************************************************//**
 * @brief Set response function
 *
 * @param[in] rsp Response function.
 *
 * @exception GException::rsp_invalid_type
 *            Specified response is not of type GCOMResponse.
 *
 * Sets the response function for the observation. The argument has to be of
 * type GCOMResponse, otherwise an exception is thrown.
 ***************************************************************************/
void GCOMObservation::response(const GResponse& rsp)
{
    // Get pointer on COM response
    const GCOMResponse* comrsp = dynamic_cast<const GCOMResponse*>(&rsp);
    if (comrsp == NULL) {
        throw GException::rsp_invalid_type(G_RESPONSE,
              typeid(&rsp).name(), "Expected type \"GCOMResponse\".");
    }

    // Delete old response function
    if (m_response != NULL) delete m_response;

    // Clone response function
    m_response = comrsp->clone();

    // Return
    return;
}


/***********************************************************************//**
 * @brief Set COM response function
 *
 * @param[in] iaqname Name of COMPTEL IAQ response function.
 * @param[in] caldb Optional name of calibration database.
 ***************************************************************************/
void GCOMObservation::response(const std::string& iaqname,
                               const std::string& caldb)
{
    // Delete old response function
    if (m_response != NULL) delete m_response;

    // Allocate new COM response function
    m_response = new GCOMResponse;

    // Set calibration database
    m_response->caldb(caldb);

    // Load instrument response function
    m_response->load(iaqname);

    // Return
    return;
}


/***********************************************************************//**
 * @brief Returns pointer to COMPTEL response function
 ***************************************************************************/
GCOMResponse* GCOMObservation::response(void) const
{
    // Return response pointer
    return m_response;
}


/***********************************************************************//**
 * @brief Returns pointer to COMPTEL pointing direction
 *
 * Returns pointer to pointing direction.
 ***************************************************************************/
GCOMPointing* GCOMObservation::pointing(void) const
{
    // Return pointing pointer
    return m_pointing;
}


/***********************************************************************//**
 * @brief Set COMPTEL pointing direction
 *
 * @param[in] pointing Pointing.
 ***************************************************************************/
/*
void GCOMObservation::pointing(const GCOMPointing& pointing)
{
    // Free any existing pointing
    if (m_pointing != NULL) delete m_pointing;
    m_pointing = NULL;

    // Clone pointing
    m_pointing = pointing.clone();

    // Return
    return;
}
*/


/***********************************************************************//**
 * @brief Read observation from XML element
 *
 * @param[in] xml XML element.
 *
 * @exception GException::xml_invalid_parnum
 *            Invalid number of parameters found in XML element.
 * @exception GException::xml_invalid_parnames
 *            Invalid parameter names found in XML element.
 *
 * Reads information for a COMPTEL observation from an XML element.
 * The expected format of the XML element is
 *
 *  <observation name="..." id="..." instrument="...">
 *    <parameter name="DRE" file="..."/>
 *    <parameter name="DRB" file="..."/>
 *    <parameter name="DRG" file="..."/>
 *    <parameter name="DRX" file="..."/>
 *  </observation>
 *
 * for a binned observation.
 ***************************************************************************/
void GCOMObservation::read(const GXmlElement& xml)
{
    // Clear observation
    clear();

    // Initialise FITS file names
    std::string drename;
    std::string drbname;
    std::string drgname;
    std::string drxname;

    // Extract instrument name
    m_instrument = xml.attribute("instrument");

    // Determine number of parameter nodes in XML element
    int npars = xml.elements("parameter");

    // Verify that XML element has exactly 4 parameters
    if (xml.elements() != 4 || npars != 4) {
        throw GException::xml_invalid_parnum(G_READ, xml,
              "COMPTEL observation requires exactly 4 parameters.");
    }

    // Extract parameters
    int npar[] = {0, 0, 0, 0};
    for (int i = 0; i < npars; ++i) {

        // Get parameter element
        GXmlElement* par = static_cast<GXmlElement*>(xml.element("parameter", i));

        // Handle EventList
        if (par->attribute("name") == "DRE") {
            drename = par->attribute("file");
            npar[0]++;
        }

        // Handle DRB
        else if (par->attribute("name") == "DRB") {
            drbname = par->attribute("file");
            npar[1]++;
        }

        // Handle DRG
        else if (par->attribute("name") == "DRG") {
            drgname = par->attribute("file");
            npar[2]++;
        }

        // Handle PSF
        else if (par->attribute("name") == "DRX") {
            drxname = par->attribute("file");
            npar[3]++;
        }

    } // endfor: looped over all parameters

    // Verify that all parameters were found
    if (npar[0] != 1 || npar[1] != 1 || npar[2] != 1 || npar[3] != 1) {
        throw GException::xml_invalid_parnames(G_READ, xml,
              "Require \"DRE\", \"DRB\", \"DRG\" and \"DRX\""
              " parameters.");
    }

    // Load observation
    load(drename, drbname, drgname, drxname);

    // Return
    return;
}


/***********************************************************************//**
 * @brief Write observation into XML element
 *
 * @param[in] xml XML element.
 *
 * @exception GException::xml_invalid_parnum
 *            Invalid number of parameters found in XML element.
 * @exception GException::xml_invalid_parnames
 *            Invalid parameter names found in XML element.
 *
 * Writes information for a COMPTEL observation into an XML element. The
 * expected format of the XML element is
 *
 *  <observation name="..." id="..." instrument="...">
 *    <parameter name="DRE" file="..."/>
 *    <parameter name="DRB" file="..."/>
 *    <parameter name="DRG" file="..."/>
 *    <parameter name="DRX" file="..."/>
 *  </observation>
 *
 * for a binned observation.
 ***************************************************************************/
void GCOMObservation::write(GXmlElement& xml) const
{
    // If XML element has 0 nodes then append 4 parameter nodes
    if (xml.elements() == 0) {
        xml.append(new GXmlElement("parameter name=\"DRE\""));
        xml.append(new GXmlElement("parameter name=\"DRB\""));
        xml.append(new GXmlElement("parameter name=\"DRG\""));
        xml.append(new GXmlElement("parameter name=\"DRX\""));
    }

    // Verify that XML element has exactly 4 parameters
    if (xml.elements() != 4 || xml.elements("parameter") != 4) {
        throw GException::xml_invalid_parnum(G_WRITE, xml,
              "COMPTEL observation requires exactly 4 parameters.");
    }

    // Set or update parameter attributes
    int npar[] = {0, 0, 0, 0};
    for (int i = 0; i < 4; ++i) {

        // Get parameter element
        GXmlElement* par = static_cast<GXmlElement*>(xml.element("parameter", i));

        // Handle DRE
        if (par->attribute("name") == "DRE") {
            par->attribute("file", m_drename);
            npar[0]++;
        }

        // Handle DRB
        else if (par->attribute("name") == "DRB") {
            par->attribute("file", m_drbname);
            npar[1]++;
        }

        // Handle DRG
        else if (par->attribute("name") == "DRG") {
            par->attribute("file", m_drgname);
            npar[2]++;
        }

        // Handle DRX
        else if (par->attribute("name") == "DRX") {
            par->attribute("file", m_drxname);
            npar[3]++;
        }

    } // endfor: looped over all parameters

    // Verify that all required parameters are present
    if (npar[0] != 1 || npar[1] != 1 || npar[2] != 1 || npar[3] != 1) {
        throw GException::xml_invalid_parnames(G_WRITE, xml,
              "Require \"DRE\", \"DRB\", \"DRG\" and \"DRX\""
              " parameters.");
    }

    // Return
    return;
}


/***********************************************************************//**
 * @brief Load data for binned analysis
 *
 * @param[in] drename Event cube name.
 * @param[in] drbname Background cube name.
 * @param[in] drgname Geometry cube name.
 * @param[in] drxname Exposure map name.
 *
 * Load event cube from DRE file, background model from DRB file, geometry
 * factors from DRG file and the exposure map from the DRX file.
 ***************************************************************************/
void GCOMObservation::load(const std::string& drename,
                           const std::string& drbname,
                           const std::string& drgname,
                           const std::string& drxname)
{
    // Load DRE
    load_dre(drename);

    // Load DRB
    load_drb(drbname);

    // Load DRG
    load_drg(drgname);

    // Load DRX
    load_drx(drxname);

    // Return
    return;
}


/***********************************************************************//**
 * @brief Return exposure value
 *
 * @param[in] dir Sky direction.
 * @return Exposure (seconds).
 *
 * Returns the exposure as extracted from the DRX dataset. We use here a
 * kluge as the WCS of the COMPTEL data from GSFC are incorrect (they
 * pretend to be in Mercator projection, yet they are in cartesian
 * coordinates).
 ***************************************************************************/
double GCOMObservation::drx(const GSkyDir& dir) const
{
    // Get longitude index
    int nx = m_drx.nx();
    int ix = int((dir.l_deg() - m_drx_min1) / m_drx_cdelt1 + 0.5);
    if (ix < 0) {
        ix += nx;
    }
    else if (ix >= nx) {
        ix -= nx;
    }
    if (ix < 0) {
        ix = 0;
    }
    else if (ix >= nx) {
        ix = nx-1;
    }

    // Get latitude index
    int ny = m_drx.ny();
    int iy = int((dir.b_deg() - m_drx_min2) / m_drx_cdelt2 + 0.5);
    if (iy < 0) {
        iy = 0;
    }
    else if (iy >= ny) {
        iy = ny-1;
    }

    // Get pixel index
    int inx = ix + iy * nx;

    // Get exposure value
    double drx = (m_drx.pixels())[inx];

    // Return
    return drx;
}


/***********************************************************************//**
 * @brief Print COM observation information
 ***************************************************************************/
std::string GCOMObservation::print(void) const
{
    // Initialise result string
    std::string result;

    // Append header
    result.append("=== GCOMObservation ===");
    result.append("\n"+parformat("Name")+name());
    result.append("\n"+parformat("Identifier")+id());
    result.append("\n"+parformat("Instrument")+instrument());
    result.append("\n"+parformat("Statistics")+statistics());
    result.append("\n"+parformat("Ontime")+str(ontime())+" sec");
    result.append("\n"+parformat("Livetime")+str(livetime())+" sec");
    result.append("\n"+parformat("Deadtime correction")+str(m_deadc));
    result.append("\n"+parformat("Energy band")+str(ewidth())+" MeV");

    // Append pointing
    if (m_pointing != NULL) {
        result.append("\n"+m_pointing->print());
    }
    else {
        result.append("\n"+parformat("Pointing")+"undefined");
    }

    // Append response
    if (m_response != NULL) {
        result.append("\n"+response()->print());
    }
    else {
        result.append("\n"+parformat("Response")+"undefined");
    }

    // Append events
    if (m_events != NULL) {
        result.append("\n"+m_events->print());
    }
    else {
        result.append("\n"+parformat("Events")+"undefined");
    }

    // Append DRB, DRG and DRX
    //result.append("\n"+m_drb.print());
    //result.append("\n"+m_drg.print());
    //result.append("\n"+m_drx.print());

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
void GCOMObservation::init_members(void)
{
    // Initialise members
    m_instrument = "COM";
    m_drename.clear();
    m_drbname.clear();
    m_drgname.clear();
    m_drxname.clear();
    m_drb.clear();
    m_drg.clear();
    m_drx.clear();
    m_pointing   = NULL;
    m_response   = NULL;
    m_obs_id     = 0;
    m_ontime     = 0.0;
    m_livetime   = 0.0;
    m_deadc      = 0.0;
    m_ewidth     = 0.0;
    m_drx_cdelt1 = 0.0;
    m_drx_cdelt2 = 0.0;
    m_drx_crval1 = 0.0;
    m_drx_crval2 = 0.0;
    m_drx_crpix1 = 0.0;
    m_drx_crpix2 = 0.0;
    m_drx_min1   = 0.0;
    m_drx_min2   = 0.0;

    // Return
    return;
}


/***********************************************************************//**
 * @brief Copy class members
 *
 * @param[in] obs COMPTEL observation.
 ***************************************************************************/
void GCOMObservation::copy_members(const GCOMObservation& obs)
{
    // Clone members. Note that the events are cloned by the base class.
    if (obs.m_response != NULL) m_response = obs.m_response->clone();
    if (obs.m_pointing != NULL) m_pointing = obs.m_pointing->clone();

    // Copy members
    m_instrument = obs.m_instrument;
    m_drename    = obs.m_drename;
    m_drbname    = obs.m_drbname;
    m_drgname    = obs.m_drgname;
    m_drxname    = obs.m_drxname;
    m_drb        = obs.m_drb;
    m_drg        = obs.m_drg;
    m_drx        = obs.m_drx;
    m_obs_id     = obs.m_obs_id;
    m_ontime     = obs.m_ontime;
    m_livetime   = obs.m_livetime;
    m_deadc      = obs.m_deadc;
    m_ewidth     = obs.m_ewidth;
    m_drx_cdelt1 = obs.m_drx_cdelt1;
    m_drx_cdelt2 = obs.m_drx_cdelt2;
    m_drx_crval1 = obs.m_drx_crval1;
    m_drx_crval2 = obs.m_drx_crval2;
    m_drx_crpix1 = obs.m_drx_crpix1;
    m_drx_crpix2 = obs.m_drx_crpix2;
    m_drx_min1   = obs.m_drx_min1;
    m_drx_min2   = obs.m_drx_min2;

    // Return
    return;
}


/***********************************************************************//**
 * @brief Delete class members
 ***************************************************************************/
void GCOMObservation::free_members(void)
{
    // Free memory
    if (m_response != NULL) delete m_response;
    if (m_pointing != NULL) delete m_pointing;

    // Mark memory as free
    m_response = NULL;
    m_pointing = NULL;

    // Return
    return;
}


/***********************************************************************//**
 * @brief Load event cube data from DRE file
 *
 * @param[in] drename DRE filename.
 ***************************************************************************/
void GCOMObservation::load_dre(const std::string& drename)
{
    // Delete any existing event container (do not call clear() as we do not
    // want to delete the response function)
    if (m_events != NULL) delete m_events;
    m_events = NULL;

    // Allocate event cube
    m_events = new GCOMEventCube;

    // Open FITS file
    GFits file(drename);

    // Read event cube
    m_events->read(file);

    // Read observation attributes from primary extension
    GFitsHDU* hdu = file.hdu(0);
    read_attributes(hdu);

    // Close FITS file
    file.close();

    // Store event filename
    m_drename = drename;

    // Return
    return;
}


/***********************************************************************//**
 * @brief Load background model from DRB file
 *
 * @param[in] drbname DRB filename.
 *
 * Load the background model from the primary image of the specified FITS
 * file.
 *
 * @todo Check compatibility of DRB cube with event cube
 ***************************************************************************/
void GCOMObservation::load_drb(const std::string& drbname)
{
    // Open FITS file
    GFits file(drbname);

    // Get HDU
    GFitsImage* hdu = file.image("Primary");

    // Load background model as sky map
    m_drb.read(hdu);

    // Correct WCS projection (HEASARC data format kluge)
    com_wcs_mer2car(m_drb);

    // Close FITS file
    file.close();

    //TODO: Check dimensions

    // Store DRB filename
    m_drbname = drbname;

    // Return
    return;
}


/***********************************************************************//**
 * @brief Load geometry factors from DRG file
 *
 * @param[in] drgname DRG filename.
 *
 * Load the geometry factors from the primary image of the specified FITS
 * file.
 *
 * @todo Check compatibility of DRG cube with event cube
 ***************************************************************************/
void GCOMObservation::load_drg(const std::string& drgname)
{
    // Open FITS file
    GFits file(drgname);

    // Get HDU
    GFitsImage* hdu = file.image("Primary");

    // Load geometry factors as sky map
    m_drg.read(hdu);

    // Correct WCS projection (HEASARC data format kluge)
    com_wcs_mer2car(m_drg);

    // Close FITS file
    file.close();

    //TODO: Check dimensions

    // Store DRG filename
    m_drgname = drgname;

    // Return
    return;
}


/***********************************************************************//**
 * @brief Load exposure from DRX file
 *
 * @param[in] drxname DRX filename.
 *
 * Load the exposure map from the primary image of the specified FITS file.
 ***************************************************************************/
void GCOMObservation::load_drx(const std::string& drxname)
{
    // Open FITS file
    GFits file(drxname);

    // Get HDU
    GFitsImage* hdu = file.image("Primary");

    // Load exposure map as sky map
    m_drx.read(hdu);

    // Correct WCS projection (HEASARC data format kluge)
    com_wcs_mer2car(m_drx);

    // Save some attributes for DRX access kluge
    m_drx_cdelt1 = hdu->real("CDELT1");
    m_drx_cdelt2 = hdu->real("CDELT2");
    m_drx_crval1 = hdu->real("CRVAL1");
    m_drx_crval2 = hdu->real("CRVAL2");
    m_drx_crpix1 = hdu->real("CRPIX1");
    m_drx_crpix2 = hdu->real("CRPIX2");

    // Derive some attributes
    m_drx_min1 = m_drx_crval1 + (1.0-m_drx_crpix1) * m_drx_cdelt1;
    m_drx_min2 = m_drx_crval2 + (1.0-m_drx_crpix2) * m_drx_cdelt2;

    // Close FITS file
    file.close();

    // Store DRX filename
    m_drxname = drxname;

    // Return
    return;
}


/***********************************************************************//**
 * @brief Read observation attributes
 *
 * @param[in] hdu FITS HDU pointer
 *
 * Reads COM observation attributes from HDU. Mandatory attributes are
 *
 * RA_SCZ   - Right Ascension of pointing
 * DEC_SCZ  - Declination of pointing
 * TSTART   - Start time (days)
 * TSTOP    - Stop time (days)
 * E_MIN    - Minimum energy (MeV)
 * E_MAX    - Maximum energy (MeV)
 *
 * and optional attributes are
 *
 * OBS_ID   - Observation identifier
 * OBJECT   - Object
 *
 * Based on TSTART and TSTOP the ontime is computed. The deadtime fraction
 * is fixed to 15%, hence DEADC=0.85. The livetime is then computed by
 * multiplying the deadtime correction by the ontime, i.e.
 * LIVETIME = ONTIME * DEADC.
 *
 * Nothing is done if the HDU pointer is NULL.
 ***************************************************************************/
void GCOMObservation::read_attributes(const GFitsHDU* hdu)
{
    // Continue only if HDU is valid
    if (hdu != NULL) {

        // Read observation information
        m_obs_id = (hdu->hascard("OBS_ID")) ? hdu->real("OBS_ID") : 0;
        m_name   = (hdu->hascard("OBJECT")) ? hdu->string("OBJECT") : "unknown";

        // Compute ontime
        double tstart = hdu->real("TSTART");
        double tstop  = hdu->real("TSTOP");
        m_ontime   = (tstop - tstart) * 86400.0;
        m_deadc    = 0.85;
        m_livetime = m_deadc * m_ontime;

        // Compute energy width
        double emin = hdu->real("E_MIN");
        double emax = hdu->real("E_MAX");
        m_ewidth = emax - emin;

        // Set pointing information
        GSkyDir pnt;
        double  ra_scz  = hdu->real("RA_SCZ");
        double  dec_scz = hdu->real("DEC_SCZ");
        pnt.radec_deg(ra_scz, dec_scz);
        if (m_pointing != NULL) delete m_pointing;
        m_pointing = new GCOMPointing;
        m_pointing->dir(pnt);

    } // endif: HDU was valid

    // Return
    return;
}


/***********************************************************************//**
 * @brief Write observation attributes
 *
 * @param[in] hdu FITS HDU pointer
 *
 * Nothing is done if the HDU pointer is NULL.
 *
 * @todo Implement method.
 ***************************************************************************/
void GCOMObservation::write_attributes(GFitsHDU* hdu) const
{
    // Continue only if HDU is valid
    if (hdu != NULL) {

    } // endif: HDU was valid

    // Return
    return;
}
