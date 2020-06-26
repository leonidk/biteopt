from math import sqrt,atan2,pi,exp,cos,sin

spice_jar_best = -1.9132229549810362
def spice_jar(x):
    x1,x2 = x
    return sin(x1 + x2) + (x1 - x2) ** 2 - 1.5 * x1 + 2.5 * x2 + 1

import biteopt
res = biteopt.minimize(spice_jar,[-1.5,-3],[4,4],1,1,500)
res_fx = spice_jar(res)
print(res_fx)
print(abs(spice_jar_best-res_fx) < 1e-2)