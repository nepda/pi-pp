# Parallele Programmierung

	ssh chiclogin1.informatik.tu-chemnitz.de
	
	module initadd comp/gcc/422
	module initadd mpi/openmpi/gcc422
	
	bash
	
	cp -R /afs/tu-chemnitz.de/home/urz/`whoami | cut -b 1`/`whoami`/PP ~/PP
	
	mpicc -o programm programm.c
	
	qsub -I -l nodes=4:ppn=1,walltime=00:10:00 -q short
	
	mpirun -np 4 ./programm
