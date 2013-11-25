/*
 *  GFUtility.cpp
 *  GestureFollower
 *
 *  Created by Bruno Zamborlin on 6/9/08.
 *	Copyright (C) 2008 by IRCAM-Centre Georges Pompidou, Paris, France.
 */

#include "GFlibUtility.h"


const float GFlibUtility::E =				2.718282;
const float GFlibUtility::FLOAT_EPSILON =	1.192092896e-07F;
const float GFlibUtility::MIN_PROB =	1e-30;



/***********************			UTILITY					********************/

int		GFlibUtility::highestValueIndex(const float* a, const int size){	//returns the index of the max value in a list
	int t = 0;
	for (short i = 1; i < size; ++i){
		if (a[i] > a[t])
			t = i;
	}
	return t;
}
float	GFlibUtility::Mean(float* a, int size){	//returns the mean of a list
	float t = 0;
	for (short i=0; i< size; ++i){
		t += i * a[i];
	}
	return t/size;
}

float	GFlibUtility::Variance(float* a, int size){	//returns the vairance (unbiased) of a list
		float sum_x = 0;
		float sum_x2 = 0;
		float var;
		for (short i=0; i< size; ++i){
			sum_x += a[i];
			sum_x2 += a[i] * a[i];
		}
		if (size>1) {
			var =   ( sum_x2 - (sum_x * sum_x)/size ) / (size-1);
		}
		if ((size=1)|| (var <0))
		{
			var = 0;
		}		
		return var;
	}

float	GFlibUtility::Sum(float* a, int size){	//returns the sum of a T
	float t = 0;
	for (short i=0; i<size; ++i){
		t += a[i];
	}
	return t;
}
float	GFlibUtility::Max(float* a, int size){	//returns the maximum value in a list
	float t = a[0];
	for (short i=0; i<size; ++i)
		t = max(t, a[i]);
	return t;
}
float	GFlibUtility::Min(float* a, int size){	//returns the minimum value in a list
	float t = a[0];
	for (short i=0; i<size; ++i)
		t = min(t, a[i]);
	return t;
}
int		GFlibUtility::hightestValueIndex(float* a, int size, bool* filterVector){	//returns the index of the max value in a list
	int t = 0;
	for (short i = 1; i < size; ++i){
		if (a[i] > a[t] && filterVector[i])
			t = i;
	}
	return t;
}
float	GFlibUtility::Mean(float* a, int size, bool* filterVector){	//returns the mean of a list
	float t = 0;
	for (short i=0; i< size; ++i){
		if (filterVector[i])
			t += i * a[i];
	}
	return t/size;
}

float	GFlibUtility::Variance(float* a, int size, bool* filterVector){	//returns the vairance (unbiased) of a list
	float sum_x = 0;
	float sum_x2 = 0;
	float var;
	for (short i=0; i< size; ++i){
		if (filterVector[i]){
		sum_x += a[i];
		sum_x2 += a[i] * a[i];
		}	
	}
	if (size>1) {
		var =   ( sum_x2 - (sum_x * sum_x)/size ) / (size-1);
	}
	if ((size=1)|| (var <0))
	{
		var = 0;
	}		
	return var;
}



float	GFlibUtility::Sum(float* a, int size, bool* filterVector){	//returns the sum of a T
	float t = 0;
	
	for (short i=0; i<size; ++i){
		if (filterVector[i])
			t += a[i];
	}
	return t;
}
float	GFlibUtility::Max(float* a, int size, bool* filterVector){	//returns the maximum value in a list
	float t = a[0];
	
	for (short i=0; i<size; ++i)
		if (filterVector[i])
			t = max(t, a[i]);
	return t;
}
float	GFlibUtility::Min(float* a, int size, bool* filterVector){	//returns the minimum value in a list
	float t = a[0];
	for (short i=0; i<size; ++i)
		if (filterVector[i])
			t = min(t, a[i]);
	return t;
}

int		GFlibUtility::highestValueIndex	(float* a, int calculationWindowStart, int calculationWindowEnd, int size){
  int t = calculationWindowStart;
  int i = calculationWindowStart;
  while (true){
	if (a[i] > a[t])
	  t = i;
	if (i==calculationWindowEnd) break;
	i = (i+1) % size;
  }
  
  return t;
}


