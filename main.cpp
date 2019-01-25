#include <iostream>
#include <iomanip>
#include <math.h>
#include "bitmap_image.hpp"

using namespace std;

rgb_t get_colour(int x, int y)
{
    rgb_t colour;
    int clr;
    double wsp = (double)y/(100+pow(x,0.85))+(double)y/2000;

    colour.red = 255;
    colour.green = 255;
    colour.blue = 255;

    if (wsp < 1.66)
    {
        clr = round((((wsp-1)/0.666666666)*0.2+0.8)*256-1);

        colour.red = 255;
        colour.green = 255;
        colour.blue = clr;
    }

    if(wsp < 1)
    {
        clr = round((0.5+0.5*wsp)*256-1);

        colour.red = clr;
        colour.green = clr;
        colour.blue = 0;
    }

    return colour;
}

int main()
{
    int rep, posts;
    int src_h, src_w, des_h, des_w;
    double wsp;
    cout << "Insert height and width of the image: ";
    cin >> src_h >> src_w;

    cout << "Insert desired height and width of the image: ";
    cin >> des_h >> des_w;

    cout << "Insert rep and posts you want to highlight: ";
    cin >> rep >> posts;

    bitmap_image image(des_w, des_h);

    double scale_w, scale_h;

    scale_w = double(src_w/des_w);
    scale_h = double(src_h/des_h);

    int scaled_rep = round(rep/scale_h);
    int scaled_posts = round(posts/scale_w);

    for (unsigned int y = 0; y < image.height(); ++y)
    {
        for (unsigned int x = 0; x < image.width(); ++x)
        {
            image.set_pixel(x, y, get_colour(scale_w*x, scale_h*y));
            if ((x == scaled_posts || y == scaled_rep) && !(x == scaled_posts && y == scaled_rep))
                image.set_pixel(x, y, 00,00,00);
        }
    }

    wsp = (double)rep/(100+pow(posts,0.85))+(double)rep/2000;
    cout << "\nYour wsp: " << wsp;
    rgb_t user_clr = get_colour(posts, rep);
    cout << "\nYour colour: #" << hex << setfill('0') << setw(2) << (int)user_clr.red << std::setw(2) << (int)user_clr.green << std::setw(2) <<(int)user_clr.blue;
    user_clr = image.get_pixel(scaled_posts, scaled_rep);
    cout << "\nColour from map: #" << hex << setfill('0') << setw(2) << (int)user_clr.red << std::setw(2) << (int)user_clr.green << std::setw(2) <<(int)user_clr.blue;



    image.save_image("output.bmp");
}
