#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
#define MINE 2
#define SIDE 5
                                                          //.\a.exe
using std::cout;
using std::vector;

//structure for board
struct board                                  //i->   j^
{
    char boards[SIDE][SIDE];
    board ()
    {
        for(int i = 0; i <= SIDE; i++)
            for(int j = 0; j <= SIDE; j++)
            {
                boards[i][j] = '-';
                if(i > SIDE - 2)
                    boards[i][j] = '.';
                if(j > SIDE - 2)
                    boards[i][j] = '|';
            }
        
    }
};

//declarations
void play(board *my, board *real);
bool checker(int x,int y,board *my);
void decision(bool check,board *my,board *real, int x, int y);
void util(board *my,board *real, int x, int y);
char* neighbours(int i,int j, board *theboard);
void display(board *b);
char* neighbours(int i,int j, board *theboard);
void addnums(board *real,int mines[][2]);
vector<vector<int>> revealmarked(board *real,board *my);


void display(board *b)
{
    int n = 1;
    for(int i = -1; i < SIDE; i++)
    {
            for(int j = -1; j < SIDE; j++)
            {
                if(j == -1)
                {
                    if(i == -1)
                        cout<< "  ";
                    else
                        cout <<i<< " " ;   
                    
                }
            
                else if(i == -1)
                {
                    if(j == -1)
                        cout<< " ";
                    else
                        cout <<j<< " " ;          
                }
                else
                    cout<<b->boards[i][j] << " " ;
            }
            cout << std::endl;
    }
}

void place_mines(board *real)
{
    //mine = 2
    srand(time(0));
    board realboard = *real;
     srand((unsigned int)time(NULL));
    //mines placed list
    int mine[MINE][2];
    for(int i = 0; i < MINE; i++)
    {
       
        int random  = rand() % ((SIDE - 1) * (SIDE - 1));
        //cout<< i<<random<< std::endl;
        int x = random % (SIDE - 1);
        int y = random / (SIDE - 1);
        if(x > 0 && y > 0)
            if(realboard.boards[x][y] == '-')
            {
                realboard.boards[x][y] = '*';
                mine[i][0] = x;
                mine[i][1] = y;
                
            }
            else
                i--;
        else
            i--;

        //cout<< realboard.boards[x][y]<< " "<< x<< y<<std::endl;
    }

    *real = realboard;
    addnums(real, mine);
    //display(real); 
}

int main()
{
    cout << "hello world"<<std::endl;
    board realboard;
    board myboard;
    board *real = &realboard;
    board *my = &myboard;
    place_mines(real);
    //display(real);
    cout<<"lets playy!"<<std::endl;
    display(my);     // -------------------------temp
    play(my, real);
    //cout<< realboard.boards[1][2];
    
}

void play(board *my, board *real)
{
    //input

    board myboard = *my;

    cout<<"pick one:"<<std::endl<<"1. mark"<<std::endl<<"2. tip"<<std::endl;

    int n;
    std::cin >> n;
    
    cout<< "enter your coordinates: "<<std::endl;
    int x, y;
    std::cin >> x>>y;


    switch(n)
    {
        case 1:

            myboard.boards[x][y] ='M';
            *my = myboard; 
            display(my);
            play(my, real);
            break;
        case 2:
            
            //cout<< real->boards[x][y];
            //returning the board to pointer for next operations;
            *my = myboard;   
            display(my);
            bool check = checker(x,y, real);     //0 or 1
            decision(check, my, real, x, y);
    }
    
    

}

bool checker(int x,int y,board *my) 
{
    //------------!!!!real boared used!!!!!!!!-------
    board myboard = *my;
    if(myboard.boards[x][y] == '*')
        return false;
    
    return true;
}

void decision(bool check,board *my,board *real, int x, int y)
{
        if(check)
        {
            util(my, real, x, y);    
            play(my, real);                            
        }
        else
        {
            vector<vector<int>> marks = revealmarked(real, my);
            
            for(vector<int> i : marks)
                for (int j : i)
                    cout<< j<<" ";
                cout<< std::endl;
            display(my);
            //display(real);
            cout<< "you loose gooes";
            exit(0);
        }
}

