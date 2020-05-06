#include "fcntl.h"
#include "fs.h"
#include "types.h"
#include "stat.h"
#include "user.h"

unsigned char charset[]={"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"};

//untuk reverse karakter
unsigned char revchar(char ch)
{
   if (ch >= 'A' && ch <= 'Z')
      ch -= 'A';
   else if (ch >= 'a' && ch <='z')
      ch = ch - 'a' + 26;
   else if (ch >= '0' && ch <='9')
      ch = ch - '0' + 52;
   else if (ch == '+')
      ch = 62;
   else if (ch == '/')
      ch = 63;
   return(ch);
}

//fungsi encode
int encode(unsigned char in[], unsigned char out[], int len, int newline_flag, int separator)
{
   int i,j,blks,left_over;

   blks = (len / 3) * 3;
   for (i=0,j=0; i < blks; i += 3,j += 4)
   {
      out[j] = charset[in[i] >> 2];
      out[j+1] = charset[((in[i] & 0x03) << 4) + (in[i+1] >> 4)];
      out[j+2] = charset[((in[i+1] & 0x0f) << 2) + (in[i+2] >> 6)];
      out[j+3] = charset[in[i+2] & 0x3F];

      if (!(j % (separator+1)) && newline_flag)
      {
         out[j+4] = '\n';
         j++;
      }
   }
   left_over = len % 3;

   //karena perubahan bits yang awalnya 8 menjadi 6 per karakter
   // menambahkan masking '='
   // untuk menambah byte pada block karakter terakhir
   if (left_over == 1)
   {
      out[j] = charset[in[i] >> 2];
      out[j+1] = charset[(in[i] & 0x03) << 4];
      out[j+2] = '=';
      out[j+3] = '=';
      j += 4;
   }
   else if (left_over == 2)
   {
      out[j] = charset[in[i] >> 2];
      out[j+1] = charset[((in[i] & 0x03) << 4) + (in[i+1] >> 4)];
      out[j+2] = charset[(in[i+1] & 0x0F) << 2];
      out[j+3] = '=';
      j += 4;
   }
   out[j] = '\0';
   return(j);
}


int main(int argc, char *argv[])
{
    int buff_len;
    unsigned char output[1024],data[1024];
    int inputfile;

    // input default base64 [file]
    if(argc==2)
    {
      if((inputfile = open(argv[1],O_RDONLY)) < 0)
      {
         close(inputfile);
         exit();
      }
    while ((buff_len = read(inputfile,data,sizeof(data))) > 0);
    encode(data, output, strlen((char*)data),0,76);
    printf(1,"%s\n",output);
    close(inputfile);
    exit();
   }

}
