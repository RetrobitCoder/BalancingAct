#include <Arduboy2.h>

#include "Bitmaps.h"
#include "Levels.h"

enum class GameState : unsigned char
{
    Title, Play, Pause, Win, GameOver
};

Arduboy2 arduboy;

GameState gameState = GameState::Play; //TODO: change to Title

byte currentObjectIndex = 0; //current index of the object falling
byte levelIndex = 0; //current level number, used to get objects out of levels

//screen offsets for dividing up the screen into different sections
const byte WIDTH_OFFSET = 48;
const byte HEIGHT_OFFSET = 12;

const byte PLAYER_OFFSET = 8; //TODO probably want to replace once player sprite is made, maybe store in bitmaps


//platform for objects to fall on
const byte PLATFORM_X = 4;
const byte PLATFORM_Y = HEIGHT - HEIGHT_OFFSET - PLAYER_OFFSET - 1;
const Rect PLATFORM = Rect(PLATFORM_X, PLATFORM_Y, WIDTH - WIDTH_OFFSET - 4, 8);

void setup()
{
    arduboy.begin();

    Arduboy2::clear();

    Arduboy2Base::drawCompressed(0, 0, title_card);

    Arduboy2::display(CLEAR_BUFFER);

    Arduboy2::delayShort(3000);
}

/***** Start Title state functions *****/
//TODO

/***** End Title state functions *****/

/***** Start Play state functions *****/

/**
    Handles checking if the current object collided with the platform or another object
*/
void collisionCheck()
{
    bool objectCollided = false;

    for(byte i = 0; i < currentObjectIndex; i++)
    {
        //TODO get width and height from sprite info
        if(Arduboy2::collide(Rect(levels[levelIndex][currentObjectIndex].getX(), levels[levelIndex][currentObjectIndex].getY(), 8, 8),
                             Rect(levels[levelIndex][i].getX(), levels[levelIndex][i].getY(), 8, 8)))
        {
            objectCollided = true;
            break;
        }
    }

    if(!objectCollided)
    {
        if(Arduboy2::collide(PLATFORM, Rect(levels[levelIndex][currentObjectIndex].getX(), levels[levelIndex][currentObjectIndex].getY(), 8, 8))) //TODO get width and height from sprite info
        {
            objectCollided = true;
        }
    }

    if(objectCollided) currentObjectIndex++;
}

/**
    Handles drawing the balance meter
*/
void drawBalanceMeter()
{
    //draw player icon
    const byte CENTER_OFFSET = 8; //TODO probably want to replace with player icon sprite showing frustration with imbalance
    Arduboy2::drawRect(WIDTH / 2 - CENTER_OFFSET / 2, HEIGHT - CENTER_OFFSET - 2, CENTER_OFFSET, CENTER_OFFSET);

    //draw meter icons
    //TODO add icons to draw, need a way to know what the balance is, maybe keep track of a weight for left and right side and draw the number of icons based on that

    //draw dead zones, area where once the meter reaches causes a game over
    //TODO draw dead zone icons
    Arduboy2::drawCircle(5, HEIGHT - CENTER_OFFSET + 1, 4);
    Arduboy2::drawCircle(WIDTH - 5, HEIGHT - CENTER_OFFSET + 1, 4);
}

/**
    Handles drawing all objects that are currently on the screen (includes ones already placed)
*/
void drawObjects()
{
    byte lastObjIndex = currentObjectIndex;

    if(lastObjIndex == MAX_NUM_OBJS) lastObjIndex--;

    for(byte i = 0; i <= lastObjIndex; i++)
    {
        Arduboy2::drawRect(levels[levelIndex][i].getX(), levels[levelIndex][i].getY(), 8, 8); //TODO draw object sprites
    }
}

/**
    Handles dipslaying object and level info
*/
void drawInfo()
{
    Arduboy2::setCursor(WIDTH - WIDTH_OFFSET + 2, 2);
    arduboy.print("LVL");
    Arduboy2::setCursor(WIDTH - WIDTH_OFFSET + 20, 2);
    arduboy.print(levelIndex);

    byte lastObjIndex = currentObjectIndex;

    if(lastObjIndex == MAX_NUM_OBJS) lastObjIndex--; //TODO maybe this kinda check should be moved to gamePlay?

    Arduboy2::setCursor(WIDTH - WIDTH_OFFSET + 2, 10);

    levels[levelIndex][lastObjIndex].printTo(arduboy);

    if(lastObjIndex + 1 < MAX_NUM_OBJS)
    {
        size_t x = WIDTH - WIDTH_OFFSET + 2;
        size_t y = Arduboy2::getCursorY() + 8;
        
        Arduboy2::setCursor(x, y);

        arduboy.print("Next");

        y += 8;

        Arduboy2::setCursor(x, y);

        arduboy.print(levels[levelIndex][lastObjIndex + 1].getName());
    }
}

/**
    Handles drawing overlay on the screen.
*/
void drawOverlay()
{
    const byte RADIUS = 5;

    Arduboy2::drawRoundRect(0, 0, WIDTH, HEIGHT, RADIUS);

    //horizontal bar for weight indicator area
    Arduboy2::drawLine(0, HEIGHT - HEIGHT_OFFSET, WIDTH, HEIGHT - HEIGHT_OFFSET);

    //vertical bar for item info area
    Arduboy2::drawLine(WIDTH - WIDTH_OFFSET, 0, WIDTH - WIDTH_OFFSET, HEIGHT - HEIGHT_OFFSET);
}

/**
    Handles drawing the player and platform where objects will land on
*/
void drawPlayer()
{
    //draw player
    Arduboy2::drawRect((WIDTH - WIDTH_OFFSET) / 2 - PLAYER_OFFSET / 2, HEIGHT - HEIGHT_OFFSET - PLAYER_OFFSET, PLAYER_OFFSET, PLAYER_OFFSET);

    //draw object platform
    Arduboy2::drawLine(4, HEIGHT - HEIGHT_OFFSET - PLAYER_OFFSET - 1, WIDTH - WIDTH_OFFSET - 4, HEIGHT - HEIGHT_OFFSET - PLAYER_OFFSET - 1); //TODO make a rect object with the same info for object collision
}

void gamePlay()
{
    drawBalanceMeter();
    drawObjects();
    drawInfo();
    drawOverlay();
    drawPlayer();

    if(currentObjectIndex < MAX_NUM_OBJS)
    {
        levels[levelIndex][currentObjectIndex].updateObject();

        collisionCheck();
    }
    else
    {
        //level is over move to next
        //levelIndex++; TODO uncomment when working on next level progression
        //currentObjectIndex = 0;

        //check for win when no more levels
        if(levelIndex == MAX_NUM_LVLS)
        {
            //gameState = GameState::Win; TODO uncomment when working on win condition
        }
    }

    //TODO update objects list in a level
    //TODO calculate balance
    //TODO button inputs
}

/***** End Play state functions *****/

/***** Start Pause state functions *****/
//TODO

/***** End Pause state functions *****/

/***** Start Win state functions *****/
//TODO

/***** End Win state functions *****/

/***** Start GameOver state functions *****/
//TODO

/***** End GameOver state functions *****/

void loop()
{
    if(Arduboy2::nextFrame())
    {
        Arduboy2::pollButtons();

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

        Arduboy2::display(CLEAR_BUFFER);
    }
}
