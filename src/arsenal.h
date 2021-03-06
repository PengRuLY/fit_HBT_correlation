// Version 1.6.2
// Zhi Qiu

#ifndef arsenal_h
#define arsenal_h

#include "stdlib.h"
#include <vector>
#include <string>

using namespace std;

int get_number_of_lines(string filename);
double sixPoint2dInterp(double x, double y,
    double v00, double v01, double v02, double v10, double v11, double v20);

double interpCubicDirect(vector<double>* x, vector<double>* y, double xx);
double interpCubicMono(vector<double>* x, vector<double>* y, double xx);
double interpLinearDirect(vector<double>* x, vector<double>* y, double xx);
double interpLinearMono(vector<double>* x, vector<double>* y, double xx);
double interpNearestDirect(vector<double>* x, vector<double>* y, double xx);
double interpNearestMono(vector<double>* x, vector<double>* y, double xx);

double invertFunc(double (*func)(double), double y, double xL, double xR, double dx, double x0, double relative_accuracy=1e-10);

double invertTableDirect_hook(double xx);
double invertTableDirect(vector<double>* x, vector<double>* y, double y0, double x0, double relative_accuracy=1e-10);

double stringToDouble(string);
vector<double> stringToDoubles(string);
string toLower(string str);
string trim(string str);

vector< vector<double>* >* readBlockData(istream &stream_in);
void releaseBlockData(vector< vector<double>* >* data);

double adaptiveSimpsonsAux(double (*f)(double), double a, double b, double epsilon, double S, double fa, double fb, double fc, int bottom);
double adaptiveSimpsons(double (*f)(double), double a, double b,  double epsilon=1e-15, int maxRecursionDepth=50);

double qiu_simpsons(double (*f)(double), double a, double b, double epsilon=1e-15, int maxRecursionDepth=50);

long binarySearch(vector<double>* A, double value, bool skip_out_of_range=false);

void formatedPrint(ostream&, int count, ...);
double gamma_function(double x);

void print_progressbar(double percentage, int length=50, string symbol="#");
void display_logo(int which=1);

//**********************************************************************
inline long irand(long LB, long RB)
// Get an interger between LB and RB (including) with uniform distribution.
{
  return LB + (long)((RB-LB+1)*(drand48()-1e-25));
}


//**********************************************************************
inline double drand(double LB, double RB)
// Get random number with uniform distribution between LB and RB with 
// boundary-protection.
{
  double width = RB-LB;
  double dw = width*1e-30;
  return LB+dw+(width-2*dw)*drand48();
}

void GaussLegendre_getWeight(int npts,double* x,double* w, double A, double B, int opt=1);

void get_bin_average_and_count(istream& is, ostream& os, vector<double>* bins, long col_to_bin=0, void (*func)(vector<double>*)=NULL, long wanted_data_columns=-1, bool silence=false); // Note that col_to_bin starts with 1, and bins is assumed to be monotonically increasing

unsigned long int random_seed(int seed_flag);
// Seems to be included in gnu library already...
// inline double asinh(double x) { return log(x + sqrt(x*x + 1)); }
// inline double acosh(double x) { return x>0? log(x + sqrt(x*x - 1)) : -log(x + sqrt(x*x - 1)); }
// inline double atanh(double x) { return 1.0/2.0*log((1+x)/(1-x)); }


#endif



/*----------------------------------------------------------------------
 Change logs:

 04-26-2010:
 -- invertFunc, invertTable, stringToDoubles, readBlockData functions added.
 04-25-2011:
 -- interpCubic function adxed.
 12-17-2010:
 -- sixPoint2dInterp function adxed.
 08-05-2011:
 -- Ver 1.1:
    Functions adaptiveSimpsons and qiu_simpsons added. The qiu_simpsons function, when using 20 recursions, is 4 times faster than adaptiveSimpsons. The function used to test this is sin(2000*x), integrated on [0,1].
 09-09-2011:
 -- Ver 1.2:
    Function toLower added. It simply convert all letters in a string to lower case.
    Function stringToDouble added.
    Function trim added.
 02-02-2012:
 -- Ver 1.2.1:
    Function trim now also removes tabs besides spaces.
 02-04-2012:
 -- Ver 1.5:
    Functions added: interpCubic, binarySearch, formatedPrint, gamma_function,
    interpLinearDirect, interpLinearMono, interpNearestDirect, interpNearestMono.
    Function interpCubic is renamed to interpCubicMono.
 03-14-2012:
 -- Ver 1.5.1:
    Functions added: print_progressbar.
 03-19-2012:
 -- Ver 1.6:
    Functions added: display_logo, drand, irand, GaussLegendre_getweight, get_bin_average_and_count.
    Function formatedPrint now accepts a stream argument.
 03-19-2012:
 -- Ver 1.6.1:
    Function get_bin_average_and_count can now average transformed data
    that have different number of columns than the data directly read in.
 03-23-2012:
 -- Ver 1.6.2:
    Functions added: asinh, acosh, atanh.
-----------------------------------------------------------------------*/
