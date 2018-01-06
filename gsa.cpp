#include<iostream>
#include<cstdlib>
#include<time.h>
#include<cmath>
#include <algorithm>
#include <vector>
using namespace std;

void initialization(float **init_pop ,int dimension ,int solution_size ,  int **range );

void fitness_func(float **init_pop , float *fitness_array , int dimension , int solution_size );

void mass_evaluation(float *fitness_array , float *M ,  int dimension , int solution_size , float fbest );

void acc_evaluation(float**init_pop , float **acc , float **velocity ,  float *M , int dimension ,int solution_size , int kbest , float G );

float distance(float **init_pop ,int dimension,int solution_size , int r0 , int r1);

int partition (float arr[], int l, int h,int b[]);

void quickSort(float arr[], int l, int h , int b[]);

void bucketSort(float *M, float *sorted , int n);

float minimum(float *fitness_array, int dimension , int solution_size );

float maximum(float *fitness_array , int dimension , int solution_size );

time_t t1;

int main(){
    int i  , j ;
    int dimension , iterations ;
    cout<<"Input Dimension :";
    cin>>dimension;
    cout<<"Input Iteration:";
    cin>>iterations;

    cout<<"Input candidate size :";
    int solution_size;//     NO OF CANDIDATE SOLUTION
    cin>>solution_size;

    cout<<"Input Range\n";
    int **range;
    range=new int*[dimension];
    for(i=0;i<dimension;i++)
        range[i]=new int[2];
    for(i=0;i<dimension;i++)
        for(j=0;j<2;j++){
            if(j%2!=0)
                range[i][j]=-100;
            else
                range[i][j]=100;
        }



    return 0 ;

    float **init_pop;                       // INITIAL POPULATION MATRIX , WHERE ROW ARE
    init_pop=new float*[dimension];
    for(i=0;i<dimension;i++)
        init_pop[i]=new float[solution_size];

    float *fitness_array;
    fitness_array=new float[solution_size];



    float *M;
    M=new float[solution_size];

    float **acc;
    acc=new float*[dimension];
    for(i=0;i<dimension;i++)
        acc[i]=new float[solution_size];




    float **velocity;
    velocity = new float*[dimension];
    for(i=0;i<dimension;i++)
        velocity[i]=new float[solution_size];

    for(j=0;j<solution_size;j++)
        for(i=0;i<dimension;i++)
            velocity[i][j]=0;

    float kbest , kbest_part;
    int final_per=2;

    int G0=100 , alpha=20;
    float G;

    float fbest , f_avg;

    // NOW YOU NEED TO CHANGE THE FITNESS FUNTION ACCORDINGLY FOR EACH DIFFERENT PROBLEM


    //for(j=0;j<30;j++){

    //cout<<j<<" ";
    initialization(init_pop , dimension ,solution_size , range);


    for(i=0;i<iterations;i++){

        fitness_func(init_pop ,fitness_array ,dimension , solution_size );

        if(i==0)
            fbest=minimum(fitness_array , dimension , solution_size );

        if(fbest>minimum(fitness_array , dimension , solution_size ))
            fbest=minimum(fitness_array , dimension , solution_size );



        mass_evaluation(fitness_array ,M ,dimension , solution_size , fbest );
        kbest=final_per + (1-(i+1)/(iterations+0.0))*(100-final_per);
        kbest=round(solution_size*kbest/100);
        G=G0*exp(-alpha*(i+1)/iterations);
        //cout<<kbest;

        acc_evaluation(init_pop , acc , velocity , M , dimension , solution_size  , kbest , G);

        //cout<<" ITERATION NO  "<<i<<" ";

    }

    cout<<fbest;
}

void initialization(float **init_pop ,int dimension , int solution_size ,   int **range ){
    time(&t1);
    srand(t1);
    int i , j  ;
    for(j=0;j<solution_size;j++){
        for(i=0;i<dimension;i++){
            init_pop[i][j] = range[i][0] + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(range[i][1]-range[i][0])));
        }
    }
    /*for(i=0;i<dimension;i++){
        for(j=0;j<solution_size;j++)
            cout<<init_pop[i][j]<<" ";
        cout<<"\n";
    }*/

}
void fitness_func(float **init_pop , float *fitness_array , int dimension , int solution_size ){
    int i , j;

    for(i=0;i<solution_size;i++)
        fitness_array[i]=0;

    for(j=0;j<solution_size;j++){
        for(i=0;i<dimension;i++){
            fitness_array[j]+=(init_pop[i][j]*init_pop[i][j]);
        }
    }

   /* for(i=0;i<solution_size;i++)
        cout<<fitness_array[i]<<" ";*/


}
void mass_evaluation(float *fitness_array , float *M ,  int dimension , int solution_size , float fbest){
    int i;
    float sum_of_masses=0;
    float bestfit=minimum(fitness_array , dimension , solution_size );
    float worstfit=maximum(fitness_array  , dimension , solution_size );
    float m[solution_size];
    for(i=0;i<solution_size;i++){
        m[i]=(fitness_array[i]-worstfit)/(fbest-worstfit);
    }
    for(i=0;i<solution_size;i++)
        sum_of_masses+=m[i];

    for(i=0;i<solution_size;i++)
        M[i]=m[i]/sum_of_masses;

    /*cout<<"\nMASSES\N";
    for(i=0;i<solution_size;i++)
        cout<<M[i]<<" ";*/

    cout<<bestfit<<"\n";


}

