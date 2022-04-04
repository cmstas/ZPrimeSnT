import time
import os
import sys

import numba
import numpy as np
import uproot

from itertools import izip

JaggedArray = uproot.interp.jagged.JaggedArray


f = uproot.open("../../508B6DBB-9742-E811-BA65-A4BF0112BCB0.root")
# f = uproot.open("../../6204E92D-C712-E811-AF42-E0071B740D80.root")
t = f["Events"]

t0 = time.time()
info = t.arrays(["Electron_pt","Electron_jetIdx","Jet_pt"]) #,entrystart=10, entrystop=15)
print("Read branches in {:.2f} seconds".format(time.time()-t0))

pts = info["Electron_pt"]
offsets = pts.offsets

from jagged_operations import jagged_foreach_function, \
        jagged_foreach_count, jagged_foreach_count_if, \
        jagged_foreach_sum, jagged_foreach_sum_if, \
        jagged_foreach_min, jagged_foreach_min_if, \
        jagged_foreach_max, jagged_foreach_max_if

def test_operation(name,func_fast,func_slow, jagged,masks=None):
    offsets = jagged.offsets
    content = jagged.content
    nevts = len(jagged)
    # call once here to not count jitting time after t0 is set
    if masks is None:
        accums_fast = func_fast(content,offsets)
    else:
        accums_fast = func_fast(content,offsets,masks)
    N = 100
    t0 = time.time()
    for _ in range(N):
        if masks is None:
            accums_fast = func_fast(content,offsets)
        else:
            accums_fast = func_fast(content,offsets,masks)
    if masks is None:
        t1 = time.time()
        accums_slow = np.array(map(func_slow,jagged))
        t2 = time.time()
    else:
        jmasks = JaggedArray(masks,jagged.starts,jagged.stops)
        t1 = time.time()
        accums_slow = np.array(map(func_slow,izip(jagged,jmasks))) # izip for generator
        t2 = time.time()

    slow_sum = accums_slow.sum()
    fast_sum = accums_fast.sum()
    slow_time = (t2-t1)
    fast_time = (t1-t0)/N
    pctdiff = 100.0*(fast_sum-slow_sum)/slow_sum
    col_pct_start = '\033[92m'
    col_time_start = '\033[92m'
    if abs(pctdiff) > 0.0001:
        col_pct_start = '\033[91m'
    if slow_time/fast_time < 25:
        col_time_start = '\033[91m'
    col_end = '\033[0m'
    print("{:<7} tfast={:.4f}s ({:.1f}MHz), slow={:.2f}s ({:.1f}MHz) -> {}{:.0f}x{} | sumfast={:.0f}, slow={:.0f}, {}%diff={:.4f}%{}".format(
            name, fast_time, 1.0e-6*nevts/fast_time, slow_time,1.0e-6*nevts/slow_time, 
            col_time_start,slow_time/fast_time,col_end, 
            fast_sum, slow_sum, col_pct_start,pctdiff,col_end))


# note. numba jitting does not yet support builtins like min,max (WTF), so have to use numpy's
mymin = lambda x: 0. if not len(x) else np.min(x)
mymax = lambda x: 0. if not len(x) else np.max(x)

def min_mask((x,m)):
    mx = x[m]
    if len(mx): return min(mx)
    else: return 0.
def max_mask((x,m)):
    mx = x[m]
    if len(mx): return max(mx)
    else: return 0.
def sum_mask((x,m)):
    return sum(x[m],0.)
def len_mask((x,m)):
    return len(x[m])


# print jagged_foreach_function(lambda x: np.sum(x))(pts.content, pts.offsets)
# print jagged_operation(pts, "func", func=lambda x: np.sum(x))

test_operation("func", jagged_foreach_function(mymin), mymin, pts)
test_operation("count", jagged_foreach_count, len, pts)
test_operation("sum", jagged_foreach_sum, sum, pts)
test_operation("min", jagged_foreach_min, mymin, pts)
test_operation("max", jagged_foreach_max, mymax, pts)
test_operation("countif", jagged_foreach_count_if, len_mask, pts, masks=pts.content>15)
test_operation("sumif", jagged_foreach_sum_if, sum_mask, pts, masks=pts.content>15)
test_operation("minif", jagged_foreach_min_if, min_mask, pts, masks=pts.content>15)
test_operation("maxif", jagged_foreach_max_if, max_mask, pts, masks=pts.content>15)

