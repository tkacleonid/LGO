/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   test_func_own_impl.h
 * Author: leo
 *
 */

#pragma once



/**
*	Calculus Interval for Multiple function on CPU
*	@param inbox pointer to Box
*	@param inRank number of variables
*	@param outlimits pointer to estimated function limits
*/
void fnCalcFunLimitsMultiple2(const double *inBox, int inRank, double *outLimits)
{
	double x1 = (inBox[0]+inBox[1])/2;
	double x2 = (inBox[2]+inBox[3])/2;

	double var1 = inBox[0]*inBox[2];
	double var2 = inBox[0]*inBox[3];
	double var3 = inBox[1]*inBox[2];
	double var4 = inBox[1]*inBox[3];

	outLimits[0] = std::min(std::min(var1,var2),std::min(var3,var4));
	outLimits[1] = std::max(std::max(var1,var2),std::max(var3,var4));
	outLimits[2] = x1*x2;
}

/**
*	Calculus Interval for Hyperbolic function on CPU
*	@param inbox pointer to Box
*	@param inRank number of variables
*	@param outlimits pointer to estimated function limits
*/
void fnCalcFunLimitsHypebolic2(const double *inBox, int inRank, double *outLimits)
{
	double limits[2];
	double limits2[2];

	double x1 = (inBox[0]+inBox[1])/2;
	double x2 = (inBox[2]+inBox[3])/2;

	double var1 = inBox[0]*inBox[0];
	double var2 = inBox[0]*inBox[1];
	double var3 = inBox[1]*inBox[0];
	double var4 = inBox[1]*inBox[1];

	limits[0] = var2 < 0 ? 0 : std::min(std::min(var1,var2),std::min(var3,var4));
	limits[1] = std::max(std::max(var1,var2),std::max(var3,var4));

	var1 = inBox[2]*inBox[2];
	var2 = inBox[2]*inBox[3];
	var3 = inBox[3]*inBox[2];
	var4 = inBox[3]*inBox[3];

	limits2[0] = var2 < 0 ? 0 : std::min(std::min(var1,var2),std::min(var3,var4));
	limits2[1] = std::max(std::max(var1,var2),std::max(var3,var4));

	outLimits[0] = limits[0] - limits2[1];
	outLimits[1] = limits[1] - limits2[0];

	outLimits[2] = x1*x1-x2*x2;
}

/**
*	Calculus Interval for AluffiPentini function on CPU
*	@param inbox pointer to Box
*	@param inRank number of variables
*	@param outlimits pointer to estimated function limits
*/
void fnCalcFunLimitsAluffiPentini2(const double *inBox, int inRank, double *outLimits)
{
		double limits[2];
	double limits2[2];

	double x1 = (inBox[0]+inBox[1])/2;
	double x2 = (inBox[2]+inBox[3])/2;

	double var1 = inBox[0]*inBox[0];
	double var2 = inBox[0]*inBox[1];
	double var3 = inBox[1]*inBox[0];
	double var4 = inBox[1]*inBox[1];

	limits[0] = var2 < 0 ? 0 : std::min(std::min(var1,var2),std::min(var3,var4));
	limits[1] = std::max(std::max(var1,var2),std::max(var3,var4));

	var1 = inBox[2]*inBox[2];
	var2 = inBox[2]*inBox[3];
	var3 = inBox[3]*inBox[2];
	var4 = inBox[3]*inBox[3];

	limits2[0] = limits[0]*limits[0];
	limits2[1] = limits[1]*limits[1];

	outLimits[0] = 0.25*limits2[0] - 0.5*limits[1] + 0.1*inBox[0] + 0.5*(var2 < 0 ? 0 : std::min(std::min(var1,var2),std::min(var3,var4)));
	outLimits[1] = 0.25*limits2[1] - 0.5*limits[0] + 0.1*inBox[1] + 0.5*(std::max(std::max(var1,var2),std::max(var3,var4)));
	outLimits[2] = 0.25*pow(x1,4)-0.5*pow(x1,2) + 0.1*x1 + 0.5*pow(x2,2);
}


 double fnCalcFunRozenbroke(const double *inBox, int inRank)
{
	int i;
	double val = 0;;
	for(i = 0; i < inRank - 1; i++)
	{
		val += ((1 - inBox[i])*(1 - inBox[i]) + 100.0*(inBox[i+1]-inBox[i]*inBox[i])*(inBox[i+1]-inBox[i]*inBox[i]));
	}
	return val;
}

/**
*	Calculus Interval for Rozenbroke function on CPU
*	@param inbox pointer to Box
*	@param inRank number of variables
*	@param outlimits pointer to estimated function limits
*/
void fnCalcFunLimitsRozenbroke(const double *inBox, int inRank, double *outLimits)
{

	double sup = 0;
	double sub = 0;

	double sup1,sub1,sup2,sub2, a,b, val = 0,var1,var2,var3,x1,x2;


	for(int i = 0; i < inRank - 1; i++)
	{
		sub1 = 1 - inBox[i*2 + 1];
		sup1 = 1 - inBox[i*2];

		var1 = sup1*sup1;
		var2 = sup1*sub1;
		var3 = sub1*sub1;
		
		if(sub1*sup1 < 0) sub1 = 0;
		else sub1 = std::min(std::min(var1,var2),var3);
		sup1 = std::max(std::max(var1,var2),var3);


		var1 = inBox[i*2 + 1]*inBox[i*2 + 1];
		var2 = inBox[i*2 + 1]*inBox[i*2];
		var3 = inBox[i*2]*inBox[i*2];

		if(inBox[i*2 + 1]*inBox[i*2] < 0) a = 0;
		else a = std::min(std::min(var1,var2),var3);
		b = std::max(std::max(var1,var2),var3);

		sub2 = inBox[(i+1)*2] - b;
		sup2 = inBox[(i+1)*2 + 1] - a;

		var1 = sup2*sup2;
		var2 = sup2*sub2;
		var3 = sub2*sub2;

		if(sub2*sup2 < 0) sub2 = 0;
		else sub2 = 100*std::min(std::min(var1,var2),var3);
		sup2 = 100*std::max(std::max(var1,var2),var3);

		sub += sub1 + sub2;
		sup += sup1 + sup2;

		x1 = (inBox[i*2 + 1] + inBox[i*2])/2;
		x2 = (inBox[(i+1)*2 + 1] + inBox[(i+1)*2])/2;
		val += ((1 - x1)*(1 - x1) + 100*(x2-x1*x1)*(x2-x1*x1));

	}

	outLimits[0] = sub;
	outLimits[1] = sup;
	outLimits[2] = val;

/*
	double *x;
	x = (double *) malloc(inRank*sizeof(double));
	double minFun;
	int index;
	double md;
	double pw;
	double a1;
	double b1;
	int numFunValues = int(pow(2.0,double(inRank)));

	
	int i,j;
	
	for(j = 0; j < inRank; j++){
			x[j] = (inBox[j*2]+inBox[j*2+1])/2.0;
	}
	minFun = fnCalcFunRozenbroke(x, inRank);
	for(i = 0; i < numFunValues; i++){
		for(j = 0; j < inRank; j++){
			a1 = double(i);
			b1 = double(j+1);
			md = fmod(a1,pow(2.0,b1));
			pw = pow(2.0,(b1-1.0));
			index = int(md / pw);
			x[j] = inBox[j*2+index];
		}
		val = fnCalcFunRozenbroke(x, inRank);
		if(minFun > val) minFun = val;
	}

	free(x);

	outLimits[0] = sub;
	outLimits[1] = sup;
	outLimits[2] = minFun;

*/

}