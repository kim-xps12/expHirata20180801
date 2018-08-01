#include<stdio.h>
#include<math.h>

#define DIGI_ROUND 10

const int M = 512;		//[-]


double hammiWindow(int n){
	
	double alpha = 25.0/46.0;
	return (alpha - (1-alpha)*(cos( (2*M_PI*n/M) )));
}



int main(void){

	double ans = 0;
	int i = 0;
	
	for(i=0; i<=M; i++){
		
		ans = hammiWindow(i);
		printf("%d,%lf\n", i, ans);
	}
 	
	return 0;
}