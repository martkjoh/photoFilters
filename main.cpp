#include "Filter.h"

int main()
{
    Gaussian G(2, 5);
    Edge F;
    Image pic("media/blomst.jpeg");
    G.apply(pic);
    F.apply(pic);
    pic.write("media/blomst_filtrert.jpeg");
    return 0;   
}