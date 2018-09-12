#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
#include <stdio.h>
#include <iostream>
#include <cstdlib.h>
#include <math.h>
#include <fstream>
#include <opencv2/highgui.hpp>
#include <cv.h>
#include "LDP_train.h"

using namespace std;
using namespace cv;

void LDP_train::Cal_Directions(int val1,int val2,int *res){

	int M0[3][3]={{-3,-3,5},{-3,0,5},{-3,-3,5}};
	int M1[3][3]={{-3,-3,5},{-3,0,5},{-3,-3,5}};
    int M2[3][3]={{-3,5,5},{-3,0,5},{-3,-3,-3}};
    int M3[3][3]={{5,5,5},{-3,0,-3},{-3,-3,-3}};
    int M4[3][3]={{5,5,-3},{5,0,-3},{-3,-3,-3}};
    int M5[3][3]={{5,-3,-3},{5,0,-3},{5,-3,-3}};
    int M6[3][3]={{-3,-3,-3},{5,0,-3},{5,5,-3}};
    int M7[3][3]={{-3,-3,-3},{-3,0,5},{-3,5,5}};
   
    for (int j=0;j<7;j++){
    	res[j]=0;
    }
    for(int i=-1;i<2;i++){
    	for(int n=-1;n<2;n++)
    	{
    		res[0]=res[0]+((M0[i+1][n+1])*(sample_image[val1+i][val1+n]));
    	}
    }
     for(int i=-1;i<2;i++){
    	for(int n=-1;n<2;n++)
    	{
    		res[1]=res[1]+((M1[i+1][n+1])*(sample_image[val1+i][val1+n]));
    	}
    }
     for(int i=-1;i<2;i++){
    	for(int n=-1;n<2;n++)
    	{
    		res[2]=res[2]+((M2[i+1][n+1])*(sample_image[val1+i][val1+n]));
    	}
    }
     for(int i=-1;i<2;i++){
    	for(int n=-1;n<2;n++)
    	{
    		res[3]=res[3]+((M3[i+1][n+1])*(sample_image[val1+i][val1+n]));
    	}
    }
     for(int i=-1;i<2;i++){
    	for(int n=-1;n<2;n++)
    	{
    		res[4]=res[4]+((M4[i+1][n+1])*(sample_image[val1+i][val1+n]));
    	}
    }
     for(int i=-1;i<2;i++){
    	for(int n=-1;n<2;n++)
    	{
    		res[5]=res[5]+((M5[i+1][n+1])*(sample_image[val1+i][val1+n]));
    	}
    }
     for(int i=-1;i<2;i++){
    	for(int n=-1;n<2;n++)
    	{
    		res[6]=res[6]+((M6[i+1][n+1])*(sample_image[val1+i][val1+n]));
    	}
    }
     for(int i=-1;i<2;i++){
    	for(int n=-1;n<2;n++)
    	{
    		res[7]=res[7]+((M7[i+1][n+1])*(sample_image[val1+i][val1+n]));
    	}
    }
}
void LDP_train::Read_Folder_Images(char*folder)
{
	cv::Mat image;
	DIR*dir;
    struct dirent*entry;
    struct stat info;

    dir=opendir(folder);
    if(!dir)
    {
    	cout<<"could not open folder,"<<folder<<"please check if its in the same directory as the script"<<endl;
    	return ;
    }
    else{
    	while((entry=readdir(dir))!=NULL){
    		if(entry->d_name!=folder){
    			string path=string(folder)+"/"+string(entry->d_name);
    			cout<<path<<endl;
    			image=cv::imread(path);
    			if(!image.data){
    				cout<<"Could not open or find the image"<<endl;
    				continue;
    			}
    			else{
    				Create_LDP_Mat(image.rows,image.cols)
    				sample_image=new int*[image.rows];
    				for (int i=0;i<image.rows;i++){
    					sample_image[i]=new int[image.cols];
    					for(int j;j<image.cols;j++){
    						sample_image[i][j]=(int)image.at<uchar>(i,j);
    					}
    				}
    				Directional_Response(image.rows,image.cols);

    			}
    		}
    		delete [] sample_image;
    	}
    }
}

void LDP_train::Create_LDP_Mat(int rows1,int columns){
	zan =new int*[rows1];
	for(int y=0;y<rows1;y++){
		zan[y]=new int [columns];
	}
}

void LDP_train::Directional_Respone(int length,int width){
   ptr=new int**[length];
   for(int i=0;i<length;i++){
   	ptr[i]=new int*[width];
   	for(int j=0;j<width;j++)
   	{
   		ptr[i][j]=new int[7];
   		Cal_Directions(i,j,ptr[i][j]);
   	}
   }
   Liner_Dir_Pat(length,width);
}

void LDP_train::Liner_Dir_Pat(int length,int width){
	for(int i=0;i<length;i++){
		for(int j=0;j<width;j++){
			ldp_x_y=0;
			temp=new int[7];
			for(int n=0;n<7;n++){
				temp[n]=ptr[i][j][n]
			}
			bubbleSort(temp);
			int difference;
			int value;
			for(int m=0;m<7;m++){
				difference=((ptr[i][j][m])-temp[3]);
				if(difference >=0){
					value=1;
				}else{
					value=0;
				}
				ldp_x_y=ldp_x_y+(value*(pow(2,m)));
			}
			zan[i][j]=ldp_x_y;
			delete temp;
		}
	}
	delete [] ptr;
	Histogram(length,width);
}
void LDP_train::Histogram(int length,int width){
	int value1;
	tech1=new int[56];
    for(int m=0;m<56;m++){
    	tech1[m]=0;
    }
    for(int t=0;t<=56;t++){
    	for(int i=0;i<length;i++){
    		for(int j=0;j<width;j++){
    			if(zan[i][j]==t){
    				value1=1;
    			}else{
    				value1=0;
    			}
    			tech1[t]=tech1[t]+value1;
    		}
    	}
    }
    delete [] zan;
    cout<<"LDP feature is equal to:"<<endl;
    cout<<"["<<endl;
    for(int k=0;k<56;k++){
    	cout<<tech1[k]<<",";
    }
    cout<<"]"<<endl;
    ofstream myfile("LDP_feature.txt",ios::out|ios::app);
    if(myfile.is_open()){
       for(int k=0;k<56;k++){
       	myfile<<tech1[k]<<",";
       }
       myfile<<"\n";
    }
    else{
    	cout<<"Could not open or Write LDP_feature to LDP_feature.txt"<<endl;

    }
    delete [] tech1;
}
