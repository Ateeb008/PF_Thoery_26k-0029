
#include<stdio.h>

#define MAX_SENSORS 10
#define MAX_HOURS 24

//inputs all functions in 2D array
void inputReadings(float temp[MAX_SENSORS][MAX_HOURS], int sensors, int hours){
    for(int i=0;i<sensors; i++){
        printf("ENter temperature readings for sensor\t%d\t(%d hourly readings): \n",i+1,hours);
            for(int j=0; j<hours; j++){
                scanf("%f",&temp[i][j]);
            }
    }
}

// sensor Analysis 
void analyzeSensor(float readings[],int hours, int sensorNum){
    float total=0;
    float max= readings[0];
    float min = readings[0];
    int criticalCount =0;
    int warningCount=0;
    int currentStreak = 0;
    int maxStreak = 0;
    for(int j =0;j< hours; j++){
        float t=readings[j];
        total += t;

        if(t>max) max=t;
        if(t<min) min =t;

        if(t>=40.0){
            criticalCount++;
        }
        if(t>=35.0 && t<=39.0){
            warningCount++;
        }

        if(t>35.0){
            currentStreak++;
            if(currentStreak> maxStreak){
                maxStreak = currentStreak;
            }
        }else{currentStreak=0;}
    }
    float avg=total/hours;

    //Displaying Indivisuals report for each sensor
    printf("Sensor %d: Total=%.0f Max= %.0f Avg =%.2f Critical=%d Warning = %d"
    ,sensorNum,total,max,min,avg,criticalCount,warningCount,maxStreak);
}
//highest Average function
int findHighestAverageSensor(float temp[MAX_SENSORS][MAX_HOURS], int sensors,int hours,float *highestAvgOut){
    int bestSensor = 0;
    float highestAvg =-9999.0;

    for(int i =0;i<sensors;i++){
        float total=0;
        for(int j=0;j<hours;j++){
            total+=temp[i][j];
        }
        float avg= total/hours;
        if(avg>highestAvg){
            highestAvg= avg;
            bestSensor=i;
        }
    }
    *highestAvgOut= highestAvg;
    return bestSensor+1;//return sensor number starting from 1
}
int main(){
    int sensors, hours;
    printf("ENter number of sensors and hourly readings:");
    if(scanf("%d %d ",&sensors,&hours)!=2) return 0;

    float temp[MAX_SENSORS][MAX_HOURS];

    //input using function call
    inputReadings(temp, sensors,hours);

    printf("\n---Individual Sensor Report----\n");
    for(int i=0;i<sensors; i++){
        analyzeSensor(temp[i],hours,i+1);
    }
    float highestAvg =0;
    int highestSensor = findHighestAverageSensor(temp,sensors,hours,&highestAvg);

    //displaying sensor number with its highest average and highest reading
    printf("\n Highest Average : Sensor %d(%.2f)\n",highestSensor,highestAvg);

    return 0;

}
