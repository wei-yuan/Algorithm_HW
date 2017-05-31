#include <stdio.h>
#include <string.h>

char tmp[1000];
char clps[1000];
char *clpsptr = &clps;
	
//Table
int T[1001][1001] ={}; //LCS Table
int D[1001][1001] = {}; //for saving direction

//String
char ori[1000] = {};  //original string
char rev[1000] = {}; //reverse string

void PRINT_LPS(int D[][1001], char ori[], int i, int j, int *cntptr, char *clpsptr){   
	if(i== 0 || j==0){   
		return;
	}
	if(D[i][j]==1){   
		PRINT_LPS(D,ori,i,j-1,cntptr, clpsptr);
	}
	else if(D[i][j] == 3){ 
		PRINT_LPS(D,ori,i-1,j,cntptr, clpsptr);	
	}
	else{ // D[i][j] = 2
		PRINT_LPS(D,ori,i-1,j-1,cntptr, clpsptr);
		*cntptr = *cntptr + 1;
		*(clpsptr+(*(cntptr)-1)) = ori[i-1];
	}	
}

int main(){   
	int  dummy = 0;
	scanf("%d",&dummy);
	int i = 0;
	while( scanf("%s",tmp)!= '\n' ){
		int ori_len = 0;  //length of string
		size_t length = strlen(tmp);
		//passing last imformation
		int cnt = 0;
		int *cntptr = &cnt;
		//copy information into original string
		for(int i=0;i<1000;i++){
			//scanf("%c",ori[i]);
			ori[i] = tmp[i];
			if(ori[i] == '\n' || ori[i] == '\0'){
				break;
			}				
				ori_len++;				
		}
		//reverse string
		for(int i=0,j=ori_len-1;i<ori_len,j>=0;i++,j--)  // 因為固定矩陣固定是1000,正式輸入時上下限還需要調整
			rev[j] = ori[i];

		//Dynamic programming, T[row][column]
		for(int i=1;i<=ori_len;i++){
			for(int j=1;j<=ori_len;j++){
				if( ori[i-1] == rev[j-1] ){
					T[i][j] = T[i-1][j-1]+1;
					D[i][j] = 2;
				}
				else if( T[i][j-1] > T[i-1][j]){
					T[i][j] = T[i][j-1];
					D[i][j] = 1;
				}
				else{   
					T[i][j] = T[i-1][j];
					D[i][j] = 3;
				}
			}
		}
		//Print LPS
		PRINT_LPS(D, ori, ori_len, ori_len, cntptr, clpsptr);	

		printf("%d\n",cnt);
		for( int i=0;i<cnt;i++){   
			if( i!= cnt-1)
				printf("%c",clps[i]);
			else
				printf("%c\n",clps[i]);
		}			

		if(i == dummy-1) break;
		i++;
	} //while()
}