void acc_evaluation(float **init_pop ,float **acc , float **velocity ,  float *M , int dimension , int solution_size  , int kbest , float G){
    int i , j ;
    float random_num;

    float M1[solution_size];

    for(i=0;i<solution_size;i++)
        M1[i]=M[i];

    int sorted_mass[solution_size];
    for(i=0;i<solution_size;i++)
        sorted_mass[i]=i;
    quickSort(M1 , 0 , solution_size -1 , sorted_mass);


    for(j=0;j<solution_size;j++){
        for(i=0;i<dimension;i++)
            acc[i][j]=0;
        }
    /*for(i=0;i<solution_size;i++)
        cout<<M[i]<<" ";*/


    //cout<<"\n";

    /*for(i=0;i<solution_size;i++)
        cout<<sorted_mass[i]<<" ";*/


    float R;

            //NEED TO CHANGE THIS


    /*for(i=0;i<solution_size;i++)
        cout<<sorted_mass[i]<<" ";*/

    /*for(i=0;i<dimension;i++){
        for(j=0;j<solution_size;j++)
            acc[i][j]=0;
        }*/

    //cout<<"\n";

    for(j=0;j<solution_size;j++){
        for(int k=solution_size-kbest;k<solution_size;k++){
            if(j!=sorted_mass[k]){
            R=distance(init_pop ,dimension ,solution_size ,  j , sorted_mass[k]);
            //cout<<R<<"\n";
            random_num=(static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(100))))/100;

            for(i=0;i<dimension;i++)
                acc[i][j]=acc[i][j]+random_num*((G*M[sorted_mass[k]]*(init_pop[i][sorted_mass[k]]-init_pop[i][j]))/(R+exp(-10)));
            }
        }
    }
    /*cout<<"\n  ACCELERATION  \n";
    for(i=0;i<dimension;i++){
        for(j=0;j<solution_size;j++)
            cout<<acc[i][j]<<" ";
        cout<<"\n";
        }*/




    /***********************           VELOCITY             **************************/



    for(j=0;j<solution_size;j++){
        random_num=(static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(100))))/100;
        for(i=0;i<dimension;i++){
             velocity[i][j]=(random_num*velocity[i][j])+acc[i][j];
        }
    }


    /*cout<<"\n  VELOCITY";
    for(i=0;i<dimension;i++){
        for(j=0;j<solution_size;j++)
            cout<<velocity[i][j]<<" ";
        cout<<"\n";
        }*/



    /*************************************           POSITION UPDATION             ******************************************/


    /*for(i=0;i<dimension;i++){
        for(j=0;j<solution_size;j++){
            cout<<init_pop[i][j]<<" ";
        cout<<"\n";
        }
    }*/

    for(j=0;j<solution_size;j++){
        random_num=(98 + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(2))))/100;
        for(i=0;i<dimension;i++){
            init_pop[i][j]=random_num*init_pop[i][j]+velocity[i][j];

        }
    }

   /* cout<<"\n";
    for(i=0;i<dimension;i++){
        for(j=0;j<solution_size;j++)
            cout<<init_pop[i][j]<<" ";
        cout<<"\n";
    }*/



}

float distance(float **init_pop , int dimension,int solution_size , int r0 , int r1){
    float R=0;
    int i ,  j;
    for(i=0;i<dimension;i++)
        R+=(init_pop[i][r0]-init_pop[i][r1])*(init_pop[i][r0]-init_pop[i][r1]);
    return sqrt(R);
}

float minimum(float *fitness_array , int dimension , int solution_size ){
    int i;
    int min=0;
    for(i=0;i<solution_size;i++)
        if(fitness_array[i]<fitness_array[min])
            min=i;
    return fitness_array[min];
}
float maximum(float *fitness_array , int dimension , int solution_size ){
    int i;
    int max=0;
    for(i=0;i<solution_size;i++)        if(fitness_array[i]>fitness_array[max])
            max=i;
    return fitness_array[max];
}

void swap(float *a ,float *b){
    float temp;
    temp=*a;
    *a=*b;
    *b=temp;
}

void swap1(int *a ,int  *b){
    int temp;
    temp=*a;
    *a=*b;
    *b=temp;
}

int partition (float arr[], int l, int h,int b[])
{
    float x = arr[h];
    int i = (l - 1);

    for (int j = l; j <= h- 1; j++)
    {
        if (arr[j] <= x)
        {
            i++;
            swap(&arr[i], &arr[j]);
            swap1(&b[i] , &b[j]);
        }
    }
    swap(&arr[i + 1], &arr[h]);
    swap1(&b[i+1] , &b[h]);
    return (i + 1);
}

void quickSort(float arr[], int l, int h , int b[])
{
    if (l < h)
    {
        int p = partition(arr, l, h,b);
        quickSort(arr, l, p - 1 , b);
        quickSort(arr, p + 1, h,b);
    }
}
float rand0(){
    time(&t1);
    srand(t1);
    return (static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(100))))/100;
}
