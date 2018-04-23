#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

#define ANSI_FOND_RED     "\x1b[41m"
#define ANSI_FOND_GREEN   "\x1b[42m"
#define ANSI_FOND_YELLOW  "\x1b[43m"
#define ANSI_FOND_BLUE    "\x1b[44m"
#define ANSI_FOND_MAGENTA "\x1b[45m"
#define ANSI_FOND_CYAN    "\x1b[46m"
#define ANSI_FOND_RESET   "\x1b[0m"


void my_putchar(char c);
void my_putstr(char *str);
void sapin(int size);
void tronc(int size);
int starmax(int size);

void my_putchar(char c)
{
  write(1,&c,1);
}

void my_putstr(char *str) //affiche des str
{
  int i = 0;
  while (str[i] != '\0')
    {
      write(1,&str[i],1);
      i++;
    }
}

int starmax(int size)
{
    int i = 0;
    int j = 0;
    int k = 0;
    int star = 1;
    int bloc = 4;
    // int espace = 3 *size;
    int count = 0;
    int temp = count;
    int star_moins = 1;

    while (i < size) // le nombre de bloc de feuille est == a la size
    {
        while (k < bloc) //nb de ligne dans un bloc
        {
            while (j < star) //affichage du feuillage
            {
                count++;
                j++;
            }
            // espace = espace--; //permet de réduire l'espace vide avant le début de chaque ligne
            star = star +2;//ajoute une étoile de chq coté a chq ligne
            j = 0;
            k++;
            temp = count;
            count = 0;
        }
        k = 0;
        bloc++;

        if (i % 2 == 0) //tout les 2 plateau
        {
            star_moins++;
        }

        star = star - 2 *star_moins; //les nombre d'étoile perdu augmente de 2 tout les 2 plateaux
        i++;

    }
//    printf("temp = %d\n",temp);
    return temp;
}

void sapin(int size)
{
    int i = 0;
    int j = 0;
    int k = 0;
    int l = 0;
    int star = 1;
    int bloc = 4;
    int espace;
    int star_moins = 1;
    int decr = 0;
    int comp = 0;


    //calcul de l'espace max à la cime du Sapin
    espace = starmax(size)/2 - decr;
    //printf("espace = %d\n", espace);

    //construction des branches
    while (i < size)//crée les bloc 1 après l'autre
    {
        while (k < bloc) //on parcourt l'intérieur du bloc
        {
            // printf("l = %d\n", l);
            // printf("espace = %d\n", espace);
            while (l < (espace))//on affiche l'espace qui permet de centrer le sapin
            {
                my_putchar(' ');
                l++;
            }

            while (j < star) //affichage du feuillage
            {
                if ((j > 0) && (j % 2 == 1) && (k % 2 == 1))
                {
                    my_putstr(ANSI_COLOR_YELLOW);
                    my_putstr(ANSI_FOND_GREEN);
                    my_putchar('~');
                    my_putstr(ANSI_COLOR_RESET);
                    my_putstr(ANSI_FOND_RESET);
                }
                else if ((j > 0) && (j % 2 == 1) && ((k/2) % 2 == 1))
                {
                    my_putstr(ANSI_COLOR_RED);
                    my_putstr(ANSI_FOND_GREEN);
                    my_putchar('~');
                    my_putstr(ANSI_COLOR_RESET);
                    my_putstr(ANSI_FOND_RESET);
                }
                else
                {
                    my_putstr(ANSI_FOND_GREEN);
                    // my_putstr(ANSI_COLOR_GREEN);
                    my_putchar('*');
                    // my_putstr(ANSI_FOND_RESET);
                    my_putstr(ANSI_COLOR_RESET);
                }
                j++;
            }
            my_putchar('\n');
            espace--; //permet de réduire l'espace vide avant le début de chaque ligne
            star = star +2;//ajoute une étoile de chq coté a chq ligne
            j = 0;
            l = 0;
            k++;
        }
        k = 0;
        bloc++;

        if (i % 2 == 0) //tout les 2 plateau
        {
            star_moins++;
        }

        star = star - 2 *star_moins; //les nombre d'étoile perdu augmente de 2 tout les 2 plateaux
        espace = espace + star_moins; //on augmente l'espace pour compenser la perte des étoiles

        i++;
    }
}

void tronc(int size)
{
    int i = 0;
    int j = 0;
    int l = 0;
    int espace;
    int newSize;
    int largeur;

    int star_max = starmax(size);

    espace = star_max;

    if (size % 2 == 0)
        largeur = size +1;
    else
        largeur = size;

    espace = (espace - largeur)/2;

        while (i < size)
        {
            if (size % 2 == 0) //permet de gérer les cas pair ou la hauteurs du tronc != a sa largeur
                newSize = size +1;
            else
                newSize = size;

            while (l < espace) //centre le tronc
            {
                my_putchar(' ');
                l++;
            }

            while (j < newSize) //affiche le tronc
            {
                my_putstr(ANSI_FOND_RED);
                my_putstr(ANSI_COLOR_YELLOW);
                my_putchar('|');
                my_putstr(ANSI_COLOR_RESET);
                my_putstr(ANSI_FOND_RESET);
                j++;
            }
            my_putchar('\n');
            j=0;
            l = 0;
            i++;
        }
}

int main(int argc, char *argv[])
{
    int size = 0;
    char *str1 = "The argument must be positive.\n";
    char *str2 = "Sapin takes its size as it first argument.\n";

    if (argc < 2)
        my_putstr(str2);
    else
    {
        size = atoi(argv[1]);
        if (size < 0)
            my_putstr(str1);
        if (size == 0)
            write(1,"\n",1);
        sapin(size);
        tronc(size);
    }

    return 0;
}
