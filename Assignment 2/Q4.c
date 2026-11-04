#include<stdio.h>

// function to get days 
int getValidDays(){
    int days;
    while(1){
        printf("Number of days(1-7)");
        scanf("%d",&days);
        if(days>=1 && days<=7)return days;
        printf("Invalid input ! Enter a value between 1 and 7.\n");
    }
}

// function to calculate daily sales
float calculateDailySales(int dayNumber){
    int orders;
    printf("Day %d - Number of orders: ", dayNumber);
    scanf("%d",&orders);

    float totalSales = 0, highestOrder = 0;
    printf("Order amounts: ");
    for(int i=0; i< orders; i++){
        float amount;
        while(1){
            scanf("%f",&amount);
            if(amount>0) break;
            printf("Invalid amount! Re-enter amount for order %d: ",i+1);
        }
        totalSales +=amount;
        if(i==0 || amount>highestOrder ) highestOrder = amount;
    }
    printf("Total sales: Rs. %.2f\n Average Order: Rs. %.2f\nHighest Order: Rs. %.2f\n\n",
    totalSales, totalSales/orders, highestOrder);
    return totalSales;

}

//finding the best sale day of week
int findHighestSalesDay(float dailySales[],int numberOfDays){
    int bestDay = 0;
    float maxSales= dailySales[0];
    for(int i=1; i<numberOfDays ; i++){
        if(dailySales[i]>maxSales){
            maxSales = dailySales[i];
            bestDay = i;
        }
    }
    return bestDay +1;
}

void displayBarChart(float dailySales[], int numberOfDays){
    printf("\n====Daily Sales Bar Chart====\n")
    for(int i=0; i<numberOfDays; i++){
        int stars =(int)(dailySales[i]/100);
        printf("Day %d: ",i+1);
        for(int s=0; s< stars; s++) printf("*");
        printf("(Rs. %.2f)\n", dailySales[i]);
    }
}

int main(){
    int days = getValidDays();
    float dailySales[7], totalFestivalSales = 0;

    for (int i=0; i<days; i++){
        dailySales[i] = calculateDailySales(i+1);
        totalFestivalSale += dailySales[i];
    }

    int highestDay = findHighestSalesDay(dailySales, days);
    printf("=====Festival Summary====");
    printf("Total festival sales: Rs. %.2f \n", totalFestivalSales);
    printf("Day with highest sales: Day %d \n",highestDay);
    printf("Highest daily sales: Rs. %.2f\n",dailySales[highestDay - 1]);

    displayBarChart(dailySales, days);
    return 0;
}
