# Infectious Disease Simulator

### About My Final Project
My final project is an infectious disease simulator. With this
application, users can simulate an outbreak of a disease on a given
population. Available to view to the user is a container holding
particles that represent a population, a histogram visualizing
the health status of the population over time, and more.

In this simulation, there are four different health statuses that an
individual in the population can have: susceptible, symptomatic,
asymptomatic, or removed. There are several factors that affect the
spread of the disease, which will be discussed later.

**This application also supports user interaction.** Users have the
option to adjust several values and in turn change how an outbreak
is simulated. The values that users are allowed to adjust include...
- Whether the population gets quarantined if an individual's health
status is symptomatic
- The exposure time of a susceptible individual to become infected
(i.e. symptomatic or asymptomatic)
- The infected time of an infected individual to become removed
- The percentage of the population performing social distance
- The infection radius of an infected individual


### How to Set Up the Application
To build this application, I used Cinder. The following `#include`s
need to be incorporated in order to use Cinder:
- `#include "cinder/app/App.h"`
- `#include "cinder/app/RendererGl.h"`
- `#include "cinder/gl/gl.h"`

No other external libraries were used in this application.


### How to Use the Application
##### Adjusting features
Upon startup, the application window will look like the following:

**INSERT THE FINALIZED IMAGE OF THE WINDOW UPON STARTUP HERE**

At this moment, the user is allowed to make any adjustments to the
features listed on the screen. The user can press the following
keys to choose the feature they want to change:
- `q` to change whether individuals whose health status is
symptomatic gets quarantined
- `e` to change the exposure time
- `i` to change the infected time
- `d` to change the percentage of the population performing social
distance
- `r` to change the radius of infection

To actually change the value, the user can press either the arrow up
or arrow down keys.

##### Starting the outbreak
To start the outbreak, the user can press the `enter` key.

Note: once the outbreak begins, the user is not allowed to adjust
any of the features unless the user ends the outbreak. The user can
do this by pressing `clear`. This will take the user back to the
startup screen. Any values the user had changed prior to starting the
outbreak will stay the same until the user changes the values again
or the user quits the application, which will cause the values
to return to their default values.

##### Observing the outbreak
Once the outbreak has started, the user can watch the disease
spread throughout the population on the left half of the screen.
On the right half of the screen, the user can see a histogram that
visualizes the number of people belonging to each health status
in the duration of the outbreak. Statistics regarding the health
status of the population can also be viewed.

**INSERT THE FINALIZED IMAGE OF THE OUTBREAK W/O QUARANTINE HERE**

If the user has quarantine on, the screen will look like the
following:

**INSERT THE FINALIZED IMAGE OF THE OUTBREAK WITH QUARANTINE HERE**