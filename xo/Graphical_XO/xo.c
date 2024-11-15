#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "raylib.h"

bool win = false;
bool draw = false;
int empty_count = 0;
bool click_start = false;
bool X_lock = false;
bool O_lock = false;
char win_line[7] = "\0\0.png";
bool collison_f = false;


void reset(char arena[][3],int * random_number,float * handy,char * turn)
{
    win = false;
    draw = false;
    empty_count = 0;
    *random_number = rand() % 2;
    *handy = 0;
    if(random_number == 0)
        {
            *turn = 'o';
            O_lock = true;
            X_lock = false;
        }
    else if(random_number == 1)
        {
            *turn = 'x';
            X_lock = true;
            O_lock = false;
        }
    
    for(int i = 0 ; i < 3 ; i ++)
    {
        for(int j = 0 ; j < 3 ; j++)
        {
            arena[i][j] = ' ';
        }
    }
    
    win_line[0] = '\0';
    win_line[1] = '\0';    
        
}

void draw_kitten(char turn)
{
    if(turn == 'x')
    {
        Texture2D thinking_cat = LoadTexture("turn_x.png");
        DrawTexture(thinking_cat,((GetScreenWidth()/2)-(thinking_cat.width/2)),((GetScreenHeight()/2)-(thinking_cat.height/2)),WHITE);
    }
    else if (turn == 'o')
    {
        Texture2D thinking_cat = LoadTexture("turn_o.png");
        DrawTexture(thinking_cat,((GetScreenWidth()/2)-(thinking_cat.width/2)),((GetScreenHeight()/2)-(thinking_cat.height/2)),WHITE);
    }
}

bool winning_conditions_g(char arena[][3],char placeholder)
{
    //check horizontal
    if(((arena[0][0]==placeholder)&&(arena[0][0]==arena[0][1])&&(arena[0][1]==arena[0][2]))||((arena[1][0]==placeholder)&&(arena[1][0]==arena[1][1])&&(arena[1][1]==arena[1][2]))||((arena[2][0]==placeholder)&&(arena[2][0]==arena[2][1])&&(arena[2][1]==arena[2][2])))
    {
        printf("\nplayer %c won the game\n",placeholder);
        
        if(((arena[0][0]==placeholder)&&(arena[0][0]==arena[0][1])&&(arena[0][1]==arena[0][2])))
        {
            win_line[0]='r';
            win_line[1]='1';
        }
        else if(((arena[1][0]==placeholder)&&(arena[1][0]==arena[1][1])&&(arena[1][1]==arena[1][2])))
        {
            win_line[0]='r';
            win_line[1]='2';
        }
        else if(((arena[2][0]==placeholder)&&(arena[2][0]==arena[2][1])&&(arena[2][1]==arena[2][2])))
        {
            win_line[0]='r';
            win_line[1]='3';
        } 
        return true;
    }
    //check vertical
    else if (((arena[0][0]==placeholder)&&(arena[0][0]==arena[1][0])&&(arena[1][0]==arena[2][0]))||((arena[0][1]==placeholder)&&(arena[0][1]==arena[1][1])&&(arena[1][1]==arena[2][1]))||((arena[0][2]==placeholder)&&(arena[0][2]==arena[1][2])&&(arena[1][2]==arena[2][2])))
    {
        if(((arena[0][0]==placeholder)&&(arena[0][0]==arena[1][0])&&(arena[1][0]==arena[2][0])))
        {
            win_line[0]='c';
            win_line[1]='1';
        }
        else if(((arena[0][1]==placeholder)&&(arena[0][1]==arena[1][1])&&(arena[1][1]==arena[2][1])))
        {
            win_line[0]='c';
            win_line[1]='2';
        }
        else if(((arena[0][2]==placeholder)&&(arena[0][2]==arena[1][2])&&(arena[1][2]==arena[2][2])))
        {
            win_line[0]='c';
            win_line[1]='3';
        }
        printf("\nplayer %c won the game\n",placeholder);
        return true;
    }
    //check diagonal
    else if(((arena[0][0]==placeholder)&&(arena[0][0]==arena[1][1])&&(arena[1][1]==arena[2][2]))||((arena[0][2]==placeholder)&&(arena[0][2]==arena[1][1])&&(arena[1][1]==arena[2][0])))
    {
        if(((arena[0][0]==placeholder)&&(arena[0][0]==arena[1][1])&&(arena[1][1]==arena[2][2])))
        {
            win_line[0]='d';
            win_line[1]='1';
        }
        else if(((arena[0][2]==placeholder)&&(arena[0][2]==arena[1][1])&&(arena[1][1]==arena[2][0])))
        {
            win_line[0]='d';
            win_line[1]='2';
        }
        printf("\nplayer %c won the game\n",placeholder);
        return true;
    }

    return false;
}

