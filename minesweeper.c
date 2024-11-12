#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
// stage 1 = 8x8 
// stage 2 = 16x16
// stage 3 = 32x16

int menu(char *);                                                 //menu epilogon
void custom_menu(int* , int* , char* , int*);                    //menu dimiourgias custom level
int level_menu();                                               //menu epilogis prokathorismenon level
void level_creator(int, int* , int* , char* , int*);           //dimiourgia prokathorismenou level
int play(int , int, int, int*, int*);
void high_scores(int, int, int, int, int);


int main(int argc, char *argv[]) 
{
    int choice;
    int Exit = 0;
    int bomb_number = 9;   int* p_bomb_number = &bomb_number;
    int height = 8;        int* p_height = &height;
    int width = 8;         int* p_width = &width;
    char* level_str;
    int score = 0;             int* p_score = &score;         
    int change_score = 0;      int* p_change_score = &change_score;
    int first = 0;
    int just_view = 0; // nea kataxorisi high score
    int free_now = 0; 

    level_str = (char*) malloc(4*sizeof(char));   //desmefsi 4 xoron stin mnimi megedous char
    if (level_str == NULL)
    {
        printf("Memory allocation error\n");
        exit(1);
    }
    strcpy(level_str,"easy");                     //default level = easy

    while (Exit == 0)
    {
        do
        {

            choice = menu(level_str);
        
            if( choice == 1)   
            {
            
                play(height , width, bomb_number , p_score, p_change_score );
                printf("Score:%d\n",score);
                high_scores(score, change_score, first, just_view , free_now);
                first = 1;
            }
            else if (choice == 2)
            {
                int level_choice = level_menu();
                level_creator(level_choice , p_height , p_width , level_str , p_bomb_number );
            }
            else if (choice == 3)
            {
                custom_menu(p_height, p_width , level_str , p_bomb_number);
            }
            else if (choice == 4)
            {
                just_view = 1;
                high_scores(score, change_score, first, just_view , free_now);
                just_view = 0;
                first = 1;
            }
            else if (choice == 5)
            {
                Exit = 1;
                free_now = 1;
                just_view = 1;
                high_scores(score, change_score, first, just_view , free_now);
                printf("Thank you for playing\n");
                free(level_str);
                
            }
            else
            {
                printf("Invalid option\n");
            }

        } while ((choice != 1) && (choice != 2) && (choice != 3) && (choice != 4) && (choice != 5));    //mexri na dothei sosti epilogi
    }


}


int menu(char * level_str)
{
    int choice;

    printf("Minesweeper\n\n");
    printf("Level = %s \n",level_str);
    printf("1. Play\n");
    printf("2. Select Level\n");
    printf("3. Create Custom Level\n");
    printf("4. High Scores\n");
    printf("5. Exit\n");

    scanf("%d",&choice);
    printf("\n");
    return choice;
}

void custom_menu(int* p_height, int* p_width , char* level_str, int* p_bomb_number)
{
    strcpy(level_str , "custom");

    printf("Type your level's height\n");
    scanf("%d",p_height);
    printf("Type your level's width\n");
    scanf("%d",p_width);

    printf("Type how many bombs you want in your level\n");
    printf("Note that bombs should be more than 0 and 1 less than your total level's spaces\n");
    
    scanf("%d",p_bomb_number);
    printf("Custom level created\nYou will be redirected to main menu\n\n");

}

int level_menu()
{
    int choice;

    printf("Choose your Level\n\n");
    printf("1. Easy :   8x8\n");
    printf("2. Medium : 16x16\n");
    printf("3. Hard :   32x16\n");
    scanf("%d",&choice);

    return(choice);
}

void level_creator(int level_choice ,int* p_height ,int* p_width ,char* level_str, int* p_bomb_number)
{
    if(level_choice == 1)
    {
        *p_height = 8;
        *p_width = 8;
        *p_bomb_number = 10;
        
        strcpy(level_str,"easy");
        printf("\n\n\n\n\n");
    }
    else if (level_choice == 2)
    {
        *p_height = 16;
        *p_width = 16;
        *p_bomb_number = 40;
        level_str = (char*) realloc(level_str,6*sizeof(char));
        
        strcpy(level_str, "medium");
        printf("\n\n\n\n\n");

    }
    else if (level_choice == 3)
    {
        *p_height = 32;
        *p_width = 16;
        *p_bomb_number = 99;

        strcpy(level_str, "hard");
        printf("\n\n\n\n\n");
    }
    else
    {
        printf("invalid option\n");
    }
    
}

