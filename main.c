#include <stdio.h>

#include <string.h>

#include <stdlib.h>
#include <math.h>
#define MAX_columns 1000


float data[8][MAX_columns];
void record();
void recordfr();
void printfunc();
void addfunc(int z);
void rms(int y);
void catchfunc(int x);
int count=0;
int main(void) {

    recordfr();
    rms(1);
    rms(2);
    rms(3);

}

void recordfr(){
    FILE *fp = fopen("power_quality_log.csv","r");
    if (fp == NULL) {
        printf("error opening file \n");
        return ;
    }

    char line[256];

    fgets(line, sizeof(line), fp);

    while (fgets(line, sizeof(line), fp) !=NULL){
        char *token;

        token = strtok(line,",");
        data[0][count] = atof(token);

        token = strtok(NULL,",");
        data[1][count] = atof(token);

        token = strtok(NULL,",");
        data[2][count] = atof(token);

        token = strtok(NULL,",");
        data[3][count] = atof(token);

        token = strtok(NULL,",");
        data[4][count] = atof(token);

        token = strtok(NULL,",");
        data[5][count] = atof(token);

        token = strtok(NULL,",");
        data[6][count] = atof(token);

        token = strtok(NULL,",");
        data[7][count] = atof(token);

        count++;



    }
    fclose(fp);
}
void record(){
    FILE *fp = fopen("test.csv","r");
    if (fp == NULL) {
        printf("error opening file \n");
        return ;
    }

    char line[256];

    fgets(line, sizeof(line), fp);

    while (fgets(line, sizeof(line), fp) !=NULL){
        char *token;

        token = strtok(line,",");
        data[0][count] = atof(token);

        token = strtok(NULL,",");
        data[1][count] = atof(token);

        token = strtok(NULL,",");
        data[2][count] = atof(token);

        token = strtok(NULL,",");
        data[3][count] = atof(token);

        token = strtok(NULL,",");
        data[4][count] = atof(token);

        token = strtok(NULL,",");
        data[5][count] = atof(token);

        token = strtok(NULL,",");
        data[6][count] = atof(token);

        token = strtok(NULL,",");
        data[7][count] = atof(token);

        count++;



    }
    fclose(fp);
}
void printfunc(){
    for (int i = 0; i < 8; i++) {
        printf("Collumn %d: %.1f %.1f %.1f\n",
               i, data[i][0], data[i][1], data[i][2]);
    }
    return;
}
void addfunc(z){
    int sum=0;
    for (int i = 0; i<1000; i++) {
        sum += data[z][i];
    }
    printf("total = %d \n", sum);
}
void rms(y){
    float sqrsum=0;
    int cnt = 0;
    float fnl;
    for (int i=0; i<1000;i++) {
        sqrsum += data[y][i]*data[y][i];
        cnt ++;
    }
    fnl = sqrt(sqrsum/cnt);
    printf("rms = %.3f \n", fnl);
}
void catchfunc(x) {
    int catch = 0;
    for (int i = 0; i<1000; i++) {
        if(data[x][i]>=325){
            catch = catch +1;
        }
        if(data[x][i]<= -325){
            catch = catch+1;
        }
    }
    printf("the catch num is: %d \n",catch);
}