// This is the main file for the game logic and function
//
//
#include "game.h"
#include "Grid.h"
#include "Map.h"
#include "Framework\console.h"
#include "Colours.h"
#include "Player.h"
#include "Money.h"
#include "GameObject.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>
#define BACKMATCHTEXT (BACKGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED)
#define WHITETEXT (FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED)

double  g_dElapsedTime;
double  g_pregameElapsedtime;
double  g_dDeltaTime;
SKeyEvent g_skKeyEvent[K_COUNT];
SMouseEvent g_mouseEvent;

// Game specific variables here
Map level_map;
Grid test_grid;
Player* myPlayer;
int points;
Money* moneyArr[3];
int totalItem;
SGameChar   g_sChar;
EGAMESTATES g_eGameState; // initial state

// Console object
Console g_Console(100, 22, "SP1Grp5_Timothy_Jeremy_Dennis_Aloysius");

//--------------------------------------------------------------
// Purpose  : Initialisation function
//            Initialize variables, allocate memory, load data from file, etc. 
//            This is called once before entering into your main loop
// Input    : void
// Output   : void
//--------------------------------------------------------------
void init( void )
{
    // Set precision for floating point output
    g_dElapsedTime = 0.0; 
    g_pregameElapsedtime = 0.0;
    points = 0;

    // sets the initial state for the game
    g_eGameState = S_SPLASHSCREEN;

    g_sChar.m_cLocation.X = g_Console.getConsoleSize().X / 2;
    g_sChar.m_cLocation.Y = g_Console.getConsoleSize().Y / 2;
    // sets the width, height and the font name to use in the console
    g_Console.setConsoleFont(0, 16, L"Consolas");

    // remember to set your keyboard handler, so that your functions can be notified of input events
    g_Console.setKeyboardHandler(keyboardHandler);
    g_Console.setMouseHandler(mouseHandler);

    // Implemented by denniswong10 (Create player)
    myPlayer = new Player;

    totalItem = Money::GetMoneyCount();
}

