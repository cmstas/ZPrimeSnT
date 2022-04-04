import numba
import numpy as np

myjit = numba.jit(nopython=True,cache=True)

@myjit
def dPhi(phi1,phi2):
    dphi = np.abs(phi2-phi1)
    if dphi >= np.pi: dphi -= 2.0*np.pi
    if dphi < -np.pi: dphi += 2.0*np.pi
    return dphi

@myjit
def deltaR(eta1,phi1,eta2,phi2):
    dphi = dPhi(phi1,phi2)
    deta = eta2-eta1
    return (deta*deta+dphi*dphi)**0.5

@myjit
def transverse_mass(pt1,phi1,pt2,phi2):
    return (2.0*pt1*pt2*(1-np.cos(phi1-phi2)))**0.5

@myjit
def invariant_mass(pt1,eta1,phi1,mass1,pt2,eta2,phi2,mass2):
    px1 = pt1*np.cos(phi1)
    px2 = pt2*np.cos(phi2)
    py1 = pt1*np.sin(phi1)
    py2 = pt2*np.sin(phi2)
    pz1 = pt1*np.sinh(eta1)
    pz2 = pt2*np.sinh(eta2)
    e1 = np.sqrt(px1**2+py1**2+pz1**2+mass1**2)
    e2 = np.sqrt(px2**2+py2**2+pz2**2+mass2**2)
    return np.sqrt((e1+e2)**2 - (px1+px2)**2 - (py1+py2)**2 - (pz1+pz2)**2)
