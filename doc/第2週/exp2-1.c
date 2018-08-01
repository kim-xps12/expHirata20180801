/*--------------------------------------------------------------------
/
/ ����2-1����������ėp�\�[�X
/ �p���������֐��ɉ����āA�K�X�֐����ƌW���̒l��ς���B
/ 
/
/ �쐬:�ؑ��D���Y
/ ����:2017/04/24
/
/----------------------------------------------------------------------*/




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