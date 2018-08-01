#include<stdio.h>
#include<math.h>


const int M = 512;		//[-]


double blkHrsWindow(int n){
	
	return (0.423 - 0.498*(cos( (2*M_PI*n/M) )) + 0.0792*(cos( (4*M_PI*n/M) )));
}



int main(void){

	double ans = 0;
	int i = 0;
	
	for(i=0; i<=M; i++){
		
		ans = blkHrsWindow(i);
		printf("%d,%lf\n", i, ans);
	}
 	
	return 0;
}