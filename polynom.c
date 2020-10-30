#include <stdarg.h>

double  polynom(double x, int i, ...)
{
   va_list argptr;
   double  sum = 0.0, t;
   va_start (argptr, i);
   for(i--; i >= 0; i--)
   {
       t = va_arg(argptr,double);
       sum += t * pow(x, i);
   }
   va_end(argptr);
   return sum;
}
