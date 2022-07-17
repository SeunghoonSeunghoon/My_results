#include <stdio.h>
int main(){
    int num1;
    scanf("%d",&num1);
    for(int i=1;i<=6;i++){
        for(int j=1;j<=6;j++){
            if(i+j==num1){
                printf("%d %d\n",i,j);
            }
        }
    }
    return 0;
}
