#include "print.h"

/*
왜 굳이 (int)(255.999)를 하지? 256 하면 외안되?
*/

void    write_color(t_color3 pixel_color)
{
    // if (pixel_color.x)
    //     return;
        // printf("%d %d %d\n", (int)(256 * pixel_color.x),
        //                 (int)(256 * pixel_color.y),
        //                 (int)(256 * pixel_color.z));
    printf("%d %d %d\n", (int)(255.999 * pixel_color.x),
                        (int)(255.999 * pixel_color.y),
                        (int)(255.999 * pixel_color.z));
}