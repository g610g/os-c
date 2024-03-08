#include<stdio.h>
#include<stdlib.h>
#define SIZE 100

void sort_burst(int arrtime[], int burst[], int process[], int elements, int* starting, int current_time){

    int i, j, temp_burst, temp_arrtime, temp_id;

    for(i=(*starting); i<elements; i++){
        for(j=i+1; j<elements; j++){
            if(arrtime[i] == arrtime[j]){                   //checks if there are consecutive same arrival times
                if(burst[j] < burst[i]){                    // then sort proper placement of burst time in ascending order
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
            }else if (arrtime[j] <= arrtime[i]){            //however if within the calculation, this checks if arrival time of process j is less than or equal to the arrival time of process i
                temp_burst = burst[i];                      //then they need to be sorted based on other criteria, such as their burst time
                burst[i] = burst[j];
                burst[j] = temp_burst;

                temp_arrtime = arrtime[i];
                arrtime[i] = arrtime[j];
                arrtime[j] = temp_arrtime;

                temp_id = process[i];
                process[i] = process[j];
                process[j] = temp_id;
            }
            if (arrtime[j] <= current_time && burst[j] < burst[i]){     //or if within the calculation, there are still arrival times less than current times
                temp_burst = burst[i];                                  //and the burst time at j is less than burst time at i then sort burst time
                burst[i] = burst[j];
                burst[j] = temp_burst;

                temp_arrtime = arrtime[i];
                arrtime[i] = arrtime[j];
                arrtime[j] = temp_arrtime;

                temp_id = process[i];
                process[i] = process[j];
                process[j] = temp_id;
            }
        }
    }
}

int find_next_time(int* current_time, int arrtime[], int elements, int* starting){

    int i = 0;

    for (i = (*starting); i < elements; i++){
        if (arrtime[i] != (*current_time) && arrtime[i] > (*current_time)){             //this just checks for the next arrival time in the array of arrival times
            return arrtime[i];
        }
    }
    return 0;
}

int calculate_seq(int arrtime[], int burst[], int process[], int elements, int* current_time, int* starting, int* waiting_time, float* total_waiting, float* total_turnaround){

    int next_time = find_next_time(current_time, arrtime, elements, starting), i;       //arrival time found in find_next_time function is stored in next_time variable

    if (next_time == 0){

        for(int i = (*starting); i < elements; i++){
            printf("P%d\t\t%d\t\t\t%d\t\t\t%d\n", process[i], burst[i], (*waiting_time), burst[i] + (*waiting_time));
            (*total_waiting) +=(*waiting_time);
            (*total_turnaround) += burst[i] + (*waiting_time);
            (*starting)++;
            (*waiting_time) += burst[i];
        }
    }

    for(i = (*starting); i < elements; i++){
        //out of bounds to the current time
        if (arrtime[i] > (*current_time)){

            (*waiting_time) = arrtime[i];
            (*current_time) = next_time;
            return elements;
        }

        int differ = next_time - (*current_time);
        //difference is greater than the current process's burst_time
        if (differ == 0){
            return elements;
        }

        if (differ >= burst[i]){
            //printing should happen here
            printf("P%d\t\t%d\t\t\t%d\t\t\t%d\n", process[i], burst[i], (*waiting_time), burst[i] + (*waiting_time));
            (*total_waiting) += (*waiting_time);
            (*total_turnaround) += burst[i] + (*waiting_time);
            (*waiting_time) += burst[i];
            (*starting) += 1;
            (*current_time) += burst[i];
        }else if (differ < burst[i]){
            //if the burst_time is greater it means that we have to relocate it at the end of the array
            // printf("new burst:%d\n", burst[i] - differ);
            printf("P%d\t\t%d\t\t\t%d\t\t\t%d\n", process[i], differ, (*waiting_time), differ + (*waiting_time));
            (*total_waiting) += (*waiting_time);
            (*total_turnaround) += differ + (*waiting_time);
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

    (*current_time) = next_time;
    return elements;

}
void calculate_avg(float* total_waiting, float* total_turnaround, int elements){

    // float total_waitavg = 0, total_turnaroundavg = 0;

    // for(int i=0; i<elements; i++){
    //     total_waitavg = total_waitavg + waiting_time[i];
    //     total_turnaroundavg = total_turnaroundavg + turnaround_time[i];
    // }

    // printf("\nAverage Waiting Time: %.2f\n", total_waitavg/elements);
    // printf("Average Turn Around Time: %.3f\n", total_turnaroundavg/elements);
    printf("Total waiting: %f  ", (*total_waiting) / elements );
    printf("Total turnaround: %f ", (*total_turnaround) / elements);
}


int main(){

    int i, j, opt, choice, arrival_time, burst_time, arrtime[SIZE], burst[SIZE], process[SIZE];
    int elements = 0, current_arrivaltime = 0, current_time = 0, starting = 0, waiting_time = 0;
    float total_waiting = 0, total_turnaround = 0;

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
        printf("Process\t\tBurst Time\t\tWaiting Time\t\tTurn Around Time\n");
        sort_burst(arrtime, burst, process, elements, &starting, current_time);

            while (starting < elements)
            {
                elements = calculate_seq(arrtime, burst, process, elements, &current_time, &starting, &waiting_time, &total_waiting, &total_turnaround);
                sort_burst(arrtime, burst, process, elements, &starting, current_time);
            }
            calculate_avg(&total_waiting, &total_turnaround, elements);
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
