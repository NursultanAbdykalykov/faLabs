#include <stdio.h>
#include <stdlib.h>
#include "functions.h"

int main(int argc, char* argv[]) {
    if (argc != 3) {
        printf("Неверное количество аргументов!\n");
        return 1;
    }

    if (validateFirstArgument(argv[1])) { 
        printf("Второй аргумент не должен быть числом\n");
        return 1;
   }

   char *flag = argv[1]; 
   int x = atoi(argv[2]); 
   
   if (compareStrings(flag, "-h") || compareStrings(flag, "/h")) {
       flagH(x);
   } else if (compareStrings(flag, "-p") || compareStrings(flag, "/p")) { 
       flagP(x);
   } else if (compareStrings(flag, "-e") || compareStrings(flag, "/e")) {
       flagE(x);
   } else if (compareStrings(flag, "-a") || compareStrings(flag, "/a")) { 
       flagA(x);
   } else if (compareStrings(flag, "-f") || compareStrings(flag, "/f")) { 
       flagF(x);
   } else if(compareStrings(flag, "-s") || compareStrings(flag, "/s")) { 
       flagS(x);
   } else{
       printf("Вы ввели несуществующий флаг\n");
   }

   return 0;
}