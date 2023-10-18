# Table tennis arcade game in an ARM based System-on-Chip
 Implement of a multi-player game (reproducing the behaviour of the classic  table tennis-themed arcade game, originally released in 1972 by Atari) using the LandTiger Emulator available on Keil uVision.
 
It is a multi-player version of the game where the player must not 
let the ball fall below the paddle. The bottom paddle is driven by the first player, and it can only 
move horizontally. 

The *first player* operates it through the **potentiometer** available in the LandTiger
board. On the contrary, the top paddle is driven by *the second player*. It is fully automatic and, when 
the play starts, it only moves horizontally at a constant speed. The choice on how fast the top paddle 
moves is left unconstrained.


**Other rules and constrains are on the file named "information"**
