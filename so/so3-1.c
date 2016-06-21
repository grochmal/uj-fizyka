#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>

#define ME "pipeme.txt"
#define YOU "pipeyou.txt"

int IsMe(void);
int IsYou(void);

int main(void)
{
   char buf[12], *me = "Me", *you = "You";
   
   do{
      
      puts("Me or You");
      scanf("%s", buf);
      
      if(!(strcmp(buf, me)))
         return IsMe();
      
      if(!(strcmp(buf, you)))
         return IsYou();
      
   }while(1);
}

int IsMe(void)
{
   char letter, buf[80], *off = "I Want Out!";
   int i, pid;
   FILE *fme, *fyou;
   
   if((pid = fork()) == -1)
   {
      perror("Error");
      exit(1);
   }
   
   if(pid == 0)
   {
         
      if((fyou = fopen(YOU, "r")) == NULL)
      {
         perror("File opening error, maybe file pipeyou.txt does not exist.");
         exit(2);
      }
      
      do{
            
         while((letter = fgetc(fyou)) != EOF)
         {
            putchar(letter);
         }
         
      }while(1);
      
   }
   else
   {
      
      if((fme = fopen(ME, "w")) == NULL)
      {
         perror("File opening error, maybe file pipeme.txt does not exist.");
         exit(1);
      }
      
      do{
         
         i = 0;
         
         fgets(buf, 80, stdin);
         
         if(!(strncmp(buf, off, 11)))
            return 0;
         
         while(buf[i])
         {
            fputc(buf[i], fme);
            i++;
         }
         
      }while(1);
      
   }
}

int IsYou(void)
{
   char letter, buf[80], *off = "I Want Out!";
   int i, pid;
   FILE *fme, *fyou;
   
   if((pid = fork()) == -1)
   {
      perror("Error");
      exit(1);
   }
   
   if(pid == 0)
   {
         
      if((fme = fopen(ME, "r")) == NULL)
      {
         perror("File opening error, maybe file pipeyou.txt does not exist.");
         exit(2);
      }
      
      do{
            
         while((letter = fgetc(fme)) != EOF)
         {
            putchar(letter);
         }
         
      }while(1);
      
   }
   else
   {
      
      if((fyou = fopen(YOU, "w")) == NULL)
      {
         perror("File opening error, maybe file pipeme.txt does not exist.");
         exit(1);
      }
      
      do{
         
         i = 0;
         
         fgets(buf, 80, stdin);
         
         if(!(strncmp(buf, off, 11)))
            return 0;
         
         while(buf[i])
         {
            fputc(buf[i], fyou);
            i++;
         }
         
      }while(1);
      
   }
}
