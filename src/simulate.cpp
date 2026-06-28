#include  "simulate.hpp"
using namespace std;
    
    Simulation::Simulation()
    {
        x_0_        = 0;               
        time_step_  = 1;          
        sim_length_ = 10;       
        
        set_t(sim_length_,time_step_);
        set_u();
        set_x();

    }



    Simulation::Simulation(double x_0 , double time_step,double sim_length )
    {
        x_0_        = x_0;               
        time_step_  = time_step;          
        sim_length_ = sim_length;       
        
        set_t(sim_length_,time_step_);
        set_u();
        set_x();

    }
    void Simulation::update(double x_0 , double time_step,double sim_length )
    {
        x_0_        = x_0;               
        time_step_  = time_step;          
        sim_length_ = sim_length;       
        
        set_t(sim_length_,time_step_);
        set_u();
        set_x();
    }

    void Simulation::reset()
    {
        x_0_        = 0;               
        time_step_  = 1;          
        sim_length_ = 10;       
        
        set_t(sim_length_,time_step_);
        set_u();
        set_x();

    }
    void Simulation::run(std::string filename)
    {
        saveData( filename);

    }
    

    /**
     * @brief Save simulation results to a CSV file.
     *
     * Writes the simulation time vector, input vector, and
     * state response vector to a comma-separated value (CSV)
     * file suitable for analysis in spreadsheet software,
     * MATLAB, Python, or other post-processing tools.
     *
     * The generated file contains the following columns:
     *
     *      t      - Simulation time vector.
     *      U[t]   - Input signal.
     *      x[t]   - System response.
     *
     * @param filename Base name of the output file. The
     *                 ".csv" extension is appended automatically.
     *
     * @note Existing files with the same name will be overwritten.
     */
    void Simulation::saveData(std::string filename)
    {
        filename += ".csv"; 
    std::ofstream outputFile(filename);

    if (!outputFile.is_open()) {
        std::cerr << "Error: Could not create or open the file!" << std::endl;
        return ; 
    }

    outputFile << "t" << ',' << "U[t]" << ',' << "x[t]" "\n";
    for ( int i =0; i < n_; i++)
    {
        outputFile << t_.at(i) << ',' <<  u_.at(i) << ',' << x_.at(i)  << "\n";
    }

    outputFile.close();

    std::cout << "File written successfully." << std::endl;
    }

    void Simulation::set_u()
    {
        u_.assign(n_, 0.0);
    };

    
    void Simulation::set_u(const std::vector <double>& input_signal)
    {
        if(input_signal.size() != n_)
        {
            cout << "input is of different size then simulation";
        }
        u_ = input_signal;
    };

    void Simulation::set_t(double simulation_length, double sim_step)
    {
       sim_length_ = simulation_length;
       time_step_  = sim_step;
       n_ =  ( static_cast<int>(sim_length_ / time_step_ )) + 1;
       t_.assign(n_,0.0);

       for ( int i = 0; i < n_; i++) 
        {
            t_[i] +=  time_step_;
        }      
    }


    void Simulation::set_x()
    {
        
        x_.resize(n_,0);
        x_.at(0) = x_0_; 

        for(int i = 1 ; i < n_; i++)
        {
            x_.at(i) = (time_step_* u_.at(i) + x_.at(i-1)) / ( 1 + ( 2 * time_step_)); 
        }
        
    }

    const std::vector <double>& Simulation::read_t()
    {
        return t_;
    }
    
    const std::vector <double>&  Simulation::read_u()
    {
        return u_;
    }
    const std::vector <double>&  Simulation::read_x()
    {
        return x_;
    }


    int Simulation::elements()
    {
        return n_;
    }

    int Simulation::calc_time(double time_to_index)
    {
        int idx = 0;
        
        if( time_to_index < sim_length_ && time_to_index != 0)
        {
            int tryme = static_cast<int>(time_to_index / time_step_ );
            if ( t_.at(tryme) == time_to_index)
            idx = tryme;
        }
        else 
            idx = -1;
        
        return idx;

    }

    double Simulation::read_time_step()
    {
        return time_step_;
    }