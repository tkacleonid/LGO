#pragma once

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <omp.h>
#include <chrono>




void fnGetOptValueOnCPU(const double *inBox, int inRank, int inNumBoxesSplitCoeff, double inEps, double inMaxIter, void (*inFun)(const double *,int,double *), double *outBox, double*outMin, double *outEps,int *outStatus);
void fnGetOptValueOnCPUSort(const double *inBox, int inRank, int inNumBoxesSplitCoeff, double inEps, double inMaxIter, void (*inFun)(const double *,int,double *), double *outBox, double*outMin, double *outEps,int *outStatus);
void fnGetOptValueOnCPUSortOMP(const double *inBox, int inRank, int inNumBoxesSplitCoeff, double inEps, double inMaxIter, void (*inFun)(const double *,int,double *), double *outBox, double*outMin, double *outEps,int *outStatus);
void fnGetOptValueOnCPUSortDFS(const double *inBox, int inRank, int inNumBoxesSplitCoeff, double inEps, double inMaxIter, void (*inFun)(const double *,int,double *), double *outBox, double*outMin, double *outEps,int *outStatus);




