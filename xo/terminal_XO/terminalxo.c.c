#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

//terminal based global variables
bool win = false;
bool draw = false;
int empty_count = 0;

//steps

//1. create a 3x3 matrix
//2. create two types of inputs x and o with two users choosing one each
//3. there are 3 horizontal ways to win 3 vertical ways to win and 2 diagonal ways to win
//   if any of the conditions are met after taking and placing the user input then the winner is the one who gave the input 
//4. if all the places are filled then the game is a draw 
//5. ask the player if he wants to restart the game and restart if nessasary

void create_matrix();
void arena_printer(char arena[][3])
{

    printf("\n");

    //using for rows
    for (size_t i = 0; i < 3; i++)
    {
        //using for placeholders and vertical lines
        for (size_t j = 0; j < 3; j++)
        {
            if (j == 0)
            {
                printf(" %c |",arena[i][j]);
            }
            else if (j == 1)
            {
                printf(" %c ",arena[i][j]);
            }
            else
            {
                printf("| %c ",arena[i][j]);
            }
        }

        //using for horizontal lines
        if(i != 2)
        {
            printf("\n");

            for(int j = 0 ; j < 3 ; j++)
            {
                for(int k = 0 ; k < 3; k++ )
                {
                    printf("-");
                }

                printf(" ");
            }

        }
        
        printf("\n");

        //reference
        /*
             x | o | x 
            --- --- ---
             o | o | x  
            --- --- ---
             o | o | x 
        */
        
    }
    
}

void mark (char arena[][3],int row,int column,char placeholder)
{
    arena[row-1][column-1]=placeholder;

    //tester
    //to check if the mark() is storing correct value in the matrix
    if(0)
    {
        arena_printer(arena);
    } 
}

bool winning_conditions(char arena[][3],int player,char placeholder)
{
    //check horizontal
    if(((arena[0][0]==placeholder)&&(arena[0][0]==arena[0][1])&&(arena[0][1]==arena[0][2]))||((arena[1][0]==placeholder)&&(arena[1][0]==arena[1][1])&&(arena[1][1]==arena[1][2]))||((arena[2][0]==placeholder)&&(arena[2][0]==arena[2][1])&&(arena[2][1]==arena[2][2])))
    {
        printf("\nplayer %d won the game\n",player);
        return true;
    }
    //check vertical
    else if (((arena[0][0]==placeholder)&&(arena[0][0]==arena[1][0])&&(arena[1][0]==arena[2][0]))||((arena[0][1]==placeholder)&&(arena[0][1]==arena[1][1])&&(arena[1][1]==arena[2][1]))||((arena[0][2]==placeholder)&&(arena[0][2]==arena[1][2])&&(arena[1][2]==arena[2][2])))
    {
        printf("\nplayer %d won the game\n",player);
        return true;
    }
    //check diagonal
    else if(((arena[0][0]==placeholder)&&(arena[0][0]==arena[1][1])&&(arena[1][1]==arena[2][2]))||((arena[0][2]==placeholder)&&(arena[0][2]==arena[1][1])&&(arena[1][1]==arena[2][0])))
    {
        printf("\nplayer %d won the game\n",player);
        return true;
    }

    return false;
}

void player1_move(char arena[][3],char player1_char)
{
    int row , column;
    arena_printer(arena);
    printf("player 1 turn:\n");
    while(1)
    {
        printf("enter the row and column of the place at which you would like to mark (format =[a,b]): ");
        scanf(" [%d,%d]",&row,&column);
        printf("\nthe row and the coulmn are : %d and %d\n",row,column);
        if (((row < 1) || (column < 1))||((row > 3)||(column > 3)))
        {
            printf("entered row and column should be in the range 1 to 3!\nre-enter the row and column , make sure it is valid.\n");
            continue;
        }

        else if ((arena[row-1][column-1] != ' '))
        {
            printf("chosen place already has been marked choose another location\n");
            continue;
        }

        else 
        {
            break;
        }
    }

    mark(arena,row,column,player1_char);
    empty_count++;
    //tester
    //to check the matrix after changes 
    if(0)
    {
        arena_printer(arena);
    }

    if(winning_conditions(arena,1,player1_char))
    {
        win = true;
        return;
    }
    else
    {
        
        if(empty_count == 9)
        {
            draw = true;
            return;
        }
        return;
    }

}

