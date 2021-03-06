#include <Arduboy2.h>
#include <ATMlib.h>

#include "Bitmaps.h"
#include "Effects.h"
#include "Levels.h"
#include "Songs.h"

enum class GameState : unsigned char
{
    Title, Play, Pause, Win, GameOver
};

Arduboy2 arduboy;
ATMsynth atm;

//game info
GameState gameState = GameState::Title;

//screen offsets for dividing up the screen into different sections
const byte HEIGHT_OFFSET = 12;

const byte PLAYER_OFFSET = 8;

//platform for objects to fall on
const byte PLATFORM_X = 4;
const byte PLATFORM_Y = HEIGHT - HEIGHT_OFFSET - PLAYER_OFFSET - 1;

//level info
byte currentObjectIndex = 0; //current index of the object falling
byte levelIndex = 0; //current level number, used to get objects out of levels

//game info
const int MAX_WEIGHT_PER_SIDE = 200;


void setup()
{
    arduboy.begin();

    Arduboy2::audio.on();

    Arduboy2::clear();

    Arduboy2::drawCompressed(0, 0, logo_card);

    Arduboy2::display(CLEAR_BUFFER);

    Arduboy2::delayShort(3000);
}

/***** Start Title state functions *****/

void drawTitleScreen()
{
    Arduboy2::drawCompressed(0, 0, title);

    Arduboy2::setCursor(6, HEIGHT - 15);
    arduboy.print("Press A");
}

/**
    Title state function
*/
void gameTitle()
{
    drawTitleScreen();

    static bool playedTune = false;

    if(!playedTune)
    {
        atm.play(opening_tune);

        playedTune = true;
    }

    if(Arduboy2::justPressed(A_BUTTON) || Arduboy2::justPressed(B_BUTTON))
    {
        gameState = GameState::Play;
    }
}
/***** End Title state functions *****/

byte getObjWidth(const Object& obj)
{
    switch(obj.getIndex())
    {
        case 0:
            return box[0];
            break;
        case 1:
            return elephant[0];
            break;
        case 2:
            return luggage[0];
            break;
        case 3:
            return weight[0];
            break;
    }

    return 0;
}

byte getObjHeight(const Object& obj)
{
    // + 1 is to allow for the full object to be drawn and avoid bottom and top lines of objects overlapping
    switch(obj.getIndex())
    {
        case 0:
            return box[1] + 1;
            break;
        case 1:
            return elephant[1] + 1;
            break;
        case 2:
            return luggage[1] + 1;
            break;
        case 3:
            return weight[1] + 1;
            break;
    }

    return 0;
}

/***** Start Play state functions *****/

/**
    Handles figure out the weight of a side
*/
int calculateWeight(const Rect& side)
{
    int weightTotal = 0;

    for(size_t i = 0; i < currentObjectIndex; i++)
    {
        const byte objWidth = getObjWidth(levels[levelIndex][i]);
        const byte objHeight = getObjHeight(levels[levelIndex][i]);

        if(Arduboy2::collide(side, Rect(levels[levelIndex][i].getX(), levels[levelIndex][i].getY(), objWidth, objHeight)))
        {
            weightTotal += levels[levelIndex][i].getWeight();
        }
    }

    return weightTotal;
}

/**
    Handles checking if the current object collided with the platform or another object
*/
void collisionCheck()
{
    bool objectCollided = false;

    const Rect PLATFORM = Rect(PLATFORM_X, PLATFORM_Y, WIDTH - WIDTH_OFFSET - 4, 8);

    const byte curObjWidth = getObjWidth(levels[levelIndex][currentObjectIndex]);
    const byte curObjHeight = getObjHeight(levels[levelIndex][currentObjectIndex]);

    for(size_t i = 0; i < currentObjectIndex; i++)
    {
        const byte objWidth = getObjWidth(levels[levelIndex][i]);
        const byte objHeight = getObjHeight(levels[levelIndex][i]);

        // check collision from bottom side
        if(Arduboy2::collide(Rect(levels[levelIndex][currentObjectIndex].getX(), levels[levelIndex][currentObjectIndex].getY(), curObjWidth, curObjHeight),
                             Rect(levels[levelIndex][i].getX() + 1, levels[levelIndex][i].getY(), objWidth, 1)))
        {
            objectCollided = true;
            break;
        }
        // check collision from right side
        else if(Arduboy2::collide(Rect(levels[levelIndex][currentObjectIndex].getX(), levels[levelIndex][currentObjectIndex].getY(), curObjWidth, curObjHeight),
                                  Rect(levels[levelIndex][i].getX(), levels[levelIndex][i].getY(), 1, objHeight)))
        {
            levels[levelIndex][currentObjectIndex].updateObject(-1, false);
        }
        // check collision from left side
        else if(Arduboy2::collide(Rect(levels[levelIndex][currentObjectIndex].getX(), levels[levelIndex][currentObjectIndex].getY(), curObjWidth, curObjHeight),
                                  Rect(levels[levelIndex][i].getX() + objWidth, levels[levelIndex][i].getY(), 1, objHeight)))
        {
            levels[levelIndex][currentObjectIndex].updateObject(1, false);
        }
    }

    if(!objectCollided)
    {
        if(Arduboy2::collide(PLATFORM, Rect(levels[levelIndex][currentObjectIndex].getX(), levels[levelIndex][currentObjectIndex].getY(), curObjWidth, curObjHeight)))
        {
            objectCollided = true;
        }
    }

    if(objectCollided)
    {
        currentObjectIndex++;
        atm.play(crash);
    }
}

