#include <Magick++.h>
#include <iostream>

using namespace Magick;
using namespace std;

// Filer class
// 
// This class is the base for all filters

class Filter
{
    private:
        int m, n;

        int q(int i) const {return i - m;}
        int p(int j) const {return j - n;}

        ColorRGB getFiltered(float x, float y, Image & pic) const;

    protected:
        float c;

        void setNorm();
        virtual float f(float p, float q, float x, float y) const 
            {if (p == 0 && q == 0) return 1; else return 0;}

    public:
        Filter(int m = 1, int n = 1) : m{m}, n{n} {}

        int columns() const {return 2 * m + 1;}
        int rows() const {return 2 * n + 1;}

        void apply(Image & pic) const;
        void print() const;
};


// Derived classes
// 
// This are classes derived from Filter, with their own instances of f(p, q, x, y)

class Gaussian : public Filter
{
    private:
        float s;
        float f(float p, float q, float x, float y) const
            {return c / sqrt(2 * M_PI) / s * exp(-(p*p + q*q) / (2*s*s));}

    public:
        Gaussian(int n = 1, float s = 1) :s{s}, Filter(n, n) {setNorm();}
};

class Edge : public Filter
{
    private: 
        float f(float p, float q, float x, float y) const
        {
            if (p == 0 && q == 0) return rows() * columns() - 1;
            else return -1;
        }

    public:
        Edge(int n = 1) : Filter(n, n) {}
};

class Sharpen : public Filter
{
    private: 
        float f(float p, float q, float x, float y) const
        {
            if (p == 0 && q == 0) return 5;
            if ((p == -1 && q == -1) ||
                (p == -1 && q == 1) ||
                (p == 1 && q == -1) ||
                (p == 1 && q == 1))
                return -1;
            else return 0;
        }

    public:
        Sharpen() :  Filter(1, 1) {}
};
