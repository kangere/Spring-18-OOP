Elite New Kind Abstractions

-	graphics	-alg_gfx.c , gfx.h  
		   		-class that will contain the graphics setup of the game and handle graphics routines

-	Entities	- This entities are tightly coupled to GUI
				- Need to separate them
				- planet.h, shipface.h, shipdata.h
				- vector.h/c - need to separate vector from matrix 
							 - decoupled elite.c/h from vector
				- Created a new vector class that encapsulates the functionality of the vector struct in the game.