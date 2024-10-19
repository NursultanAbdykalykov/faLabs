#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "functions.h"

#define PI 3.1415
#define MAX_INTERATION 47

long double binPow(long double a, int n) {
    long double res = 1;
    while (n != 0) {
        if (n & 1)
            res *= a;
        a *= a;
        n >>= 1;
    }
    return res;
}

long double factorial(int n) {
	long double res = 1.0;
	for (int i = 2; i <= n; i++) {
		res *= i;
	}
	return res;
}

long double eLimit(double epsilon) {
	long double e = 0.0;
	int n = 1;
	while (1) {
		long double term = binPow(1.0 + 1.0 / n, n);
		if (fabs(term - e) < epsilon) {
			break;
		}
		e = term;
		n++;
	}
	return e;
}

long double eSeries(double epsilon) {
	long double e = 1.0;
	long double term = 1.0;
	int n = 1;
	while (fabs(term) > epsilon) {
		term /= n;
		e += term;
		n++;
	}
	return e;
}

long double eEquation(double epsilon) {
	long double x = 2.0;
	while (fabs(log(x) - 1.0) > epsilon) {
		x -= (log(x) - 1.0) / (1.0 / x);
	}
	return x;
}

long double piLimit(double epsilon) {
	long double pi = 4;
	long double prev_pi = 0.0;
	int n = 1;
	while (fabs(pi - prev_pi) > epsilon) {
		prev_pi = pi;
		pi *= 4.0 * ((n + 1) * n) / binPow(2 * n + 1, 2);
		n++;
	}
	return pi;
}

long double piSeries(double epsilon) {
	long double pi = 1.0;
	long double term = 1.0;
	int n = 2;
	while (fabsl(term) > epsilon) {
		term = ((n - 1) % 2 ? -1.0 : 1.0) / (2 * n - 1);
		pi += term;
		n++;
	}
	return pi * 4;
}

long double piEquation(double epsilon) {
	long double x = 3.0;
	while (fabsl(cos(x) + 1.0) > epsilon) {
		x -= (cos(x) + 1.0) / (-sin(x));
	}
	return x;
}

long double ln2Limit(double epsilon) {
	long double ln2 = 0.0;
	long double term;
	int n = 1;
	while (1) {
		term = n * (powl(2, 1.0 / n) - 1);
		if (fabsl(term - ln2) < epsilon) {
			break;
		}
		ln2 = term;
		n++;
	}
	return ln2;
}

long double ln2Series(double epsilon) {
	long double ln2 = 0.0; 
	long double term = 1.0; 
	int sign = 1; 
	int n = 1;

	while (fabsl(term) > epsilon) { 
	    term = sign * (1.0 / n); 
	    ln2 += term; 
	    sign = -sign; 
	    n++; 
	}

	return ln2; 
}

long double ln2Equation(double epsilon) {
	long double x = 1.0; 
	while (fabsl(exp(x) - 2.0) > epsilon) { 
	    x -= (exp(x) - 2.0) / exp(x); 
	}
	return x; 
}

long double sqrt2Limit(double epsilon) {
	long double sqrt2 = -0.5; 
	long double next = sqrt2 - (sqrt2 * sqrt2)/2 + 1; 
	while (fabs(sqrt2 - next) > epsilon){ 
	    sqrt2 = next; 
	    next = sqrt2 - (sqrt2 * sqrt2)/2 + 1; 
	} 
	return next; 
}

long double sqrt2Series(double epsilon){
	long double sqrt2 = 1.0; // Начальное значение 
	long double term; 
	int k=2; 
	while(true){ 
	    term=powl(2, powl(2, -k)); 
	    sqrt2*=term; 
	    if(fabsl(term-1)<epsilon){ 
	        break; 
	    } 
	    k++; 
	  } 
	  return sqrt2; 
}

long double sqrt2Equation(double epsilon){
	long double x=1.0; 
	while(fabsl(x*x-2.0)>epsilon){ 
	    x -= (x*x-2.0)/(2*x);  
	  }  
	  return x;  
}

long double gammaLimit(double epsilon){
	long double gamma=0.0;  
	long double prev_gamma=0.0;  
	int m=1;  
	long double fact_m=1;  
	while(true){  
	    long double sum=0.0;  
	    long double fact_k=1;  
	    for(int k=1;k<=m;k++){  
	        fact_k*=k;  
	        long double binom=fact_m/(fact_k*factorial(m-k));  
	        sum+=binom*(k%2?-1.0:1.0)*log(fact_k)/k;  
	      }  

	      if(m==1){  
	          prev_gamma=-100;  
	      }else{  
	          prev_gamma=gamma;  
	      }  

	      gamma=sum;  

	      if(m>=MAX_INTERATION){  
	          return gamma;  
	      }  

	      if(fabsl(gamma-prev_gamma)<epsilon){  
	          break;  
	      }  
	      m++;  
	      fact_m*=m;  
	  }  

	  return gamma;  
}

long double gammaSeries(double epsilon){
	long double gamma=0;  
	long double term=0;  
	long double gamma_prev;  
	int k=2;

	while(true){   
	    gamma_prev=gamma;   
	    term=(1.0/pow(floor(sqrt(k)),2))-(1.0/k);   
	    gamma+=term;

	    if(fabsl(term)<epsilon && term!=0){   
	        break;   
	    }

	    k++;   
	  }

	  return gamma-PI*PI/6.0;   
}


bool isPrime(int n){
	if(n<2){   
	    return false;   
	  }
	for(int i=2;i<=sqrt(n);i++){   
	    if(n%i==0){   
	        return false;   
	      }
	  }
	return true;   
}


double prodResult(int t){
	double product=1.0;

	for(int p=2;p<=t;p++){   
	    if(isPrime(p)){   
	        product*=(double)(p-1)/p;   
	      }
	  }
	return product;   
}

long double gammaEquation(double epsilon){
	double t=2.0; // Начальное значение лимита
	double prev_x=0.0;

	for(int i=0;i<1000;i++){   
	    double product=prodResult((int)t);   

	    double current_x=log(t)*product;

	    if(fabs(current_x-prev_x)<epsilon){   
	        return current_x;   
	      }

	    prev_x=current_x;   
	    t+=1;   
	  }

	return prev_x;   
}

double myStrtod(const char* str, char** end){
	while(isspace((unsigned char)*str)){   
	    str++;   
	  }

	int sign=1;

	if(*str=='-'){   
	    sign=-1;   
	    str++;   
	  }else if(*str=='+'){   
	    str++;   
	  }

	double integer_part=0.0;

	while(isdigit((unsigned char)*str)){   
	    integer_part=integer_part*10+(*str-'0');   
	    str++;   
	  }

	double fraction_part=0.0;

	if(*str=='.'){   
	    str++;   

	    double divisor=10.0;

	    while(isdigit((unsigned char)*str)){   
	        fraction_part+=(*str-'0')/divisor;   
	        divisor*=10;   
	        str++;   
	      }
	  }

	double result=sign*(integer_part+fraction_part);

	if(end){   
	    *end=(char*)str;    
	  }

	return result;    
}