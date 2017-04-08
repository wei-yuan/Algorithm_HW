#include <stdio.h>
#include <string.h>

char tmp[1000];
//storing LPS information
char clps[1000]; 
char *clpsptr = &clps;
//Table
int T[1001][1001] ={0},D[1001][1001] = {0}; // T:LCS Table, D:for saving direction
//String
char rev[1000] = {0}; //reverse string
// for read line
char *line = NULL;
size_t len = 0;	  //unsigned
ssize_t read = 0; //signed

void PRINT_LPS(int D[][1001], char *line, int i, int j, int *cntptr, char *clpsptr){   
	if(i== 0 || j==0)return;
	if(D[i][j]==1)   
		PRINT_LPS(D, line, i, j-1, cntptr, clpsptr);
	else if(D[i][j] == 3)
		PRINT_LPS(D, line, i-1, j, cntptr, clpsptr);	
	else{ // D[i][j] = 2
		PRINT_LPS(D, line, i-1, j-1, cntptr, clpsptr);
		*cntptr = *cntptr + 1;
		*(clpsptr+(*(cntptr)-1)) = *(line+(i-1));
	}	
}

int main(){   
	int i = 0;
	int p;
	int dummy = 0; 

	scanf("%d",&dummy);
	getchar(); //remove newline character
	while( read != -1){
		int ori_len = 0;  //length of string
		//passing last imformation
		int cnt = 0;
		int *cntptr = &cnt;
		//readline
		read = getline(&line, &len, stdin) -1; //-1 for stop counting newline character
		for(int i=0,j=read-1;i<read-1,j>=0;i++,j--)  // 因為固定矩陣固定是1000,正式輸入時上下限還需要調整
			rev[j] = *(line+i);
		//Dynamic programming, T[row][column]
		for(int i=1;i<=read;i++){
			for(int j=1;j<=read;j++){
				if( *(line+(i-1)) == rev[j-1] ){
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

		PRINT_LPS(D, line, read, read, cntptr, clpsptr);	

		printf("%d\n",cnt);
		puts(clps);

		if(i == dummy-1)break;
		i++;
	} //while()
	free(line); //free memory space for read line
}