void player2_move(char arena[][3],char player2_char)
{
    int row , column;
    arena_printer(arena);
    printf("player 2 turn:\n");
    while(1)
    {
        printf("enter the row and column of the place at which you would like to mark (format =[a,b]): ");
        scanf(" [%d,%d]",&row,&column);
        printf("\nthe row and the coulmn are : %d and %d\n",row,column);
        if (((row < 1) || (column < 1))||((row > 3)||(column > 3)))
        {
            printf("entered row and column should be in the range 1 to 3!\nre-enter the row and column , make sure it is valid.\n");
            continue;
        }

        else if ((arena[row-1][column-1] != ' '))
        {
            printf("chosen place already has been marked choose another location\n");
            continue;
        }

        else 
        {
            break;
        }
    }

    mark(arena,row,column,player2_char);
    empty_count++;
    //tester
    //to check the matrix after changes 
    if(0)
    {
        arena_printer(arena);
    }

    if(winning_conditions(arena,2,player2_char))
    {
        win = true;
        return;
    }
    else
    {    
        if(empty_count == 9)
        {
            draw = true;
            return;
        }
        return;
    }

}

void play(char arena [][3])
{
    char player1_char;
    char player2_char;

    time_t t;
    srand((unsigned) time (&t));
    int random_num = rand();

    if(random_num%2 == 0)
    {
        //tester
        //helps to check the value getting stored as random
        if(0)
        {
            printf("%d",random_num);
        }
        printf("player 1 choose which placeholder whould you like to choose (available options = x,o): ");
        scanf(" %c",&player1_char);
        while (player1_char != 'x' && player1_char != 'o') 
        {
            printf("Invalid choice! Please choose either 'x' or 'o': ");
            scanf(" %c", &player1_char);
            printf("\n");
        }
        printf("player 1 your charecter is %c",player1_char);
        if (player1_char == 'x')
        {
            player2_char = 'o';
        }
        else if (player1_char == 'o')
        {
            player2_char = 'x';
        }
        printf("\nplayer 2 your charecter is %c",player2_char);

    }
    else
    {
        //tester 
        //helps to check the value getting stored as random
        if(0)
        {
            printf("%d",random_num);
        }

        /*
        while (player1_char != 'x' && player1_char != 'o') 
        {
            printf("Invalid choice! Please choose either 'x' or 'o': ");
            scanf(" %c", &player1_char);
        }
        */
        printf("player 2 choose which placeholder whould you like to choose (available options = x,o): ");
        scanf(" %c",&player2_char);
        while (player2_char != 'x' && player2_char != 'o') 
        {
            printf("Invalid choice! Please choose either 'x' or 'o': ");
            scanf(" %c", &player2_char);
        }
        printf("\nplayer 2 your charecter is %c",player2_char);
        if (player2_char == 'x')
        {
            player1_char = 'o';
        }
        else if (player2_char == 'o')
        {
            player1_char = 'x';
        }
        printf("\nplayer 1 your charecter is %c",player1_char);

    }

    while(1)
    {
        player1_move(arena,player1_char);
        if(win == true)
        {
            break;
        }
        else if(draw == true)
        {
            printf("\nthe match is declared as a draw\n");
            break;
        }
        //player2_move
        player2_move(arena,player2_char);
        if(win == true)
        {
            break;
        }
        else if(draw == true)
        {
            printf("\nthe match is declared as a draw\n");
            break;
        }
    }


    printf("\nwould you like to play again ?(yes = 1 , no = 0): ");
    int rematch_option;
    scanf(" %d",&rematch_option);
    if(rematch_option == 1)
    {
        empty_count = 0;
        draw = false;
        win = false;
        create_matrix();
    }
    else 
    {
        return;
    }

}

void create_matrix()
{
    //make a 3x3 charecter matrix 
    //initalize all places with space (32 ascii)
    //call play and give the matrix to play
    char arena[3][3];

    for(int i = 0 ; i < 3 ; i ++)
    {
        for(int j = 0 ; j < 3 ; j++)
        {
            arena[i][j] = ' ';
        }
    }


    play(arena);

}

int main()
{
    create_matrix();
}