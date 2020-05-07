#include "fcntl.h"
#include "fs.h"
#include "types.h"
#include "stat.h"
#include "user.h"

int folding(unsigned char in[],int batas, int len, int newline_flag, int separator)
{
   int i;
   for (i=0; i <=len; i ++)
   {
      printf(1,"%c",in[i]);
      if(i%batas==batas-1)
      {
        printf(1,"\n");
      }
   }
   return 0;
}

int main(int argc, char *argv[])
{
  int buff_len;
  unsigned char data[1024];
  int inputfile;
  int batas=5;

  if(argc==2)
  {
    if((inputfile = open(argv[1],O_RDONLY)) < 0)
    {
       close(inputfile);
       exit();
    }
  while ((buff_len = read(inputfile,data,sizeof(data))) > 0);
  folding(data,batas,strlen((char*)data),0,76);
  close(inputfile);
  exit();
  }
  else if(argc==3)
  {
    char tipe[20];
    int newbatas,i,j;
    strcpy(tipe, argv[1]);
    newbatas=strlen(tipe);
    for(i=0,j=2;j<newbatas;i++,j++)
    {
      tipe[i]=tipe[j];
    }
    batas=atoi(tipe);
    if((inputfile = open(argv[2],O_RDONLY)) < 0)
    {
       close(inputfile);
       exit();
    }
    while ((buff_len = read(inputfile,data,sizeof(data))) > 0);
    folding(data,batas,strlen((char*)data),0,76);
    close(inputfile);
    exit();
  }
}
