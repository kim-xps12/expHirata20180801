/*--------------------------------------------------------------------
/
/ 実験1を実現する汎用ソース
/ 設定に応じて、呼び出す三角関数, 初期位相を変更する。
/ 二つの三角関数を合成する場合は、各周波数で三角関数を呼び加算する。
/
/ 作成:木村優太郎
/ 日時:2017/04/17
/
/----------------------------------------------------------------------*/



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