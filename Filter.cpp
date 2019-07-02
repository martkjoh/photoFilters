#include "Filter.h"

void Filter::setNorm()
{
    c = 1;
    float S = 0;
    for (int j = 0; j < rows(); j++)
    {
        for(int i = 0; i < columns(); i++)
        {
            S += f(q(i), q(j), 0, 0);
        }
    }
    if (S != 0) 
        c = 1 / S;
}


void Filter::apply(Image & pic) const
{
    pic.quantizeColorSpace(RGBColorspace);
    Image picCopy(pic);

    for (int y = m; y < pic.rows() - m; y++)
    {
        for (int x = n; x < pic.columns() - n; x++)
        {
            pic.pixelColor(x, y, getFiltered(x, y, picCopy));
        }
    }
}

ColorRGB Filter::getFiltered(float x, float y, Image & pic) const
{
    // Tuple to carry pre-filter colors
    ColorRGB rgb;
    // Tuple to carry filtered colors 
    ColorRGB rgbF(0, 0, 0);
    for (int j = 0; j < rows(); j++)
    {
        for(int i = 0; i < columns(); i++)
        {
            rgb = pic.pixelColor(x + p(i), y + q(j));
            rgbF.red(rgbF.red() + rgb.red() * f(p(i), q(j), x, y));
            rgbF.blue(rgbF.blue() + rgb.blue() * f(p(i), q(j), x, y));
            rgbF.green(rgbF.green() + rgb.green() * f(p(i), q(j), x, y));
        }
    }
    return rgbF;
}


void Filter::print() const
{
    for (int i = 0; i < columns(); i++)
    {
        for(int j = 0; j < rows(); j++)
        cout << f(p(i), q(j), 0, 0) << "     ";
    cout << endl;
    }
}