/**
    Checks to make sure spot of current object's spawn point is free from obstacles
    If not will try another spot at the top, unless there are no spots to place
    @return true if spawn is ok, false otherwise
*/
bool checkSpawn()
{
    bool objectCollided = false;

    const byte curObjWidth = getObjWidth(levels[levelIndex][currentObjectIndex]);
    const byte curObjHeight = getObjHeight(levels[levelIndex][currentObjectIndex]);

    static byte newX = 1;

    for(size_t i = 0; i < currentObjectIndex; i++)
    {
        const byte objWidth = getObjWidth(levels[levelIndex][i]);
        const byte objHeight = getObjHeight(levels[levelIndex][i]);

        // check collision at spawn
        if(Arduboy2::collide(Rect(levels[levelIndex][currentObjectIndex].getX(), levels[levelIndex][currentObjectIndex].getY(), curObjWidth, curObjHeight),
                             Rect(levels[levelIndex][i].getX() + 1, levels[levelIndex][i].getY(), objWidth, objHeight)))
        {
            objectCollided = true;
            break;
        }
    }

    if(objectCollided)
    {
        levels[levelIndex][currentObjectIndex].setX(newX);
        newX++;
        return checkSpawn();
    }
    else if(newX + curObjWidth >= (WIDTH - WIDTH_OFFSET))
    {
        return false;
    }
    else
    {
        return true;
    }
}

