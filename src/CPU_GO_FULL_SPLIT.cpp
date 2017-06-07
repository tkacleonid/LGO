/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File: CPU_GO_FULL_SPLIT.cpp
 * Author: Leodid, Tkachenko
 * 
 * 
 */


#include "CPU_GO.h"
#include "interval.h"
#include "boxes_sort.h"



/**
*	Calculus minimum value for function on CPU
*	@param inbox pointer to Box
*	@param inRank number of variables
*	@param inNumBoxesSplitCoeff number of parts for each dimension
*	@param inEps required accuracy
*	@param inMaxIter maximum count of iterations
*	@param inFun pointer to optimazing function
*	@param outBox pointer to optimal box
*	@param outMin pointer to optimal value
*	@param outEps pointer to reached accuracy
*	@param outEps pointer to status of solving optimization problem
*/
void fnGetOptValueOnCPUSort(const double *inBox, const int inRank, const int inNumBoxesSplitCoeff, const double inEps, const double inMaxIter, void (*inFun)(const double *,int,double *), double *outBox, double*outMin, double *outEps,int *outStatus)
{
    int maxArrayLen = 50000000;
    int incrementCoeff = 2;

    const int numBoxes = inNumBoxesSplitCoeff;

    double *boxes =  new double[numBoxes*inRank*2*maxArrayLen];
    double *boxesResult = new double[numBoxes*3*maxArrayLen];
    double *restBoxes = new double[numBoxes*inRank*2*maxArrayLen];
    double *tempRestBoxes = NULL;
    double h;
    int numNewBoxes = 0;
    int maxDimensionIndex = -1;
    double maxDimension = 0.0;

    memcpy(restBoxes,inBox,inRank*2*sizeof(double));

    int numRestBoxes = 1;

    int countIter = 0;
    double curEps = inEps*10;
	
    inFun(inBox,inRank,boxesResult);
    double funcMin = boxesResult[2];

    int i,k,n;

    *outStatus = 1;

    while(true) {
        if(countIter == inMaxIter || numRestBoxes == 0) {
            delete [] restBoxes;
            delete [] boxes;
            delete [] boxesResult;
            break;
	} 
        
        for(k = 0; k < numRestBoxes; k++){
            maxDimensionIndex = 0;
            maxDimension = restBoxes[(k*inRank)*2 + 1] - restBoxes[(k*inRank)*2];
            for(int i = 0; i < inRank; i++){
		h = (restBoxes[(k*inRank+i)*2 + 1] - restBoxes[(k*inRank+i)*2]);
		if (maxDimension < h) {
                    maxDimension = h;
                    maxDimensionIndex = i;
		}
            }
            h = maxDimension/inNumBoxesSplitCoeff;
            for(n = 0; n < numBoxes; n++)   {
		for(i = 0; i < inRank; i++) {
                    if (i==maxDimensionIndex) {
			boxes[((k*numBoxes + n)*inRank+i)*2] = restBoxes[(k*inRank+i)*2] + h*n;
			boxes[((k*numBoxes + n)*inRank+i)*2 + 1] = restBoxes[(k*inRank+i)*2] + h*(n+1);
                    } else {
                        boxes[((k*numBoxes + n)*inRank+i)*2] = restBoxes[(k*inRank+i)*2];
			boxes[((k*numBoxes + n)*inRank+i)*2 + 1] = restBoxes[(k*inRank+i)*2 + 1];
                    }
		}
		inFun(&boxes[((k*numBoxes + n)*inRank)*2],inRank,&boxesResult[(k*numBoxes + n)*3]);
            }
        }
	for(n = 0; n < numRestBoxes*numBoxes; n++)  {
            if(funcMin > boxesResult[n*3 + 2] ) {
                funcMin = boxesResult[n*3+2];
                for(int i = 0; i < inRank; i++) 
                    outBox[i] = (boxes[(n*inRank + i)*2] + boxes[(n*inRank + i)*2+1])/2.0;
            }
	}
        
        sort_quick_recursive(boxes,boxesResult,inRank, numRestBoxes*numBoxes);
        
	for(n = 0; n < numRestBoxes*numBoxes; n++){
            if(funcMin < boxesResult[(n)*3] + inEps) break;	
	}
	curEps = boxesResult[0] - funcMin > 0 ? boxesResult[0] - funcMin : funcMin - boxesResult[0];
	*outEps = curEps;
	*outMin = funcMin;
	if(curEps < inEps) {
            *outStatus = 0;
            return;
	}

	numNewBoxes = n;

	if(numRestBoxes*numBoxes > maxArrayLen) {
            delete [] restBoxes;
            delete [] boxesResult;

            maxArrayLen *= incrementCoeff;
            restBoxes = new double[numNewBoxes*inRank*2*maxArrayLen];
            std::cout << (restBoxes==nullptr);
            boxesResult = new double[numBoxes*3*maxArrayLen];
            memcpy(restBoxes,boxes,numNewBoxes*inRank*2*sizeof(double));
            delete [] boxes;
            boxes = new double[numBoxes*inRank*2*maxArrayLen];
	} else {
            tempRestBoxes = boxes;
            boxes = restBoxes;
            restBoxes = tempRestBoxes;
	}

	numRestBoxes = numNewBoxes;

        //std::cout << "n = " << numRestBoxes  << "\tmin" << funcMin << "\n";
        //printf("[%.15lf]\t[%.13lf]\n",funcMin,curEps);
	countIter++;
    }
}