void playerO(char arena[][3])
{
    
    Texture2D O = LoadTexture("O.png");
        Rectangle r11 = {(GetScreenWidth()/2)-(O.width/2)-139,(GetScreenHeight()/2)-(O.height/2)-142,O.width,O.height};
        Rectangle r12 = {(GetScreenWidth()/2)-(O.width/2)+4,(GetScreenHeight()/2)-(O.height/2)-142,O.width,O.height};
        Rectangle r13 = {(GetScreenWidth()/2)-(O.width/2)+142,(GetScreenHeight()/2)-(O.height/2)-142,O.width,O.height};
        Rectangle r21 = {(GetScreenWidth()/2)-(O.width/2)-139,(GetScreenHeight()/2)-(O.height/2)+3,O.width,O.height};
        Rectangle r22 = {(GetScreenWidth()/2)-(O.width/2)+4,(GetScreenHeight()/2)-(O.height/2)+3,O.width,O.height};
        Rectangle r23 = {(GetScreenWidth()/2)-(O.width/2)+142,(GetScreenHeight()/2)-(O.height/2)+3,O.width,O.height};
        Rectangle r31 = {(GetScreenWidth()/2)-(O.width/2)-139,(GetScreenHeight()/2)-(O.height/2)+142,O.width,O.height};
        Rectangle r32 = {(GetScreenWidth()/2)-(O.width/2)+4,(GetScreenHeight()/2)-(O.height/2)+142,O.width,O.height};
        Rectangle r33 = {(GetScreenWidth()/2)-(O.width/2)+142,(GetScreenHeight()/2)-(O.height/2)+142,O.width,O.height};
        if(!IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            return;
        }

            if(CheckCollisionPointRec(GetMousePosition(),r11))
            {
                //for 1,1
                if(arena[0][0] != ' ')
                {
                    //play error sound here
                    return;
                }
                else
                {
                    arena[0][0] = 'o';
                    collison_f = true;
                    empty_count++;
                }
            }
            else if(CheckCollisionPointRec(GetMousePosition(),r12))
            {
                //for 1,2
                if(arena[0][1] != ' ')
                {
                    //play error sound here
                    return;
                }
                else
                {
                    arena[0][1] = 'o';
                    empty_count++;
                    collison_f = true;
                }
            }
            else if(CheckCollisionPointRec(GetMousePosition(),r13))
            {
                //for 1,3
                if(arena[0][2] != ' ')
                {
                    //play error sound here
                    return;
                }
                else
                {
                    arena[0][2] = 'o';
                    empty_count++;
                    collison_f = true;
                }
            }
            else if(CheckCollisionPointRec(GetMousePosition(),r21))
            {
                //for 2,1
                if(arena[1][0] != ' ')
                {
                    //play error sound here
                    return;
                }
                else
                {
                    arena[1][0] = 'o';
                    empty_count++;
                    collison_f = true;
                }
            }
            else if(CheckCollisionPointRec(GetMousePosition(),r22))
            {
                //for 2,2
                if(arena[1][1] != ' ')
                {
                    //play error sound here
                    return;
                }
                else
                {
                    arena[1][1] = 'o';
                    empty_count++;
                    collison_f = true;
                }
            }
            else if(CheckCollisionPointRec(GetMousePosition(),r23))
            {
                //for 2,3
                if(arena[1][2] != ' ')
                {
                    //play error sound here
                    return;
                }
                else
                {
                    arena[1][2] = 'o';
                    empty_count++;
                    collison_f = true;
                }
            }
            else if(CheckCollisionPointRec(GetMousePosition(),r31))
            {
                //for 3,1
                if(arena[2][0] != ' ')
                {
                    //play error sound here
                    return;
                }
                else
                {
                    arena[2][0] = 'o';
                    empty_count++;
                    collison_f = true;
                }
            }
            else if(CheckCollisionPointRec(GetMousePosition(),r32))
            {
                //for 3,2
                if(arena[2][1] != ' ')
                {
                    //play error sound here
                    return;
                }
                else
                {
                    arena[2][1] = 'o';
                    empty_count++;
                    collison_f = true;
                }
            }
            else if(CheckCollisionPointRec(GetMousePosition(),r33))
            {
                //for 3,3
                if(arena[2][2] != ' ')
                {
                    //play error sound here
                    return;
                }
                else
                {
                    arena[2][2] = 'o';
                    empty_count++;
                    collison_f = true;
                }
            }

            
        if(winning_conditions_g(arena,'o'))
        {
            win = true;
            return;
        }
        if(empty_count == 9)
        {
            draw = true;
        }
        O_lock = false;
        X_lock = true;
}


