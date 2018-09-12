#include <cv.h>       // opencv general include file
#include <ml.h> // opencv machine learning include file
#include <iostream>
#include <stdio.h>
#include <fstream>
#include "LDP_train.h"

void  Nueral_Network_LDP_train(void){
  int number_of_training_samples = 100;
  int attributes_per_sample = 56;
  int number_of_testing_samples = 30;
  int number_of_classes = 3;

  // define training data storage matrices (one for attribute examples, one
  // for classifications)
  CvMat* training_data = cvCreateMat(number_of_training_samples, attributes_per_sample, CV_32FC1);
  CvMat* training_classifications = cvCreateMat(number_of_training_samples, number_of_classes, CV_32FC1);
  cvZero(training_classifications);

  // define testing data storage matrices
  CvMat* testing_data = cvCreateMat(number_of_testing_samples, attributes_per_sample, CV_32FC1);
  CvMat* testing_classifications = cvCreateMat(number_of_testing_samples, number_of_classes, CV_32FC1);
  cvZero(testing_classifications);

  // define classification output vector
  CvMat* classificationResult = cvCreateMat(1, number_of_classes, CV_32FC1);
  CvPoint max_loc = {0,0};

  int layers_d[] = { attributes_per_sample, 100,  number_of_classes};
  CvMat* layers = cvCreateMatHeader(1,3,CV_32SC1);
  cvInitMatHeader(layers, 1,3,CV_32SC1, layers_d);

  CvANN_MLP* nnetwork = new CvANN_MLP;
  nnetwork->create(layers, CvANN_MLP::SIGMOID_SYM, 0.6, 1);
  Read_Files("LDP_training_features.txt",training_data);
  Read_Files("LDP_training_classes.txt",training_classifications);

  CvANN_MLP_TrainParams params = CvANN_MLP_TrainParams(cvTermCriteria(CV_TERMCRIT_ITER+CV_TERMCRIT_EPS, 1000, 0.000001),CvANN_MLP_TrainParams::BACKPROP,0.1,0.1);
  int iterations = nnetwork->train(training_data, training_classifications, NULL, NULL, params);
}

void  Read_Files(const char *filename,CvMat*data)
{
   File *fptr;
   //int *lineVab;
   char trev;
   int istatus;
   int i=0;
   int line=0;
   int attribute=0;
   //lineVab=new int [56];
   fptr=fopen(filename,"r");
   if(!fptr)
   {
   printf("cannot  open or read file \n");
   return 0;
   }
   istatus=fscanf(fptr,"%c",&trev);
   while(istatus!=EOF){
          if(trev!='\n'){
             CV_MAT_ELEM(*data,int,line,attribute)=(int)trev;
             
             istatus=fscanf(ftpr,"%c",&trev);
             attribute++;
             }
           else{
             line++;
             attribute=0;
             }
   }
}
void  Testing_Neural(void){

    CvMat test_sample;
    int correct_class = 0;
    int wrong_class = 0;
    int false_positives [number_of_classes] = {0,0,0,0,0,0,0,0,0,0};

    for (int tsample = 0; tsample < number_of_testing_samples; tsample++)
    {
      // extract a row from the testing matrix

      cvGetRow(testing_data, &test_sample, tsample );

      // run neural network prediction

      nnetwork->predict(&test_sample, classificationResult);

        // The NN gives out a vector of probabilities for each class
        // We take the class with the highest "probability"
        // for simplicity (but we really should also check separation
        // of the different "probabilities" in this vector - what if
        // two classes have very similar values ?)

        cvMinMaxLoc(classificationResult, 0, 0, 0, &max_loc, 0 );

      printf("Testing Sample %i -> class result (digit %d)\n", tsample, max_loc.x);

      // if the corresponding location in the testing classifications
      // is not "1" (i.e. this is the correct class) then record this

      if (!(CV_MAT_ELEM(*testing_classifications, float, tsample, max_loc.x)))
      {
        // if they differ more than floating point error => wrong class
        wrong_class++;

        false_positives[(int) max_loc.x]++;
      }
      else
      {
        // otherwise correct

        correct_class++;
        }
     }
        printf( "\nResults on the testing LDP_Dataset:\t"
        "\tCorrect classification: %d (%g%%)\n"
        "\tWrong classifications: %d (%g%%)\n",
        correct_class, (double) correct_class*100/number_of_testing_samples,
        wrong_class, (double) wrong_class*100/number_of_testing_samples);

    for (int i = 0; i < number_of_classes; i++)
    {
      printf( "\tClass (digit %d) false postives  %d (%g%%)\n", i,
           false_positives[i],
           (double) false_positives[i]*100/number_of_testing_samples);
    }


    // free all memory

    cvReleaseMat( &training_data );
    cvReleaseMat( &training_classifications );
    cvReleaseMat( &testing_data );
    cvReleaseMat( &testing_classifications );
    cvReleaseMat( &classificationResult);

     // all OK : main returns 0

       return 0;
}

void main (void){
  LDP_train myObject();
  myObject.Read_Folder_Images("bad_train");
  myObject.Read_Folder_Images("good_train");
  myObject.Read_Folder_Images("empty_train");
  myObject.Read_Folder_Images("bad_test");
  myObject.Read_Folder_Images("good_test");
  myObject.Read_Folder_Images("empty_test");
  cout<<"Printing   Training"<<endl;
  Nueral_Network_LDP_train();
  cout<<"Testing  Model"<<endl;
  Testing_Neural_Network();
  cout<<"DONE"<<endl;

}
