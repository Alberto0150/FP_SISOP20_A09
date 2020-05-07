#include "types.h"
#include "stat.h"
#include "user.h"
#include "fs.h"

char buf[512];

int
main(int argc, char *argv[])
{
 int i, l, w, c, inword, n;
 int fd;
struct stat st;

if((fd = open(argv[1], 0)) < 0){
   		printf(2, "cannot open %s\n", argv[1]);
   		exit();
  	}
  	if(fstat(fd, &st) < 0){
    		printf(2, "cannot stat %s\n", argv[1]);
    		close(fd);
    		exit();
     }

 if(argc < 1){
   printf(1, "Need Argument\n");
   exit();
 }

 if (st.type == 2){
	printf(1, "cant delete file\n");
}

  l = w = c = 0;
  inword = 0;
    while((n = read(fd, buf, sizeof(buf))) > 0){
    for(i=0; i<n; i++){
      c++;
      if(buf[i] == '\n')
        l++;
      if(strchr(" \r\t\n\v", buf[i]))
        inword = 0;
      else if(!inword){
        w++;
        inword = 1;
      }
    }
  }
	
//   printf(1,"%d", l);
	if(l==0){
	unlink(argv[1]);
	}
	else{
	printf(1, "cant delete cause there something inside\n");
}
  exit();

   }
