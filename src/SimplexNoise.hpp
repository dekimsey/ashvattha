#ifndef __SIMPLEX_NOISE_H
#define __SIMPLEX_NOISE_H

class SimplexNoise {
    public:
        static SimplexNoise& getInstance() {
            static SimplexNoise noise = SimplexNoise();
            return noise;
        }

        static double noise(double xin, double yin);    
        static double noise(double xin, double yin, double zin);
        static double noise(double xin, double yin, double zin, double win);
        
        class Grad {
            public:
                double _x, _y, _z, _w;
                Grad(double x, double y, double z, double w = 0);
        };

    private:
        SimplexNoise();
        SimplexNoise(SimplexNoise const&); //leave unimplemented
        void operator=(SimplexNoise const&); //leave unimplemented 

        static const Grad grad3[];
        static const Grad grad4[];
        
        static const short perm[512];
        static short permMod12[512];

        static const double F2;
        static const double G2;
        static const double F3;
        static const double G3;
        static const double F4;
        static const double G4;

        static int fastfloor(double x);
        static double dot(const Grad& g, double x, double y);
        static double dot(const Grad& g, double x, double y, double z);
        static double dot(const Grad& g, double x, double y, double z, double w); 
};

#endif
