#include <Arduboy2.h>

#include "Bitmaps.h"

enum class GameState : unsigned char
{
    Title, Play, Pause, Win, GameOver
};

Arduboy2 ab;

GameState gameState = GameState::Play; // TODO: change to Title

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
 * Handles drawing overlay on the screen.
 */
void drawOverlay()
{
    byte radius = 5;
    byte widthOffset = 48;
    byte heightOffset = 12;
    
    ab.drawRoundRect(0, 0, WIDTH, HEIGHT, radius);

    // horizontal bar for weight indicator area
    ab.drawLine(0, HEIGHT - heightOffset, WIDTH, HEIGHT - heightOffset);

    // vertical bar for item info area
    ab.drawLine(WIDTH - widthOffset, 0, WIDTH - widthOffset, HEIGHT - heightOffset);
}

void gamePlay()
{
    drawOverlay();
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