int play(int height , int  width, int bomb_number, int* p_score, int* p_change_score)
{
    int lost = 0;
    int current_height;
    int current_width;
    int i;
    int j;
    int bomb_x;
    int bomb_y;
    int choice_height;
    int choice_width;
    int A[height][width];     //pinakas me bombs 
    int B[height][width];    //pikanas pou fenetai 
    int count;
    int wrong = 0;
    int counter = 0;

    * p_score =0;

    for (i=0; i<height; i++)          //arxikopoiisi pinakon me '?'
    {
        for (j=0; j<width; j++)
        {
            B[i][j] = 63;
            A[i][j] = 63;            
            printf("%c  ",B[i][j]);
        }
        printf("\n");
    }
    
    
    printf("\nchoose height:");                //epilogi xristi
    scanf("%d",&choice_height);
    printf("\nchoose width:");
    scanf("%d",&choice_width);

    srand(time(NULL));                         //arxikopoiisi rand
    rand();
    
    for (i=0; i<bomb_number; i)                  //tixaia katanomi ton bomb
    {

        bomb_x = rand()%(height);
        bomb_y = rand()%(width);

        if ((A[bomb_x][bomb_y] == 63) && (A[bomb_x][bomb_y] != 66))           //elegxos oste na min paei ana bomb stin idia thesi 2 fores kai etsi kathei 1 bomb
        {
            A[bomb_x][bomb_y] = 66;
            i++;
        }
    }


    if(A[choice_height][choice_width] != 63)    //elegxos an i proti epilogi tou xristi exei bomb
    {
        wrong = 1;
    }


    if (wrong == 1)    //metakinisi tou bomb oste o xristis na min xasei stin 1h prospatheia
    {
        for (i=0; i<height; i++)
        {
            for (j=0; j<width; j++)
            {
                if((wrong == 1) && (A[i][j] != 66))
                {
                    A[i][j] = 66;
                    wrong = 0;
                    
                }
            }
        }
    }

    A[choice_height][choice_width] = 63;              // afou h bomb metakinithike i epilogi tou xristi ginetai '?'



    //kathirismos arithmou gitonikon bomb


    //elegxos giro apo to proto stixio tis protis stilis

    if((A[0][0] != 66) && (A[0][1] == 66))
    {
        counter++;
    }
    if((A[0][0] != 66) && (A[1][0] == 66))
    {
        counter++;
    }
    if((A[0][0] != 66) && (A[1][1] == 66))
    {
        counter++;
    }
    if((counter != 0) && (A[0][0] != 66))
    {
        A[0][0] = counter;
    }
    else if ((counter == 0) && (A[0][0] != 66))
    {
        A[0][0] = 0;
    }


    //elegxos giro apo tin 1h stili

    for (i=1; i<height-1; i++)
    {
        counter = 0;
        j=0;
        if ((A[i][j] != 66) && (A[i-1][j] == 66))
        {
            counter++;
        }
        if ((A[i][j] != 66) && (A[i-1][j+1] == 66))
        {
            counter++;
        }
        if ((A[i][j] != 66) && (A[i][j+1] == 66))
        {
            counter++;
        }
        if ((A[i][j] != 66) && (A[i+1][j+1] == 66))
        {
            counter++;
        }
        if ((A[i][j] != 66) && (A[i+1][j] == 66))
        {
            counter++;
        }
        if ((counter != 0) && (A[i][j] != 66))
        {
            A[i][j] = counter;
        }
        else if ((counter == 0) && (A[i][j] != 66))
        {
            A[i][j] = 0;
        }
    }


    //elegxos giro apo to teleftaio stixio tis protis stilis

    counter = 0;
    if((A[height-1][0] != 66) && (A[height-2][0] == 66))
    {
        counter++;
    }
    if((A[height-1][0] != 66) && (A[height-2][1] == 66))
    {
        counter++;
    }
    if((A[height-1][0] != 66) && (A[height-1][1] == 66))
    {
        counter++;
    }
    if((counter != 0) && (A[height-1][0] != 66))
    {
        A[height-1][0] = counter;
    }
    else if ((counter == 0) && (A[height-1][0] != 66))
    {
        A[height-1][0] = 0;
    }


    //elegxos tis giro apo tin teleftaia grammi
    
    for(i=1; i<width-1; i++)
    {
        counter = 0;
        if((A[height-1][i] != 66) && (A[height-1][i-1] == 66))
        {
            counter++;
        }
        if((A[height-1][i] != 66) && (A[height-2][i-1] == 66))
        {
            counter++;
        }
        if((A[height-1][i] != 66) && (A[height-2][i] == 66))
        {
            counter++;
        }
        if((A[height-1][i] != 66) && (A[height-2][i+1] == 66))
        {
            counter++;
        }
        if((A[height-1][i] != 66) && (A[height-1][i+1] == 66))
        {
            counter++;
        }
        if((counter != 0 ) && (A[height-1][i] != 66))
        {
            A[height-1][i] = counter;
        }
        else if ((counter == 0) && (A[height-1][i] != 66))
        {
            A[height-1][i] = 0;
        }
    }


    //elegxos giro apo to teleftaio stixio tis teleftaias grammis

    counter = 0;
    if((A[height-1][width-1] !=66) && (A[height-1][width-2] == 66))
    {
        counter++;
    }
    if((A[height-1][width-1] !=66) && (A[height-2][width-2] == 66))
    {
        counter++;
    }
    if((A[height-1][width-1] !=66) && (A[height-2][width-1]) == 66)
    {
        counter++;
    }
    if((counter != 0) && (A[height-1][width-1] !=66))
    {
        A[height-1][width-1] = counter;
    }
    else if ((counter == 0) && (A[height-1][width-1] != 66))
    {
        A[height-1][width-1] = 0;
    }



    //elegxos giro apo tin teleftaia stili

    for(i=1; i<height-1; i++)
    {
        counter = 0;
        if((A[i][width-1] != 66) && (A[i-1][width-1] == 66))
        {
            counter++;
        }
        if((A[i][width-1] != 66) && (A[i-1][width-2] == 66))
        {
            counter++;
        }
        if((A[i][width-1] != 66) && (A[i][width-2] == 66))
        {
            counter++;
        }
        if((A[i][width-1] != 66) && (A[i+1][width-2] == 66))
        {
            counter++;
        }
        if((A[i][width-1] != 66) && (A[i+1][width-1] == 66))
        {
            counter++;
        }
        if((counter != 0) && (A[i][width-1] != 66))
        {
            A[i][width-1] = counter;
        }
        else if ((counter == 0) && (A[i][width-1] != 66))
        {
            A[i][width-1] = 0;
        }
    }


    //elegxos teleftaiou stixiou protis grammis

    counter = 0;
    if((A[0][width-1] != 66) && (A[0][width-2] == 66))
    {
        counter++;
    }
    if((A[0][width-1] != 66) && (A[1][width-2] == 66))
    {
        counter++;
    }
    if((A[0][width-1] != 66) && (A[1][width-1] == 66))
    {
        counter++;
    }
    if((counter != 0) && (A[0][width-1] != 66))
    {
        A[0][width-1] = counter;
    }
    else if ((counter == 0) && (A[0][width-1] != 66))
    {
        A[0][width-1] = 0;
    }


    //elegxos giro apo tin proti grammi

    for(j=1; j<width-1; j++)
    {
        counter = 0;
        if((A[0][j] != 66) && (A[0][j-1] == 66))
        {
            counter++;
        }
        if((A[0][j] != 66) && (A[1][j-1]== 66))
        {
            counter++;
        }
        if((A[0][j] != 66) && (A[1][j] == 66))
        {
            counter++;
        }
        if((A[0][j] != 66) && (A[1][j+1] == 66))
        {
            counter++;
        }
        if((A[0][j] != 66) && (A[0][j+1] == 66))
        {
            counter++;
        }
        if((counter != 0) && (A[0][j] != 66))
        {
            A[0][j] = counter;
        }
        else if ((counter == 0) && (A[0][j] != 66))
        {
            A[0][j] = 0;
        }
    }


    // elegxos ollon ton ipolipon stixion

    for(i=1; i<height-1; i++)
    {
        for(j=1; j<width-1; j++)
        {
            counter = 0;
            if((A[i][j] != 66) && (A[i-1][j-1] == 66))
            {
                counter++;
            }
            if((A[i][j] != 66) && (A[i][j-1] == 66))
            {
                counter++;
            }
            if((A[i][j] != 66) && (A[i+1][j-1] == 66))
            {
                counter++;
            }
            if((A[i][j] != 66) && (A[i+1][j] == 66))
            {
                counter++;
            }
            if((A[i][j] != 66) && (A[i+1][j+1] == 66))
            {
                counter++;
            }
            if((A[i][j] != 66) && (A[i][j+1] == 66))
            {
                counter++;
            }
            if((A[i][j] != 66) && (A[i-1][j+1] == 66))
            {
                counter++;
            }
            if((A[i][j] != 66) && (A[i-1][j] == 66))
            {
                counter++;
            }
            if((counter != 0) && (A[i][j] != 66))
            {
                A[i][j] = counter;
            }
            else if ((counter == 0) && (A[i][j] != 66))
            {
                A[i][j] = 0;
            }
        }
    }


    while(lost == 0)
    {

                                     //debug pinakas me tis lisis 
        /*
        for (i=0; i<height; i++)
        {
            for (j=0; j<width; j++)
            {
                if ((A[i][j] == 66) || (A[i][j] == 63))
                {
                    printf("%c  ",A[i][j]);             //an A[i][j] einai '?' tote ektiponetai os '?' kai oxi os 63
                }
                else
                {
                    printf("%d  ",A[i][j]);             //an A[i][j] einai arithmos ektiponetai os arithmos
                }
            }
            printf("\n");
        }
        printf("\n\n");
        */


        if (A[choice_height][choice_width] == 66)     //an o xristis epileksei bomb
        {
             lost = 1;
             printf("Game Over\n");

        }


        
    /* 
        prospatheia emfanisis mono geitonikon midenikon

        current_height = choice_height;
        current_width = choice_width;

        B[current_height][current_width] = 0;
        // enimerosi pinaka B meta apo tin proti epilogi

        int starting_height;
        int starting_width;

        starting_height = choice_height;
        starting_width = choice_width;


        int up = (A[current_height-1][current_width] == 0);            //elegxos diplanon stixion
        int down = (A[current_height+1][current_width] == 0);
        int left = (A[current_height][current_width-1] == 0);
        int right = (A[current_height][current_width+1] == 0);
        
        int up_inside = (current_height-1 >= 0);                       //elegxos iperxilisis
        int down_inside = (current_height+1 <= (height-1));
        int left_inside = (current_width-1 >= 0);
        int right_inside = (current_width+1 <= (width-1));

        for (i=0; i<1000; i++)
        {
            
            for(j=0; j<1000; j++)
            {
                if((up_inside) && (up))    //an up=0
                {
                    current_height --;
                    B[current_height][current_width] = 0;
                    up_inside = (current_height-1 >= 0); 
                    up = (A[current_height-1][current_width] == 0);
                }
                else
                {
                    break;
                }
            }

                //printf("%d %d %d %d", up, up_inside, right_inside, right);

                while(1) //kiklos / 
                {
                    up = (A[current_height-1][current_width] == 0);              //ananeosi elegxou diplanon stixion
                    down = (A[current_height+1][current_width] == 0);
                    left = (A[current_height][current_width-1] == 0);
                    right = (A[current_height][current_width+1] == 0);
        
                    up_inside = (current_height-1 >= 0);                          //ananeosi elegxou iperxilisis
                    down_inside = (current_height+1 <= (height-1));
                    left_inside = (current_width-1 >= 0);
                    right_inside = (current_width+1 <= (width-1));


                    if((up_inside) && (!up) && (right_inside) && (right))
                    {
                        
                        current_width++;
                        B[current_height][current_width] = 0;
                        
                        
                    }
                    else if((!up_inside) && (right_inside) && (right))
                    {
                        current_width++;
                        B[current_height][current_width] = 0;
                    }
                    else if((up_inside) && (right_inside) && (down_inside) && (!up) && (!right) && (down))
                    {
                        current_height++;
                        B[current_height][current_width] = 0;
                    }
                    else if ((up_inside) && (!right_inside) && (down_inside) && (!up) && (down))
                    {
                        current_height++;
                        B[current_height][current_width] = 0;
                    }
                    else if ((!up_inside) && (!right_inside) && (down))
                    {
                        current_height++;
                        B[current_height][current_width] = 0;
                    }
                    else if ((up_inside) && (left_inside) && (up) && (left))
                    {
                        current_width--;
                        B[current_height][current_width] = 0;
                    }
                    else if ((!right_inside) && (down_inside) && (up_inside) && (up) && (down))
                    {
                        current_height++;
                        B[current_height][current_width] = 0;
                    }
                    else if ((down_inside) && (B[current_height-1][current_width] == 0) && (down))
                    {
                        current_height++;
                        B[current_height][current_width] = 0;
                    }
                    //else if ((up_inside) && (down_inside) && (left_inside) && (right_inside) && (left) && (B[current_height+1][current_height] == 0))
                    //{
                    //    current_width--;
                    //    B[current_height][current_width] = 0;
                    //}
                    else if ((!left_inside) && (!down_inside) && (up_inside) && (right_inside) && ( right) && (B[current_height-1][current_width] == 0))
                    {
                        current_width++;
                        B[current_height][current_width] = 0;
                    }
                    else if((starting_height -= current_height) && (starting_width == current_width))
                    {
                        break;
                    }
                    else
                    {
                        break;
                    }
                }
            
            
        }

        if(A[current_height-1][current_width] != 66)
        {
            current_height --;
            B[current_height][current_width] = 0;
        }
        
    */




        for(i=0; i<height; i++)         //emfanisi olon ton midenikon
        {
            for(j=0; j<height; j++)
            {
                if(A[i][j] == 0)
                {
                    B[i][j] = 0;
                    
                }
            }
        }

        *p_score = 0;

        if(A[choice_height][choice_width] != 66)            
        {
            B[choice_height][choice_width] = 0;
        }


        for(i=0; i<height; i++)        //ipologismos score
        {
            for(j=0; j<height; j++)
            {
                if(B[i][j] != 63)
                {
                    *p_score += 10;
                }
            }
        }




        if(A[choice_height][choice_width] != 66)
        {
            printf("    ");
            for(i=0; i<width; i++)
            {
                if(i<10)
                {
                    printf("%d  ",i);
                }
                else
                {
                    printf("%d ",i);
                }
                
            }
            printf("\n\n");
            for(i=0; i<height; i++)
            {
                if(i<10)
                {
                    printf("%d   ",i);
                }
                else
                {
                    printf("%d  ",i);
                }
               for(j=0; j<width; j++)                //ektiposi pinaka
               {
                    if(B[i][j] == 0)                   //an o b einai 0 tote ektiponei ton A san arithmo   
                    {
                        printf("%d  ",A[i][j]);
                    }
                    else if(B[i][j] == 63)
                    {
                        printf("%c  ",B[i][j]);
                    }
                }
                printf("\n");
            }
            printf("\n");
        }


        count = 0;
        for(i=0; i<height; i++)
        {
            for(j=0; j<width; j++)
            {
                
                if((B[i][j] == 63))
                {
                    count++;
                }
            }
        }

        
        if(count == bomb_number)        //an ola ta '?' exoun bombs piso tous tote o xristis nikise 
        {
            lost = 1;
            printf("You Win\n");
        }


        if (lost == 0)
        {
            printf("\nchoose height:");
            scanf("%d",&choice_height);
            printf("\nchoose width:");
            scanf("%d",&choice_width);
        }

    }

    
}


