#include<stdio.h>
#include<math.h>

const int num = 512;			//[-]
const int freqSign = 10;		//[Hz]
const double freqSample = 512;	//[Hz]

const double iniPhaseDeg = 45;	//[deg]


int main(void){
	
	double iniPhaseRad = iniPhaseDeg /180 *M_PI;		//[rad]
	
	int i = 0;
	for(i=0; i<=num; i++){
		printf("%f,%lf\n", (float)i/num, sin( (2*M_PI*freqSign*i/freqSample) +iniPhaseRad) );
	}
	
	return 0;
}