//--------------------------------------------------------------
// Purpose  : Reset before exiting the program
//            Do your clean up of memory here
//            This is called once just before the game exits
// Input    : Void
// Output   : void
//--------------------------------------------------------------
void shutdown( void )
{
    // Reset to white text on black background
    colour(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
    
    //delete variables ?? any??
    g_Console.clearBuffer();
}

//--------------------------------------------------------------
// Purpose  : Get all the console input events
//            This function sets up the keyboard and mouse input from the console.
//            We will need to reset all the keyboard status, because no events will be sent if no keys are pressed.
//
//            Remember to set the handlers for keyboard and mouse events.
//            The function prototype of the handler is a function that takes in a const reference to the event struct
//            and returns nothing. 
//            void pfKeyboardHandler(const KEY_EVENT_RECORD&);
//            void pfMouseHandlerconst MOUSE_EVENT_RECORD&);
// Input    : Void
// Output   : void
//--------------------------------------------------------------
void getInput( void )
{
    // resets all the keyboard events
    memset(g_skKeyEvent, 0, K_COUNT * sizeof(*g_skKeyEvent));
    // then call the console to detect input from user
    g_Console.readConsoleInput();    
}

//--------------------------------------------------------------
// Purpose  : This is the handler for the keyboard input. Whenever there is a keyboard event, this function will be called.
//            Ideally, you should pass the key event to a specific function to handle the event.
//            This is because in some states, some keys would be disabled. Hence, to reduce your code complexity, 
//            it would be wise to split your keyboard input handlers separately.
//            
//            The KEY_EVENT_RECORD struct has more attributes that you can use, if you are adventurous enough.
//
//            In this case, we are not handling any keyboard event in the Splashscreen state
//            
// Input    : const KEY_EVENT_RECORD& keyboardEvent - reference to a key event struct
// Output   : void
//--------------------------------------------------------------
void keyboardHandler(const KEY_EVENT_RECORD& keyboardEvent)
{    
    switch (g_eGameState)
    {
    case S_SPLASHSCREEN: // don't handle anything for the splash screen
        break;
    case S_GAME: gameplayKBHandler(keyboardEvent); // handle gameplay keyboard event 
        break;
    default: gameplayKBHandler(keyboardEvent);
        break;
    }
}

//--------------------------------------------------------------
// Purpose  : This is the handler for the mouse input. Whenever there is a mouse event, this function will be called.
//            Ideally, you should pass the key event to a specific function to handle the event.
//            This is because in some states, some keys would be disabled. Hence, to reduce your code complexity, 
//            it would be wise to split your keyboard input handlers separately.
//            
//            For the mouse event, if the mouse is not moved, no event will be sent, hence you should not reset the mouse status.
//            However, if the mouse goes out of the window, you would not be able to know either. 
//
//            The MOUSE_EVENT_RECORD struct has more attributes that you can use, if you are adventurous enough.
//
//            In this case, we are not handling any mouse event in the Splashscreen state
//            
// Input    : const MOUSE_EVENT_RECORD& mouseEvent - reference to a mouse event struct
// Output   : void
//--------------------------------------------------------------
void mouseHandler(const MOUSE_EVENT_RECORD& mouseEvent)
{    
    switch (g_eGameState)
    {
    case S_SPLASHSCREEN: gameplayMouseHandler(mouseEvent);
        break;
    case S_GAME: gameplayMouseHandler(mouseEvent); // handle gameplay mouse event
        break;
    }
}

//--------------------------------------------------------------
// Purpose  : This is the keyboard handler in the game state. Whenever there is a keyboard event in the game state, this function will be called.
//            
//            Add more keys to the enum in game.h if you need to detect more keys
//            To get other VK key defines, right click on the VK define (e.g. VK_UP) and choose "Go To Definition" 
//            For Alphanumeric keys, the values are their ascii values (uppercase).
// Input    : const KEY_EVENT_RECORD& keyboardEvent
// Output   : void
//--------------------------------------------------------------
void gameplayKBHandler(const KEY_EVENT_RECORD& keyboardEvent)
{
    // here, we map the key to our enums
    EKEYS key = K_COUNT;
    switch (keyboardEvent.wVirtualKeyCode)
    {
    case VK_UP: key = K_UP; break;
    case VK_DOWN: key = K_DOWN; break;
    case VK_LEFT: key = K_LEFT; break; 
    case VK_RIGHT: key = K_RIGHT; break; 
    case VK_SPACE: key = K_SPACE; break;
    case VK_ESCAPE: key = K_ESCAPE; break; 
    }
    // a key pressed event would be one with bKeyDown == true
    // a key released event would be one with bKeyDown == false
    // if no key is pressed, no event would be fired.
    // so we are tracking if a key is either pressed, or released
    if (key != K_COUNT)
    {
        g_skKeyEvent[key].keyDown = keyboardEvent.bKeyDown;
        g_skKeyEvent[key].keyReleased = !keyboardEvent.bKeyDown;
    }    
}

//--------------------------------------------------------------
// Purpose  : This is the mouse handler in the game state. Whenever there is a mouse event in the game state, this function will be called.
//            
//            If mouse clicks are detected, the corresponding bit for that mouse button will be set.
//            mouse wheel, 
//            
// Input    : const KEY_EVENT_RECORD& keyboardEvent
// Output   : void
//--------------------------------------------------------------
void gameplayMouseHandler(const MOUSE_EVENT_RECORD& mouseEvent)
{
    if (mouseEvent.dwEventFlags & MOUSE_MOVED) // update the mouse position if there are no events
    {
        g_mouseEvent.mousePosition = mouseEvent.dwMousePosition;
    }
    g_mouseEvent.buttonState = mouseEvent.dwButtonState;
    g_mouseEvent.eventFlags = mouseEvent.dwEventFlags;
}

//--------------------------------------------------------------
// Purpose  : Update function
//            This is the update function
//            double dt - This is the amount of time in seconds since the previous call was made
//
//            Game logic should be done here.
//            Such as collision checks, determining the position of your game characters, status updates, etc
//            If there are any calls to write to the console here, then you are doing it wrong.
//
//            If your game has multiple states, you should determine the current state, and call the relevant function here.
//
// Input    : dt = deltatime
// Output   : void
//--------------------------------------------------------------
void update(double dt)
{
    // get the delta time
    g_dElapsedTime += dt;
    g_dDeltaTime = dt;

    switch (g_eGameState)
    {
        case S_SPLASHSCREEN : splashScreenWait(); // game logic for the splash screen
            break;
        case S_GAME: updateGame(); // gameplay logic when we are in the game
            break;
        case S_TIMESUP:
            restartGameUpdate();
            g_pregameElapsedtime += dt;
            break;
    }
}

void splashScreenWait()    // waits for time to pass in splash screen
{
     if (g_mouseEvent.buttonState == FROM_LEFT_1ST_BUTTON_PRESSED) 
        g_eGameState = S_GAME;
}

void updateGame()       // gameplay logic
{
    processUserInput(); // Waiting to be Implemented (From denniswong10)
    if (Player::CheckOnPlayer()) { moveCharacter(); } // Implemented by denniswong10 (Update MoveCharacter)
}

void restartGameUpdate()
{
    if (g_skKeyEvent[K_SPACE].keyReleased) {
        // Set precision for floating point output
        init();
        return;
    }
    if (g_pregameElapsedtime > 20.0) {
        g_bQuitGame = true;
    }
}

// Modified by denniswong10 (I don't like how the default one operator it. So i mod it)
void moveCharacter()
{    
    // Define threat
    int direction = 0;
    int index = 0;

    // Input key movement
    if (g_skKeyEvent[K_UP].keyDown) direction = 1;
    if (g_skKeyEvent[K_LEFT].keyDown) direction = 2;
    if (g_skKeyEvent[K_DOWN].keyDown) direction = 3;
    if (g_skKeyEvent[K_RIGHT].keyDown) direction = 4;

    // Player still survive. If not skip this
    if (Player::CheckOnPlayer())
    {
        // Pillar Checker: Collision is true 
        index = 0;

        for (int i = 0; i < totalPillar; i++)
        {
            if (myPillar[i] != nullptr && myPlayer->checkForCollision(myPillar[i], direction))
            {
                index = i;
                break;
            }
        }
        
        //done by dennis wong
        // Player still survive. If not skip this
        if (myPlayer != nullptr && direction != 0)
        {
            // Player Direction (Collision is false then move)
            if (myPlayer->checkForCollision(level_map.get_map_grid(myPlayer->getRoomPos('x'), myPlayer->getRoomPos('y')), direction) == false)
            {
                switch (direction)
                {
                    //TODO: find out why character still can move out
                case 1: // UP
                    if ((myPlayer->getPosition().getRow() - 1) > -1) myPlayer->MoveObject(0, -1);
                    break;

                case 2: // LEFT
                    if ((myPlayer->getPosition().getColumn() - 1) > -1) myPlayer->MoveObject(-1, 0);
                    break;

                case 3: // DOWN
                    if ((myPlayer->getPosition().getRow() + 1) < 15) myPlayer->MoveObject(0, 1);
                    break;

                case 4: // RIGHT
                    if ((myPlayer->getPosition().getColumn() + 1) < 35) myPlayer->MoveObject(1, 0);
                    break;

                default: // STOP
                    break;
                }
            }
            else {
                g_Console.writeToBuffer(0, 0, "Invalid movement");
            }

            // Item Collector from Player (Money, Jewel)
            index = 0;
            direction = 0;

            for (int i = 0; i < totalItem; i++)
            {
                if (moneyArr[i] != nullptr && myPlayer->isCollided(moneyArr[i]))
                {
                    myPlayer->Interact(moneyArr[i]);
                    moneyArr[i]->Interact(myPlayer);
                    break;
                }
            }

            //added by timothy
            if (myPlayer->checkIsOOB() != 0) {
                g_sChar.m_cLocation.X = myPlayer->getPosition().getColumn() + 10;
                g_sChar.m_cLocation.Y = myPlayer->getPosition().getRow() + 3;
            }
            else {
                g_sChar.m_cLocation.X = myPlayer->getPosition().getColumn() + 10;
                g_sChar.m_cLocation.Y = myPlayer->getPosition().getRow() + 3;
            }
        }
}

// Waiting to be modified (From denniswong10)
void processUserInput()
{
    // quits the game if player hits the escape key
    if (g_skKeyEvent[K_ESCAPE].keyReleased)
        g_bQuitGame = true;    
}

//--------------------------------------------------------------
// Purpose  : Render function is to update the console screen
//            At this point, you should know exactly what to draw onto the screen.
//            Just draw it!
//            To get an idea of the values for colours, look at console.h and the URL listed there
// Input    : void
// Output   : void
//--------------------------------------------------------------
void render()
{
    clearScreen();      // clears the current screen and draw from scratch 
    switch (g_eGameState)
    {
    case S_SPLASHSCREEN: renderSplashScreen();
        break;
    case S_GAME: 
        renderGame();
        renderFramerate();      // renders debug information, frame rate, elapsed time, etc
        break;
    default:
        rendertimesup();
        break;
    }
    renderToScreen();       // dump the contents of the buffer to the screen, one frame worth of game
}

void clearScreen()
{
    // Clears the buffer with this colour attribute
    g_Console.clearBuffer(COLOURS::DARKGREY);
}

void renderToScreen()
{
    // Writes the buffer to the console, hence you will see what you have written
    g_Console.flushBufferToConsole();
}

void renderSplashScreen()  // renders the splash screen
{
   //display title
    COORD c = g_Console.getConsoleSize();
    c.Y = (c.Y / 3) * 2;
    c.X = c.X / 2 - 9;
    g_Console.writeToBuffer(c, "Use arrow keys to move", BACKMATCHTEXT);
    c.Y += 1;
    c.X = g_Console.getConsoleSize().X / 2 - 14;
    g_Console.writeToBuffer(c, "Left click to switch on lights", BACKMATCHTEXT);
    c.Y += 1;
    c.X = g_Console.getConsoleSize().X / 2 - 8;
    g_Console.writeToBuffer(c, "Press 'Esc' to quit", BACKMATCHTEXT);
    c.Y += 1;
    c.X = g_Console.getConsoleSize().X / 2 - 11;
    g_Console.writeToBuffer(c, "Press ENTER to start", BACKMATCHTEXT);
}

void renderGame()
{
    renderMap();        // Suggestion changes from denniswong10
    renderCharacter();  // Implemented by denniswong10 (Update renderCharacter)
    renderUI();
}

void renderMap() // Suggestion by denniswong10 (Display object into the screen)
{
    //TODO: figureoutwhydontwork
    COORD c;
    g_Console.writeToBuffer(10, 2, "o", BACKGROUND_INTENSITY | FOREGROUND_RED);
    std::string outputStr = "Live: Camera " + level_map.get_map_grid(myPlayer->getRoomPos('x'), myPlayer->getRoomPos('y')).getRoomPos();
    g_Console.writeToBuffer(12, 2, outputStr, BACKMATCHTEXT);
    renderLocationMap(myPlayer->getRoomPos('x'), myPlayer->getRoomPos('y'));
    if (g_mouseEvent.buttonState == FROM_LEFT_1ST_BUTTON_PRESSED) {
        for (int i = 3; i < 18; i++) {
            for (int j = 10; j < 45; j++) {
                c.X = j;
                c.Y = i;
                level_map.get_map_grid(myPlayer->getRoomPos('x'), myPlayer->getRoomPos('y')).set_lights(true);
                g_Console.writeToBuffer(c, " ", COLOURS::GREY);
                g_Console.writeToBuffer(10, 18, "System: Error 404: The lights have been hacked", BACKMATCHTEXT);
                g_Console.writeToBuffer(18, 10, "Error: No signal", BACKMATCHTEXT);
            }
        }
    }
    else {
        level_map.get_map_grid(myPlayer->getRoomPos('x'), myPlayer->getRoomPos('y')).set_lights(false);
        std::string outputStr = "System: Location name: " + level_map.get_map_grid(myPlayer->getRoomPos('x'), myPlayer->getRoomPos('y')).getName();
        g_Console.writeToBuffer(10, 18, outputStr, BACKMATCHTEXT);
    }

    level_map.update_minmap_char(*myPlayer);
    for (int j = 3; j < 7; j++) {
        for (int i = 48; i < 56; i += 2) {
            c.X = i;
            c.Y = j;
            if (level_map.get_minmap_char((i - 48) / 2, j - 3) == 'J') {
                g_Console.writeToBuffer(48, 3, "  ", COLOURS::DARKGOLD);
            }
            if (level_map.get_minmap_char((i - 48) / 2, j - 3) == 'X') {
                g_Console.writeToBuffer(c, "  ", COLOURS::RED);
            }
            else {
                g_Console.writeToBuffer(c, "  ", COLOURS::WHITE);
            }
        }
    }
    outputStr = "System: Now in " + std::to_string(myPlayer->getRoomPos('x')) + ", " + std::to_string(myPlayer->getRoomPos('y'));
    g_Console.writeToBuffer(48, 7, outputStr, BACKMATCHTEXT);
}

// Modified by denniswong10 (Display character into the screen)
void renderCharacter()
{
    // Draw the location of the character
    if (myPlayer != nullptr) g_Console.writeToBuffer(g_sChar.m_cLocation.X, g_sChar.m_cLocation.Y, myPlayer->getEntityChar(), BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED);
}

// Modified by denniswong10 (Display UI into the screen)
void renderFramerate()
{
    //COORD c;
    //// displays the framerate
    //std::ostringstream ss;
    //ss << std::fixed << std::setprecision(3);
    //ss << 1.0 / g_dDeltaTime << "fps";
    //c.X = g_Console.getConsoleSize().X - 9;
    //c.Y = 0;
    //g_Console.writeToBuffer(c, ss.str());
}

void renderUI()
{
    COORD c;
    c.X = 48;
    c.Y = 9;
    std::string outputStr;
    outputStr = "Money Stolen: $" + std::to_string(Player::CheckOnMoney() * 1000);
    g_Console.writeToBuffer(c, outputStr, BACKMATCHTEXT);
    c.Y++;
    //edited by aloysius (timer)
    double timer = (181 - g_dElapsedTime);
    outputStr = "Time remaining: " + std::to_string((int)timer) + " seconds";
    if ((181 - g_dElapsedTime) < 0) {
        g_pregameElapsedtime = 0.0;
        g_eGameState = S_TIMESUP;
    }
    g_Console.writeToBuffer(c, outputStr, BACKMATCHTEXT);
    c.Y += 2;
    outputStr = "Objective: " + level_map.getObjective();
    g_Console.writeToBuffer(c, outputStr, BACKMATCHTEXT);
}

void renderLocationMap(int x, int y) {
    COORD c;
    for (int i = 3; i < 18; ++i) {
        for (int j = 10; j < 45; j++) {
            c.X = j;
            c.Y = i;
            g_Console.writeToBuffer(c, " ", level_map.get_map_grid(x, y).getTile(j - 10, i - 3).get_tile_color());
        }
    }
}

void rendertimesup()
{
    COORD c;
    std::ifstream readfile("time'sup.txt");
    std::string outputStr;
    int i = 0;
    while (std::getline(readfile, outputStr)) {
        c.X = 4;
        c.Y = i;
        g_Console.writeToBuffer(c, outputStr, BACKMATCHTEXT);
        i++;
    }
    c.Y += 3;
    //TODO: display points
    c.X = g_Console.getConsoleSize().X / 2 - 11;
    g_Console.writeToBuffer(c, "Press <space> to retry", BACKMATCHTEXT);
    c.Y += 2;
    c.X = g_Console.getConsoleSize().X / 2 - 8;
    outputStr = "Continue?     " + std::to_string((int)(20 - g_pregameElapsedtime));
    g_Console.writeToBuffer(c, outputStr, BACKMATCHTEXT);
}

void renderWinScreen() {
    COORD c;
    std::ifstream readfile("win.txt");
    std::string outputStr;
    int i = 0;
    while (std::getline(readfile, outputStr)) {
        c.X = 4;
        c.Y = i;
        g_Console.writeToBuffer(c, outputStr, BACKMATCHTEXT);
        i++;
    }
}

void renderLoseScreen() {
    COORD c;
    std::ifstream readfile("failure.txt");
    std::string outputStr;
    int i = 0;
    while (std::getline(readfile, outputStr)) {
        c.X = 4;
        c.Y = i;
        g_Console.writeToBuffer(c, outputStr, BACKMATCHTEXT);
        i++;
    }
}

