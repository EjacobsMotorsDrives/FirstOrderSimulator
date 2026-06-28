/*
    class accepts 
    input parameters:
        - paramater a that defines the model: x' = ax + u
        - initial state x0
        - take a time series  
        - input u  as time series

    class simulation logic should be completely seperated from
    how it is displayed and gui or plotting logic  
    write a unit test in cmake 

    methods 
    constructor method
    update method -> should call reset method and be treated as a new instances 
    run method 
    reset method
    
    
    
    save simulation results to csv 
        - first column is time 
        - second column is input
        - third column is state
        
    writing a test for this class 
    do the same simiulation in matlab 
    - has to load data from matlab output and has to simulate system
      and then compare with the matlab within a defined tolerance 


    we when do the switch in the menu loop for each input selection
    we will generate the inputs and values of time 
    at time of selection of input type we also get input from user 
    on length of simulation and time step 

    
    

*/
#include <iostream>
#include "input_waves.hpp"
#include "simulate.hpp"
#include <limits>

int    input_handler_int(int min, int max);
double input_handler_double(double min, double max);
input_signal input_handler_inputSig(int min,int max);

// this bool maintains the outer menu loop and is set false to exit the TUI
bool run = true;


input_signal input_type = input_signal::ramp; 

int selection = 0;

// simulation Global Variables
double x0         =  0.0;
double sim_step   =  1.0;
double sim_length = 10.0;

// Input signal Global variables 
double base_value = 0.0;    
double peak_value = 1.0;
double step_value = 1.0;
double slope      = 1.0;
double step_time  = 1.0;
double period     = 1.0;  
double duty_cycle = 0.5;


int limit_mainMenu_min   = 1;
int limit_mainMenu_max   = 3;

int limit_inputsig_min   = 1;
int limit_inputsig_max   = 5;

// Limits
// Input defined for input parameters
// eventually once working this will be moved into a TUI header file 

double limit_x0_min         =  0.0;
double limit_x0_max         =  5.0;

double limit_sim_length_min =  10;
double limit_sim_length_max = 100;

double limit_sim_step_min   = 0.01;
double limit_sim_step_max   = 1.00;

double limit_base_value_min =  0.0;
double limit_base_value_max =  5.0;

double limit_peak_value_min =  5.0;
double limit_peak_value_max = 10.0;

double limit_step_value_min =  1.0;
double limit_step_value_max = 10.0;

double limit_step_time_min  =  1.0;
double limit_step_time_max  =  5.0;

double limit_period_min     =  1.0;
double limit_period_max     =  5.0;

double limit_duty_cycle_min = 0.0;
double limit_duty_cycle_max = 1.0;

double limit_slope_min      = 0.5;
double limit_slope_max      = 1.0;



