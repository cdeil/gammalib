/***************************************************************************
 *        GCTAResponse.i  -  CTA instrument response function class        *
 * ----------------------------------------------------------------------- *
 *  copyright (C) 2010-2012 by Juergen Knoedlseder                         *
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
 * @file GCTAResponse.i
 * @brief CTA instrument response function Python interface definition
 * @author Juergen Knoedlseder
 */
%{
/* Put headers and other declarations here that are needed for compilation */
#include "GCTAResponse.hpp"
%}


/***********************************************************************//**
 * @class GCTAResponse
 *
 * @brief CTA instrument response function
 ***************************************************************************/
class GCTAResponse : public GResponse {

public:
    // Constructors and destructors
    GCTAResponse(void);
    GCTAResponse(const GCTAResponse& rsp);
    explicit GCTAResponse(const std::string& rspname, const std::string& caldb = "");
    virtual ~GCTAResponse(void);

    // Implement pure virtual base class methods
    virtual void          clear(void);
    virtual GCTAResponse* clone(void) const;
    virtual bool          hasedisp(void) const;
    virtual bool          hastdisp(void) const;
    virtual double        irf(const GEvent&       event,
                              const GPhoton&      photon,
                              const GObservation& obs) const;
    virtual double        npred(const GPhoton&      photon,
                                const GObservation& obs) const;

    // Overload virtual base class methods
    virtual double irf_extended(const GEvent&       event,
                                const GSource&      source,
                                const GObservation& obs) const;
    virtual double irf_diffuse(const GEvent&       event,
                               const GSource&      source,
                               const GObservation& obs) const;
    virtual double npred_extended(const GSource&      source,
                                  const GObservation& obs) const;
    virtual double npred_diffuse(const GSource&      source,
                                 const GObservation& obs) const;

    // Other Methods
    GCTAEventAtom*  mc(const double& area, const GPhoton& photon,
                       const GObservation& obs, GRan& ran) const;
    void            caldb(const std::string& caldb);
    std::string     caldb(void) const;
    void            load(const std::string& rspname);
    void            eps(const double& eps);
    const double&   eps(void) const;
    std::string     rmffile(void) const;
    void            load_aeff(const std::string& filename);
    void            load_psf(const std::string& filename);
    void            load_edisp(const std::string& filename);
    void            offset_sigma(const double& sigma);
    double          offset_sigma(void) const;
    const GCTAAeff* aeff(void) const;
    void            aeff(GCTAAeff* aeff);
    const GCTAPsf*  psf(void) const;
    void            psf(GCTAPsf* psf);

    // Low-level response methods
    double aeff(const double& theta,
                const double& phi,
                const double& zenith,
                const double& azimuth,
                const double& srcLogEng) const;
    double psf(const double& delta,
               const double& theta,
               const double& phi,
               const double& zenith,
               const double& azimuth,
               const double& srcLogEng) const;
    double psf_delta_max(const double& theta,
                         const double& phi,
                         const double& zenith,
                         const double& azimuth,
                         const double& srcLogEng) const;
    double edisp(const double& obsLogEng,
                 const double& theta,
                 const double& phi,
                 const double& zenith,
                 const double& azimuth,
                 const double& srcLogEng) const;
    double npsf(const GSkyDir&      srcDir,
                const double&       srcLogEng,
                const GTime&        srcTime,
                const GCTAPointing& pnt,
                const GCTARoi&      roi) const;
    double nedisp(const GSkyDir&      srcDir,
                  const GEnergy&      srcEng,
                  const GTime&        srcTime,
                  const GCTAPointing& pnt,
                  const GEbounds&     ebds) const;
};


/***********************************************************************//**
 * @brief GCTAResponse class extension
 *
 * The irf() and npred() methods are required here to force swig to build
 * also interface for these methods. I guess that it is a swig bug that these
 * interfaces are not built automatically.
 ***************************************************************************/
%extend GCTAResponse {
    GCTAResponse copy() {
        return (*self);
    }
/*
    double irf(const GEvent&       event,
               const GModelSky&    model,
               const GEnergy&      srcEng,
               const GTime&        srcTime,
               const GObservation& obs) const {
        return self->GResponse::irf(event, model, srcEng, srcTime, obs);
    }
    double npred(const GModelSky&    model,
                 const GEnergy&      srcEng,
                 const GTime&        srcTime,
                 const GObservation& obs) const {
        return self->GResponse::npred(model, srcEng, srcTime, obs);
    }
*/
};


/***********************************************************************//**
 * @brief GCTAResponse type casts
 ***************************************************************************/
%inline %{
    GCTAResponse* cast_GCTAResponse(GResponse* arg) {
        GCTAResponse* rsp = dynamic_cast<GCTAResponse*>(arg);
        if (rsp == NULL) {
            throw GException::bad_type("cast_GCTAResponse(GResponse*)",
                                       "GResponse not of type GCTAResponse");
        }
        return rsp;
    }
%}
