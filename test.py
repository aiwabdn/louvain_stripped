import numpy as np
from ctypes import *

x = np.loadtxt('/Users/anindya/Downloads/edge_list.txt', delimiter=' ')
louvain = cdll.LoadLibrary('./obj/liblouv.so')

g = louvain.runLouvain(c_void_p(x.ctypes.data), c_int(x.shape[0]))
