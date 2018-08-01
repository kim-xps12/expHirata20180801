#include<stdio.h>
#include<math.h>

const int num = 512;		//[-]
const int freqSign1 = 10.913;				//[Hz]
const int freqSign2 = 10.913 + 5;		//[Hz]
const double freqSample = 512;	//[Hz]

const double iniPhaseDeg = 0;		//[deg]


double mixedSign(int i){
	
	return  sin(2*M_PI*freqSign1*i/freqSample) + sin(2*M_PI*freqSign2*i/freqSample);
}


int main(void){
	
	double iniPhaseRad = iniPhaseDeg /180 *M_PI;
	
	int i = 0;
	
	for(i=0; i<=num; i++){
		printf("%f,%lf\n", (float)i/num,  mixedSign(i) );
	}
	
	return 0;
}