This program implements the slicing tree sizing algorithm, which takes a floorplan topology and a list of possible shapes for each module and computes the optimal area of the floorplan. For this algorithm, individual blocks may rotate, but after they are joined by a "V" or "H" operator, they may no longer rotate. 
The program requires an input file, where the ith row provides information for module i, for all i = 1,2...n. The first column is the name (which must match the name in the topology), the second is the area, and the third is the aspect ratio (height / width).

This program continues on to run a simulated annealing algorithm on the previous idea. This algorithm allows for worse solutions occasionally, depending on a probability that decreases with time.

[Linux]
Type "make" without quotes to compile and run.
