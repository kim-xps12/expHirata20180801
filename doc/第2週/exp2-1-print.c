/*--------------------------------------------------------------------
/
/ 実験2-1を実現する汎用ソース
/ 用いたい窓関数に応じて、適宜関数名と係数の値を変える。
/ 
/
/ 作成:木村優太郎
/ 日時:2017/04/24
/
/----------------------------------------------------------------------*/




#include<stdio.h>
#include<math.h>

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