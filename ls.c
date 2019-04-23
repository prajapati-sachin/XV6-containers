#include "types.h"
#include "stat.h"
#include "user.h"
#include "fs.h"

char*
fmtname(char *path)
{
  static char buf[DIRSIZ+1];
  char *p;

  // Find first character after last slash.
  for(p=path+strlen(path); p >= path && *p != '/'; p--)
    ;
  p++;

  // Return blank-padded name.
  if(strlen(p) >= DIRSIZ){
    return p;
  }


  memmove(buf, p, strlen(p));
  memset(buf+strlen(p), ' ', DIRSIZ-strlen(p));
  // printf(2, "ls: %d\n", cn);
  return buf;
}

int check(char *path)
{
  char *p;
  for(p=path+strlen(path); p >= path && *p != '/'; p--)
    ;
  p++;
  // Return blank-padded name.
  if(strlen(p) >= DIRSIZ)
    return 0;

  char *pp; 
  int cn =0;
  for(pp=p+strlen(p); pp >= p; pp--){
    if(*pp=='%')
      cn=1;
  }

  if(cn==0)
    return 0;

  for(pp=p+strlen(p); pp >= p && *pp != '%'; pp--)
    ;

  // *pp = '\0';

  pp++;

  char t = *pp;
  int n = 0;
  n+= (int)t - '0';
  n*=10;
  pp++;
  t=*pp;
  n+= (int)t - '0';

  return n;
}

char*
cut(char *path)
{
  static char buf[DIRSIZ+1];
  char *p;

  // Find first character after last slash.
  for(p=path+strlen(path); p >= path && *p != '/'; p--)
    ;
  p++;

  // Return blank-padded name.
  // if(strlen(p) >= DIRSIZ){
  //   return p;
  // }

  memmove(buf, p, strlen(p)-3);
  memset(buf+strlen(p)-3, ' ', DIRSIZ-strlen(p)+3);
  // printf(2, "ls: %d\n", cn);
  return buf;


  // memmove(buf, p, strlen(p));
  // memset(buf+strlen(p), ' ', DIRSIZ-strlen(p));
  // // printf(2, "ls: %d\n", cn);
  // return buf;
}

void
ls(char *path)
{
  char buf[512], *p;
  int fd;
  struct dirent de;
  struct stat st;

  if((fd = open(path, 0)) < 0){
    printf(2, "ls: cannot open %s\n", path);
    return;
  }

  if(fstat(fd, &st) < 0){
    printf(2, "ls: cannot stat %s\n", path);
    close(fd);
    return;
  }
  //////////////////////////////////////////////////
  char record[100][28];
  int count=0;
  int cid = getcid();


  ///////////////////////////////////////////
  switch(st.type){
  case T_FILE:
    printf(1, "%s %d %d %d\n", fmtname(path), st.type, st.ino, st.size);
    break;

  case T_DIR:
    if(strlen(path) + 1 + DIRSIZ + 1 > sizeof buf){
      printf(1, "ls: path too long\n");
      break;
    }
    strcpy(buf, path);
    p = buf+strlen(buf);
    *p++ = '/';
    while(read(fd, &de, sizeof(de)) == sizeof(de)){
      if(de.inum == 0)
        continue;
      memmove(p, de.name, DIRSIZ);
      p[DIRSIZ] = 0;
      if(stat(buf, &st) < 0){
        printf(1, "ls: cannot stat %s\n", buf);
        continue;
      }

      int cd = check(buf);

      // if(count >2)
      // printf(1, "cd: %d\n", cd );
      
      if(cid==0){
        if(cd == 0){
          // char *dese = record[count];
          // strcpy(dese, fmtname(buf));
          // count++;
          printf(1, "%s %d %d %d %d\n", fmtname(buf), st.type, st.ino, st.size, cd);
        }
        else{
          printf(1, "%s %d %d %d %d\n", fmtname(buf), st.type, st.ino, st.size, cd);
        }
      }
      else{
        
        if(cd==0){
          char *dese = record[count];
          strcpy(dese, fmtname(buf));
          count++;
          printf(1, "%s %d %d %d %d\n", fmtname(buf), st.type, st.ino, st.size, cd);
        }else{
          // if(cd==cid){
            int j=-1;
            char *name = cut(buf);
            for(j=0;j<count;j++){
              char *dese = record[j];
              if(strcmp(dese,name)==0)
                break;
            }
            printf(1, "j: %d\n", j );
            if(j==count)
              printf(1, "%s %d %d %d %d\n", fmtname(buf), st.type, st.ino, st.size, cd);
          // }
        }
        

      }
      
      
      // printf(1, "%s %d %d %d\n", fmtname(buf), st.type, st.ino, st.size);
    }
    break;
  }
  close(fd);
}

int
main(int argc, char *argv[])
{
  int i;

  if(argc < 2){
    ls(".");
    exit();
  }
  for(i=1; i<argc; i++)
    ls(argv[i]);
  exit();
}
