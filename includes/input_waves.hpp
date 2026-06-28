/*

    This is a collection of helper functions 

    input signal generators

    step:
    Y0+step     |     _________________________
                |     |
            Y0  |_____|
                |______________________________
             t  0      t-step
        input:
            - step time 
            - base value
            - step value
            - simulation length 
            - time step of simulation 
        output 
            - time series of input signal 
    ramp:

    Y0+step     |   /  
                |  /   
                | /
                |/_________
             t  0      
        input:
            - slope 
            - initial value
            - simulation length 
            - time step of simulation 
        output 
            - time series of input signal 

    square,
                     
    Y0+square   |     ________     ________ 
                |     |      |     |      |
            Y0  |_____|      |_____|      |____
                |______________________________
             t  0     | on t |Off t|  
        input: 
            - base value
            - Step value
            - duty cycle
            - period
            - simulation length 
            - time step of simulation 
        output 
            - time series of input signal 

    sawtooth,                 
    Y0+Peak     |   /|   /|   /|   /|   /|   /|
                |  / |  / |  / |  / |  / |  / |
                | /  | /  | /  | /  | /  | /  | /
                |/___|/___|/___|/___|/___|/___|/_
             t  0          
        input: 
            - base value
            - slope
            - peak value
            - period
            - simulation length 
            - time step of simulation 
        output 
            - time series of input signal 


    triangle

    Y0+Peak     |   /\      /\      /\      /
                |  /  \    /  \    /  \    / 
                | /    \  /    \  /    \  /  
                |/______\/______\/______\/______
             t  0          
        input: 
            - base value
            - slope
            - peak value
            - period
            - simulation length 
            - time step of simulation 
        output 
            - time series of input signal 





*/


#pragma once 
#include <iostream>
#include <vector>
#include "simulate.hpp"

enum class input_signal 
{
    step,
    ramp,
    square,
    sawtooth,
    triangle
};



void step(
            double step_time, 
            double base_value,
            double step_value,
            Simulation& sim 
         );

void ramp(
            double slope, 
            double base_value,
            Simulation& sim 
          );

void square(
             double base_value,
             double peak_value,
             double duty_cycle,
             double period,
             Simulation& sim 
           );

void sawtooth(
               double base_value,
               double peak_value,
               double period,
               Simulation& sim 
             );    

void triangle( 
               double base_value,
               double peak_value,
               double period,
               Simulation& sim 
             );


