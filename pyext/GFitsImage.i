/***************************************************************************
 *      GFitsImage.i  - FITS image abstract base class SWIG interface      *
 * ----------------------------------------------------------------------- *
 *  copyright : (C) 2008-2012 by Juergen Knoedlseder                       *
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
 * @file GFitsImage.i
 * @brief GFitsImage class SWIG file.
 * @author Juergen Knoedlseder
 */
%{
/* Put headers and other declarations here that are needed for compilation */
#include "GFitsImage.hpp"
#include "GFitsImageByte.hpp"
#include "GFitsImageDouble.hpp"
#include "GFitsImageFloat.hpp"
#include "GFitsImageLong.hpp"
#include "GFitsImageLongLong.hpp"
#include "GFitsImageSByte.hpp"
#include "GFitsImageShort.hpp"
#include "GFitsImageULong.hpp"
#include "GFitsImageUShort.hpp"
#include "GTools.hpp"
%}

/***********************************************************************//**
 * @brief Tuple to index conversion to provide pixel access.
 *
 * The following function provides conversion between a Python tuple and
 * an integer array. This allows pixel access via tuples, such as in
 * a[(3,5,10)] = 10.0 or c = a[(2,9)]. Note that the typemap will be
 * globally defined after inclusing of this file, hence GFitsImage.i has
 * to be included before all image class swig files.
 ***************************************************************************/
%{
static int image_pixel_tuple(PyObject *input, int *ptr) {
    if (PySequence_Check(input)) {
        int size = PyObject_Length(input);
        if (size > 4) {
            PyErr_SetString(PyExc_ValueError,"Too many arguments in tuple");
            return 0;
        }
        ptr[0] = size;
        for (int i = 0; i < size; i++) {
            PyObject *o = PySequence_GetItem(input,i);
            if (!PyInt_Check(o)) {
                Py_XDECREF(o);
                PyErr_SetString(PyExc_ValueError,"Expecting a tuple of integers");
                return 0;
            }
            ptr[i+1] = (int)PyInt_AsLong(o);
            Py_DECREF(o);
        }
        return 1;
    }
    else {
        ptr[0] = 1;
        if (!PyInt_Check(input)) {
            PyErr_SetString(PyExc_ValueError,"Expecting an integer");
            return 0;
        }
        ptr[1] = (int)PyInt_AsLong(input);
        return 1;       
    }
}
%}
%typemap(in) int GFitsImageInx[ANY](int temp[5]) {
   if (!image_pixel_tuple($input,temp)) {
      return NULL;
   }
   $1 = &temp[0];
}


/***********************************************************************//**
 * @class GFitsImage
 *
 * @brief Abstract SWIG interface for the FITS image classes.
 ***************************************************************************/
class GFitsImage : public GFitsHDU {
public:
    // Constructors and destructors
    GFitsImage(void);
    explicit GFitsImage(int bitpix, int nx);
    explicit GFitsImage(int bitpix, int nx, int ny);
    explicit GFitsImage(int bitpix, int nx, int ny, int nz);
    explicit GFitsImage(int bitpix, int nx, int ny, int nz, int nt);
    GFitsImage(const GFitsImage& image);
    virtual ~GFitsImage(void);

    // Pure virtual methods
    virtual void        clear(void) = 0;
    virtual GFitsImage* clone(void) const = 0;
    virtual void*       pixels(void) = 0;
    virtual double      pixel(const int& ix) const = 0;
    virtual double      pixel(const int& ix, const int& iy) const = 0;
    virtual double      pixel(const int& ix, const int& iy, const int& iz) const = 0;
    virtual double      pixel(const int& ix, const int& iy, const int& iz, const int& it) const = 0;
    virtual int         type(void) const = 0;

    // Implemented pure virtual methods
    HDUType exttype(void) const { return HT_IMAGE; }

    // Methods
    int   size(void) const;
    int   bitpix(void) const;
    int   naxis(void) const;
    int   naxes(int axis) const;
    int   anynul(void) const;
    void  nulval(const void* value);
    void* nulval(void);
};


/***********************************************************************//**
 * @brief GFitsImage class extension
 ***************************************************************************/
%extend GFitsImage {
    char *__str__() {
        return tochar(self->print());
    }
};