void playerX(char arena[][3])
{
    
    Texture2D X = LoadTexture("X.png");
        Rectangle r11 = {(GetScreenWidth()/2)-(X.width/2)-139,(GetScreenHeight()/2)-(X.height/2)-142,X.width,X.height};
        Rectangle r12 = {(GetScreenWidth()/2)-(X.width/2)+4,(GetScreenHeight()/2)-(X.height/2)-142,X.width,X.height};
        Rectangle r13 = {(GetScreenWidth()/2)-(X.width/2)+142,(GetScreenHeight()/2)-(X.height/2)-142,X.width,X.height};
        Rectangle r21 = {(GetScreenWidth()/2)-(X.width/2)-139,(GetScreenHeight()/2)-(X.height/2)+3,X.width,X.height};
        Rectangle r22 = {(GetScreenWidth()/2)-(X.width/2)+4,(GetScreenHeight()/2)-(X.height/2)+3,X.width,X.height};
        Rectangle r23 = {(GetScreenWidth()/2)-(X.width/2)+142,(GetScreenHeight()/2)-(X.height/2)+3,X.width,X.height};
        Rectangle r31 = {(GetScreenWidth()/2)-(X.width/2)-139,(GetScreenHeight()/2)-(X.height/2)+142,X.width,X.height};
        Rectangle r32 = {(GetScreenWidth()/2)-(X.width/2)+4,(GetScreenHeight()/2)-(X.height/2)+142,X.width,X.height};
        Rectangle r33 = {(GetScreenWidth()/2)-(X.width/2)+142,(GetScreenHeight()/2)-(X.height/2)+142,X.width,X.height};
        if(!IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            return;
        }

            if(CheckCollisionPointRec(GetMousePosition(),r11))
            {
                //for 1,1
                if(arena[0][0] != ' ')
                {
                    //play error sound here
                    return;
                }
                else
                {
                    arena[0][0] = 'x';
                    empty_count++;
                    collison_f = true;
                }
                
            }
            else if(CheckCollisionPointRec(GetMousePosition(),r12))
            {
                //for 1,2
                if(arena[0][1] != ' ')
                {
                    //play error sound here
                    return;
                }
                else
                {
                    arena[0][1] = 'x';
                    empty_count++;
                    collison_f = true;
                }
            }
            else if(CheckCollisionPointRec(GetMousePosition(),r13))
            {
                //for 1,3
                if(arena[0][2] != ' ')
                {
                    //play error sound here
                    return;
                }
                else
                {
                    arena[0][2] = 'x';
                    empty_count++;
                    collison_f = true;
                }
            }
            else if(CheckCollisionPointRec(GetMousePosition(),r21))
            {
                //for 2,1
                if(arena[1][0] != ' ')
                {
                    //play error sound here
                    return;
                }
                else
                {
                    arena[1][0] = 'x';
                    empty_count++;
                    collison_f = true;
                }
            }
            else if(CheckCollisionPointRec(GetMousePosition(),r22))
            {
                //for 2,2
                if(arena[1][1] != ' ')
                {
                    //play error sound here
                    return;
                }
                else
                {
                    arena[1][1] = 'x';
                    empty_count++;
                    collison_f = true;
                }
            }
            else if(CheckCollisionPointRec(GetMousePosition(),r23))
            {
                //for 2,3
                if(arena[1][2] != ' ')
                {
                    //play error sound here
                    return;
                }
                else
                {
                    arena[1][2] = 'x';
                    empty_count++;
                    collison_f = true;
                }
            }
            else if(CheckCollisionPointRec(GetMousePosition(),r31))
            {
                //for 3,1
                if(arena[2][0] != ' ')
                {
                    //play error sound here
                    return;
                }
                else
                {
                    arena[2][0] = 'x';
                    empty_count++;
                    collison_f = true;
                }
            }
            else if(CheckCollisionPointRec(GetMousePosition(),r32))
            {
                //for 3,2
                if(arena[2][1] != ' ')
                {
                    //play error sound here
                    return;
                }
                else
                {
                    arena[2][1] = 'x';
                    empty_count++;
                    collison_f = true;
                }
            }
            else if(CheckCollisionPointRec(GetMousePosition(),r33))
            {
                //for 3,3
                if(arena[2][2] != ' ')
                {
                    //play error sound here
                    return;
                }
                else
                {
                    arena[2][2] = 'x';
                    empty_count++;
                    collison_f = true;
                }
            }
        
        
        if(winning_conditions_g(arena,'x'))
        {
            win = true;
            return;
        }
        if(empty_count == 9)
        {
            draw = true;
        }
        X_lock = false;
        O_lock = true;
}

