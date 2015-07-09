#!/usr/bin/env bash

doxygen && cd latex && make && cd .. && cp latex/refman.pdf mpi-summary.pdf
