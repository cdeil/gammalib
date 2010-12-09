/***************************************************************************
 *   GFitsImageShort.i  - FITS short integer image class SWIG interface    *
 * ----------------------------------------------------------------------- *
 *  copyright : (C) 2010 by Jurgen Knodlseder                              *
 * ----------------------------------------------------------------------- *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/
/**
 * @file GFitsImageShort.i
 * @brief GFitsImageShort class SWIG file.
 * @author J. Knodlseder
 */
%{
/* Put headers and other declarations here that are needed for compilation */
#include "GFitsImageShort.hpp"
%}

/***********************************************************************//**
 * @class GFitsImageShort
 *
 * @brief SWIG interface for the FITS short integer image class.
 ***************************************************************************/
class GFitsImageShort : public GFitsImage {

public:
    // Constructors and destructors
    GFitsImageShort(void);
    explicit GFitsImageShort(int nx, const short* pixels = NULL);
    explicit GFitsImageShort(int nx, int ny, const short* pixels = NULL);
    explicit GFitsImageShort(int nx, int ny, int nz, const short* pixels = NULL);
    explicit GFitsImageShort(int nx, int ny, int nz, int nt, const short* pixels = NULL);
    GFitsImageShort(const GFitsImageShort& image);
    virtual ~GFitsImageShort(void);

    // Methods
    double           pixel(const int& ix) const;
    double           pixel(const int& ix, const int& iy) const;
    double           pixel(const int& ix, const int& iy, const int& iz) const;
    double           pixel(const int& ix, const int& iy, const int& iz, const int& it) const;
    void*            pixels(void);
    int              type(void) const;
    GFitsImageShort* clone(void) const;
};


/***********************************************************************//**
 * @brief GFitsImageShort class extension
 ***************************************************************************/
%extend GFitsImageShort {
    GFitsImageShort(const GFitsImage& image) {
        if (image.type() != 21)
            throw GException::fits_invalid_type("GFitsImageShort(GFitsImage&)",
                                                "Expecting short integer image.");
        return (GFitsImageShort*)&image;
    }
    short __getitem__(int GFitsImageInx[]) {
        if (GFitsImageInx[0] == 1)
            return self->at(GFitsImageInx[1]);
        else if (GFitsImageInx[0] == 2)
            return self->at(GFitsImageInx[1], GFitsImageInx[2]);
        else if (GFitsImageInx[0] == 3)
            return self->at(GFitsImageInx[1], GFitsImageInx[2], GFitsImageInx[3]);
        else if (GFitsImageInx[0] == 4)
            return self->at(GFitsImageInx[1], GFitsImageInx[2], GFitsImageInx[3], GFitsImageInx[4]);
        else
            throw GException::fits_wrong_image_operator("__getitem__(int)",
                                                        self->naxis(), GFitsImageInx[0]);
    }
    void __setitem__(int GFitsImageInx[], short value) {
        if (GFitsImageInx[0] == 1)
            self->at(GFitsImageInx[1]) = value;
        else if (GFitsImageInx[0] == 2)
            self->at(GFitsImageInx[1], GFitsImageInx[2]) = value;
        else if (GFitsImageInx[0] == 3)
            self->at(GFitsImageInx[1], GFitsImageInx[2], GFitsImageInx[3]) = value;
        else if (GFitsImageInx[0] == 4)
            self->at(GFitsImageInx[1], GFitsImageInx[2], GFitsImageInx[3], GFitsImageInx[4]) = value;
        else
            throw GException::fits_wrong_image_operator("__setitem__(int)",
                                                        self->naxis(), GFitsImageInx[0]);
    }
    GFitsImageShort copy() {
        return (*self);
    }
};