void gmark(int i, int j , char placeholder)
{
    if(placeholder == 'x')
    {
        /*
        Rectangle r11 = {(GetScreenWidth()/2)-(X.width/2)-139,(GetScreenHeight()/2)-(X.height/2)-142,X.width,X.height};
        Rectangle r12 = {(GetScreenWidth()/2)-(X.width/2)+4,(GetScreenHeight()/2)-(X.height/2)-142,X.width,X.height};
        Rectangle r13 = {(GetScreenWidth()/2)-(X.width/2)+142,(GetScreenHeight()/2)-(X.height/2)-142,X.width,X.height};
        Rectangle r21 = {(GetScreenWidth()/2)-(X.width/2)-139,(GetScreenHeight()/2)-(X.height/2)+3,X.width,X.height};
        Rectangle r22 = {(GetScreenWidth()/2)-(X.width/2)+4,(GetScreenHeight()/2)-(X.height/2)+3,X.width,X.height};
        Rectangle r23 = {(GetScreenWidth()/2)-(X.width/2)+142,(GetScreenHeight()/2)-(X.height/2)+3,X.width,X.height};
        Rectangle r31 = {(GetScreenWidth()/2)-(X.width/2)-139,(GetScreenHeight()/2)-(X.height/2)+142,X.width,X.height};
        Rectangle r32 = {(GetScreenWidth()/2)-(X.width/2)+4,(GetScreenHeight()/2)-(X.height/2)+142,X.width,X.height};
        Rectangle r33 = {(GetScreenWidth()/2)-(X.width/2)+142,(GetScreenHeight()/2)-(X.height/2)+142,X.width,X.height};
        */
        Texture2D X = LoadTexture("X.png");
        Rectangle r11 = {(GetScreenWidth()/2)-(X.width/2)-139,(GetScreenHeight()/2)-(X.height/2)-142,X.width,X.height};
        if((i==0)&&(j==0))
        {
            DrawTexture(X,(GetScreenWidth()/2)-(X.width/2)-139,(GetScreenHeight()/2)-(X.height/2)-142,WHITE);
        }
        else if((i==0)&&(j==1))
        {
            DrawTexture(X,(GetScreenWidth()/2)-(X.width/2)+4,(GetScreenHeight()/2)-(X.height/2)-142,WHITE);
        }
        else if((i==0)&&(j==2))
        {
            DrawTexture(X,(GetScreenWidth()/2)-(X.width/2)+142,(GetScreenHeight()/2)-(X.height/2)-142,WHITE);
        }
        else if((i==1)&&(j==0))
        {
            DrawTexture(X,(GetScreenWidth()/2)-(X.width/2)-139,(GetScreenHeight()/2)-(X.height/2)+3,WHITE);
        }
        else if((i==1)&&(j==1))
        {
            DrawTexture(X,(GetScreenWidth()/2)-(X.width/2)+4,(GetScreenHeight()/2)-(X.height/2)+3,WHITE);
        }
        else if((i==1)&&(j==2))
        {
            DrawTexture(X,(GetScreenWidth()/2)-(X.width/2)+142,(GetScreenHeight()/2)-(X.height/2)+3,WHITE);
        }
        else if((i==2)&&(j==0))
        {
            DrawTexture(X,(GetScreenWidth()/2)-(X.width/2)-139,(GetScreenHeight()/2)-(X.height/2)+142,WHITE);
        }
        else if((i==2)&&(j==1))
        {
            DrawTexture(X,(GetScreenWidth()/2)-(X.width/2)+4,(GetScreenHeight()/2)-(X.height/2)+142,WHITE);
        }
        else if((i==2)&&(j==2))
        {
            DrawTexture(X,(GetScreenWidth()/2)-(X.width/2)+142,(GetScreenHeight()/2)-(X.height/2)+142,WHITE);
        }
    }
    else
    {
        Texture2D O = LoadTexture("O.png");
        Rectangle r11 = {(GetScreenWidth()/2)-(O.width/2)-139,(GetScreenHeight()/2)-(O.height/2)-142,O.width,O.height};
        if((i==0)&&(j==0))
        {
            DrawTexture(O,(GetScreenWidth()/2)-(O.width/2)-139,(GetScreenHeight()/2)-(O.height/2)-142,WHITE);
        }
        else if((i==0)&&(j==1))
        {
            DrawTexture(O,(GetScreenWidth()/2)-(O.width/2)+4,(GetScreenHeight()/2)-(O.height/2)-142,WHITE);
        }
        else if((i==0)&&(j==2))
        {
            DrawTexture(O,(GetScreenWidth()/2)-(O.width/2)+142,(GetScreenHeight()/2)-(O.height/2)-142,WHITE);
        }
        else if((i==1)&&(j==0))
        {
            DrawTexture(O,(GetScreenWidth()/2)-(O.width/2)-139,(GetScreenHeight()/2)-(O.height/2)+3,WHITE);
        }
        else if((i==1)&&(j==1))
        {
            DrawTexture(O,(GetScreenWidth()/2)-(O.width/2)+4,(GetScreenHeight()/2)-(O.height/2)+3,WHITE);
        }
        else if((i==1)&&(j==2))
        {
            DrawTexture(O,(GetScreenWidth()/2)-(O.width/2)+142,(GetScreenHeight()/2)-(O.height/2)+3,WHITE);
        }
        else if((i==2)&&(j==0))
        {
            DrawTexture(O,(GetScreenWidth()/2)-(O.width/2)-139,(GetScreenHeight()/2)-(O.height/2)+142,WHITE);
        }
        else if((i==2)&&(j==1))
        {
            DrawTexture(O,(GetScreenWidth()/2)-(O.width/2)+4,(GetScreenHeight()/2)-(O.height/2)+142,WHITE);
        }
        else if((i==2)&&(j==2))
        {
            DrawTexture(O,(GetScreenWidth()/2)-(O.width/2)+142,(GetScreenHeight()/2)-(O.height/2)+142,WHITE);
        }

    }
    
}

