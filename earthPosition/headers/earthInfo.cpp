#include "earthInfo.h"
#include "orbitalMotion.h"
    
#include <iostream>  
#include <iomanip> // setprecision(int)  
using namespace std;

EarthInfo::EarthInfo(const double & beginTime, const double & stopTime, const double & timeAcc)
{
    //Setting up initial information
    startTime = beginTime; //Starting time (s)
    endTime = stopTime; //Ending time (s)
    timeRes = timeAcc; //Time resolution (s)
    tolData = ((endTime-startTime)/timeRes) + 1; //Total Number of Data points (in hours) in earthCon, plus one for the last 'section'

    //Alocate memory for earthCon, one entry for every data point
    earthCon = new elements<double> [tolData]();
    
    //TODO: iterative runge kutta to speed up execution speed, reuse previous solution.

    for(int i=0; i<tolData; i++)
    { 
        earthCon[i]=earthInitial(calc_time(i));//Obtaining conditions of the earth every hour
        std::cout << "Number of runs: " << i << ", results: " << earthCon[i] << std::endl;
    }
}

elements<double> EarthInfo::getCondition(const double & currentTime)
{
    elements<double> lower;
    elements<double> upper;
    int index;
    index = calcIndex(currentTime);//Location of data (in hours) based on time (in seconds)
    lower = earthCon[index];
    upper = earthCon[index + 1];
    double lowerWeight = 1 - ((currentTime-calc_time(index))/timeRes);
    double upperWeight = 1 - ((calc_time(index+1)-currentTime)/timeRes);

    return interpolate(lower,upper,lowerWeight,upperWeight);
}

int EarthInfo::calcIndex(const double & currentTime)
{
   return static_cast<int>((currentTime-startTime)/timeRes);

}

double EarthInfo::calc_time(const int & currentIndex)
{
    return startTime + (currentIndex*timeRes);
}

int EarthInfo::getTolData(){
    return tolData;
}

elements<double> EarthInfo::interpolate(const elements<double> & lower,const elements<double> & upper,const double & lowerWeight,const double & upperWeight)
{
    return (lower*lowerWeight)+(upper*upperWeight);
}

EarthInfo::~EarthInfo()
{
    delete [] earthCon;
}