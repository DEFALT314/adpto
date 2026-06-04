#include <stdio.h>
#include <string.h>
#define N 50
#define MAX 400
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
struct
{
    int x, y;
    Dir dir;
} lasers[MAX];
int lit_n;
Point lit_pos[MAX];
int lit_map[N][N];
int left_mirror[4] = {[UP] = RIGHT, [RIGHT] = UP, [DOWN] = LEFT, [LEFT] = DOWN};
int right_mirror[4] = {[UP] = LEFT, [RIGHT] = DOWN, [DOWN] = RIGHT, [LEFT] = UP};

int simulate()
{
    int visited[N][N][4] = {0};
    memset(lit_map, 0, sizeof(lit_map));
    lit_n = 0;
    for (int i = 0; i < lasers_n; i++)
    {
        int x = lasers[i].x + map[lasers[i].dir].x;
        int y = lasers[i].y + map[lasers[i].dir].y;
        int dir = lasers[i].dir;
        while (x >= 0 && x < W && y >= 0 && y < H && !visited[y][x][dir])
        {
            visited[y][x][dir] = 1;
            if (board[y][x] == '#')
            {
                break;
            }
            if (!lit_map[y][x])
            {
                lit_map[y][x] = 1;
                if (board[y][x] == '.')
                {
                    lit_pos[lit_n].x = x;
                    lit_pos[lit_n].y = y;
                    lit_n++;
                }
            }
            if (board[y][x] == '/')
            {
                dir = left_mirror[dir];
            }
            else if (board[y][x] == '\\')
            {
                dir = right_mirror[dir];
            }
            x += map[dir].x;
            y += map[dir].y;
        }
    }
    for (int i = 0; i < cats_n; i++)
    {
        if (!lit_map[cats[i].y][cats[i].x])
        {
            return false;
        }
    }
    return true;
}
int solve(int mirror_n)
{
    int is_solved = simulate();
    if (is_solved)
    {
        return true;
    }
    if (mirror_n == 0)
    {
        return false;
    }
    Point candidates[MAX];
    int n = lit_n;
    memcpy(candidates, lit_pos, sizeof(Point) * lit_n);
    for (int i = 0; i < n; i++)
    {
        board[candidates[i].y][candidates[i].x] = '/';
        if (solve(mirror_n - 1))
        {
            return true;
        }
        board[candidates[i].y][candidates[i].x] = '\\';
        if (solve(mirror_n - 1))
        {
            return true;
        }
        board[candidates[i].y][candidates[i].x] = '.';
    }
    return false;
}

int main()
{
    scanf("%d %d %d\n", &W, &H, &L);
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
                lasers[lasers_n].x = j;
                lasers[lasers_n].y = i;
                lasers[lasers_n].dir = UP;
                lasers_n++;
                break;
            case 'V':
                lasers[lasers_n].x = j;
                lasers[lasers_n].y = i;
                lasers[lasers_n].dir = DOWN;
                lasers_n++;
                break;
            case '<':
                lasers[lasers_n].x = j;
                lasers[lasers_n].y = i;
                lasers[lasers_n].dir = LEFT;
                lasers_n++;
                break;
            case '>':
                lasers[lasers_n].x = j;
                lasers[lasers_n].y = i;
                lasers[lasers_n].dir = RIGHT;
                lasers_n++;
                break;
            }
        }

    }
    solve(L);
    printf("%d %d %d\n", W, H, L);
    for (int i = 0; i < H; i++)
    {
        for (int j = 0; j < W; j++){
            putchar(board[i][j]);
        }
        putchar('\n');
    }
    
}