void checker(char arena [][3])
{
    //tester 
    //to check if the arena is getting into the checker in the correct way or not
    if(0)
    {
        static bool k = 0;
        if(k == 1)
        {
            return;
        }
        for(int i = 0 ; i < 3; i++)
        {
            for(int j = 0 ; j < 3 ; j++)
            {
                if(arena[i][j] == ' ')
                {
                    printf("s ");
                }
            }
            printf("\n");
        }
        k = 1;
    }
    
    for(int i = 0 ; i < 3; i++)
    {
        for(int j = 0 ; j < 3 ; j++)
        {
            if(arena[i][j] == 'x')
            {
                gmark(i,j,'x');
            }
            else if(arena[i][j] == 'o')
            {
                gmark(i,j,'o');
            }
            else 
            {
                continue;
            }
        }
    }
   
}

void xo_grid(char arena [][3])
{
        //spacing from center of the window 
        float grid_spacing_from_center = 70;
        
        //vertical line dimentions
        float ver_w = 5;
        float ver_h = 400;
        
        //horizontal line dimentions
        float ho_w = 400;
        float ho_h = 5;
        
        ClearBackground(WHITE);
        DrawRectangle((GetScreenWidth()/2)-grid_spacing_from_center,(GetScreenHeight()/2)-(ver_h/2),ver_w,ver_h,BLUE);
        DrawRectangle((GetScreenWidth()/2)+grid_spacing_from_center,(GetScreenHeight()/2)-(ver_h/2),ver_w,ver_h,BLUE);
        DrawRectangle((GetScreenWidth()/2)-(ho_w/2),(GetScreenHeight()/2)+grid_spacing_from_center,ho_w,ho_h,BLUE);
        DrawRectangle((GetScreenWidth()/2)-(ho_w/2),(GetScreenHeight()/2)-grid_spacing_from_center,ho_w,ho_h,BLUE);
        
        checker(arena);
        
        Texture2D X = LoadTexture("X.png");
        //tester
        if(0)
        {
            //for 1,2
            DrawTexture(X,(GetScreenWidth()/2)-(X.width/2)+4,(GetScreenHeight()/2)-(X.height/2)-142,WHITE);
            //for 1,3
            DrawTexture(X,(GetScreenWidth()/2)-(X.width/2)+142,(GetScreenHeight()/2)-(X.height/2)-142,WHITE);
            //for 2,1
            DrawTexture(X,(GetScreenWidth()/2)-(X.width/2)-139,(GetScreenHeight()/2)-(X.height/2)+3,WHITE);
            //for 2,2
            DrawTexture(X,(GetScreenWidth()/2)-(X.width/2)+4,(GetScreenHeight()/2)-(X.height/2)+3,WHITE);
            //for 2,3
            DrawTexture(X,(GetScreenWidth()/2)-(X.width/2)+142,(GetScreenHeight()/2)-(X.height/2)+3,WHITE);
            //for 3,1
            DrawTexture(X,(GetScreenWidth()/2)-(X.width/2)-139,(GetScreenHeight()/2)-(X.height/2)+142,WHITE);
            //for 3,2
            DrawTexture(X,(GetScreenWidth()/2)-(X.width/2)+4,(GetScreenHeight()/2)-(X.height/2)+142,WHITE);
            //for 3,3
            DrawTexture(X,(GetScreenWidth()/2)-(X.width/2)+142,(GetScreenHeight()/2)-(X.height/2)+142,WHITE); 
        }
       
}

