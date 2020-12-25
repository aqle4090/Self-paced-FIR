from __future__ import print_function

import sys

sys.path.append('/home/xilinx')
from pynq import Overlay
from pynq import allocate
import numpy as np
from time import time

if __name__ == "__main__":
    print("Entry:", sys.argv[0])
    print("System argument(s):", len(sys.argv))

    print("Start of \"" + sys.argv[0] + "\"")

    ol = Overlay("/home/xilinx/IPBitFile/Yu_Chi/fir.bit")
    regIP = ol.fir_0
    
    numSamples = 256
    inBuffer0 = allocate(shape=(numSamples,), dtype=np.int32)
    outBuffer0 = allocate(shape=(numSamples,), dtype=np.int32)

    for i in range(numSamples):
        inBuffer0[i] = i
    timeKernelStart = time()
    regIP.write(0x80, len(inBuffer0) * 4)
    regIP.write(0x18, inBuffer0.device_address)
    regIP.write(0x10, outBuffer0.device_address)
    regIP.write(0x00, 0x01)
    while (regIP.read(0x00) & 0x4) == 0x0:
        continue
    timeKernelEnd = time()
    print("Kernel execution time: " + str(timeKernelEnd - timeKernelStart) + " s")

    print(" Output = " + str(outBuffer0[numSamples-1]))
    print("============================")
    print("Exit process")