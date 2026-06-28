/*
    


*/

#pragma once 
#include <vector>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

class Simulation {




public:
    Simulation();
    Simulation(double x_0, double time_step,double sim_length );
    void update(double x_0 , double time_step,double sim_length );
    void reset();
    void run(std::string filename);
    void saveData(std::string filename);
    void set_u();
    void set_u(const std::vector <double>& input_signal);
    void set_t(double simulation_length, double sim_step);
    void set_x();

    const std::vector <double>&  read_t();
    const std::vector <double>&  read_u();
    const std::vector <double>&  read_x();
    int elements();
    double read_time_step();
    int calc_time(double time_to_index);




private:
    
    //define our time, input, state time series 
    std::vector <double> u_;  // input time series 
    std::vector <double> t_;  // time input time series
    std::vector <double> x_;  // state variable time series
    double x_0_;              // initial condition
    int    n_;                // number of elements in time series 
    double time_step_;        // time increment in seconds  
    double sim_length_;       // length of simulation in seconds 


};