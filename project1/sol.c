#include <stdio.h>
#include <string.h>
#define N 100
#define MAX 1000
#define true 1
#define false 0
int W, H, L;
char board[N][N];
typedef enum
{
    UP,
    RIGHT,
    DOWN,
    LEFT
} Dir;
typedef struct
{
    int x, y;
} Point;
Point map[4] = {{0, -1}, {1, 0}, {0, 1}, {-1, 0}};
int cats_n;
Point cats[MAX];
int lasers_n;
int lit_map[N][N] = {0};
int left_mirror[4] = {[UP] = RIGHT, [RIGHT] = UP, [DOWN] = LEFT, [LEFT] = DOWN};
int right_mirror[4] = {[UP] = LEFT, [RIGHT] = DOWN, [DOWN] = RIGHT, [LEFT] = UP};
int visited[N][N][4] = {0};
int solve(int mirror_n, Point pos, Dir dir)
{
    if (pos.x < 0 || pos.x >= W || pos.y < 0 || pos.y >= H || visited[pos.y][pos.x][dir] || board[pos.y][pos.x] == '#'){
        for (int i = 0; i < cats_n; i++)
        {
            if (!lit_map[cats[i].y][cats[i].x])
            {
                return false;
            }
        }
        return true;
    }
    int is_new = lit_map[pos.y][pos.x] == false;
    int can_place_mirror = mirror_n && board[pos.y][pos.x] == '.';
    visited[pos.y][pos.x][dir] = true;
    lit_map[pos.y][pos.x] = true;
    Point new_pos;
    int new_dir= dir;
    if(can_place_mirror)
    { 
        new_dir = right_mirror[dir];
        Point new_pos = {pos.x + map[new_dir].x, pos.y + map[new_dir].y};
        board[pos.y][pos.x] = '\\';
        if (solve(mirror_n - 1, new_pos, new_dir ))
        {
            return true;
        }
        new_dir = left_mirror[dir];
        new_pos = (Point){pos.x + map[new_dir].x, pos.y + map[new_dir].y};
        board[pos.y][pos.x] = '/';
        if (solve(mirror_n - 1, new_pos, new_dir ))
        {
            return true;
        }
        board[pos.y][pos.x] = '.';
    }
    new_dir = dir;
    if (board[pos.y][pos.x] == '/')
        new_dir = left_mirror[dir];
    else if (board[pos.y][pos.x] == '\\')
        new_dir = right_mirror[dir];
    new_pos = (Point){pos.x + map[new_dir].x, pos.y + map[new_dir].y};
    if(solve(mirror_n, new_pos, new_dir))
        return true;
    if (is_new)
        lit_map[pos.y][pos.x] = false;
    visited[pos.y][pos.x][dir] = false;
    return false;
}

int main()
{
    scanf("%d %d %d\n", &W, &H, &L);
    Point laser_pos;
    Dir laser_dir;
    for (int i = 0; i < H; i++)
    {
        for (int j = 0; j < W; j++)
        {
            char c;
            while ((c = getchar()) != 'O' && c != 'A' && c != 'V' && c != '<' && c != '>' && c != '.' && c != '#');
            board[i][j] = c;
            switch (board[i][j])
            {
            case 'O':
                cats[cats_n].x = j;
                cats[cats_n].y = i;
                cats_n++;
                break;
            case 'A':
                laser_pos = (Point){j,i};
                laser_dir = UP;
                break;
            case 'V':
                laser_pos = (Point){j,i};
                laser_dir = DOWN;
                break;
            case '<':
                laser_pos = (Point){j,i};
                laser_dir = LEFT;
                break;
            case '>':
                laser_pos = (Point){j,i};
                laser_dir = RIGHT;
                break;
            }
        }

    }
    solve(L, laser_pos, laser_dir);
    printf("%d %d %d\n", W, H, L);
    for (int i = 0; i < H; i++)
    {
        for (int j = 0; j < W; j++){
            putchar(board[i][j]);
        }
        putchar('\n');
    }
    
}