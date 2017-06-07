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
void fnGetOptValueOnCPUSortDFS(const double *inBox, int inRank, int inNumBoxesSplitCoeff, double inEps, double inMaxIter, void (*inFun)(const double *,int,double *), double *outBox, double*outMin, double *outEps,int *outStatus)
{
	int maxArrayLen = 1000000;
	int incrementCoeff = 4;

	const int numBoxes = inNumBoxesSplitCoeff;

	double *boxes =  new double[numBoxes*inRank*2*maxArrayLen];
	double *boxesResult = new double[numBoxes*3*maxArrayLen];
	double h;
	int maxDimensionIndex = -1;
	double maxDimension = 0.0,minDimension=0.0,sumDimension=0.0;

	memcpy(boxes,inBox,inRank*2*sizeof(double));

	int numRestBoxes = 1;

	int countIter = 0;
	double curEps = inEps*10;
	
	inFun(inBox,inRank,boxesResult);
	double funcMin = boxesResult[2];
        double limitMin = boxesResult[0];

	int i,k,n;
        double leftBound;

	*outStatus = 1;
     
	while(true)
	{

            k = numRestBoxes - 1;

            maxDimensionIndex = 0;
            maxDimension = boxes[(k*inRank)*2 + 1] - boxes[(k*inRank)*2];
            minDimension = boxes[(k*inRank)*2 + 1] - boxes[(k*inRank)*2];
            sumDimension = 0.0;
            for(i = 0; i < inRank; i++)
            {
                h = (boxes[(k*inRank+i)*2 + 1] - boxes[(k*inRank+i)*2]);
                sumDimension+=h;
                if (maxDimension < h) {
                    maxDimension = h;
                    maxDimensionIndex = i;
                }
                if (minDimension > h) {
                    minDimension = h;
                }
				
            }
            h = maxDimension/(double)inNumBoxesSplitCoeff;
                
                
            if(funcMin < boxesResult[(numRestBoxes-1)*3] + inEps) {
                numRestBoxes--;
                if(numRestBoxes==0) {
                    *outEps = limitMin - funcMin > 0 ? limitMin - funcMin : funcMin - limitMin;
                    *outMin = funcMin;
                    return;
                }
                continue;
            }         

		for(n = 0; n < numBoxes; n++)
		{
                    for(i = 0; i < inRank; i++)
                    {              
                        leftBound = boxes[(k*inRank+i)*2];
			if (i==maxDimensionIndex) {
                            boxes[((k + n)*inRank+i)*2] = leftBound + h*n;
                            boxes[((k + n)*inRank+i)*2 + 1] = leftBound + h*(n+1);
                            } else {
				boxes[((k + n)*inRank+i)*2] = boxes[(k*inRank+i)*2];;
				boxes[((k + n)*inRank+i)*2 + 1] = boxes[(k*inRank+i)*2+1];
                            }
                    }
                    
                    inFun(&boxes[((k + n)*inRank)*2],inRank,&boxesResult[(k + n)*3]);
                    if(funcMin > boxesResult[(k+n)*3 + 2] ) {
                        funcMin = boxesResult[(k+n)*3+2];
                        limitMin = boxesResult[(k+n)*3];
                        for(int i = 0; i < inRank; i++) 
                            outBox[i] = (boxes[((k + n)*inRank+i)*2] + boxes[((k + n)*inRank+i)*2+1])/2.0;
                        }   
		}
                

/*
                        
                sort_quick_recursive(boxes,boxesResult,inRank, k + numBoxes);

		for(n = 0; n < k + numBoxes ; n++)
		{
			curEps = boxesResult[0] - funcMin > 0 ? boxesResult[0] - funcMin : funcMin -boxesResult[0];
			*outEps = curEps;
			*outMin = funcMin;
			if(curEps < inEps)
			{
				*outStatus = 0;
				//memcpy(outBox,boxes + boxMinIndex*inRank*2,inRank*2*sizeof(double));
				return;
			}
			if(funcMin < boxesResult[(n)*3] + inEps) break;		
		}

		numRestBoxes = n + numBoxes;
    */           
             
                numRestBoxes = k+numBoxes;
                         
                
		if(numRestBoxes > maxArrayLen) {
                        delete [] boxesResult;
			maxArrayLen *= incrementCoeff;                 
			double *temp = new double[numBoxes*inRank*2*maxArrayLen];
			boxesResult = new double[numBoxes*3*maxArrayLen];
			memcpy(temp,boxes,numRestBoxes*inRank*2*sizeof(double));
                        
                        delete [] boxes;
                        boxes = temp;
			
		}

		countIter++;
	}
}

