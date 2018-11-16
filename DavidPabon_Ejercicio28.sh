
mpicc -o integra integra.c
mpicc -o pi pi.c

mpiexec -np 16 ./pi
mpiexec -np 16 ./integra 1000
mpiexec -np 16 ./integra 10000
mpiexec -np 16 ./integra 100000

