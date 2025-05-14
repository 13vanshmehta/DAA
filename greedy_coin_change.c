#include <stdio.h>
int main(){
    int n, i, j, amount, total_coins = 0;
    printf("Enter number of coin types: ");
    scanf("%d",&n);
    int coin[n], count[n];
    printf("Enter coin values:\n");
    for(i=0;i<n;i++){
        scanf("%d",&coin[i]);
        count[i]=0;
    }
    for(i=0;i<n-1;i++){
        for(j=0;j<n-i-1;j++){
            if(coin[j]<coin[j+1]){
                int temp=coin[j];
                coin[j]=coin[j+1];
                coin[j+1]=temp;
            }
        }
    }
    printf("Enter amount: ");
    scanf("%d",&amount);
    printf("\nCoin Distribution:\n");
    printf("----------------\n");
    printf("Coin\tCount\tValue\n");
    printf("----------------\n");
    for(i=0;i<n;i++){
        if(amount>=coin[i]){
            count[i]=amount/coin[i];
            amount=amount%coin[i];
            total_coins+=count[i];
            printf("%d\t%d\t%d\n",coin[i],count[i],coin[i]*count[i]);
        }
    }
    printf("----------------\n");
    printf("Total coins needed: %d\n",total_coins);
    if(amount>0) printf("Remaining amount: %d (Cannot be exchanged)\n",amount);
    return 0;
}