/*Assignment 2 Q#1 
Written by Ateeb (26k-0029) 
code for cenima hall 
shoing seating arrangments and booking methods*/
#include<stdio.h>

int main(){
    int rows,cols,k;
    printf("Enter number of rows and seats per row: ");
    if(scanf("%d %d", &rows ,&cols ) !=2 )return 0;

    int seating[50][50];
    printf("Enter the seating status (0 for free, 1 for booked:\n)");
    for(int i=0; i<rows; i++){
        for (int j=0; j<cols; j++){
            scanf("%d",&seating[i][j]);
        }//end inner loop
    }//end outer loop
    //upper loop system is used to calculate the sequesce of booked and free seats

    //displaying seats arrangments
    printf("\n Complete seating Plan:\n");
    for(int i=0;i<rows;i++){
        printf("R%d\t", i);
        for(int j=0; j<cols;j++){
            if(seating[i][j]==0){
                printf("-");
            }else{
                printf("X");
            }
        }
        printf("\n");
    }

    //seats avalibility report
    int total_free = 0;
    printf("\n Free seats per row: ");
    for(int i=0; i<rows; i++){
        int count=0;
        for(int j=0;j<cols;j++){
            if(seating[i][j]==0) count++;
        }
        total_free +=count;
        printf("%d", count);
    }
    printf("Total free: %d\n",total_free);

    //Group Booking & Allocation Rules
    printf("\nEnter number if coustomers (k) who want to sit together: ");
    scanf("%d",&k);

    if(k<=0 || k>cols){
        printf("Invalid group size! \n");
        return 0;
    }

    int mid_row = rows/2;
    int found =0;
    int allocated_row = -1, allocated_start_seats= -1;

    for(int dist =0; dist<rows; dist++ ){
        int candidate_rows[2];
        int num_candidate =0;

        int r1 = mid_row-dist;
        int r2 = mid_row + dist;

        if( r1> 0 && r1<rows){
            candidate_rows[num_candidate++]=r1;
        }
        if(r2 !=r1 && r2>=0 && r2<rows){
            candidate_rows[num_candidate++]=r2;
        }
        if(num_candidate == 2 && candidate_rows[0]> candidate_rows[1]){
            int temp =candidate_rows[0];
            candidate_rows[0]=candidate_rows[1];
            candidate_rows[1]=temp;
        }

        for(int c=0; c<num_candidate;c++){
            int r=candidate_rows[c];
            int consecutive_count =0;
            int start_seat= -1;
            for(int j=0;j<cols;j++){
                if(seating[r][j] == 0){
                    if(consecutive_count == 0){
                        start_seat=j;
                    }
                    consecutive_count++;
                    if(consecutive_count == k){
                        found = 1;
                        allocated_row = r;
                        allocated_start_seats = start_seat;
                        break;
                    }
                }else{
                    consecutive_count=0;
                    start_seat=-1;
                }
            }
            if(found)break;
        }
        if(found)break;
    }
    
    //confirming Bookings
    if(found){
        printf("Group of %d seated in Row %d, Seats %d to %d\n ",k, allocated_row, allocated_start_seats,
        allocated_start_seats+ k-1);
        for(int j=allocated_start_seats; j<allocated_start_seats+k; j++){
            seating[allocated_row][j] = 1;
        }
        printf("\n Updated Seating Plan\n");
        for(int i=0; i<rows; i++){
            printf("R%d\t",i);
            for(int j=0;j<cols;j++){
                if(seating[i][j] == 0){
                    printf("\t.\t");
                }else{
                    printf("\tx\t");
                }
            }
            printf("\n");
        }

        int new_total_free =0;
        printf("Free seats per row: ");
        for(int i=0;i<rows;i++){
            int count=0;
            for(int j=0;j<cols;j++){
                if(seating[i][j] == 0)count++;
            }
            new_total_free += count;
            printf("%d",count);
        }
        printf("Total free: %d\n",new_total_free);
    }else{
        printf("No row Contaions %d consecutive avaliable seats. seating plan unchanged,\n",k);

    }
    return 0;
    
    
}