void start_button()
{
    //text position
    int start_text_x = (GetScreenWidth()/2)-50;
    int start_text_y = (GetScreenHeight()/2)-15;
    
    
    
    Texture2D play_button = LoadTexture("start.png");
    DrawTexture(play_button,(GetScreenWidth()/2)-(play_button.width/2),(GetScreenHeight()/2)-(play_button.height/2),WHITE);
    
    //collison rectangle dimentions
    int width_of_rectangle = 150;
    int height_of_rectangle = 145;
    
    
    Rectangle start_button = {(GetScreenWidth()/2)-84,(GetScreenHeight()/2)-85,width_of_rectangle,height_of_rectangle};
    if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
            if(CheckCollisionPointRec(GetMousePosition(),start_button))
            {
                click_start = true;
                Sound start_button_click = LoadSound("audio/start_click.mp3");
                PlaySound(start_button_click);
            }
    }
    
}

int main()
{   
    //graphical game 
    if(1)
    {
        win = false;
        draw = false;
        empty_count = 0;
        time_t seconds;
        srand(time(0));
        int random_number = rand() % 2;
        float handy = 0;
        char turn;
        
        if(random_number == 0)
        {
            turn = 'o';
            O_lock = true;
            X_lock = false;
        }
        else 
        {
            turn = 'x';
            X_lock = true;
            O_lock = false;
        }
                
        printf("%d is the random number",random_number);
        
        //checker to check if random number is getting generated or not 
        if(0)
        {
            return 0;
        }
        
        char arena[3][3];

        for(int i = 0 ; i < 3 ; i ++)
        {
            for(int j = 0 ; j < 3 ; j++)
            {
                arena[i][j] = ' ';
            }
        }
        
        int width_of_window = 800;
        int height_of_window = 500;
        SetTargetFPS(143);
        
       // InitAudioDevice();
        InitWindow(width_of_window,height_of_window,"XO game");
        Music music_bg = LoadMusicStream("audio/bg.mp3");
        
            while(!WindowShouldClose())
            {
                //UpdateMusicStream(music_bg);
                BeginDrawing();
                    ClearBackground(WHITE);
                    if(click_start == true)
                    {
                        //PlayMusicStream(music_bg);
                        if(win == true)
                        {
                            static int i = 0;
                            if (i == 0)
                            {
                                Sound winn = LoadSound("audio/win_sound.mp3");
                                PlaySound(winn);
                                i++;
                            }
                            
                            if(turn == 'x')
                            {
                                draw_kitten('x');
                            }
                            else if(turn == 'o')
                            {
                                draw_kitten('o');
                            }
                            //DrawRectangle(GetScreenWidth()/2,GetScreenHeight()/2,100,20,RED);
                            xo_grid(arena);
                            Texture2D line = LoadTexture(win_line);
                            DrawTexture(line,(GetScreenWidth()/2-line.width/2)+2,(GetScreenHeight()/2-line.height/2),WHITE);
                            DrawCircle(GetScreenWidth()-40,GetScreenHeight()-40,30,LIGHTGRAY);
                            Texture2D resetg = LoadTexture("refresh.png");
                            DrawTexture(resetg,GetScreenWidth()-61,GetScreenHeight()-61,WHITE);
                            if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
                            {
                                if(CheckCollisionPointCircle(GetMousePosition(),(Vector2){GetScreenWidth()-40,GetScreenHeight()-40},30))
                                {
                                    i = 0;
                                    
                                    reset(arena,&random_number,&handy,&turn);
                                    collison_f = false;
                                    draw_kitten(turn);
                                    EndDrawing();
                                    continue;
                                }
                            }
                            EndDrawing();
                            continue;
                        }
                        if(draw == true)
                        {
                            static int i = 0;
                            if (i == 0)
                            {
                                Sound draww = LoadSound("audio/draw_sound.mp3");
                                PlaySound(draww);
                                i++;
                            }
                            ClearBackground(WHITE);
                            Texture2D o_x = LoadTexture("o_x.png");
                            DrawTexture(o_x,(GetScreenWidth()/2-o_x.width/2),(GetScreenHeight()/2-o_x.height/2),WHITE);
                            Texture2D hands = LoadTexture("handshake.png");
                            DrawTexture(hands,(GetScreenWidth()/2-hands.width/2),(GetScreenHeight()/2-hands.height/2)+handy,WHITE);
                            if(handy >= 50)
                            {
                                //DrawTexture(o_x,(GetScreenWidth()/2-o_x.width/2),(GetScreenHeight()/2-o_x.height/2),WHITE);
                            }
                            if(handy>= 123)
                            {
                                Texture2D draw = LoadTexture("draww.png");
                                DrawTexture(draw,(GetScreenWidth()/2-draw.width/2),(GetScreenHeight()/2-draw.height/2),WHITE);
                                DrawCircle(GetScreenWidth()-40,GetScreenHeight()-40,30,LIGHTGRAY);
                                Texture2D resetg = LoadTexture("refresh.png");
                                DrawTexture(resetg,GetScreenWidth()-61,GetScreenHeight()-61,WHITE);
                                if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
                                {
                                    if(CheckCollisionPointCircle(GetMousePosition(),(Vector2){GetScreenWidth()-40,GetScreenHeight()-40},30))
                                    {
                                        i = 0;
                                        handy = 0;
                                        reset(arena,&random_number,&handy,&turn);
                                        draw_kitten(turn);
                                        EndDrawing();
                                        continue;
                                    }
                                }
                            }
                            else 
                            {
                                handy += 100*GetFrameTime();
                            }
                            EndDrawing();
                            continue;
                        }
                        draw_kitten(turn);
                        xo_grid(arena);
                        DrawCircle(GetScreenWidth()-40,GetScreenHeight()-40,30,LIGHTGRAY);
                            Texture2D resetg = LoadTexture("refresh.png");
                            DrawTexture(resetg,GetScreenWidth()-61,GetScreenHeight()-61,WHITE);
                            
                        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
                        {
                            
                            if(CheckCollisionPointCircle(GetMousePosition(),(Vector2){GetScreenWidth()-40,GetScreenHeight()-40},30))
                            {   
                                reset(arena,&random_number,&handy,&turn);
                                draw_kitten(turn);
                                EndDrawing();
                                continue;
                            }
                            if((O_lock == true)&&(X_lock == false))
                            {  
                                playerO(arena);
                                Sound marking = LoadSound("audio/mark.mp3");
                                PlaySound(marking);
                                if(collison_f == false)
                                {
                                    if((O_lock == false)&&(X_lock == true))
                                    {
                                        turn = 'o';
                                        O_lock = true;
                                        X_lock = false;
                                        collison_f = false;
                                    }
                                }
                                else
                                {
                                    if((O_lock == false)&&(X_lock == true))
                                    {
                                        turn = 'x';
                                        collison_f = false;
                                    }
                                }
                                
                                EndDrawing();
                                continue;
                            }
                            if((O_lock == false)&&(X_lock == true))
                            {
                                
                                playerX(arena);
                                Sound marking = LoadSound("audio/mark.mp3");
                                PlaySound(marking);
                                if(collison_f == false)
                                {
                                    if((O_lock == true)&&(X_lock == false))
                                    {
                                        turn = 'x';
                                        O_lock = false;
                                        X_lock = true;
                                        collison_f = false;
                                    }
                                }
                                else
                                {
                                    if((O_lock == true)&&(X_lock == false))
                                    {
                                        turn = 'o';
                                        collison_f = false;
                                    }
                                }
                                EndDrawing();
                                continue;
                            }
                        }
    
                    }
                    else 
                    {
                        start_button();
                    }
                EndDrawing(); 
            }
        //CloseAudioDevice();
        CloseWindow();
    }
   
}