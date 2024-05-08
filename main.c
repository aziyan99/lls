#include <stdio.h>
#include <unistd.h>
#include <limits.h>
#include <dirent.h>
#include <stdlib.h>

#ifdef _WIN32
#define PATH_SEPARATOR "\\"
#elif _linux
#define PATH_SEPARATOR "/"
#endif // _WIN32

struct fileStruct {
  int fileSize;
  char fileName[255];
  char realPath[255];
};

int main(void){

  // TODO: Accept argument(s)
  
  char cwd[PATH_MAX];
  DIR *directory;
  struct dirent *entry;
  struct fileStruct availableFiles[100];

  if(getcwd(cwd, sizeof(cwd)) == NULL){
    printf("error: getcwd()\n");
    return 1;
  }
  
  directory = opendir(cwd);
  if(directory == NULL){
    printf("Unable to read directory\n");
    return 1;
  }
  
  char currentDir[sizeof(cwd)];
  int index = 0;
  while((entry = readdir(directory))){
    if((strcmp(entry->d_name, ".")) != 0 && (strcmp(entry->d_name, "..")) != 0){ // excluse "." and ".."
      strcpy(currentDir, cwd);
      availableFiles[index].fileSize = 0;
      strcpy(availableFiles[index].fileName, entry->d_name);

      strcat(currentDir, PATH_SEPARATOR);
      strcpy(availableFiles[index].realPath,  strcat(currentDir, entry->d_name));

      index++;
    }
  }
  
  closedir(directory);

  // Print the results
  printf("\n\tDirectory: %s\n", cwd);
  printf("Name\n");
  printf("----\n");
  for(int i=0; i < index; i++){
    printf("%s\t\n", availableFiles[i].realPath);
  }
  printf("\n");

  return 0;
}
