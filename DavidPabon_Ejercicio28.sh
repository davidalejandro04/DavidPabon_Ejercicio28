make

module load rocks-openmpi_ib
mpirun_rsh -np -hostfile hosts ./pi