/**
    Handles drawing the balance meter
*/
void drawBalanceMeter(const int& platformWeight)
{
    //draw player icon
    const byte CENTER_OFFSET = balance_meter_icons[0];
    byte frame = 0;

    if(platformWeight < 0) frame = 1;
    else if(platformWeight > 0) frame = 2;

    Sprites::drawSelfMasked((WIDTH / 2) - (CENTER_OFFSET / 2), HEIGHT - CENTER_OFFSET - 2, balance_meter_icons, frame);

    //draw meter
    const byte MAX_WEIGHT_FILL = (WIDTH / 2) - (CENTER_OFFSET / 2);

    const int WEIGHT_FILL = (MAX_WEIGHT_FILL * platformWeight) / MAX_WEIGHT_PER_SIDE;

    if(platformWeight < 0) //left
    {
        Arduboy2::fillRect(MAX_WEIGHT_FILL + WEIGHT_FILL, HEIGHT - HEIGHT_OFFSET + 1, (-1 * WEIGHT_FILL), HEIGHT - HEIGHT_OFFSET + 1);
    }
    else if(platformWeight > 0) //right
    {
        Arduboy2::fillRect(MAX_WEIGHT_FILL + CENTER_OFFSET, HEIGHT - HEIGHT_OFFSET + 1, WEIGHT_FILL, HEIGHT - HEIGHT_OFFSET + 1);
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

    Arduboy2::setCursor(WIDTH - WIDTH_OFFSET + 2, 10);

    levels[levelIndex][currentObjectIndex].printTo(arduboy);

    if(currentObjectIndex + 1 < MAX_NUM_OBJS)
    {
        size_t x = WIDTH - WIDTH_OFFSET + 2;
        size_t y = Arduboy2::getCursorY() + 8;

        Arduboy2::setCursor(x, y);

        arduboy.print("Next");

        y += 8;

        Arduboy2::setCursor(x, y);

        arduboy.print(levels[levelIndex][currentObjectIndex + 1].getName());
    }
}

/**
    Handles drawing all objects that are currently on the screen (includes ones already placed)
*/
void drawObjects()
{
    byte lastObjIndex = currentObjectIndex;

    if(lastObjIndex == MAX_NUM_OBJS) lastObjIndex--;

    for(size_t i = 0; i <= lastObjIndex; i++)
    {
        const byte x = levels[levelIndex][i].getX();
        const byte y = levels[levelIndex][i].getY();

        switch(levels[levelIndex][i].getIndex())
        {
            case 0:
                Sprites::drawSelfMasked(x, y, box, 0);
                break;
            case 1:
                Sprites::drawSelfMasked(x, y, elephant, 0);
                break;
            case 2:
                Sprites::drawSelfMasked(x, y, luggage, 0);
                break;
            case 3:
                Sprites::drawSelfMasked(x, y, weight, 0);
                break;
        }
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
    Arduboy2::drawCompressed((WIDTH - WIDTH_OFFSET) / 2 - PLAYER_OFFSET / 2, HEIGHT - HEIGHT_OFFSET - PLAYER_OFFSET, clown);

    //draw object platform
    Arduboy2::drawLine(PLATFORM_X, PLATFORM_Y, WIDTH - WIDTH_OFFSET - 4, HEIGHT - HEIGHT_OFFSET - PLAYER_OFFSET - 1);
}

/**
    Handles getting user input to move object
*/
void moveObject()
{
    float x = levels[levelIndex][currentObjectIndex].getX();
    float lateralMove = 0;

    if(Arduboy2::pressed(LEFT_BUTTON) && x != 1) lateralMove = -0.5;
    else if(Arduboy2::pressed(RIGHT_BUTTON) && x != WIDTH - WIDTH_OFFSET - getObjWidth(levels[levelIndex][currentObjectIndex])) lateralMove = 0.5;

    levels[levelIndex][currentObjectIndex].updateObject(lateralMove, false);
}

/**
    Play state function
*/
void gamePlay()
{
    if(!Arduboy2::justPressed(A_BUTTON) && !Arduboy2::justPressed(B_BUTTON))
    {
        //hit box to figure out how much the left and right side weigh on the platform
        const Rect LEFT_SIDE = Rect(0, 0, (WIDTH - WIDTH_OFFSET) / 2, HEIGHT - HEIGHT_OFFSET);
        const Rect RIGHT_SIDE = Rect((WIDTH - WIDTH_OFFSET) / 2, 0,  (WIDTH - WIDTH_OFFSET) / 2, HEIGHT - HEIGHT_OFFSET);

        drawOverlay();
        drawPlayer();
        drawObjects();

        int platformWeight = 0;


        if(currentObjectIndex < MAX_NUM_OBJS)
        {
            drawInfo();

            if(checkSpawn())
            {
                moveObject();

                if(Arduboy2::pressed(DOWN_BUTTON) || Arduboy2::pressed(UP_BUTTON)) levels[levelIndex][currentObjectIndex].updateObject(1, true);
                else levels[levelIndex][currentObjectIndex].updateObject();

                collisionCheck();

                platformWeight = calculateWeight(RIGHT_SIDE) - calculateWeight(LEFT_SIDE);

                drawBalanceMeter(platformWeight);

                if(platformWeight >= MAX_WEIGHT_PER_SIDE || (-1 * platformWeight) >= MAX_WEIGHT_PER_SIDE)
                {
                    gameState = GameState::GameOver;
                }
            }
            else
            {
              gameState = GameState::GameOver;
            }
        }
        else
        {
            //level is over move to next
            levelIndex++;
            currentObjectIndex = 0;

            //check for win when no more levels
            if(levelIndex == MAX_NUM_LVLS)
            {
                gameState = GameState::Win;
            }
        }
    }
    else
    {
        gameState = GameState::Pause;
    }
}

/***** End Play state functions *****/

/***** Start Pause state functions *****/

/**
    Handles drawing pause screen
*/
void drawPauseScreen()
{
    Arduboy2::drawCompressed(0, 0, pause_screen);

    Arduboy2::setCursor(WIDTH / 2 - (2 * 8), HEIGHT / 2);
    arduboy.print("Paused");
}

/**
    Pause state function
*/
void gamePause()
{
    drawPauseScreen();

    if(Arduboy2::justPressed(A_BUTTON) || Arduboy2::justPressed(B_BUTTON))
    {
        gameState = GameState::Play;
    }
}
/***** End Pause state functions *****/

/**
    Handles resetting the game after a game over or game win state
*/
void resetGame()
{
    for(size_t i = 0; i < MAX_NUM_LVLS; i++)
    {
        for(size_t j = 0; j < MAX_NUM_OBJS; j++)
        {
            levels[i][j].setX(START_X);
            levels[i][j].setY(START_Y);
        }
    }

    currentObjectIndex = 0;
    levelIndex = 0;
}

/***** Start Win state functions *****/

/**
    Handles drawing the win screen
*/
void drawWinScreen()
{
    Arduboy2::drawCompressed(0, 0, win);
}

/**
    Win state function
*/
void gameWin()
{
    drawWinScreen();

    static bool playedTune = false;

    if(!playedTune)
    {
        atm.play(win_tune);

        playedTune = true;
    }

    if(Arduboy2::justPressed(A_BUTTON))
    {
        gameState = GameState::Title;
        resetGame();
    }
}

/***** End Win state functions *****/

/***** Start GameOver state functions *****/

/**
    Handles drawing the lose screen
*/
void drawLoseScreen()
{
    Arduboy2::drawCompressed(0, 0, lose);
}

/**
    GameOver state function
*/
void gameOver()
{
    drawLoseScreen();

    static bool playedTune = false;

    if(!playedTune)
    {
        atm.play(lose_tune);

        playedTune = true;
    }

    if(Arduboy2::justPressed(A_BUTTON))
    {
        gameState = GameState::Title;
        resetGame();
    }
}
/***** End GameOver state functions *****/

void loop()
{
    if(Arduboy2::nextFrame())
    {
        Arduboy2::pollButtons();

        switch(gameState)
        {
            case GameState::Title:
                gameTitle();
                break;
            case GameState::Play:
                gamePlay();
                break;
            case GameState::Pause:
                gamePause();
                break;
            case GameState::Win:
                gameWin();
                break;
            case GameState::GameOver:
                gameOver();
                break;
        }

        Arduboy2::display(CLEAR_BUFFER);
    }
}