float	GFlibUtility::Mean				(float* a, int calculationWindowStart, int calculationWindowEnd, int size){
  float t = 0;
  float sum = 0;
  int i = calculationWindowStart;
  while (true){
	t += i * a[i];
    sum += a[i];
	if (i==calculationWindowEnd) break;
	i = (i+1) % size;
  }
  return t / sum;
}

float	GFlibUtility::Variance				(float* a, int calculationWindowStart, int calculationWindowEnd, int size){
	float sum_x = 0;
	float sum_x2 = 0;
	float n = 0;
	float var;
	int i = calculationWindowStart;
	while (true){
		sum_x += a[i];
		sum_x2 += a[i] * a[i];
		n+=1;
		if (i==calculationWindowEnd) break;
		i = (i+1) % size;
	}
	if (n>1) {
		var =   ( sum_x2 - (sum_x * sum_x)/n ) / (n-1);
	}
	if ((n=1)|| (var <0))
	{
		var = 0;
	}		
	return var;
}

float	GFlibUtility::Sum					(float* a, int calculationWindowStart, int calculationWindowEnd, int size){
  float t = 0;
  
  int i = calculationWindowStart;
  while (true){
	t += a[i];
	if (i==calculationWindowEnd) break;
	i = (i+1) % size;
  }
  
  return t;
}
float	GFlibUtility::Max					(float* a, int calculationWindowStart, int calculationWindowEnd, int size){
  float t = a[0];
  
  int i = calculationWindowStart;
  while (true){
	t = max(t, a[i]);
	if (i==calculationWindowEnd) break;
	i = (i+1) % size;
  }
  
  return t;
}
float	GFlibUtility::Min					(float* a, int calculationWindowStart, int calculationWindowEnd, int size){
  float t = a[0];
  int i = calculationWindowStart;
  while (true){
	t = min(t, a[i]);
	if (i==calculationWindowEnd) break;
	i = (i+1) % size;
  }
  return t;
}





float	GFlibUtility::Mahalanobis(float* a,	float* b, int size, float* weights, float stddev){	//returns the Mahalanobis distance between "a" and "b", both with same size. b starts at "b_pos" position
	//no control for size>0 and stddev>0 for optimization
	float d = 0;
	for (short i=0; i<size; ++i){
		if (weights[i] != 0){      
			d += pow((b[i]-a[i]) / stddev , 2) * weights[i];
		}
	}
	return (pow(E , -d) + GFlibUtility::MIN_PROB);
}



float	GFlibUtility::KullbackLeibler(float* a,	float* b, int b_pos, int size, float* weights, float stddev){	//returns the Kullback-Leibler distance between "a" and "b", both with same size. b starts at "b_pos" position
	//no control for size>0 and stddev>0 for optimization
	float d = 0;
	for (short i=0; i<size; ++i){
		if (weights[i] != 0){
			if (b[b_pos+i] != 0) {
				d += (a[i] * log(a[i] / b[b_pos+i]) +  b[i] * log(b[i] / a[b_pos+i]) ) * weights[i];
			}
			else {
				d += (a[i] * log(a[i] / FLOAT_EPSILON) + b[i] * log(b[i] / FLOAT_EPSILON)) * weights[i];
			}
		}
	}
	return d;
}
float	GFlibUtility::scale				(float in, float lowIn, float highIn, float lowOut, float highOut){			//scale the input from [lowIn,highIn] to [lowOut,hiOut]
	return (in-lowIn) / (highIn-lowIn) * (highOut-lowOut) + lowOut;
}
float GFlibUtility::fmod(float a,float b) {
	return (a/b)- (((int)(a/b))*b);
}

void	GFlibUtility::Sorti				(float* list, int size, int* result){													//returns indexes of elements of the corresponding sorted list 
  
  for (int i=0; i<size; ++i) {
	int c = 0;
	for (int j=0; j<size; ++j){
	  if ( list[i]<list[j] || (list[i]==list[j] && i<j) )
        ++c;
	}
	result[c] = i+1;
  }
}






