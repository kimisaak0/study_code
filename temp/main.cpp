#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct score
{
    int kor, eng, math;
};

struct student
{
    int id, sum;
    double avg;
    score numScore;

};

void scanlist(student* );



int main(void)
{
    srand(time(NULL));

    student sList[5];
    for (int i = 0; i < 5; i++) {
        sList[i].id = i;
        sList[i].numScore.kor = rand() % 100;
        sList[i].numScore.eng = rand() % 100;
        sList[i].numScore.math = rand() % 100;
    }

    scanlist(sList);
}

void scanlist(student* lp)
{
    for (int i = 0; i < 5; i++)
    {
        lp[i].sum = lp[i].numScore.kor + lp[i].numScore.eng + lp[i].numScore.math;
        lp[i].avg = lp[i].sum / 3.0;
    }

    for (int i = 0; i < 5; i++) {
        for (int k = i; k < 5; k++) {
            if (lp[i].sum > lp[k].sum) {
                student temp = lp[i];
                lp[i] = lp[k];
                lp[k] = temp;
            }
        }
    }

    for (int i = 0; i < 5; i++)
    {
        printf("ÇÐ»ý ¹øÈ£ : : %d, ÃÑÁ¡ : %d, Æò±Õ: %lf \n", lp[i].id, lp[i].sum, lp[i].avg);
    }

    
}