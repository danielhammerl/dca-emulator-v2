DCA Emulator refactored, improved and re-written in C++

Performance is compared to v1 (NodeJS version) round about 250(!!) times faster!
(NodeJS version got about 110-130K instructions per second without gpu, c++ version about 20-35M instructions per second, compared with the gpu3 example program on apple m1 mac)