void high_scores(int score, int change_score, int first, int just_view, int free_now)
{
    
    int i;
    static int A[10];
    int j;
    int temp;
    char* temp_str;
    static char* B[10];
    
    if (first == 0)
    {
        for (i=0; i<10; i++)        //desmefsi mnimis gia ton pinaka ma ta arxika
        {
            B[i] = (char*) malloc(3*sizeof(char));
            if(B[i] == NULL)
            {
                printf("Memory allocation error\n");
                exit(1);
            }
        }

        temp_str = (char*) malloc(3*sizeof(char));
        if (temp_str == NULL)
        {
            printf("Memory allocation error\n");
            exit(1);
        }
    }
    
    if (first == 0)             //an proti fora arxikopoiisi pinakon
    {
        for(j=0; j<10; j++)
        {
            B[j] = strcpy (B[j],"___");
        }

    
        for (i=0; i<10; i++)
        {
            A[i] = 0;
        }
    }

    
    if (just_view == 0)         //apothikeusi neou high score stin thesi tou mikroterou         
    {
        if(score > A[9])
        {
            A[9] = score;
            printf("\n New High score\n Please write your initials:___\n");
            scanf("%s",B[9]);
            A[9] = score;
        }
    }


    for (i=0; i<10; i++)                 //taksinomisi
    {
        for (j=1; j<10; j++)
        {
            if(A[j-1] < A[j])
            {
                temp = A[j-1];
                A[j-1] = A[j];
                A[j] = temp;

                strcpy(temp_str, B[j-1]);
                strcpy(B[j-1],B[j]);
                strcpy(B[j],temp_str);
            }
        }
    }


    for(i=0; i<10; i++)                              //ektiposi
    {
        printf("%d. %s : %d \n",i+1,B[i] ,A[i]);
    }

    
    
    if (free_now == 1)
    {
        for (i=0; i<10; i++)        //apodesmefsi mnimis gia ton pinaka ma ta arxika
        {
            free(B[i]);
        }
        free(temp_str);
    }

}
