#include "input_waves.hpp"




/**
 * @brief Generate a discrete step input waveform for the simulation.
 *
 * Generates a step signal of the form:
 *
 *      u(t) = base_value                     for t < step_time
 *      u(t) = base_value + step_value       for t >= step_time
 *
 * The generated waveform is discretized according to the
 * simulation time vector contained within the Simulation object.
 * The resulting input signal is stored in the Simulation object
 * as the system input waveform.
 *
 * @param step_time   Time (seconds) at which the step transition
 *                    occurs.
 *
 * @param base_value  Initial value of the input signal prior to
 *                    the step transition.
 *
 * @param step_value  Magnitude of the step change. The final
 *                    signal value is:
 *
 *                        final_value = base_value + step_value
 *
 * @param sim         Simulation object containing the discretized
 *                    time information and receiving the generated
 *                    input waveform.
 *
 * @note The generated waveform length matches the number of
 *       simulation samples.
 *
 * @note Samples prior to the step index are assigned
 *       base_value.
 *
 * @note Samples at and after the step index are assigned
 *       final_value.
 */
void step(
            double step_time, 
            double base_value,
            double step_value,
            Simulation& sim 
          )
{
    int              n = sim.elements();
    double final_Value = base_value + step_value;
    int    step_index  = sim.calc_time(step_time);

    std::vector <double> input_wave(n, base_value);

    std::fill(input_wave.begin()+ step_index, input_wave.end(), final_Value);          
    sim.set_u(input_wave);
}


/**
 * @brief Generate a ramp input waveform for the simulation.
 *
 * Generates a ramp signal of the form:
 *
 *      u(t) = slope * t + base_value
 *
 * where t is each sample in the simulation time vector.
 *
 * The generated waveform is stored in the Simulation object
 * as the system input signal.
 *
 * @param slope        Ramp slope (units per second).
 * @param base_value   Initial value of the ramp at t = 0.
 * @param sim          Simulation object containing the time vector
 *                     and receiving the generated input waveform.
 *  
 */
void ramp(
            double slope,
            double base_value, 
            Simulation& sim 
          )
{
    
    std::vector <double> input_wave = sim.read_t();

    for ( auto& t : input_wave) 
    {
        t = ((t * slope) + base_value);
    }      
        
    sim.set_u(input_wave);
}


/**
 * @brief Generate a periodic square-wave input signal for the simulation.
 *
 * Generates a discrete square waveform oscillating between
 * base_value and peak_value. The waveform remains at
 * peak_value for a fraction of the period specified by
 * duty_cycle and remains at base_value for the remainder
 * of the cycle.
 *
 * The generated signal has the following form:
 *
 *      peak_value  ┌───────┐       ┌───────┐
 *                  │       │       │       │
 *                  │       │       │       │
 *      base_value ─┘       └───────┘       └───────
 *
 * The waveform repeats every period seconds.
 *
 * The duty cycle is specified as a fraction of the period:
 *
 *      duty_cycle = 0.50  -> 50% ON time
 *      duty_cycle = 0.25  -> 25% ON time
 *      duty_cycle = 0.75  -> 75% ON time
 *
 * The requested period and ON time are converted to an
 * integer number of simulation samples using
 * Simulation::calc_time().
 *
 * @param base_value  Minimum value of the square waveform.
 *                    This value is present during the OFF
 *                    portion of each cycle.
 *
 * @param peak_value  Maximum value of the square waveform.
 *                    This value is present during the ON
 *                    portion of each cycle.
 *
 * @param duty_cycle  Fraction of each period during which
 *                    the waveform remains at peak_value.
 *                    Valid range is [0.0, 1.0].
 *
 * @param period      Desired waveform period in seconds.
 *
 * @param sim         Simulation object containing the
 *                    discretized simulation information and
 *                    receiving the generated input waveform.
 *
 * @note The generated input vector length matches the number
 *       of simulation samples.
 *
 * @note The waveform is generated in the discrete-time domain.
 *       Therefore, the actual simulated period and duty cycle
 *       are constrained by the simulation time step.
 *
 * @note The generated waveform is stored in the Simulation
 *       object via Simulation::set_u().
 */
void square(
             double base_value,
             double peak_value,
             double duty_cycle,
             double period,
             Simulation& sim 
            )
{
    
    int n = sim.elements();
    int period_in_samples = sim.calc_time(period);
    int on_time  = sim.calc_time(period*duty_cycle); // this will be 
    int cycle;

    std::vector <double> input_wave(n, base_value);  

    for (int i = 0; i < n; i++)
    {
        cycle = i % period_in_samples;

        if(cycle < on_time)
        {
            input_wave[i] = peak_value;
        }
        else
        {
            input_wave[i] = base_value;
        }
    }
    

    sim.set_u(input_wave);

}


