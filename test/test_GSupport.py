# ==========================================================================
# This module performs unit tests for the GammaLib support module.
#
# Copyright (C) 2012 Juergen Knoedlseder
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.
#
# ==========================================================================
from gammalib import *
from math import *
import os


# =============================== #
# Test class for GammaLib support #
# =============================== #
class Test(GPythonTestSuite):
    """
    Test class for GammaLib support.
    """
    # Constructor
    def __init__(self):
        """
        Constructor.
        """
        # Call base class constructor
        GPythonTestSuite.__init__(self)

        # Return
        return

    # Set all test functions
    def set(self):
        """
        Set all test functions.
        """
        # Set test name
        self.name("support")

        # Append tests
        self.append(self.test_node_array, "Test GNodeArray")

        # Return
        return

    # Test GNodeArray class
    def test_node_array(self):
        """
        Test GNodeArray class.
        """
        # Set-up vector and data array. Test all vector elements.
        vector = GVector(20)
        data = GVector(20)
        for i in range(20):
            vector[i] = 10.0 + i * 5.0
            data[i] = sin(0.15 * (vector[i] - 10.0))
            self.test_value(data[i], sin(0.15 * i * 5.0))

        # Set-up node array
        array = GNodeArray()
        array.nodes(vector)

        # Get values
        x_val = []
        y_val = []
        for i in range(100):
            x = i - 10
            array.set_value(x)
            inx_left = array.inx_left()
            inx_right = array.inx_right()
            wgt_left = array.wgt_left()
            wgt_right = array.wgt_right()
            y = wgt_left * data[inx_left] + wgt_right * data[inx_right]
            x_val.append(x)
            y_val.append(y)

        # Return
        return