int main()
{
    
    
    while(run)
    {
        std::cout << "The program simulates the function x' = 2x + u" << std::endl;
        std::cout << "please choose one of the following three options" << std::endl;
        std::cout << " (1) Load a prevous run into memory and plot it " << std::endl;
        std::cout << " (2) Start a new run " << std::endl;
        std::cout << " (3) Exit the simulation " << std::endl;
        
        selection = input_handler_int(limit_mainMenu_min,limit_mainMenu_max);

        switch(selection)
        {

            case 1:
            {
                    // implement running python script to plot simulations
                break;
            }
            case 2:
            {
                std::cout << "You selected New simulation" << std::endl;
                std::cout << "First enter a initial condition" << std::endl;
                std::cout << "valid input from " << limit_x0_min  << " to " << limit_x0_max << std::endl;
                x0 = input_handler_double(limit_x0_min, limit_x0_max);
                
                std::cout << "First enter a initial condition" << std::endl;
                std::cout << "valid input from " << limit_sim_length_min  << " to " << limit_sim_length_max << std::endl;
                sim_length = input_handler_double(limit_sim_length_min, limit_sim_length_max);

                // TODO need to write a input handler helper function that ensures
                //      that sim time step is within less than sim length 
                //      This could be specified further to include a minimum
                //      number of discretized elements to define a bare minimum
                //      simulation
                std::cout << "First enter a simulation time step" << std::endl;
                std::cout << "valid input from " << limit_sim_step_min  << " to " << limit_sim_step_max << std::endl;
                sim_step = input_handler_double(limit_sim_step_min, limit_sim_step_max);
                
                Simulation sim(x0, sim_step, sim_length);

                std::cout << "Select an Input signal and then configure signal" << std::endl;
                std::cout << "please choose one of the following five options" << std::endl;
                std::cout << " (1) Step     Signal " << std::endl;
                std::cout << " (2) Ramp     Signal " << std::endl;
                std::cout << " (3) SawTooth Signal " << std::endl;
                std::cout << " (4) Square   Signal " << std::endl;
                std::cout << " (5) Triangle Signal " << std::endl;
                
                input_type = input_handler_inputSig(limit_inputsig_min, limit_inputsig_max);
                
                switch(input_type)
                {

                    case input_signal::step :
                    {
                        std::cout << "You Selected an Input signal of a Step signal " << std::endl;

                        std::cout << "please choose a step time" << std::endl;
                        step_time = input_handler_double(limit_step_time_min, limit_step_time_max);
                        std::cout << "please choose a base value" << std::endl;
                        base_value = input_handler_double(limit_base_value_min, limit_base_value_max);
                        std::cout << "please choose a step value" << std::endl;
                        step_value = input_handler_double(limit_step_value_min, limit_step_value_max);

                        step( step_time, base_value, step_value, sim);

                        break;
                    }
                    case input_signal::ramp :
                    {
                        std::cout << "You Selected an Input signal of a ramp signal " << std::endl;

                        std::cout << "please choose a slope" << std::endl;
                        slope = input_handler_double(limit_slope_min, limit_slope_max);
                        std::cout << "please choose a base value" << std::endl;
                        base_value = input_handler_double(limit_base_value_min, limit_base_value_max);
                        

                        ramp(slope, base_value, sim);
                        break;
                    }
                    case input_signal::sawtooth :
                    {    
                        std::cout << "You Selected an Input signal of a Sawtooth signal " << std::endl;


                        std::cout << "please choose a base value" << std::endl;
                        base_value = input_handler_double(limit_base_value_min, limit_base_value_max);
                        std::cout << "please choose a peak value" << std::endl;
                        peak_value = input_handler_double(limit_peak_value_min, limit_peak_value_max);
                        std::cout << "please choose a period" << std::endl;
                        period = input_handler_double(limit_period_min, limit_period_max);

                        sawtooth(base_value,peak_value,period,sim);
                        break;
                    }
                    case input_signal::square :
                    {
                        std::cout << "You Selected an Input signal of a Square signal " << std::endl;


                        std::cout << "please choose a base value" << std::endl;
                        base_value = input_handler_double(limit_base_value_min, limit_base_value_max);
                        std::cout << "please choose a peak value" << std::endl;
                        peak_value = input_handler_double(limit_peak_value_min, limit_peak_value_max);
                        std::cout << "please choose a duty_cycle" << std::endl;
                        duty_cycle = input_handler_double(limit_duty_cycle_min, limit_duty_cycle_max);
                        std::cout << "please choose a period" << std::endl;
                        period = input_handler_double(limit_period_min, limit_period_max);



                        square(base_value,peak_value,duty_cycle,period,sim);
                        break;
                    }
                    case  input_signal::triangle :
                    {
                        std::cout << "You Selected an Input signal of a Triangle signal " << std::endl;


                        std::cout << "please choose a base value" << std::endl;
                        base_value = input_handler_double(limit_base_value_min, limit_base_value_max);
                        std::cout << "please choose a peak value" << std::endl;
                        peak_value = input_handler_double(limit_peak_value_min, limit_peak_value_max);
                        std::cout << "please choose a period" << std::endl;
                        period = input_handler_double(limit_period_min, limit_period_max);

                        triangle(base_value,peak_value,period,sim);
                        break;
                    }
                }

                sim.run("test");

                break;
            }    
            case 3:
            {
                run = false;
                break;
            }
        }
    }

    return 0;
}


    int input_handler_int(int min, int max)
    { 
        int sel = 1;
        while (!(std::cin >> sel) || sel <  min || sel >  max) 
        {
            std::cin.clear(); 
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
            
            std::cout << "Invalid input. Please enter a number between " << min << " and " << max << ": ";
        }

        std::cout << "You selected: " << sel << std::endl;
        return sel;
    }

    double input_handler_double(double min, double max)
    {
             
        double sel = 1.0;
        while (!(std::cin >> sel) || sel <  min || sel >  max) 
        {
            std::cin.clear(); 
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
            
            std::cout << "Invalid input. Please enter a number between " << min << " and " << max << ": ";
        }

        std::cout << "You selected: " << sel << std::endl;
        return sel;
        

    }

    input_signal input_handler_inputSig(int min,int max)
    {
        int sel = 1; 
        input_signal  sig = input_signal::step;
        while (!(std::cin >> sel) || sel <  min || sel >  max) 
        {

            std::cin.clear(); 
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
            
            std::cout << "Invalid input. Please enter a number between " << min << " and " << max << ": ";
        }
        sel -= 1; // users enter 1-5 but enum looks at 0-4
        std::cout << "You selected: " << sel << std::endl;
        sig = static_cast<input_signal>(sel);
        return sig;
        

    }
