/*
 *  GFUtility.h
 *  GestureFollower
 *
 *  Created by Bruno Zamborlin on 6/9/08.
 *	Copyright (C) 2008 by IRCAM-Centre Georges Pompidou, Paris, France.
 */


#ifndef GFUTILITY
#define GFUTILITY


#include <math.h>
#include <float.h>
#include <algorithm>

using namespace std;

/***********************			UTILITY				********************/


class GFlibUtility{
  
public:
  
  static const float E;
  static const float FLOAT_EPSILON;
  static const float MIN_PROB;
	
	
  static int	highestValueIndex	(const float* a, const int size);											//returns the index of the max value in a list
  static float	Mean				(float* a, int size);														//returns the mean of a float_vect
  static float	Variance			(float* a, int size);														//returns the variance (unbiased) of a float_vect
  static float	Sum					(float* a, int size);														//returns the sum  of a float_vect
  static float	Max					(float* a, int size);														//returns the max  of a float_vect
  static float	Min					(float* a, int size);														//returns the min  of a float_vect
  static int	hightestValueIndex	(float* a, int size, bool* filterVector);									//returns the index of the max value in a list based on the filter vector
  static float	Mean				(float* a, int size, bool* filterVector);									//returns the mean of a float_vect based on the filter vector
  static float	Variance		    (float* a, int size, bool* filterVector);								//returns the variance (unbiased) a float_vect based on the filter vector
  static float	Sum					(float* a, int size, bool* filterVector);									//returns the sum  of a float_vect based on the filter vector
  static float	Max					(float* a, int size, bool* filterVector);									//returns the max  of a float_vect based on the filter vector
  static float	Min					(float* a, int size, bool* filterVector);									//returns the min  of a float_vect based on the filter vector
  
  
  static int	highestValueIndex	(float* a, int calculationWindowStart, int calculationWindowEnd, int size);	//returns the index of the max value in a list based on a window
  static float	Mean				(float* a, int calculationWindowStart, int calculationWindowEnd, int size);	//returns the mean of a float_vect based on a window
  static float	Variance			(float* a, int calculationWindowStart, int calculationWindowEnd, int size);//returns the variance (unbiased) of a float_vect based on a window
  static float	Sum					(float* a, int calculationWindowStart, int calculationWindowEnd, int size);	//returns the sum  of a float_vect based on a window
  static float	Max					(float* a, int calculationWindowStart, int calculationWindowEnd, int size);	//returns the max  of a float_vect based on a window
  static float	Min					(float* a, int calculationWindowStart, int calculationWindowEnd, int size);	//returns the min  of a float_vect based on a window
  
  
  static float	Mahalanobis			(float* a,	float* b,  int size, float* weight, float stddev);				//returns the Mahalanobis distance between two vectors with a given length
  static float	KullbackLeibler		(float* a,	float* b, int b_pos, int size, float* weight, float stddev);	//returns the Kullback-Leibler distance between two vectors with a given length
  static float	scale				(float in, float lowIn, float highIn, float lowOut, float highOut);			//scale the input from [lowIn,highIn] to [lowOut,hiOut]
  static float	fmod				(float, float);																//float modulo
  static void	Sorti				(float* list, int size, int* result);													//returns indexes of elements of the corresponding sorted list 
};



#endif
