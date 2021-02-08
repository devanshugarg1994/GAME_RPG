# GAME_RPG
A RPG game using SFML and C++. In doing so we are building our own Game Engine as well<br /><br />

### We will keep track of important commit and link here so that we can refer the changes done in the respected commit
<br />

[Game Class](../../tree/e0dd4603728a098a480f7d6e1a960996c10dbe7e)<br />
Game class is the main class which have render, draw and update calls of the game.
We ceate a single instance of the game class and this class will handle our game functionality
like update , render and draw call. <br /><br />
[Window config using a file](../../tree/4a0be8d80e745c689247367d74123dd50ec48900)<br />
We are Reading file `Config/window.init` to get window basic parameters like title, width,
height which are set on window object when initialized. <br /><br />
[State and GameState](../../tree/2af6e06ac5245df241b0aca5ac0d4a1627f54839)<br />
State is a abstact class which is inherit by other various component.
State is used to break our game into smaller and relatable components which make code
loosely coupled and reusable.<br />
Right know we have only Game state class which use `state class as abstact`,
in future we will add more.<br /><br />

[Supported Keys and Binding Keys](../../tree/98f5c5c15fc350e12e8da21325c066ea717e48af)<br />
We have add map in Game class which include supported keys in the map from `Config/supported_keys.init`.<br />
We pass this map as a pointer to state class which are pushed in `States` stack.
Using this we <i>bind</i> key which are supported with appropriate <b>Event string</b> from there keybinding file at
`Config\.`
<br /><br />

[Button Class](../../tree/61a2632b6951f0f3f48963eaa9d47453899bf35d)<br />
Added a buttton class with basic feature<br />
Button class contain diffrent state and it change when we clicked or hover it.<br />
Button contain a text parameter which is used to set a text on the button. Text is centrally aligned wr.t button.
<br /><br />
[State end functionality Refactor](../../tree/860d5c120d8759df8fd86a301243c2202020e851)<br />
Now we have `endState` declare and define at Absract State class.<br />
It's not declared virtual and should not overrided. Game loop check at every iteration for the quit value of the state
at the top of stack,
which can change in inhertited class accordingly using `endSate` of Base class `State`.
<br /><br />

[Basic Player Entity](../../tree/a28c5fe8d056412394cb2b026451edbc3db95e49)<br />
Start working on differnt Component. We have created basic `Player` class which extends `Entity`.
<br />
<br />
[MovementComponent](../../tree/dc3042a029180d27b756c070008ab53e555ce47d)<br />
Movement Component is like tarit which is added when required by the Entity.<br />
Right now it is tightly coupled with sprite which is used with entity and use `move` function of <b>SFML::Sprite</b> to
move.</br>
We calculate the direction the basis of key pressed and decide velocity on the basis of maxvelocity permitted and use
dragFactor as well to have a check on velocity.
<br />
<br />

[Button Class Update](../../tree/1fdc24edd74a3d03b2aaa2242ec45774d2aa1fc5)<br />
Button class updated with text Color change on the basis of Button state and size of text is also now userdefine.<br />
Still Button shape will act as hit area for the button.
```diff
-Bug: Text is not getting centrally align with the buttton for big text size especially vertically.
```

[AnimationComponent](../../tree/85dc3e3c9c36086f2c7408ec34467a08a6bc4914)<br />
We have created a animationComponent which is used to add multiple animation associated with entity.<br />
We can add multiple animation associate with entity which can be played according to the entity state and it's
interaction with the world.<br /><br />

[HitBoxComponent](../../tree/99bbc4eacf66fe957a1826c4d36da59a4147cb59)<br />
Hitbox is another compoenet added to entity which will be used when this entity is intreacted with other entity in the
scene<br /><br />

[Priority Animation ](../../tree/429019d652b72443c5125912dff154819146ee18)<br />
When multiple animation attach to player then if player state change then running animation was getting stop and remain
with a frame for some time and next animation start <br />
We have fixed both issue. Firstly now animation get change as soon as we change player state.. Secondly In CAse if we
want to change animtion if the current animation is run completely then we ca use `priority` paramter in play function
of `animationComponent` <br/><br/>
[Pause Menu](../../tree/9fb25b4d67fe9f01cd54496b38175464b4e95a4b)<br />
We have added the functionality of pause while we are in `GameState` i.e.. when we are playing the game.
[DropDownList GUI](../../tree/30e229ec51d19a584682740a72b05c9c7a9e40d8)<br />
We started to create our own GUI libray. We have ported `Button` class and created `DropDownList`GUi element as well which used button class to create a Drop Down List.