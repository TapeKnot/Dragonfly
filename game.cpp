//
// game.cpp
//

// Engine includes.
#include "Managers/GameManager.h"
#include "Managers/LogManager.h"
#include "Managers/ResourceManager.h"
#include "Testing/Testing.h"

// Game includes.
#include "Testing/Saucer Shoot Dragonfly/GameStart.h"
#include "Testing/Saucer Shoot Dragonfly/Star.h"

// Function prototypes.
void loadResources(void);
void populateWorld(void);
 
int main(int argc, char *argv[]) {
  bool testingEnabled = false;      // true = Testing, false = launch Saucer Shoot

  // Start up game manager.
  if (GM.startUp())  {
    LM.writeLog("Error starting game manager!");
    GM.shutDown();
    return 0;
  }

  // Set flush of logfile during development (when done, make false).
  LM.setFlush(true);

  if (testingEnabled) {
      ts::Testing::testAll();
  }
  else {
        // Load game resources.
        loadResources();

        // Setup some objects.
        populateWorld();

        // Run game (this blocks until game loop is over).
        GM.run();
  }
 
  // Shut everything down.
  GM.shutDown();
}

// Load resources (sprites, sound effects, music).
void loadResources(void) {
    RM.loadSprite("Testing/Saucer Shoot Dragonfly/sprites-simple/saucer-spr.txt", "saucer");
    RM.loadSprite("Testing/Saucer Shoot Dragonfly/sprites-simple/ship-spr.txt", "ship");
    RM.loadSprite("Testing/Saucer Shoot Dragonfly/sprites-simple/bullet-spr.txt", "bullet");
    RM.loadSprite("Testing/Saucer Shoot Dragonfly/sprites-simple/explosion-spr.txt", "explosion");
    RM.loadSprite("Testing/Saucer Shoot Dragonfly/sprites-simple/gamestart-spr.txt", "gamestart");
    RM.loadSprite("Testing/Saucer Shoot Dragonfly/sprites-simple/gameover-spr.txt", "gameover");
    RM.loadSound("Testing/Saucer Shoot Dragonfly/sounds/fire.wav", "fire");
    RM.loadSound("Testing/Saucer Shoot Dragonfly/sounds/explode.wav", "explode");
    RM.loadSound("Testing/Saucer Shoot Dragonfly/sounds/nuke.wav", "nuke");
    RM.loadSound("Testing/Saucer Shoot Dragonfly/sounds/game-over.wav", "game over");
    RM.loadMusic("Testing/Saucer Shoot Dragonfly/sounds/start-music.wav", "start music");
}
 
// Populate world with some objects.
void populateWorld(void) {

  // Spawn some Stars.
  for (int i=0; i<16; i++) 
    new Star;
 
  // Create GameStart object.
  new GameStart();
}
