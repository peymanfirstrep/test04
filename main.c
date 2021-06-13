#include <stdio.h>
#include <math.h>
// first

#define     K      201                           //total number of rows
#define     I       40                             //total number of columns
#define     PI     3.142857                  //pi 

int main(int argc, char **argv)
{
    // variables
    int i,k;
    int j;
    float datain[K][I];              // row data as input
    float dataout[K][I];            // centralized  data
    const float R=PI/20;
   
   // structure
    struct PIPECENTER {
        float ro; 
        float fi;
    } pc[K];
    
           
	printf("hello world\n");                                                                    // to check the project execution only
    printf("The angle between the fingers = %f Radian\n",R);            // to check the calculation
    
    
    // File pointers
    FILE *fin;                         // file pointer for input data
    FILE *fcopy;                    // the input data to be copied in datacopy.txt to check the reading and fcopy is the filo pointer
    FILE *fpc;                        // file pointer for the pipecenter.txt in which the coordinate of the center of pipe is written
    FILE *fout;                      // file pointer for the centralized  data (final output)
    
    //Reading data from the file
    fin=fopen("data.txt","r");
     for(k=0;k<K;k++)
    {
        for(i=0;i<I;i++)
        {
            fscanf(fin, "%f", &datain[k][i]);
        }
    }
    fclose(fin);
    
    
    
    //copy the data.txt to datacopy.txt for checking the reading writing  process
    fcopy=fopen("datacopy.txt","w");
     for(k=0;k<K;k++)
    {
        for(i=0;i<I;i++)
        {
            fprintf(fcopy, "%f\t", datain[k][i]);
        }
        fprintf(fcopy, "\n");
    }
    fclose(fcopy);
   
   
   
    //Calculating OA and OL
    float OL[K];    // Offset abs length
    float OA[K];   // offset angle to first finger in radian
    float temp1;
    int n;
     n=0;  
    for(k=0;k<K;k++)
    {
        OL[k]=0;
        
       for(j=0;j<I/2;j++)
       {
           temp1=fabs(datain[k][j]- datain[k][j+20]);
           if(temp1/2 > OL[k])
           {
               OL[k]=temp1/2;
               n=j;
           }
       }
       if(datain[k][n]>datain[k][n+20])
       {
           OA[k] = R* n + PI;
        }
         else
         {
            OA[k] = R*n;
            
         }
     }    
     
     // pipe center coordinates
     for(k=0;k<K;k++)
     {
         pc[k].ro=OL[k];
         if(OA[k]<PI)
             pc[k].fi= OA[k]+PI;
         else
             pc[k].fi= OA[k]-PI;
        
     }
    
    
    // writing the pipe center coordinate (ro,fi) in the pipecenter.txt
     fpc=fopen("pipecenter.txt","w");
     for(k=0;k<K;k++)
     {
         fprintf(fpc,"%f\t%f\n", pc[k].ro, pc[k].fi);
     }
    fclose(fpc);
    
    
    //centralizing  the measured data
    float Angi,TG,PG,AiG,temp2;
    for(k=0;k<K;k++)
    {
        for(i=0;i<I;i++)
        {
            // calculation
            Angi=i*R-OA[k];
            TG=datain[k][i]*cos(Angi);
            PG=TG+OL[k];
            AiG=datain[k][i]*sin(Angi);
            temp2=PG*PG + AiG*AiG;
            dataout[k][i] =  sqrt(temp2);
        }
    }
    
    // writing the centralized data in the dataout.txt
    fout=fopen("dataout.txt","w");
    for(k=0;k<K;k++)
    {
        for(i=0;i<I;i++)
        {
            fprintf(fout,"%f\t",dataout[k][i]);
        }
        fprintf(fout,"\n");
    }
    
    fclose(fout);
    
    printf("\nend of the calculation\n\n\n\n");   // to make sure the whole program is done
    
  
	return 0;
}
