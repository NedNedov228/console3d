// #От профессионала


#include <iostream>
#include <stdio.h>
#include <windows.h>
#include "Vector.h"


void SetWindow(int Width, int Height)
{
    _COORD coord;
    coord.X = Width;
    coord.Y = Height;
    _SMALL_RECT Rect;
    Rect.Top = 0;
    Rect.Left = 0;
    Rect.Bottom = Height - 1;
    Rect.Right = Width - 1;
    HANDLE Handle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleScreenBufferSize(Handle, coord);
    SetConsoleWindowInfo(Handle, TRUE, &Rect);
}


int main()
{
    int width = 120;
    int height = 30;
    //SetWindow(width, height);
    float aspect = (float)width / height;
    float pixelAspect = 11.0f / 24.0f;
    char grad[] = " .:!/r(l1Z4H9W8$@";//" .a@";
    int gradSize = std::size(grad) - 2;

    char* screen = new char[width * height + 1];

    screen[width * height] = '\0';

    
    //Vector3 light = normalize(Vector3(-0.5,0.5, -1.0));

    for(int t = 0; 1; t++)
    {
        Vector3 light = normalize(Vector3(sin(t * 0.001), cos(t * 0.001), -1.0));
        for (int i = 0; i < width; i++) {
            for (size_t j = 0; j < height; j++)
            {
                Vector2 uv = Vector2(i,j) / Vector2(width,height) * 2.0f - 1.0f;
                uv.x *= aspect * pixelAspect;

                Vector3 ro = Vector3(-2, 0, 0);
                Vector3 rd = normalize(Vector3(1, uv));
                //uv.x += sin(t * 0.001f);
                char pixel = grad[0];
                //float dist = sqrt(uv.x * uv.x + uv.y * uv.y);
                int shade = 0; //(int)(1.0f / dist);
                Vector2 intersection = sphere(ro, rd, 1);
                
                if (intersection.x > 0) {
                    //shade = 10;
                    Vector3 itPoint = ro + rd * intersection.x;
                    Vector3 n = normalize(itPoint);
                    float diff = dot(n, light);
                    shade = (int)(diff * 20.0f);
                }
                shade = valClamp(shade, 0, gradSize);
                pixel = grad[(int)shade];

                screen[i + j * width] = pixel;
            }
        }
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        COORD pos = { 0, 0 };
        SetConsoleCursorPosition(hConsole, pos);
        printf("%s",screen);
    }
    


   
    getchar();
}

