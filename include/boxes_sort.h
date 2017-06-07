/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   boxes_sort.h
 * Author: Leonid, Tkachenko
 *
 * Created on June 6, 2017, 12:37 PM
 */

#pragma once


/*!
* quickSortOMP - параллельная реализация алгоритма быстрой сортировки
* @param boxes сортируемый массив брусов
* @param boxesResult сортируемый массив  интервальных оценок
* @param inRank рамерность бруса
* @param n индекс последнего элемента массива (не размер массива!)
*/
void quickSortOMP(double* boxes,double* boxesResult, const int inRank, const long n);


/*!
* quickSortBase - последовательная реализация алгоритма быстрой сортировки
* @param boxes сортируемый массив брусов
* @param boxesResult сортируемый массив  интервальных оценок
* @param inRank рамерность бруса
* @param l левое опрное значение
* @param r правое опорное значение
*/
void quickSortBase(double *boxes,double *boxesResult, const int inRank, const int l, const int r);


/*!
* sort_quick_recursive - вызов алгоритма быстрой сортировки
* @param boxes сортируемый массив брусов
* @param boxesResult сортируемый массив  интервальных оценок
* @param inRank рамерность бруса
* @param n количество брусов
*/
void sort_quick_recursive(double *boxes,double *boxesResult, const int inRank, const int n);




