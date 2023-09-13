
import os

#from libvsc import core
#from libvsc.core import *

def get_deps():
    return ["debug_mgr"]

def get_libs():
    return ["vsc-dm"]

def get_libdirs():
    pkg_dir = os.path.dirname(os.path.abspath(__file__))
    return [pkg_dir]

def get_incdirs():
    pkg_dir = os.path.dirname(os.path.abspath(__file__))
    if os.path.isdir(os.path.join(pkg_dir, "include")):
        return [os.path.join(pkg_dir, "include")]
    else:
        root_dir = os.path.abspath(os.path.join(pkg_dir, "../.."))
        return [os.path.join(root_dir, "src", "include")]

