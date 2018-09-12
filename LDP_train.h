#ifndef LDR_train_H
#define LDR_train_H
class LDP_train
{
private:
	int**sample_image;      //points to matrix to store image
	int***ptr        ;      //used to stores the kirch response vector  the sample image
	int**zan         ;      //points to the matrix that s
	int ldp_x_y;
	int *temp;
	int *tech1; 
public:
	void Histogram(int length, int width);
	void BubbleSort(int arr[]);
	void Liner_Dir_Path(int length,int width);
	void Directional_Response(int length,int width);
	void Cal_Directions(int val1,int val2,int *res);
	void Create_LDP_Mat(int rows1,int columns);
	void Read_Folder_Images(char *folder);
};
#endif  LDR_train_H