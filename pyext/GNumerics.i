/***************************************************************************
 *       GNumerics.i - Numerical functions                                 *
 * ----------------------------------------------------------------------- *
 *  copyright (C) 2011-2012 by Juergen Knoedlseder                         *
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
 * @file GNumerics.i
 * @brief Numerical functions
 * @author Christoph Deil
 */
%{
/* Put headers and other declarations here that are needed for compilation */
#include "GNumerics.hpp"
%}


/***********************************************************************//**
 * @brief Computes the Li & Ma significance of an on-off measurement
 *
 * Reference: 1983ApJ...272..317L, equation (17)
 *
 * @param[in] n_on Number of counts in the on region.
 * @param[in] n_off Number of counts in the off region.
 * @param[in] alpha Ratio in background exposure on / off.
 ***************************************************************************/

double li_ma_significance(const double& n_on, const double& n_off, const double& alpha);

