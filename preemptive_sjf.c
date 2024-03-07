#include<stdio.h>
#include<stdlib.h>
#define SIZE 100

void sort_burst(int arrtime[], int burst[], int process[], int elements, int* starting, int current_time){

    int i, j, temp_burst, temp_arrtime, temp_id;

    for(i=(*starting); i<elements; i++){
        for(j=i+1; j<elements; j++){
            if(arrtime[i] == arrtime[j]){
                if(burst[j] < burst[i]){
                            temp_burst = burst[j];
                            burst[j] = burst[i];
                            burst[i] = temp_burst;

                            temp_arrtime = arrtime[j];
                            arrtime[j] = arrtime[i];
                            arrtime[i] = temp_arrtime;

                            temp_id = process[j];
                            process[j] = process[i];
                            process[i] = temp_id;

                }
            }else if (arrtime[j] <= current_time && burst[j] < burst[i]){
                temp_burst = burst[i];
                burst[i] = burst[j];
                burst[j] = temp_burst; 

                temp_arrtime = arrtime[i];
                arrtime[i] = arrtime[j];
                arrtime[j] = temp_arrtime;

                temp_id = process[i];
                process[i] = process[j];
                process[j] = temp_id;
                
            }
            // else if (arrtime[j] < arrtime[i]){
            //     temp_burst = burst[i];
            //     burst[i] = burst[j];
            //     burst[j] = temp_burst; 

            //     temp_arrtime = arrtime[i];
            //     arrtime[i] = arrtime[j];
            //     arrtime[j] = temp_arrtime;

            //     temp_id = process[i];
            //     process[i] = process[j];
            //     process[j] = temp_id;
            // }
        }
    }
}
int find_next_time(int* current_time, int arrtime[], int elements_len, int* starting){
    int i = 0;
    for (i = (*starting); i < elements_len; i++){
        if (arrtime[i] != (*current_time) && arrtime[i] > (*current_time)){
            return arrtime[i];
        }
    }
    return 0;
}
void print_arr(int arrtime[], int burst[], int process[], int elements, int starting){
    for (int i = starting; i < elements; i++){
        printf(" id: %d burst_time: %d arrival time: %d\n", process[i], burst[i], arrtime[i]);
    }   
}
int calculate_seq(int arrtime[], int burst[], int process[], int elements, int* current_time, int* starting, int* waiting_time){
    int next_time = find_next_time(current_time, arrtime, elements, starting), i;
    if (next_time == 0){
        //do the sequence stuff
        for(int i = (*starting); i < elements; i++){
            printf("Process:%d Burst Time:%d, Waiting Time: %d, Turn-around Time: %d\n", process[i], burst[i], (*waiting_time), burst[i] + (*waiting_time));
            (*starting)++;
            (*waiting_time) += burst[i];
        }
    }
    for(i = (*starting); i < elements; i++){
        //out of bounds to the current time
        if (arrtime[i] > (*current_time)){
            printf("arr time: %d\n", arrtime[i]);
            //not sure
            // (*current_time) = arrtime[i];
            return elements;
        }
        int differ = next_time - (*current_time);
        //difference is greater than the current process's burst_time
        if (differ == 0){
            return elements;
        }
        if (differ >= burst[i]){
            //printing should happen here
            printf("Process:%d Burst Time:%d, Waiting Time: %d, Turn-around Time: %d\n", process[i], burst[i], (*waiting_time), burst[i] + (*waiting_time));
            (*waiting_time) += burst[i];
            (*starting) += 1; 
            (*current_time) += burst[i];
        }else if (differ < burst[i]){
            //if the burst_time is greater it means that we have to relocate it at the end of the array
            // printf("new burst:%d\n", burst[i] - differ);
            printf("Process:%d Burst Time:%d, Waiting Time: %d, Turn-around Time: %d\n", process[i], differ, (*waiting_time), differ + (*waiting_time));
            (*waiting_time) += differ;
            burst[elements] = burst[i] - differ; 
            process[elements] = process[i];
            arrtime[elements] = arrtime[i];
            (*starting) += 1;
            ++elements;
            (*current_time) = next_time;
            return elements;
        }
    }
    return elements;

}

void calculate_avg(int elements, int burst[], int waiting_time[], int turnaround_time[]){

    float total_waitavg = 0, total_turnaroundavg = 0;

    for(int i=0; i<elements; i++){
        total_waitavg = total_waitavg + waiting_time[i];
        total_turnaroundavg = total_turnaroundavg + turnaround_time[i];
    }

    printf("\nAverage Waiting Time: %.2f\n", total_waitavg/elements);
    printf("Average Turn Around Time: %.3f\n", total_turnaroundavg/elements);
}

/*void calculate_waitandtnt(int elements, int process[], int burst[], int waiting_time[], int turnaround_time[]){

    int i, current_waittime = 0;

    for(i=0; i<elements; i++){

        waiting_time[i] = current_waittime;
        turnaround_time[i] = current_waittime + current_bursttime[i];
        current_waittime = current_waittime + current_bursttime[i];
    }

    printf("\nProcess Time \tBurst Time \tWaiting Time \tTurn Around Time\n");
    for(int i=0; i<elements; i++){

        printf("P[%d]\t\t\t%d\t\t%d\t\t%d\n", process_id[i], burst[i], waiting_time[i], turnaround_time[i]);
    }

    calculate_avg(elements, burst, waiting_time, turnaround_time);
}*/


int main(){

    int i, j, opt, choice, arrival_time, burst_time, arrtime[SIZE], burst[SIZE], process[SIZE];
    int elements = 0, current_arrivaltime = 0, current_time = 0, starting = 0, waiting_time = 0;
    //int waiting_time[SIZE], turnaround_time[SIZE];

    start:
    printf("1. Add Element   2. Solve   3. Exit   4.Display\n");
    printf("Enter Choice: ");
    scanf("%d", &choice);

    switch(choice){

    case 1:
        error1:
        printf("\nEnter Arrival Time for P[%d]: ", elements);
        scanf("%d", &arrival_time);

        if(arrival_time < current_arrivaltime){
            printf("Invalid Input!\n");
            goto error1;
        }

        printf("Enter Burst Time for P[%d]: ", elements );
        scanf("%d", &burst_time);

        current_arrivaltime = arrival_time;
        arrtime[elements] = arrival_time;

        burst[elements] = burst_time;

        process[elements] = elements;
        elements++;

        break;
    case 2:
        sort_burst(arrtime, burst, process, elements, &starting, current_time);
            while (starting < elements)
            {
                elements = calculate_seq(arrtime, burst, process, elements, &current_time, &starting, &waiting_time);
                sort_burst(arrtime, burst, process, elements, &starting, current_time);
                printf("current_time:%d\n", current_time);
                print_arr(arrtime, burst, process, elements, starting);
             
            }
             
        // calculate_waitandtnt(elements, process, burst, waiting_time, turnaround_time);
        break;
    case 3:
        exit(0);
    case 4:
        printf("\nProcess\t\tArrival Time\t\tBurst Time\n");
        for(i=0; i<elements; i++){
            printf("P%d\t\t%d\t\t\t%d\n", process[i], arrtime[i], burst[i]);
        }
        break;
    default:
        printf("\nInvalid Input!");

    }

    printf("\nDo you want to continue? Y = 1/N = 2: ");
    scanf("%d", &opt);

    if(opt == 1){
        goto start;
    }
    else if(opt == 2){
        exit(0);
    }
    else{
        printf("\nInvalid Input!");
    }


}
