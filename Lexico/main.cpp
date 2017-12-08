# include <stdio.h>
# include <curses.h>
# include <string.h>
# include <stdlib.h>

# define oprel 300
# define men 301
# define mei 302
# define igu 303
# define mai 304
# define may 305
# define dif 306

int i=0, f=0;

char buf[20]={"="};

struct complex
{
 int token;
 int lexema;
};

char sigcar ()
{
return buf[f++];
}

struct complex obtentoken ()
{
int edo=0;
char c;
struct complex cl;

    while (1)
       {
         switch (edo)
          {
            case 0:
              c=sigcar();
                  if (c==' ' || c=='\t' || c=='\n' || c=='\r'){
                     edo=0;
                     i=f;
                     }
                  else if (c=='<'){
                     edo=1;
                     }
                  else if (c=='='){
                     edo=5;
                     }
                  else if (c=='>'){
                   edo=6;
                   }
            break;

            case 1:
                  c=sigcar ();
              if (c=='='){
                   edo=2;
       }
                  else if (c=='>'){
                   edo=3;
                     }
                  else
                   {
                     edo=4;
                     f--;
                     }
            break;

            case 2:
              cl.token =oprel;
                  cl.lexema=dif;
                  i=f;
                  return cl;
            break;

            case 3:
              cl.token =oprel;
                  cl.lexema=dif;
                  i=f;
                  return cl;
             break;

            case 4:
              cl.token= oprel;
                  cl.lexema=men;
                  i=f;
                  return cl;
            break;

            case 5:
              cl.token=oprel;
                  cl.lexema=igu;
                  i=f;
                  return cl;
           break;

           case 6:
              c=sigcar ();
      if (c=='='){
                     edo=7;
                     }
      else{
                   edo=8;
                     f--;
                     }
           break;

           case 7:
              cl.token =oprel;
                  cl.lexema =mai;
                  i=f;
                  return cl;
           break;

           case 8:
              cl.token=oprel;
                  cl.lexema = may;
                  i=f;
                  return cl;
           break;
           }      //fin switch
         } //fin while
} //fin funcion


int main ()
{
struct complex a;
while (f<strlen (buf))
 {
   a = obtentoken ();
   printf ("%d ", a.token);
   printf ("%d\n", a.lexema);
  }
getch ();
return 0;
}