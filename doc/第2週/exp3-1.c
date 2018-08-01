#include<stdio.h>
#include<math.h>

#define DIGI_ROUND 10

const int M = 15;		//[-]


double hanWindow(int n){
	
	return 0.5*(1-cos( (2*M_PI*n/M) ));
}



int main(void){

	double ans = 0;
	int i = 0;
	
	for(i=0; i<=M; i++){
		
		ans = hanWindow(i);
		printf("%d,%lf\n", i, ans);
	}
 	
	return 0;
}