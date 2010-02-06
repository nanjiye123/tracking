#Copyright 2010 Thomas A Caswell
#tcaswell@uchicago.edu
#http://jfi.uchicago.edu/~tcaswell
#
#This program is free software; you can redistribute it and/or modify
#it under the terms of the GNU General Public License as published by
#the Free Software Foundation; either version 3 of the License, or (at
#your option) any later version.
#
#This program is distributed in the hope that it will be useful, but
#WITHOUT ANY WARRANTY; without even the implied warranty of
#MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
#General Public License for more details.
#
#You should have received a copy of the GNU General Public License
#along with this program; if not, see <http://www.gnu.org/licenses>.

from numpy import *
import matplotlib.pyplot as plt
import random
import itertools
import h5py

def _make_rot_mat(angle):
    return matrix([[cos(angle), -sin(angle)],[sin(angle),cos(angle)]])

def _make_cluster(center,angle):
    rot = _make_rot_mat(angle)
    ivec = matrix([1,0]).T
    

    cluster = [center]
    
    for k in range (0,6):
        rot = _make_rot_mat(angle + k*pi/3)

        cluster.append((rot*ivec + center))

    return cluster




def grid_centers(sz,spacing):
    for x in range(spacing,(sz+1)*spacing,spacing):
        for y in range(spacing,(sz+1)*spacing,spacing):
            yield matrix([x,y]).T


        
class hex_plane:
    def __init__(self,fid,size,angle):
        self.fid = fid
        self.part_count = size*7
        self.x = zeros(self.part_count)
        self.y = zeros(self.part_count)
        # 
    def to_hdf(self,h):
        # open plane
        # dump x,y
        # close plane
        # add any extra meta-data (z-posistion)
        pass



def _main():
    f_count = 1
    grd_sz = 2
    spc = 6
    
    f = h5py.File("test.h5",'w')
       
    f.attrs['dims'] = [(grd_sz+1)* spc,(grd_sz+1)* spc]
    f.attrs['number-of-planes'] = f_count
    for fr in range(0,f_count):
        clusters = []
        cents = grid_centers(grd_sz,spc)
        for a,c in itertools.izip(range(0,25),cents):
            clusters.extend(_make_cluster(c,(pi/3) * (a/25 + 0*fr/5)))

        clust = hstack(clusters)
        g = f.create_group("frame%(#)06d"%{"#":fr})
        g.create_dataset('x',data=clust[0,:])
        g.create_dataset('y',data=clust[1,:])
        g.attrs['z-position'] = fr

    f.close()

_main()


