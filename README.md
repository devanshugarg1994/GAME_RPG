# GAME_RPG
A RPG game using SFML and C++. In doing so we are building our own Game Engine as well<br/><br/>

### We will keep track of important commit and link here so that we can refer the changes done in the respected commit
<br/>

[Game Class](../../tree/e0dd4603728a098a480f7d6e1a960996c10dbe7e)<br/>
Game class is the main class which have render, draw and update calls of the game.
We ceate a single instance of the game class and this class will handle our game functionality 
like update , render and draw call.  <br/><br/>
[Window config using a file](../../tree/4a0be8d80e745c689247367d74123dd50ec48900)<br/>
We are Reading file `Config/window.init` to get window basic parameters like title, width,
height which are set on window object when initialized. <br/><br/>
[State and GameState](../../tree/2af6e06ac5245df241b0aca5ac0d4a1627f54839)<br/>
 State is a abstact class which is inherit by other various component.
 State is used to break our game into smaller and relatable components which make code 
 loosely coupled and reusable.<br/>
 Right know we have only Game state class which use `state class as abstact`,
 in future we will add more.<br/><br/>
 
[Supported Keys and Binding Keys](../../tree/98f5c5c15fc350e12e8da21325c066ea717e48af)<br/>
We have add map in Game class which include supported keys in the map from `Config/supported_keys.init`.<br/>
We pass this map as a pointer to state class which are pushed in `States` stack. 
Using this we <i>bind</i> key which are supported with appropriate <b>Event string</b> from there keybinding file at `Config\.`
<br/><br/>

[Button Class](../../tree/61a2632b6951f0f3f48963eaa9d47453899bf35d)<br/>
Added a buttton class with basic feature<br/>
Button class contain diffrent state and it change when we clicked or hover it.<br/>
Button contain a text parameter which is used to set a text on the button. Text is centrally aligned wr.t button.  
<br/><br/>
[State end functionality Refactor](../../tree/860d5c120d8759df8fd86a301243c2202020e851)<br/>\
Now we have `endState` decalre and define at Absract State class.<br/>
It's not decalred virtual and should not overrided. Game loop check at every iteration for the quit value of the state at the top of stack,
which can change in inhertited class  accordingly using `endSate` of Base class `State`.
<br/><br/>

