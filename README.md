

# README

this consist of three layers a  TUI frontend a wave generator middle layer and the simulation backend

We are adding content to the readme and 
creating a new branch from main 

## TUI 
---
- the TUI will take prompt the user for input from a discrete set of   acctions.
- top level will give the user the following prompts 
    - the user to load a prevous run simulation
    - start a new run 
    - exit

---
Ter

make a menu first in terminal using printout statements

select type of input 
options
1. step
2. sine 
3. pulse 

enter prompt 1, 2 or 3 

goal is to create the logc and data structure that will simulate this 

declare input variable 

outer menu menu loop that switch driven only accept integer input
for case 1,2,3 
could use enum type

given the selection it will populate input variable 
then after that we will have a constructor for the simulation class
and that constructor will accept as its input defined input variable 

then we run simulation 

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

    
    

