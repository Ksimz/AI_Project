
/*   Author :  Kudzai Simau
     Artificial Intelligence Image Classification Project
*/
#include <iostream>
#include <string>
#include <cstdlib>
#include <math.h>
#include <fstream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;

void Cal_Directions(int val1,int val2,int *res);
void Create_LDP_Mat(void);
void bubbleSort(int arr[]);

int sample_image[9][9]={{88,82,84,88,85,83,80,93,102},{88,80,78,80,80,78,73,94,100},{85,79,80,78,77,74,65,91,99},{38,35,40,35,39,74,77,70,65},{20,25,23,28,37,69,64,60,57},{22,26,22,28,40,65,64,59,34},{24,28,24,30,37,60,58,56,66},{21,22,23,27,38,60,67,65,67},{23,22,22,25,38,59,64,67,66}};
int ***ptr;
int **zan;
int ldp_x_y;
int *temp;
int *tech1;

void Directional_Response(void){

        ptr = new int**[9];

        for (int i=0;i<9;i++)
        {
                ptr[i]=new int *[9];
                for (int j=0;j<9;j++)
                {
                        ptr[i][j]=new int[7];

                Cal_Directions(i,j,ptr[i][j]);
                }
        }
}
void Cal_Directions(int val1,int val2,int *res)
{

        int M0[3][3]={{-3,-3,5},{-3,0,5},{-3,-3,5}};
        int M1[3][3]={{-3,-3,5},{-3,0,5},{-3,-3,5}};
        int M2[3][3]={{-3,5,5},{-3,0,5},{-3,-3,-3}};
        int M3[3][3]={{5,5,5},{-3,0,-3},{-3,-3,-3}};
        int M4[3][3]={{5,5,-3},{5,0,-3},{-3,-3,-3}};
        int M5[3][3]={{5,-3,-3},{5,0,-3},{5,-3,-3}};
        int M6[3][3]={{-3,-3,-3},{5,0,-3},{5,5,-3}};
        int M7[3][3]={{-3,-3,-3},{-3,0,5},{-3,5,5}};

        for (int j=0;j<7;j++)
        {
                res[j]=0;
        }

        for (int i=-1;i<2;i++)
        {
                for (int n=-1;n<2;n++)
                {
                        res[0]=res[0]+((M0[i+1][n+1])*(sample_image[val1+i][val2+n]));
                }
        }
                for (int i=-1;i<2;i++)
        {
                for (int n=-1;n<2;n++)
                {
                        res[1]=res[1]+((M1[i+1][n+1])*(sample_image[val1+i][val2+n]));
                }
        }
        for (int i=-1;i<2;i++)
        {
                for (int n=-1;n<2;n++)
                {
                        res[2]=res[2]+((M2[i+1][n+1])*(sample_image[val1+i][val2+n]));
                }
        }
        for (int i=-1;i<2;i++)
        {
                for (int n=-1;n<2;n++)
                {
                        res[3]=res[3]+((M3[i+1][n+1])*(sample_image[val1+i][val2+n]));
                }
        }
        for (int i=-1;i<2;i++)
        {
                for (int n=-1;n<2;n++)
                {
                        res[4]=res[4]+((M4[i+1][n+1])*(sample_image[val1+i][val2+n]));
                }
        }
        for (int i=-1;i<2;i++)
        {
                for (int n=-1;n<2;n++)
                {
                        res[5]=res[5]+((M5[i+1][n+1])*(sample_image[val1+i][val2+n]));
                }
        }
        for (int i=-1;i<2;i++)
        {
                for (int n=-1;n<2;n++)
                {
                        res[6]=res[6]+((M6[i+1][n+1])*(sample_image[val1+i][val2+n]));
                }
        }
        for (int i=-1;i<2;i++)
        {
                for (int n=-1;n<2;n++)
                {
                        res[7]=res[7]+((M7[i+1][n+1])*(sample_image[val1+i][val2+n]));
                }
        }


}

void Liner_Dir_Pat(void)
{
        for (int i=0;i<9;i++)
        {
                for(int j=0;j<9;j++)
                {
                        int maxVal=0;
                        ldp_x_y=0;
                        temp=new int[7];
                        for(int n=0;n<7;n++)
                        {
                                temp[n]=ptr[i][j][n];
                        }
                        bubbleSort(temp);

                        int difference;
                        int value;
                        for(int m=0;m<7;m++)
                        {
                               
                                difference=((ptr[i][j][m])-temp[3]);
                                if(difference >= 0)
                                  {
                                    value=1;
                                    }
                                else
                                   {
                                    value=0;
                                     }
                                ldp_x_y=ldp_x_y+(value*(pow(2,m)));
                        }
                

                        zan[i][j]=ldp_x_y;
                }
        }
}

void Create_LDP_Mat(void)
{
    zan= new int*[9];
        for(int y=0 ;y<9;y++)
        {
                zan[y]=new int [9];
        }
}

void bubbleSort(int arr[])
{
   int i, j,temp1;
   for (i = 0; i < 7; i++)      
   {  
       for (j = 0; j < 6; j++)
       { 
           if (arr[j] > arr[j+1])
           {
              temp1=arr[j];
              arr[j]=arr[j+1];
              arr[j+1]=temp1;            
           }
       }
   }
}

void Histogram()
{
        int value1;
        tech1=new int[56];
        delete[] ptr;
       for(int m=0;m<56;m++)
        {
           tech1[m]=0;
        }

        for(int t=0;t<=56;t++)
        {
                for(int i=0;i<9;i++)
                {
                        for(int j=0;j<9;j++)
                        {
                                if(zan[i][j]==t)
                                {
                                 value1=1;
                                }
                                else{
                                        value1=0;
                                }
                                tech1[t]=tech1[t]+value1;
                        }
                }
                cout<<" Result "<<"["<<"\n";
                for(int k=0;k<56;k++)
                {
                        cout<<tech1[k]<<",";
                }
                cout<<"]"<<"\n";
        }
        ofstream myfile("result.txt",ios::out|ios::app);
        if(myfile.is_open())
        {
                for(int k=0;k<56;k++)
                {
                        myfile<<tech1[k]<<",";
                }  
                myfile<<"\n";  
        }
        else{
            cout<<"Could not open file"<<"\n";
        }
}   

int main(void)
{
     Create_LDP_Mat();
     Directional_Response();

         cout<<"[";
         for (int i=0;i<9;i++)
         {

                 for (int t=0;t<9;t++)
                 {
                         cout<<"[";
                         for (int j=0;j<7;j++)
                         {
                                 cout<<ptr[i][t][j]<<",";
                         }
                         cout<<"] ,";
                 }
                 cout<<"\n";
         }
         cout<<"]";
         Liner_Dir_Pat();


         cout<<"Printing the LDP Matrix"<<endl;
         cout<<"[";
         for(int i=0;i<9;i++)
         {
                 for(int j=0;j<9;j++)
                 {
                         cout<<zan[i][j]<<",";
                 }
                 cout<<"\n";
         }
         cout<<"]";
         cout<<"\n"<<"\n"<<"\n";
         Histogram();

         cout<<"done";
        

         return 0;




}