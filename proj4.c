#include <stdio.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <stdlib.h>

/*
 * Compare input files one and two by writing any byte from file one that is not
 * equal to the corresponding byte in file two into the file called 
 * differencesFoundInFile1.txt
 */
void step1(const char *, const char *);

/*
 * Compare input files one and two by writing any byte from file two that is not
 * equal to the corresponding byte in file one into the file called 
 * differencesFoundInFile2.txt
 */
void step2(const char *, const char *);

/*
 * Main function that runs the code for proj 4
 */
int main(int argc, char * argv[]){
  //check for 3 arguments
  if(argc != 3){
    printf("Usage: proj4.out <file1> <file2>\n");
    return 1;
  }
  //open files for validity check
  FILE *fp1, *fp2;
  fp1 = fopen(argv[1], "r");
  fp2 = fopen(argv[2], "r");
  
  //check that both files exist
  if (fp1 == NULL || fp2 == NULL){
    printf("There was an error reading a file.\n");
    exit(EXIT_FAILURE);
  }
  
  //clean up after checks
  fclose(fp1);
  fclose(fp2);

  step1(argv[1], argv[2]);
  step2(argv[1], argv[2]);
  
return 0;
}//main


void step1(const char * argv1, const char * argv2){
  struct timeval begin, end;
  gettimeofday(&begin, NULL); //begin timer

  // open files to compare & differences
  FILE *fp1, *fp2, *fp3;
  fp1 = fopen(argv1, "r");
  fp2 = fopen(argv2, "r");
  fp3 = fopen("differencesFoundInFile1.txt", "w");
  
  int c1;
  int c2;
  //loop through byte by byte until the EOF to find differences
  do {
    c1 = fgetc(fp1);
    c2 = fgetc(fp2);
    if(c1 != c2 && c1 > 0){
      fputc(c1,fp3);
    }
  }
  while (c1 != EOF);
    
  //clean up
  fclose(fp1);
  fclose(fp2);
  fclose(fp3);
  
  //calculate time of completion  
  gettimeofday(&end, NULL);
  printf("Step 1 took %f milliseconds\n", (((double)end.tv_usec / 1000)
                  - ((double)begin.tv_usec / 1000)));

}


void step2(const char * argv1, const char * argv2){
  struct timeval begin, end;
  gettimeofday(&begin, NULL); //begin timer
  
  FILE *fp1, *fp2, *fp3;

  // open files to compare & differences
  fp1 = fopen(argv1, "r");
  fp2 = fopen(argv2, "r");
  fp3 = fopen("differencesFoundInFile2.txt", "w");
  
  //get size for files for step2
  struct stat fileStat1;
  struct stat fileStat2;
  stat(argv1, &fileStat1);
  stat(argv2, &fileStat2);
  int size1 = fileStat1.st_size;
  int size2 = fileStat2.st_size;

  char * fileArray1 = malloc(size1); //create array
  fread(fileArray1, size1, 1, fp1); //store bytes in array
  char * fileArray2 = malloc(size2); //create array
  fread(fileArray2, size2, 1, fp2); //store bytes in array

  //check for differences and write to file if found
  for(int i = 0; i < size2; i++){
    if(fileArray1[i] != fileArray2[i]){
      fwrite(&fileArray2[i], 1, 1, fp3);
    }
  }

  //clean up
  free(fileArray1);
  free(fileArray2);
  fclose(fp1);
  fclose(fp2);
  fclose(fp3);

  //calculate time of completion   
  gettimeofday(&end, NULL);
  printf("Step 2 took %f milliseconds\n", (((double)end.tv_usec / 1000)
                  - ((double)begin.tv_usec / 1000)));
}//step2
