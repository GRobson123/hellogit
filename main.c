#include <stdio.h>

#include <string.h>

#include <stdlib.h>
#include <math.h>
#define MAX_columns 1000


float data[8][MAX_columns];
void recordfr();
int dcfunc(int z);
float rms(int y);
int catchfunc(int x);
void rangefunc(int p);
float ptpfunc(int t);
int count=0;
float resultf;
int resulti;
float minimum;
float maximum;

int main(void) {

    recordfr();
    FILE *fz = fopen("results.txt","w");
    if (fz == NULL) {
        printf("error opening file \n");
        return 1;
    }
    fprintf(fz,"results\n");
    resultf = rms(1);
    fprintf(fz,"rms of phase a is: %.3f\n", resultf);
    resultf = ptpfunc(1);
    fprintf(fz,"peak to peak of phase a is: %.1f\n", resultf);
    resulti = dcfunc(1);
    fprintf(fz,"dc offset of phase a is: %d\n", resulti);
    resultf = rms(2);
    fprintf(fz,"rms of phase b is: %.3f\n", resultf);
    resultf = rms(3);
    fprintf(fz,"rms of phase c is: %.3f\n", resultf);
    resulti = catchfunc(1);
    fprintf(fz,"number of clipped readings of phase a is: %d\n", resulti);
    resulti = catchfunc(2);
    fprintf(fz,"number of clipped readings of phase b is: %d\n", resulti);
    resulti = catchfunc(3);
    fprintf(fz,"number of clipped readings of phase c is: %d\n", resulti);
    rangefunc(5);
    fprintf(fz,"the frequency range is: %.3f - %.3f \n",minimum,maximum);
    rangefunc(6);
    fprintf(fz,"the power factor range is: %.3f - %.3f \n",minimum,maximum);
    rangefunc(7);
    fprintf(fz,"the thd range is: %.3f - %.3f \n",minimum,maximum);
    fclose(fz);

}

void recordfr(){
    FILE *fp = fopen("power_quality_log.csv","r");
    if (fp == NULL) {
        printf("error opening file \n");
        return;
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

int dcfunc(z){
    int sum=0;
    int dc;
    for (int i = 0; i<1000; i++) {
        sum += data[z][i];
    }
    dc = sum/1000;
    printf("dc offset = %d \n", dc);
    return dc;
}
float rms(y){
    float sqrsum=0;
    int cnt = 0;
    float fnl;
    for (int i=0; i<1000;i++) {
        sqrsum += data[y][i]*data[y][i];
        cnt ++;
    }
    fnl = sqrt(sqrsum/cnt);
    printf("rms = %.3f \n", fnl);
    return fnl;
}
int catchfunc(x) {
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
    return catch;
}
void rangefunc(p){
    float high =0;
    float low=100;
    for (int i = 0; i<1000; i++) {
        if (data[p][i]>high){
            high=data[p][i];
        }
        if (data[p][i]<low){
            low=data[p][i];
        }
    }
    printf("the range max is: %.3f \n",high);
    printf("the range min: %.3f \n",low);
    maximum = high;
    minimum = low;


}

float ptpfunc(t){
    float high =0;
    float low=1000;
    float ptp;
    for (int i = 0; i<1000; i++) {
        if (data[t][i]>high){
            high=data[t][i];
        }
        if (data[t][i]<low){
            low=data[t][i];
        }
    }
    ptp= high- low;
    printf("the peak to peak is: %.1f \n",ptp);
    return ptp;

}

