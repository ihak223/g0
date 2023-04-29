#include <math.h>

double pi_big = 3.14159265359;

double degrees(double radians)
{
    return radians * (180.0 / M_2_PI);
}

double radians(double degrees)
{
    return degrees * (M_2_PI / 180.0);
}

void slope_from_angle(double* sx, double* sy, double angle)
{
    *sx = sin(radians(angle));
    *sy = cos(radians(angle));
}

double get_angle(double run, double rise) {
    if (rise == 0 && run == 0) {
        return NAN;
    } else if (rise == 0) {
        return 0.0;
    } else if (run == 0) {
        if (rise > 0)
        {
            return (double)90.0;
        }
        else
        {
            return (double)(-90.0);
        }
    } else {
        double slope = rise / run;
        double angle = atan(slope);
        double angle_degrees = angle * 180.0 / pi_big;
        if (rise > 0 && run < 0) {
            angle_degrees += 180.0;
        } else if (rise < 0 && run < 0) {
            angle_degrees -= 180.0;
        }
        return angle_degrees;
    }
}

void slope(double* sx, double* sy, int ax, int ay, int bx, int by) {
    if (ax == bx) {
        *sx = INFINITY;
        *sy = NAN;
    } else {
        *sx = (double) (by - ay) / (double) (bx - ax);
        *sy = 0.0;
    }
}