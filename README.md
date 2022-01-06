# cpp_pong

building pong in c++ to learn sfml.

## 1/5/2022

i've sketched in the basic major components of the game, the paddles and game ball and their data and gotten them drawn to the window. i'm looking at this
as a sort of code kata since i've already built pong in java and the structure of the game and the various problems to be solved are already familiar.
i've spent most of my time researching various aspects of c++; the transition from java is not as smooth as i imagined. i've dabbled with the language before
but now that i'm actually digging into it and  using the OOP aspects of it is clear how different of a world it is. cpp is so powerful and has so many features it
can be a bit *overwhelming*. i'm attempting to get my head around the core functionality i need and simply learn to wield those features properly. sfml seems
straight-forward so far, though it is a challenge to change my thinking from the structure of java's gui apis.

## 1/6/2022

![demo of pong game progress](/demos/cpp_pong.gif)

i've implemented basic left-to-right collision detection. the game gets reset if the ball passes either paddle. the direction the ball goes in to start the game
is chosen by a crude random number contrivance based on the parity of a rand i stuck at the beginning of the game. cpp is starting to become a bit easier to
wield. my goal is to be as comfortable with it as i am with java. the greatest challenge will be in understanding cpp oop conventions in apis and libraries.
it seems that since cpp is not *oop to the core* like java being that it's pretty much c with classes glued on, it can be wild at times. however i totally get
why considering the power the language provides in terms of access to computer resources. i took the opportunity to understand basic cpp pass-by-reference in
implementing the update_edges() function. i'm not sure i'll get any closer to using pointers in this little program, but they aren't intimidating until you are
trying to understand someone else's code. i may practice pointers by digging a bit deeper into the sfml docs or some other code here on github. there was a cpp
implementation of the lempel ziv algorithm i wanted to try and comprehend a while back that i may check out now that cpp is coming into focus.

my next step with pong is to add north-south collision detection. i plan to add data to the paddle class to have the y_speed field of the game ball affected by
which section of the paddle the ball collides with. this will send the ball toward the top or bottom edge and bring the problem of north-south collision detection
into view. the dynamic paddle for some reason is sort of a hang up for me ever since i learned that it was an important part of the original pong arcade game. so
even though i could probably get away with just having the departure angle of the ball be random whenever it contacts a surface, i *have* to implement that feature.
i like the feature i think because it actually makes the game a game of skill in that you can be intentional as to your placement of the ball. i intend to keep adding
features to the game until i lose interest so maybe there could be power-ups? classes will start soon so i likely won't have time at that point though.
