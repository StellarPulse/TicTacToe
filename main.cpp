#include <iostream>

using namespace std;


char matrix[3][3]; /* the tic tac toe matrix */
char check();
void init_matrix();
void get_player_move();
void bestMove();
void disp_matrix();
void rule();
int minimax( int depth , bool isMaximizer);
/* Checks for the winner for future turns
return +10 if the computer 
return -10 if the player wins 
returns 1 if there is a tie 
returns 0 if there are more spaces avaiable and no one wins*/
int checkWinner()
{
    int i , openSpot;
    char chTest = ' ';
    do
    {
        for(i=0; i<3; i++) /* check rows */
        if(matrix[i][0]==matrix[i][1] &&
        matrix[i][0]==matrix[i][2] && matrix[i][0]!=' ')
        {chTest = matrix[i][0];
        break;
        }
        for(i=0; i<3; i++) /* check columns */
        if(matrix[0][i]==matrix[1][i] && matrix[0][i]==matrix[2][i] && matrix[0][i]!=' ')
        {chTest = matrix[0][i];
        break;}
        /* test diagonals */
        if(matrix[0][0]==matrix[1][1] &&
        matrix[1][1]==matrix[2][2] && matrix[0][0]!=' ')
        {chTest = matrix[0][0];
        break;}
        if(matrix[0][2]==matrix[1][1] &&
        matrix[1][1]==matrix[2][0] && matrix[0][2]!=' ')
        {chTest =  matrix[0][2];
        break;}
        }while(false);
        for (int i = 0 ; i<3 ; i++){
            for(int j = 0 ; j<3 ; j++){
                if(matrix[i][j] == ' ')
                    openSpot++;
            }
        }

         if (chTest == ' ' && openSpot == 0) {
            return 1;
            }
        if(chTest == 'X')
            return -10;
        if(chTest == 'O')
            return 10;

        return 0;
}

int main()
{
    char move = ' ' , done = ' ';
    cout << "Hello I am TIC TACK TOE !!!!" << endl;
    cout << "Try to beat me" << endl;
    init_matrix();
    rule();
    do
    {
        disp_matrix();
        get_player_move();
        done = check();
        if (done!=' ')
        {
            cout << "\n\t!!!!!!!!!!!!!!!!!!!!!!! Conratulations you won!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! :)\n" << endl;
            break;

        }
        bestMove();
        done = check();
        if (done!=' ')
        {
            cout << "\n\t!!!!!!!!!!!!!!!!!!!You lost to me , Better luck next time :(!!!!!!!!!!!!!!!!!!!!!!!!!! \n" << endl;
            break;
        }
    }while(done == ' ');
        disp_matrix();
        return 0;
}

// initialises the matrix 
void init_matrix()
{
    int i, j;
    for(i=0; i<3; i++)
    for(j=0; j<3; j++) matrix[i][j] = ' ';
}

//Display the matrix on the screen whenever required 
void disp_matrix()
{
    for (int i = 0 ; i<3 ; i++)
    {
        printf(" %c | %c | %c ", matrix[i][0] , matrix[i][1] , matrix[i][2] ) ;
        if ( i!=2 )
        printf("\n---|---|---\n");

    }
}

// Display the rule or raher the instrutions of the game 
void rule()
{
    cout << "You are cross and the computer is naughts. \nYou have to enter the co-ordinates of the shell each time.\nFor example co-ordinates 2  3  means second row and third coloumn.\n";
}

void get_player_move()
{
    int x , y ;
    cout << "\nIt's your turn , enter the co-ordinates of the cell :" ;
    cin >> x >> y;
    x-- ; y-- ;
    if (x>2 || x<0 || y>2 || y<0 || matrix[x][y]!= ' ')
    {
        cout << "\nWrong turn please enter again" << endl;
        get_player_move();
    }
    else
    {
                matrix[x][y] = 'X' ;
    }
}

// Check for the winner 
char check(void)
{
int i ;
for(i=0; i<3; i++) /* check rows */
if(matrix[i][0]==matrix[i][1] &&
matrix[i][0]==matrix[i][2] && matrix[i][0]!=' ') return matrix[i][0];
for(i=0; i<3; i++) /* check columns */
if(matrix[0][i]==matrix[1][i] && matrix[0][i]==matrix[2][i] && matrix[0][i]!=' ') return matrix[0][i];
/* test diagonals */
if(matrix[0][0]==matrix[1][1] &&
matrix[1][1]==matrix[2][2] && matrix[0][0]!=' ')
return matrix[0][0];
if(matrix[0][2]==matrix[1][1] &&
matrix[1][1]==matrix[2][0] && matrix[0][2]!=' ')
return matrix[0][2];
return ' ';
}

//finds the best move for the computer oe better say  it implements the AI system  in the programme 
void bestMove()
{
    int bestScore = -100000 ;
    int bestMoveRow , bestMovecolumn ;
    for ( int i = 0 ; i<3 ; i++ )
    {
        for( int j = 0 ; j<3 ; j++)
        {
            if (matrix[i][j] == ' ')
            {
                matrix[i][j] = 'O';
                int score = minimax( 0 , false );
                matrix[i][j] = ' ';
                if (score > bestScore)
                {
                    bestScore = score ;
                    bestMoveRow = i ;
                    bestMovecolumn = j ;
                }
            }

        }
    }
    matrix[bestMoveRow][bestMovecolumn] = 'O';
}

// Implements the algorithm
int minimax(int depth , bool isMaximizer)
{
    int bestMoveRow , bestMovecolumn ;
    int result = checkWinner();
    if (result!=0)
    {
        return result ;
    }
    //For computer's turn
    if (isMaximizer)
    {
        int bestScore = -10000;
         for ( int i = 0 ; i<3 ; i++ )
         {
                for( int j = 0 ; j<3 ; j++)
                {
                        if (matrix[i][j] == ' ')
                        {
                             matrix[i][j] = 'O' ;
                             int score = minimax( depth+1 , false );
                             matrix[i][j] = ' ';
                             if (score > bestScore)
                            {
                                bestScore = score ;
                                bestMoveRow = i ;
                                bestMovecolumn = j ;
                            }
                        }

                }
        }
        return bestScore;
    }
    //for Humans turn
        if (isMaximizer)
    {
        int bestScore = 10000;
         for ( int i = 0 ; i<3 ; i++ )
         {
                for( int j = 0 ; j<3 ; j++)
                {
                        if (matrix[i][j] == ' ')
                        {
                             matrix[i][j] = 'X' ;
                             int score = minimax( depth+1 , true );
                             matrix[i][j] = ' ';
                             if (score < bestScore)
                            {
                                bestScore = score ;
                                bestMoveRow = i ;
                                bestMovecolumn = j ;
                            }
                        }

                }
        }
        return bestScore;
    }
}
