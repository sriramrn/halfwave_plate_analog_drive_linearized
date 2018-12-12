#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Tue Dec 11 19:12:37 2018

@author: sriram
"""

import numpy as np
from scipy.constants import pi

import matplotlib.pyplot as plt

power = 0.5 # percent to set at

hwp_deflection_range = 45 # degrees the hwp has to rotate for one full power cycle
gear_ratio = 1 # coupling ratio between servo rotation and HWP rotation
max_deflection_angle = hwp_deflection_range * gear_ratio

offset = 0 # angular offset to adjust to initial zero position

x = np.arange(0,pi/2,0.01)

y = (np.sin(x))**2

p = np.arccos(1-(2*power))/2
print(p)

xval = offset + (np.arccos(1-2*power))*max_deflection_angle/pi
print(xval)

"""
Derivation:
    
Step 1: get x given y

sin^2(x) = (1-cos2x)/2  ----eq-1

y = sin^2(x) from Malus's law 
(sin conveniently introduces a phase shift to start from zero intensity)

substituting eq1,

y = (1-cos2x)/2

1-cos2x = 2y

cos2x = 1-2y

x = (cos^-1(1-2y))/2    ----eq-2

Step 2: get angular rotation of servo in the real world from x


hwp_deflection_range = 45 degrees
gear_ratio = 1

max_deflection angle = gear_ratio * hwp_deflection_range
(angular rotation in degrees of the servo to reach 100% laser power)

range of variable x = 0 to pi/2

using eq2 :
    
angle to set for a given power fraction 'y' = [((cos^-1(1-2y))/2)/(pi/2)]*max_deflection_angle
                                            
                                            = [2*(cos^-1(1-2y))/(2*pi)]*max_deflection_angle
                                            
                                            = [(cos^-1(1-2y))/pi]*max_deflection_angle

"""


plt.figure()
plt.plot(x,y)
plt.vlines(p,0,1)
plt.hlines(power,0,pi/2)

plt.show()