#include "rk4sys.h"
#include "calcThrust.h"
#include <iostream>
#include <fstream>
#include <ctime>
#include <chrono>
#include <ratio>
//TODO: SC: Why are we using these? What benefit are they serving?

int main()
{
    // setting initial conditions of the asteroid
    elements<double> y0;
    y0.r = 3.150802646376772e+11/AU;// radial position (au)
    y0.theta= -3.081519548404041;// angular position (rad)
    y0.z =  1.760293325286572e+10/AU;// off-plane position (au)
    y0.vr = 4706.64912336045/AU;// radial velocity (au/s)
    y0.vtheta= 16716.9055348804/AU;// azimuthal velocity (rad/s)
    y0.vz= -81.4453413932308/AU;// off-plane velocity (au/s)

    // conditions for the acceleration components
    double tau = 3./4;
    double gamma = 3./4;
    double accel = 0.0001/AU;

double accel = 0.0001/AU;// thrust acceleration (au/s^2)

// setup of thrust angle calculations
coefficients<double> coeff;
for (int i : coeff.gamma){
  coeff.gamma[i]=1;
}
for (int i : coeff.tau){
  coeff.tau[i]=1;
}

    // seting Runge-Kutta tolerance
    double absTol = 1e-9;

    // Initialize memory for the solution vector of the dependant solution
    //TODO: SC: That is *times? Where and why are you using numSteps == 500?
    elements<double>* y;
    y = new elements<double>[numSteps];
    double *times;
    times = new double[numSteps];

    // Recording the start time for performance metric
    std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();

    // Our output function (yp)
    //TODO: SC: This is not a helpful comment, 'Our' is nebulous, output function (yp) does not describe what an output function (yp) is 
    elements<double> *yp;
    for (int repeat = 0; repeat<1; repeat++){ //TODO: SC: I know why this was put in but it should either: 1) be made part of the code or 2) removed
        //TODO: SC: While I would not normally say a function call needs a comment, this function call is complicated. A comment or two about what is going on here is needed. A list a veriables is not inherently readable
        yp = rk4sys(timeInitial,timeFinal,times,y0,deltaT,y,absTol,accel,tau,gamma);
    }
    // recording stop time
    std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();

    // calculating elapsed time of rk4sys() call(s)
    std::chrono::duration<double> time_span = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);
    std::cout << "rk4sys() call took " << time_span.count() << " seconds." << std::endl;

//    Our output function (yp)
elements<double> *yp;
for (int repeat = 0; repeat<1; repeat++){
  yp = rk4sys(timeInitial,timeFinal,times,y0,deltaT,y,absTol,coeff,accel);
}
//    recording stop time
  std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
    //TODO: SC: Why?
    if (time_span.count()==0)
        std::cout<<"I am speed" << std::endl;

    // Output of yp to a text file
    std::ofstream output;    
    output.open ("orbitalMotion-accel.bin", std::ios::binary);

//    Output of elasped time
  std::cout << "It took me " << time_span.count() << " seconds." << std::endl;
if (time_span.count()==0)
std::cout<<"I am speed" << std::endl;

// Output of yp to a binary file
  std::ofstream output;
  
  output.open ("orbitalMotion-accel.bin", std::ios::binary);
  for(int i=0; i < numSteps; i++)
  {
    //output << yp[i];
    output.write((char*)&yp[i], sizeof (elements<double>));
    output.write((char*)&times[i], sizeof (double));
  }
  output.close();

    // cleaning up dynamic yp
    //TODO: SC: What about times? Might want to clean that up too
    delete [] yp;

    return 0;
}