/**
 * @brief Generate a periodic sawtooth input signal for the simulation.
 *
 * Generates a discrete sawtooth waveform that ramps linearly from
 * base_value to peak_value over one period and then immediately
 * resets to base_value at the start of the next cycle.
 *
 * The generated signal has the following form:
 *
 *      peak_value
 *           /|    /|
 *          / |   / |
 *         /  |  /  |
 *        /   | /   |
 *       /    |/    |
 *      base_value
 *
 * The waveform repeats every period in seconds.
 *
 * The requested period is converted to an integer number of
 * simulation samples using Simulation::calc_time().
 *
 * @param base_value  Minimum value of the sawtooth waveform.
 *                    This value occurs at the beginning of each cycle.
 *
 * @param peak_value  Maximum value reached by the waveform immediately
 *                    before the signal resets.
 *
 * @param period      Desired waveform period in seconds.
 *
 * @param sim         Simulation object containing the discretized
 *                    simulation information and receiving the
 *                    generated input waveform.
 *
 * @note The generated input vector length matches the number
 *       of simulation samples.
 *
 * @note The waveform is generated in the discrete-time domain.
 *       Therefore, the actual simulated period is constrained by
 *       the simulation time step.
 *
 * @note The generated waveform is stored in the Simulation object
 *       via Simulation::set_u().
 */
void sawtooth(
                double base_value,
                double peak_value,
                double period,
                Simulation& sim 
             )
{
    int n = sim.elements();
    int period_in_samples = sim.calc_time(period);
    int cycle;  

    double amplitude = peak_value - base_value;
    double slope     = amplitude / period_in_samples;
    
    std::vector <double> input_wave(n, base_value);  
    
    
    for (int i = 0; i < n; i++)
    {
        cycle = i % period_in_samples;
        input_wave[i] = base_value + slope * (cycle);
    }
    
    sim.set_u(input_wave);

}


/**
 * @brief Generate a periodic triangle-wave input signal for the simulation.
 *
 * Generates a discrete triangle waveform oscillating between
 * base_value and peak_value. The waveform is periodic and is
 * discretized according to the simulation time step already
 * configured within the Simulation object.
 *
 * The generated signal has the following form:
 *
 *      Rising segment:
 *
 *          base_value  ---> peak_value
 *
 *      Falling segment:
 *
 *          peak_value ---> base_value
 *
 * The waveform repeats every period seconds.
 *
 * The peak amplitude remains constant regardless of the selected
 * period. Changing the period changes only the rate at which the
 * waveform rises and falls.
 *
 * The requested period is converted to an integer number of
 * simulation samples using Simulation::calc_time().
 *
 * @param base_value  Minimum value of the triangle waveform.
 *                    This value occurs at the beginning of each cycle.
 *
 * @param peak_value  Maximum value reached by the waveform at the
 *                    midpoint of each cycle.
 *
 * @param period      Desired waveform period in seconds.
 *
 * @param sim         Simulation object containing the discretized
 *                    simulation information and receiving the
 *                    generated input waveform.
 *
 * @throws std::invalid_argument if the requested period is smaller
 *         than two simulation samples.
 *
 * @note The generated input vector length matches the number of
 *       simulation samples.
 *
 * @note The waveform is generated in the discrete-time domain.
 *       Therefore, the actual simulated period is constrained by
 *       the simulation time step.
 *
 * @note The generated waveform is stored in the Simulation object
 *       via Simulation::set_u().
 */
void triangle( 
                double base_value,
                double peak_value,
                double period,
                Simulation& sim 
              )
{

    int n = sim.elements();
    int period_in_samples = sim.calc_time(period);
    int half_period       =  period_in_samples/ 2;
    int cycle;  

    double amplitude = peak_value - base_value;
    double slope     = amplitude / half_period;
    
    std::vector <double> input_wave(n, base_value);  
    
    for (int i = 0; i < n; i++)
    {
        cycle = i % period_in_samples;

        if(cycle < half_period)
        {
            input_wave[i] = base_value + slope * (cycle);
        }
        else
        {
            input_wave[i] = peak_value - slope * (cycle-half_period);
        }
    }
    
    sim.set_u(input_wave);
}