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

#include "interval.h"

/*!
* quickSortOMP - параллельная реализация алгоритма быстрой сортировки
* @param boxes сортируемый массив брусов
* @param boxesResult сортируемый массив  интервальных оценок
* @param inRank рамерность бруса
* @param n индекс последнего элемента массива (не размер массива!)
*/
void quickSortOMP(double* boxes,double* boxesResult, const int inRank, const long n) {
	long i = 0, j = n;
	double pivot = boxesResult[(n / 2)*3]; // опорный элемент
	do {
		while (boxesResult[i*3] < pivot) i++;
		while (boxesResult[j*3] > pivot) j--;
		if (i <= j) {
			std::swap(boxesResult[i*3], boxesResult[j*3]);
			std::swap(boxesResult[i*3+1], boxesResult[j*3+1]);
			std::swap(boxesResult[i*3+2], boxesResult[j*3+2]);

			for(int m = 0; m < inRank; m++) {
				std::swap(boxes[2*(inRank*i+m)], boxes[2*(inRank*j+m)]);
				std::swap(boxes[2*(inRank*i+m)+1], boxes[2*(inRank*j+m)+1]);
			}
			i++; j--;
		}
	} while (i <= j);

	if (n < 100) { // если размер массива меньше 100
		// сортировка выполняется в текущем потоке
		if (j > 0) quickSortOMP(boxes,boxesResult,inRank, j);
		if (n > i) quickSortOMP(boxes+inRank*2*i,boxesResult+3*i,inRank, n - i);
		return;
	}

	#pragma omp task shared(boxes,boxesResult)
		if (j > 0) quickSortOMP(boxes,boxesResult,inRank, j);
	#pragma omp task shared(boxes,boxesResult)
		if (n > i) quickSortOMP(boxes+inRank*2*i,boxesResult+3*i,inRank, n - i);
	#pragma omp taskwait
}


/*!
* quickSortBase - последовательная реализация алгоритма быстрой сортировки
* @param boxes сортируемый массив брусов
* @param boxesResult сортируемый массив  интервальных оценок
* @param inRank рамерность бруса
* @param l левое опрное значение
* @param r правое опорное значение
*/
void quickSortBase(double *boxes,double *boxesResult, const int inRank, const int l, const int r) {
    int i = l, j = r,m;
    double pp[3] = { boxesResult[3*l], boxesResult[3*r], boxesResult[3*((l+r)>>1)]};
    double p = pp[0];
    if (pp[1] >= pp[0] && pp[1]<=pp[0]) p=pp[1];
    else if (pp[2] >= pp[0] && pp[2]<=pp[1]) p=pp[2];
    
    while (i <= j) {
        while (p > boxesResult[3*i])
           i++;
        while (boxesResult[3*j] > p)
           j--;
        if (i <= j) {
			double temp;
			temp = boxesResult[i*3];
			boxesResult[i*3] = boxesResult[j*3];
			boxesResult[j*3] = temp;

			temp = boxesResult[i*3+1];
			boxesResult[i*3+1] = boxesResult[j*3+1];
			boxesResult[j*3+1] = temp;

			temp = boxesResult[i*3+2];
			boxesResult[i*3+2] = boxesResult[j*3+2];
			boxesResult[j*3+2] = temp;

			for(m=0; m < inRank; m++)
			{
				temp = boxes[(i*inRank+m)*2];
				boxes[(i*inRank+m)*2] = boxes[(j*inRank+m)*2];
				boxes[(j*inRank+m)*2] = temp;

				temp = boxes[(i*inRank+m)*2+1];
				boxes[(i*inRank+m)*2+1] = boxes[(j*inRank+m)*2+1];
				boxes[(j*inRank+m)*2+1] = temp;
			}
            i++;
            j--;
        }
    }

    if (l < j)
       quickSortBase(boxes,boxesResult,inRank, l, j);
    if (i < r)
       quickSortBase(boxes,boxesResult,inRank, i, r);
}


/*!
* sort_quick_recursive - вызов алгоритма быстрой сортировки
* @param boxes сортируемый массив брусов
* @param boxesResult сортируемый массив  интервальных оценок
* @param inRank рамерность бруса
* @param n количество брусов
*/
void sort_quick_recursive(double *boxes,double *boxesResult, const int inRank, const int n) {
   quickSortBase(boxes,boxesResult,inRank,0,n-1);
}


