#include <stdio.h>

#define WIDTH 50
#define HEIGHT 20
#define MAX 20

char canvas[HEIGHT][WIDTH];

typedef struct
{
    int type;      // 1=Rectangle 2=Line 3=Triangle 4=Circle
    int x1, y1, x2, y2;
    int radius;
} Shape;

Shape shapes[MAX];
int count = 0;

/* Clear Canvas */
void clearCanvas()
{
    int i, j;

    for(i = 0; i < HEIGHT; i++)
        for(j = 0; j < WIDTH; j++)
            canvas[i][j] = ' ';
}

/* Display Canvas */
void displayCanvas()
{
    int i, j;

    for(i = 0; i < HEIGHT; i++)
    {
        for(j = 0; j < WIDTH; j++)
            printf("%c", canvas[i][j]);

        printf("\n");
    }
}

/* Rectangle */
void drawRectangle(int x1, int y1, int x2, int y2)
{
    int i, temp;

    if(x1 > x2)
    {
        temp = x1;
        x1 = x2;
        x2 = temp;
    }

    if(y1 > y2)
    {
        temp = y1;
        y1 = y2;
        y2 = temp;
    }

    for(i = x1; i <= x2; i++)
    {
        canvas[y1][i] = '*';
        canvas[y2][i] = '*';
    }

    for(i = y1; i <= y2; i++)
    {
        canvas[i][x1] = '*';
        canvas[i][x2] = '*';
    }
}

/* Horizontal or Vertical Line */
void drawLine(int x1, int y1, int x2, int y2)
{
    int i;

    if(y1 == y2)
    {
        if(x1 > x2)
        {
            int temp = x1;
            x1 = x2;
            x2 = temp;
        }

        for(i = x1; i <= x2; i++)
            canvas[y1][i] = '*';
    }
    else if(x1 == x2)
    {
        if(y1 > y2)
        {
            int temp = y1;
            y1 = y2;
            y2 = temp;
        }

        for(i = y1; i <= y2; i++)
            canvas[i][x1] = '*';
    }
}

/* Triangle */
void drawTriangle(int x, int y, int h)
{
    int i, j;

    for(i = 0; i < h; i++)
    {
        canvas[y+i][x-i] = '*';
        canvas[y+i][x+i] = '*';
    }

    for(j = x-h+1; j <= x+h-1; j++)
        canvas[y+h-1][j] = '*';
}

/* Circle */
void drawCircle(int xc, int yc, int r)
{
    int x, y;

    for(y = -r; y <= r; y++)
    {
        for(x = -r; x <= r; x++)
        {
            if(x*x + y*y <= r*r)
            {
                if(yc+y >= 0 && yc+y < HEIGHT &&
                   xc+x >= 0 && xc+x < WIDTH)
                {
                    canvas[yc+y][xc+x] = '*';
                }
            }
        }
    }
}

/* Add Shape */
void addShape(Shape s)
{
    if(count < MAX)
        shapes[count++] = s;
}

/* Delete Shape */
void deleteShape(int pos)
{
    int i;

    if(pos < 1 || pos > count)
    {
        printf("Invalid shape number!\n");
        return;
    }

    for(i = pos-1; i < count-1; i++)
        shapes[i] = shapes[i+1];

    count--;

    printf("Shape deleted.\n");
}

/* Render All Shapes */
void render()
{
    int i;

    clearCanvas();

    for(i = 0; i < count; i++)
    {
        if(shapes[i].type == 1)
            drawRectangle(shapes[i].x1, shapes[i].y1,
                          shapes[i].x2, shapes[i].y2);

        else if(shapes[i].type == 2)
            drawLine(shapes[i].x1, shapes[i].y1,
                     shapes[i].x2, shapes[i].y2);

        else if(shapes[i].type == 3)
            drawTriangle(shapes[i].x1,
                         shapes[i].y1,
                         shapes[i].x2);

        else if(shapes[i].type == 4)
            drawCircle(shapes[i].x1,
                       shapes[i].y1,
                       shapes[i].radius);
    }
}

/* Main */
int main()
{
    int choice;

    while(1)
    {
        printf("\n===== 2D GRAPHICS EDITOR =====\n");
        printf("1. Add Rectangle\n");
        printf("2. Add Line\n");
        printf("3. Add Triangle\n");
        printf("4. Add Circle\n");
        printf("5. Delete Shape\n");
        printf("6. Display Picture\n");
        printf("7. Exit\n");

        printf("Enter choice: ");
        scanf("%d", &choice);

        Shape s;

        switch(choice)
        {
            case 1:
                s.type = 1;
                printf("x1 y1 x2 y2: ");
                scanf("%d%d%d%d",
                      &s.x1,&s.y1,
                      &s.x2,&s.y2);
                addShape(s);
                break;

            case 2:
                s.type = 2;
                printf("x1 y1 x2 y2: ");
                scanf("%d%d%d%d",
                      &s.x1,&s.y1,
                      &s.x2,&s.y2);
                addShape(s);
                break;

            case 3:
                s.type = 3;
                printf("CenterX TopY Height: ");
                scanf("%d%d%d",
                      &s.x1,&s.y1,&s.x2);
                addShape(s);
                break;

            case 4:
                s.type = 4;
                printf("CenterX CenterY Radius: ");
                scanf("%d%d%d",
                      &s.x1,&s.y1,&s.radius);
                addShape(s);
                break;

            case 5:
            {
                int num;

                printf("Shape Number (1-%d): ", count);
                scanf("%d", &num);

                deleteShape(num);
                break;
            }

            case 6:
                render();
                displayCanvas();
                break;

            case 7:
                return 0;

            default:
                printf("Invalid Choice!\n");
        }
    }

    return 0;
}