void util(board *my,board *real, int x, int y)
{
    board myboard = *my;
    board realboard = *real;

    myboard.boards[x][y] = realboard.boards[x][y];
    //display(real);

    //reveal the nodes
    int i, j, flag = 0;
    i = x;
    j = y;
    //bottom right
    while(flag == 0)
    {   
            //char* neigbour = neighbours(i, j, real);
                if(realboard.boards[i][j] != '*' && realboard.boards[i][j] != '.' && realboard.boards[i][j] != '|')
                    myboard.boards[i][j] = realboard.boards[i][j];
                else
                    flag = 1;
                i++;
                j++;
                if(i > 4 && flag == 0 && j > 4 )
                    break;
                
           //cout<<i<<j<<realboard.boards[i][j]<<std::endl;
                
    }

    //right
    i = x;
    j = y;
    flag = 0;
    while(flag == 0)
    {   
            //char* neigbour = neighbours(i, j, real);
                if(realboard.boards[i][j] != '*' && realboard.boards[i][j] != '.' && realboard.boards[i][j] != '|')
                    myboard.boards[i][j] = realboard.boards[i][j];
                else
                    flag = 1;
                                
                if(j > 4)
                    break;
                j++;          
    }

    //bottom
    i = x;
    j = y;
    flag = 0;
    while(flag == 0)
    {   
            //char* neigbour = neighbours(i, j, real);
                if(realboard.boards[i][j] != '*' && realboard.boards[i][j] != '.' && realboard.boards[i][j] != '|')
                    myboard.boards[i][j] = realboard.boards[i][j];
                else
                    flag = 1;

                if(i > 4 )
                    break;
                i++;
    }

    //top
    i = x;
    j = y;
    flag = 0;
    while(flag == 0)
    {   
            //char* neigbour = neighbours(i, j, real);
                if(realboard.boards[i][j] != '*' && realboard.boards[i][j] != '.' && realboard.boards[i][j] != '|')
                    myboard.boards[i][j] = realboard.boards[i][j];
                else
                    flag = 1;

                if( i < 0 )
                    break;
                i--;   
    }


    //left
    i = x;
    j = y;
    flag = 0;
    while(flag == 0)
    {   
            //char* neigbour = neighbours(i, j, real);
                if(realboard.boards[i][j] != '*' && realboard.boards[i][j] != '.' && realboard.boards[i][j] != '|')
                    myboard.boards[i][j] = realboard.boards[i][j];
                else
                    flag = 1;

                if(j < 0)
                    break;
                j--;      
    }

    //bottom left
    i = x;
    j = y;
    flag = 0;
    while(flag == 0 )
    {   
            //char* neigbour = neighbours(i, j, real);
                if(realboard.boards[i][j] != '*' && realboard.boards[i][j] != '.' && realboard.boards[i][j] != '|')
                    myboard.boards[i][j] = realboard.boards[i][j];
                else
                    flag = 1;

                if(i > 4 ) 
                    break;
                else if(j < 0)
                    break;

                i++;
                j--;
    }

    //top left
    i = x;
    j = y;
    flag = 0;
    while(flag == 0)
    {   
            //char* neigbour = neighbours(i, j, real);
                if(realboard.boards[i][j] != '*' && realboard.boards[i][j] != '.' && realboard.boards[i][j] != '|')
                    myboard.boards[i][j] = realboard.boards[i][j];
                else
                    flag = 1;

                if(i < 0 )
                    break;
                else if( j < 0)
                    break;
                j--;
                i--;
    }

    //top right
    i = x;
    j = y;
    flag = 0;
    while(flag == 0)
    {   
            //char* neigbour = neighbours(i, j, real);
                if(realboard.boards[i][j] != '*' && realboard.boards[i][j] != '.' && realboard.boards[i][j] != '|')
                    myboard.boards[i][j] = realboard.boards[i][j];
        else
            flag = 1;

        if(j > 4 )
            break;
        else if( i > 0)
            break;

        j++;
        i--;       
    }



    *my = myboard;
    display(my);
}

void addnums(board *real,int mines[][2])
{
    //it will add the numbers in the matrix

    char around[8];
    board realboard = *real;
    
    for(int i = 0; i < SIDE - 1; i++)
            for(int j = 0; j < SIDE - 1; j++)
            {
                //skip if the node itself is mine
                if(realboard.boards[i][j] == '*')
                    continue;
                char* around = neighbours(i, j, real);
                //cout<<i<<j<<"value sof i and j"<<realboard.boards[i][j]<<std::endl
                // if(top == '*' || top_left == '*' || top_right == '*' || right == '*' || left == '*' || bottom == '*' || bottom_left == '*' || bottom_right == '*')               
                int count = 0;
                for(int k = 0; k < 8; k++)
                {
                    if(around[k] == '*')
                    {
                        count++;
                        // cout<< count<<"valof count "<<around[k]<<"val of around"<<k<<std::endl;
                    }
                }
                //adding the count to to 0 to replace the val.
                realboard.boards[i][j] = count + '0';
                //cout<<realboard.boards[i][j]<<"realboardval"<<std::endl;
            }

            *real = realboard;
           // display(real);
}

char* neighbours(int i,int j, board *theboard)
{
    char* around = new char[8];
    board realboard = *theboard;

    around[0] = realboard.boards[i-1][j];
    around[1] = realboard.boards[i][j-1];
    around[2] = realboard.boards[i-1][j-1];
    around[3] = realboard.boards[i+1][j-1];
    around[4] = realboard.boards[i+1][j];
    around[5]= realboard.boards[i+1][j+1];
    around[6] = realboard.boards[i][j+1];
    around[7] = realboard.boards[i-1][j+1];

      // char top = realboard.boards[i-1][j];
    // char left = realboard.boards[i][j-1];
    // char top_left = realboard.boards[i-1][j-1];
    // char bottom_left = realboard.boards[i+1][j-1];
    // char bottom = realboard.boards[i+1][j];
    // char bottom_right = realboard.boards[i+1][j+1];
    // char right = realboard.boards[i][j+1];
    // char top_right = realboard.boards[i-1][j+1];

   
    *theboard = realboard;
    return around; 
}

vector<vector<int>> revealmarked(board *real,board *my)
{
    board realboard = *real;
    board myboard = *my;
    vector<vector<int>> miss;

    for(int i = 0; i < SIDE - 1; i++)
            for(int j = 0; j < SIDE - 1; j++)
                if(myboard.boards[i][j] == 'M')
                {
                    if(realboard.boards[i][j] != '*')
                    {
                        myboard.boards[i][j] = realboard.boards[i][j];
                        miss.push_back({i, j}); 
                    }
                    else
                    {
                        myboard.boards[i][j] = 'M';
                    }

                }
                else
                    myboard.boards[i][j] = realboard.boards[i][j];



    *my = myboard;
    *real = realboard;

    return miss;

}


