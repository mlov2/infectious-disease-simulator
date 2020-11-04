# Final Project Proposal
A C++ application I am interested in designing for my final
project is an infectious disease simulator.  Given that we
are currently in a pandemic, I thought it would be cool to
create an application that models what we are going through.
I was also inspired by the video created by 3Blue1Brown that
talked about simulating an epidemic.  Mainly, I will focus
on simulating COVID-19 infections since it is the cause of
our current pandemic.

A rough timeline of what I hope to accomplish:
* Week 1:
    * Refactor the ideal gas simulation assignment to be used
    to simulate the spread of an infectious disease
        * Delete unnecessary code from Ideal Gas assignment
        * Adjust Cinder code/UI
            * Make particle size smaller
            * Slow down particle velocities
            * Color particles to represent a person who is
            susceptible, infectious, and removed
            * Have a timer visible to show the amount of time
            elapsed since the start of the outbreak
            * Have the number of people in each category visible
            (i.e. the number of people who are susceptible,
            infectious, and removed)
            * Adjust histogram to show people who are susceptible,
            infectious, and removed
            * Create a condition that will represent exposure time
    * Create data structures that will hold for each particle:
        * The category to which the particle/person falls under
        (susceptible, infectious, removed)
        * Running count of exposure time
    * Have variables to hold...
        * Exposure time
        * Probability of infection
        * Duration of illness
        * The position of every particle falling under a certain
        category (i.e. all particles that are susceptible in one
        data structure, etc)
* Week 2:
    * Incorporate different human behaviors (part 1):
        * Putting those with symptoms in quarantine
        * Taking into account asymptomatic individuals
    * Complete READ.ME
* Week 3:
    * Incorporate different human behaviors (part 2):
        * Moving to a central location
        * Social distancing
    * Allow for adjustment of features from sketchpad (i.e. amount
    of social distancing, exposure time, probability of infection)
    * Complete READ.ME
    
If I finish early and have extra time, I hope to also model other
infectious diseases, such as measles or the flu.  I could also allow
the user to save the results of a simulation to a file, which could
include details such as the number of people susceptible, infected,
and removed at a certain period of time given a certain set of
conditions.