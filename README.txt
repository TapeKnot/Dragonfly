Developer: Benjamin Levy

Platform: Windows

Files: All files can be found in the source directory or the "Managers" and "Events" folders. The Testing files can be found in the "Testing" folder. The files "Testing.h" and "Testing.cpp" are used for system testing. Also included are the files for the game Saucer Shoot (an existing game pulled from the Dragonfly website), to be used for additional testing.

Code Structure: All automated testing code is contained within "Testing.h" and "Testing.cpp". The tests can be started from "game.cpp", which has the "main" function which begins testing by default. You can also change the Boolean "testingEnabled" to false to start up Saucer Shoot Dragonfly for additional manual testing.

How to Compile:
First, extract the contents of the zipped folder "SFML-3.0" to the same directory.

Then, open the project solution in Visual Studio and build the game. Run the game from Visual Studio (game.cpp will run the "main" function that begins testing).

Additional info on Dragonfly can be found on the engine's website:
https://dragonfly.wpi.edu/