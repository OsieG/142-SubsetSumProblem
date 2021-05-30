#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <time.h>

int fixSet(int* set, char* line){                       //populates the set and returns the size of array
    int i, num, count = 0;
    char* token;
    char* copy;

    token = strtok(line," ");
    num = atoi(token);
    set[count] = num;
    while(token!=0){
        token = strtok(0," ");
        if(token==NULL) break;
        count++;
        num = atoi(token);
        set[count] = num;
    }
    return(count+1);
}

void backTrack(int a[],int** matrix, int count, int total){
    if(matrix[count-1][total]==0){
        printf("There's no solution terminating program....");
        return;
    }
    int copyJ = total;
    int j = total;
    int i = count-1;
    for(; j >= 0; j--){
        for(; i >=0; i--){
            if(matrix[i][j]==0){
                printf("%d ",a[i+1]);
                j = (copyJ-a[i+1]);
                copyJ = j++;
                i = count-1;
                break;
            }else if(i==0 && matrix[i][j]==1 && j != 0){
                printf("%d ",a[i]);
                j = 1;
            }
        }
    }



}

int max(int a, int b){
    if(a>=b){
        return(a);
    }
    return(b);
}

void fix2DMatrix(int a[],int** matrix,int count,int total){
    for(int i = 0; i < count; i++){
        matrix[i][a[i]] = 1;
        for(int j = 1; j < total+1; j++){
            if(i-1>=0){
                if(matrix[i-1][j]==1){
                    matrix[i][j] = 1;
                }else{
                    matrix[i][j] = matrix[i-1][j];
                    if(j-a[i]>=0){
                        int val = max(matrix[i-1][j],matrix[i-1][j-a[i]]);
                        if(val) matrix[i][j] = val;
                    }
                }
            }
        }
    }
}

void swap(int *a, int *b){                              //helper function
	int temp;
	temp = *a;
	*a = *b;
	*b = temp;
}

void bubbleSort(int a[],int size){                      //sorts the set using bubblesort
    int i, swapped = 1;

    while(swapped){
        swapped = 0;
        for(i = 0; i < size-1; i++){
            if(a[i]>a[i+1]){
                swap(&a[i],&a[i+1]);
                swapped = 1;
            }
        }
        size--;
    }
}

int main(){
    int total, count = 0, set[100];
    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    printf("Target Total: ");
    scanf("%d", &total);

    while((read = getline(&line,&len,stdin))!=-1){              //reads the line for the array
        if (count==1) break;
        printf("Retrieved line of length %zu :\n",read);
        count++;
    }
    count = fixSet(set, line);          //set now usable; total; change count value
    bubbleSort(set,count);

    int **arr2D = (int **)malloc(sizeof(int *)*count);      //creates 2dmatriix
    for (int i = 0; i < count; i++){
        arr2D[i] = (int *)malloc(sizeof(int)*total+1);
    }

    for(int i = 0; i < count; i++){                         //initializes 2Dmatrix values
        for(int j = 0; j < total+1; j++){
            if(j==0) arr2D[i][j] = 1;
            else arr2D[i][j] = 0;
        }
    }
    fix2DMatrix(set,arr2D,count,total);                     //returns the correct 2Dmatrix
    backTrack(set,arr2D,count,total);                       //returns the solution

    for(int i = 0; i < count; i++){                         //free allocated memory
        free(arr2D[i]);
    }
    free(arr2D);
    free(line);
    

    return 0;
}