#include<stdio.h>
#include<math.h>

const int num = 512;					//[-]
const int freqSign = 10.913 + 5;		//[Hz]
const double freqSample = 512;			//[Hz]


int main(void){

	int i = 0;
	for(i=0; i<=num; i++){
		printf("%f,%lf\n", (float)i/num, sin(2*M_PI*freqSign*i/freqSample) );
	}
	
	return 0;
}