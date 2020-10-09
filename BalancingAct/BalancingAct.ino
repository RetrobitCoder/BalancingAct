#include <Arduboy2.h>

#include "Bitmaps.h"
#include "Levels.h"

enum class GameState : unsigned char
{
    Title, Play, Pause, Win, GameOver
};

Arduboy2 ab;

GameState gameState = GameState::Play; //TODO: change to Title

//screen offsets for dividing up the screen into different sections
const byte WIDTH_OFFSET = 48;
const byte HEIGHT_OFFSET = 12;

byte currentObjectIndex = 0; //current index of the object falling
byte levelIndex = 0; //current level number, used to get objects out of levels

void setup()
{
    ab.begin();
    ab.clear();

    ab.drawCompressed(0, 0, title_card);

    ab.display();
    ab.delayShort(3000);
}

/***** Start Title state functions *****/

/***** End Title state functions *****/

/***** Start Play state functions *****/

/**
    Handles drawing the balance meter
*/
void drawBalanceMeter()
{
    //draw player icon
    const byte CENTER_OFFSET = 8; //TODO probably want to replace with player icon sprite showing frustration with imbalance
    ab.drawRect(WIDTH / 2 - CENTER_OFFSET / 2, HEIGHT - CENTER_OFFSET - 2, CENTER_OFFSET, CENTER_OFFSET);

    //draw meter icons
    //TODO add icons to draw, need a way to know what the balance is, maybe keep track of a weight for left and right side and draw the number of icons based on that

    //draw dead zones, area where once the meter reaches causes a game over
    //TODO draw dead zone icons
    ab.drawCircle(5, HEIGHT - CENTER_OFFSET + 1, 4);
    ab.drawCircle(WIDTH - 5, HEIGHT - CENTER_OFFSET + 1, 4);
}

/**
 * Handles drawing all objects that are currently on the screen (includes ones already placed)
 */
void drawObjects()
{
  for(byte i = 0; i <= currentObjectIndex; i++)
  {
    ab.drawRect(levels[levelIndex][i].getX(), levels[levelIndex][i].getY(), 8, 8); //TODO draw object sprites
  }
}

/**
    Handles dipslaying object info
*/
void drawObjectInfo()
{
    ab.setCursor(WIDTH / 2 + 2, 4);
    ab.print(levels[0][1].getX()); //TODO display current object's info, and maybe what next object is
}

/**
    Handles drawing overlay on the screen.
*/
void drawOverlay()
{
    const byte RADIUS = 5;

    ab.drawRoundRect(0, 0, WIDTH, HEIGHT, RADIUS);

    //horizontal bar for weight indicator area
    ab.drawLine(0, HEIGHT - HEIGHT_OFFSET, WIDTH, HEIGHT - HEIGHT_OFFSET);

    //vertical bar for item info area
    ab.drawLine(WIDTH - WIDTH_OFFSET, 0, WIDTH - WIDTH_OFFSET, HEIGHT - HEIGHT_OFFSET);
}

/**
    Handles drawing the player and platform where objects will land on
*/
void drawPlayer()
{
    //draw player
    const byte PLAYER_OFFSET = 8; //TODO probably want to replace once player sprite is made, maybe store in bitmaps
    ab.drawRect((WIDTH - WIDTH_OFFSET) / 2 - PLAYER_OFFSET / 2, HEIGHT - HEIGHT_OFFSET - PLAYER_OFFSET, PLAYER_OFFSET, PLAYER_OFFSET);

    //draw object platform
    ab.drawLine(4, HEIGHT - HEIGHT_OFFSET - PLAYER_OFFSET - 1, WIDTH - WIDTH_OFFSET - 4, HEIGHT - HEIGHT_OFFSET - PLAYER_OFFSET - 1); //TODO make a rect object with the same info for object collision
}

void gamePlay()
{
    drawBalanceMeter();
    drawObjects();
    drawObjectInfo();
    drawOverlay();
    drawPlayer();

    levels[levelIndex][currentObjectIndex].updateObject();

    //TODO update objects list in a level
    //TODO calculate balance
    //TODO draw objects
    //TODO display object info
    //TODO object collisions
}

/***** End Play state functions *****/

/***** Start Pause state functions *****/

/***** End Pause state functions *****/

/***** Start Win state functions *****/

/***** End Win state functions *****/

/***** Start GameOver state functions *****/

/***** End GameOver state functions *****/

void loop()
{
    if(!ab.nextFrame()) return;

    ab.pollButtons();

    ab.clear();

    switch(gameState)
    {
        case GameState::Title:
            break;
        case GameState::Play:
            gamePlay();
            break;
        case GameState::Pause:
            break;
        case GameState::Win:
            break;
        case GameState::GameOver:
            break;
    }

    ab.display();
}
