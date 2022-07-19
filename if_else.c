
#include <stdio.h>
int main (void)
{
    
    int hour, min;
    scanf("%d %d",&hour, &min);
    if(min - 30 >= 0){ 
        printf("%d %d", hour, min -30);
        
    }
    else
    {
        hour--;
        if(hour<0)
        {hour =23;}
        
        printf("%d %d", hour, 30+min);
    }
 
    return 0;
}
    
