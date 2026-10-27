#include<stdio.h>

int sumOfProperDivisor(int num) {
    if (num <= 1) return 0;
    int sum = 1; // 1 is always a proper divisor for any number > 1
    for (int i = 2; i * i <= num; i++) {
        if (num % i == 0) {
            sum += i; 
            if (i != num / i) {
                sum += (num / i);
            }
        }
    }
    return sum;
}
int main(){
    int n;
    printf("Enter number n: ");
    if(scanf("%d",&n)!= 1)return 0;
    
    printf("Amicable pairs up to %d: \n", n);
    int count=0;

    for(int i=1; i<=n; i++){
        int j=sumOfProperDivisor(i);
        if(j>i && j<=n){
            if(sumOfProperDivisor(j)==i){
                printf("(%d,%d)\n",i,j);
                count++;
            }
        }
    }
    
    printf("Total pairs %d\n",count);
    return 0;
}
