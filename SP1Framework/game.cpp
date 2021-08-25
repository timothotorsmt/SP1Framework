// This is the main file for the game logic and function
//
//
#include "game.h"
#include "Grid.h"
#include "Map.h"
#include "Framework\console.h"
#include "keys.h"
#include "Colours.h"
#include "Leaderboard.h"
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
unsigned int scrollNum;
std::string playerId;

// Console object
Console g_Console(100, 22, "SP1Grp5_Timothy_Jeremy_Dennis_Aloysius");

//ascii art goes here
std::vector<std::string> titleart = readfile("title.txt");
std::vector<std::string> timesupart = readfile("time'sup.txt");
std::vector<std::string> pausescreenart = readfile("paused.txt");
std::vector <std::string> newsopen = readfile("news.txt");
std::vector <std::string> newsclosed = readfile("newsclosed.txt");
std::vector<std::string> leaderboardart = readfile("leaderboardart.txt");

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
    
    delete myPlayer;
    
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
    case S_KEYINNAME:
        gameplayKBHandler(keyboardEvent);
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
    case VK_KEY_A: key = K_A; break;
    case VK_KEY_B: key = K_B; break;
    case VK_KEY_C: key = K_C; break;
    case VK_KEY_D: key = K_D; break;
    case VK_KEY_E: key = K_E; break;
    case VK_KEY_F: key = K_F; break;
    case VK_KEY_G: key = K_G; break;
    case VK_KEY_H: key = K_H; break;
    case VK_KEY_I: key = K_I; break;
    case VK_KEY_J: key = K_J; break;
    case VK_KEY_K: key = K_K; break;
    case VK_KEY_L: key = K_L; break;
    case VK_KEY_M: key = K_M; break;
    case VK_KEY_N: key = K_N; break;
    case VK_KEY_O: key = K_O; break;
    case VK_KEY_P: key = K_P; break;
    case VK_KEY_Q: key = K_Q; break;
    case VK_KEY_R: key = K_R; break;
    case VK_KEY_S: key = K_S; break;
    case VK_KEY_T: key = K_T; break;
    case VK_KEY_U: key = K_U; break;
    case VK_KEY_V: key = K_V; break;
    case VK_KEY_W: key = K_W; break;
    case VK_KEY_X: key = K_X; break;
    case VK_KEY_Y: key = K_Y; break;
    case VK_KEY_Z: key = K_Z; break;
    case VK_BACK: key = K_BACKSPACE; break;
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
        case S_SPLASHSCREEN : 
            splashScreenWait(); // game logic for the splash screen
            break;
        case S_GAME: 
            updateGame(); // gameplay logic when we are in the game
            g_dElapsedTime += dt;
            break;
        case S_PAUSE:
            pauseUpdate();
            break;
        case S_ANIMATION:
            g_pregameElapsedtime += dt;
            animationInteraction();
            break;
        case S_KEYINNAME:
            keyInName();
            break;
        case S_LEADERBOARD:
            leaderboardUpdate();
            break;
        default:
            restartGameUpdate();
            g_pregameElapsedtime += dt;
            break;
    }
}

void splashScreenWait()    // waits for time to pass in splash screen
{
     if (g_mouseEvent.buttonState == FROM_LEFT_1ST_BUTTON_PRESSED && g_mouseEvent.mousePosition.Y == 16) {
        g_eGameState = S_ANIMATION;
        g_pregameElapsedtime = 0;
    }
    else if (g_mouseEvent.buttonState == FROM_LEFT_1ST_BUTTON_PRESSED && g_mouseEvent.mousePosition.Y == 17) {
        scrollNum = 0;
        g_eGameState = S_LEADERBOARD;
    }
    else if (g_mouseEvent.buttonState == FROM_LEFT_1ST_BUTTON_PRESSED && g_mouseEvent.mousePosition.Y == 19) {
        g_bQuitGame = true;
    }
}

void updateGame()       // gameplay logic
{
    processUserInput(); // Waiting to be Implemented (From denniswong10)
    if (Player::CheckOnPlayer()) { moveCharacter(); } // Implemented by denniswong10 (Update MoveCharacter)
}

void restartGameUpdate()
{
    switch (g_eGameState)
    {
    case S_TIMESUP:
        if (g_mouseEvent.buttonState == FROM_LEFT_1ST_BUTTON_PRESSED && g_mouseEvent.mousePosition.Y == 15) {
            init();
        }
        else if (g_mouseEvent.mousePosition.Y == 16 && g_mouseEvent.buttonState == FROM_LEFT_1ST_BUTTON_PRESSED) {
            g_eGameState = S_KEYINNAME;
        }
        break;
    case S_WIN:
        break;
    case S_FAIL:
        break;
    }
    if (g_pregameElapsedtime > 20.0) {
        g_bQuitGame = true;
    }
    if (g_pregameElapsedtime > 20.0) {
        g_bQuitGame = true;
    }
}

void pauseUpdate()
{
    if (g_mouseEvent.buttonState == FROM_LEFT_1ST_BUTTON_PRESSED && g_mouseEvent.mousePosition.Y == 13) {
        g_eGameState = S_GAME;
    }
    else if (g_mouseEvent.buttonState == FROM_LEFT_1ST_BUTTON_PRESSED && g_mouseEvent.mousePosition.Y == 15) {
        g_bQuitGame = true;
    }
    else if (g_mouseEvent.buttonState == FROM_LEFT_1ST_BUTTON_PRESSED && g_mouseEvent.mousePosition.Y == 14 && g_mouseEvent.mousePosition.X > 40 && g_mouseEvent.mousePosition.X < 50 ) {
        init();
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
        g_eGameState = S_PAUSE;
    if (g_mouseEvent.mousePosition.Y == 2 && (g_mouseEvent.mousePosition.X > 91 && g_mouseEvent.mousePosition.X < 99) && g_mouseEvent.buttonState == FROM_LEFT_1ST_BUTTON_PRESSED) {
        g_eGameState = S_PAUSE;
    } 
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
    case S_TIMESUP:
        rendertimesup();
        break;
    case S_PAUSE:
        renderPauseScreen();
        break;
    case S_ANIMATION:
        renderPreGameAnimation();
        break;
    case S_LEADERBOARD:
        renderLeaderboard();
        break;
    case S_KEYINNAME:
        renderInputPlayerID();
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
   COORD c;
    std::string outputStr;
    for (unsigned int i = 0; i < titleart.size(); i++) {
        c.X = 9;
        c.Y = i;
        outputStr = titleart[i];
        g_Console.writeToBuffer(c, outputStr, BACKMATCHTEXT);
    }
    c = g_Console.getConsoleSize();
    c.Y = 16;
    c.X = g_Console.getConsoleSize().X / 2 - 11;
    g_Console.writeToBuffer(c, "CLICK HERE TO START", BACKMATCHTEXT);
    if (g_mouseEvent.mousePosition.Y == 16) {
        c.X = g_Console.getConsoleSize().X / 2 - 13;
        g_Console.writeToBuffer(c, "> CLICK HERE TO START", BACKGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_INTENSITY);
    }
    c.Y++;
    c.X = g_Console.getConsoleSize().X / 2 - 13;
    g_Console.writeToBuffer(c, "CLICK TO SEE LEADERBOARD", BACKMATCHTEXT);
    if (g_mouseEvent.mousePosition.Y == 17) {
        c.X = g_Console.getConsoleSize().X / 2 - 15;
        g_Console.writeToBuffer(c, "> CLICK TO SEE LEADERBOARD", BACKGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_INTENSITY);
    }

    c.Y += 2;
    c.X = g_Console.getConsoleSize().X / 2 - 6;
    g_Console.writeToBuffer(c, "QUIT GAME", BACKMATCHTEXT);
    if (g_mouseEvent.mousePosition.Y == 19) {
        c.X = g_Console.getConsoleSize().X / 2 - 8;
        g_Console.writeToBuffer(c, "> QUIT GAME", BACKGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_INTENSITY);
    }
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
    g_Console.writeToBuffer(10, 2, "o", BACKGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_INTENSITY);
    std::string outputStr = "Live: Camera " + level_map.get_map_grid(myPlayer->getRoomPos('x'), myPlayer->getRoomPos('y')).getRoomPos();
    g_Console.writeToBuffer(12, 2, outputStr, BACKMATCHTEXT);
    renderLocationMap(myPlayer->getRoomPos('x'), myPlayer->getRoomPos('y'));
    if (g_mouseEvent.buttonState == FROM_LEFT_1ST_BUTTON_PRESSED) {
        for (int i = 3; i < 18; i++) {
            for (int j = 10; j < 45; j++) {
                c.X = j;
                c.Y = i;
                level_map.get_map_grid(myPlayer->getRoomPos('x'), myPlayer->getRoomPos('y')).set_lights(true);
                g_Console.writeToBuffer(c, " ", COLOURS::BLACK);
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
    if ((181 - g_dElapsedTime) < 60) {
        g_Console.writeToBuffer(c, outputStr, BACKGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_INTENSITY);
    }
    else {
        g_Console.writeToBuffer(c, outputStr, BACKMATCHTEXT);
    }
    points = ((Player::CheckOnMoney() * 100) + (((int)(181 - g_dElapsedTime)) * 10));
    if ((181 - g_dElapsedTime) < 0) {
        g_pregameElapsedtime = 0.0;
        g_eGameState = S_TIMESUP;
    }
    c.Y += 2;
    outputStr = "Objective: " + level_map.getObjective();
    g_Console.writeToBuffer(c, outputStr, BACKMATCHTEXT);
    c.X = 93;
    c.Y = 2;
    g_Console.writeToBuffer(c, "PAUSE", BACKGROUND_RED | BACKGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE);

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
    std::string outputStr;
    for (unsigned int i = 0; i < timesupart.size(); i++) {
        c.X = 4;
        c.Y = i + 1;
        outputStr = timesupart[i];
        g_Console.writeToBuffer(c, outputStr, BACKMATCHTEXT);
    }
    c.Y += 3;
    c.X = g_Console.getConsoleSize().X / 2 - 10;
    outputStr = "Total points:   " + std::to_string(points);
    g_Console.writeToBuffer(c, outputStr, BACKMATCHTEXT);
    c.Y++;
    c.X = g_Console.getConsoleSize().X / 2 - 5;
    g_Console.writeToBuffer(c, "MAIN MENU", BACKMATCHTEXT);
    c.Y++;
    g_Console.writeToBuffer(c, "ADD TO LEADERBOARD", BACKMATCHTEXT);
    c.Y += 2;
    c.X = g_Console.getConsoleSize().X / 2 - 8;
    outputStr = "Continue?     " + std::to_string((int)(20 - g_pregameElapsedtime));
    g_Console.writeToBuffer(c, outputStr, BACKMATCHTEXT);
    if (g_mouseEvent.mousePosition.Y == 15) {
        c.X = g_Console.getConsoleSize().X / 2 - 7;
        c.Y = 15;
        g_Console.writeToBuffer(c, "> MAIN MENU", BACKGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_INTENSITY);
    }
    if (g_mouseEvent.mousePosition.Y == 16) {
        c.X = g_Console.getConsoleSize().X / 2 - 7;
        c.Y = 16;
        g_Console.writeToBuffer(c, "> ADD TO LEADERBOARD", BACKGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_INTENSITY);
    }
}

void renderWinScreen() {
    COORD c;
    std::string outputStr;
    for (unsigned int i = 0; i < timesupart.size(); i++) {
        c.X = 4;
        c.Y = i + 1;
        outputStr = timesupart[i];
        g_Console.writeToBuffer(c, outputStr, BACKMATCHTEXT);
    }
}

void renderLoseScreen() {
    COORD c;
    std::string outputStr;
    for (unsigned int i = 0; i < timesupart.size(); i++) {
        c.X = 4;
        c.Y = i + 1;
        outputStr = timesupart[i];
        g_Console.writeToBuffer(c, outputStr, BACKMATCHTEXT);
    }
}

void renderPauseScreen() {
    COORD c;
    g_Console.writeToBuffer(10, 2, "o", BACKGROUND_INTENSITY | FOREGROUND_RED);
    std::string outputStr = "Live: Camera " + level_map.get_map_grid(myPlayer->getRoomPos('x'), myPlayer->getRoomPos('y')).getRoomPos();
    g_Console.writeToBuffer(12, 2, outputStr, BACKMATCHTEXT);
    renderLocationMap(myPlayer->getRoomPos('x'), myPlayer->getRoomPos('y'));
    outputStr = "System: Location name: " + level_map.get_map_grid(myPlayer->getRoomPos('x'), myPlayer->getRoomPos('y')).getName();
    g_Console.writeToBuffer(10, 18, outputStr, BACKMATCHTEXT);

    level_map.update_minmap_char(*myPlayer);
    for (int j = 3; j < 7; j++) {
        for (int i = 48; i < 56; i += 2) {
            c.X = i;
            c.Y = j;
            g_Console.writeToBuffer(c, "  ", COLOURS::WHITE);
        }
    }
    c.X = 93;
    c.Y = 2;
    g_Console.writeToBuffer(c, "PAUSE", BACKGROUND_RED | BACKGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE);
    outputStr = "System: Now in " + std::to_string(myPlayer->getRoomPos('x')) + ", " + std::to_string(myPlayer->getRoomPos('y'));
    g_Console.writeToBuffer(48, 7, outputStr, BACKMATCHTEXT);
    for (int i = 0; i < 13; i++) {
        for (int j = 0; j < 60; j++) {
            c.X = (g_Console.getConsoleSize().X / 2 - 30) + j;
            c.Y = (g_Console.getConsoleSize().Y / 2 - 7) + i;

            g_Console.writeToBuffer(c, " ", COLOURS::RED);

        }
    }
    for (unsigned int i = 0; i < pausescreenart.size(); i++) {
        c.X = g_Console.getConsoleSize().X / 2 - 27;
        c.Y = (g_Console.getConsoleSize().Y / 2 - 7) + i;
        outputStr = pausescreenart[i];
        g_Console.writeToBuffer(c, outputStr, BACKGROUND_RED | BACKGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
    }
    c.X = g_Console.getConsoleSize().X / 2 - 8;
    c.Y = g_Console.getConsoleSize().Y / 2 + 2;
    g_Console.writeToBuffer(c, "CONTINUE", BACKGROUND_RED | BACKGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
    c.Y++;
    g_Console.writeToBuffer(c, "MAIN MENU", BACKGROUND_RED | BACKGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
    c.Y++;
    g_Console.writeToBuffer(c, "QUIT GAME", BACKGROUND_RED | BACKGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
    c.X = g_Console.getConsoleSize().X / 2 - 10;
    if (g_mouseEvent.mousePosition.Y == 13) {
        c.Y = 13;
        g_Console.writeToBuffer(c, "> CONTINUE", BACKGROUND_RED | BACKGROUND_INTENSITY);
    }
    if (g_mouseEvent.mousePosition.Y == 14) {
        c.Y = 14;
        g_Console.writeToBuffer(c, "> MAIN MENU", BACKGROUND_RED | BACKGROUND_INTENSITY);
    }
    if (g_mouseEvent.mousePosition.Y == 15) {
        c.Y = 15;
        g_Console.writeToBuffer(c, "> QUIT GAME", BACKGROUND_RED | BACKGROUND_INTENSITY);
    }
}

void renderLeaderboard() {
    COORD c;
    std::string outputStr;
    for (unsigned int i = 0; i < leaderboardart.size(); i++) {
        c.X = 1;
        c.Y = i;
        outputStr = leaderboardart[i];
        g_Console.writeToBuffer(c, outputStr, BACKMATCHTEXT);
    }
    if (g_skKeyEvent[K_S].keyDown)
        scrollNum++;
    else if (g_skKeyEvent[K_W].keyDown)
        if ((scrollNum - 1) < -1)
            scrollNum--;
    leaderboard.printLeaderboard(g_Console, scrollNum);
    g_Console.writeToBuffer(5, 18, "< Main Menu", BACKMATCHTEXT);
}

void renderInputPlayerID() {
    COORD c;
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 20; j++) {
            c.X = (g_Console.getConsoleSize().X / 2 - 10) + j;
            c.Y = (g_Console.getConsoleSize().Y / 2 - 3) + i;
            g_Console.writeToBuffer(c, " ", COLOURS::DARKGREY);
        }
    }
    g_Console.writeToBuffer(40, 8, "Enter Player name: ", BACKMATCHTEXT);
    if (playerId == "") {
        g_Console.writeToBuffer(40, 13, "Type something here...", BACKMATCHTEXT);
    }
    g_Console.writeToBuffer(40, 13, playerId, BACKMATCHTEXT);
    g_Console.writeToBuffer(90, 17, "Done", BACKMATCHTEXT);
}

void keyInName()
{
    if (playerId.size() < 15) {
        if (g_skKeyEvent[K_A].keyReleased)
            playerId.append("A");
        if (g_skKeyEvent[K_B].keyReleased)
            playerId.append("B");
        if (g_skKeyEvent[K_C].keyReleased)
            playerId.append("C");
        if (g_skKeyEvent[K_D].keyReleased)
            playerId.append("D");
        if (g_skKeyEvent[K_E].keyReleased)
            playerId.append("E");
        if (g_skKeyEvent[K_F].keyReleased)
            playerId.append("F");
        if (g_skKeyEvent[K_G].keyReleased)
            playerId.append("G");
        if (g_skKeyEvent[K_H].keyReleased)
            playerId.append("H");
        if (g_skKeyEvent[K_I].keyReleased)
            playerId.append("I");
        if (g_skKeyEvent[K_J].keyReleased)
            playerId.append("J");
        if (g_skKeyEvent[K_K].keyReleased)
            playerId.append("K");
        if (g_skKeyEvent[K_L].keyReleased)
            playerId.append("L");
        if (g_skKeyEvent[K_M].keyReleased)
            playerId.append("M");
        if (g_skKeyEvent[K_N].keyReleased)
            playerId.append("N");
        if (g_skKeyEvent[K_O].keyReleased)
            playerId.append("O");
        if (g_skKeyEvent[K_P].keyReleased)
            playerId.append("P");
        if (g_skKeyEvent[K_Q].keyReleased)
            playerId.append("Q");
        if (g_skKeyEvent[K_R].keyReleased)
            playerId.append("R");
        if (g_skKeyEvent[K_S].keyReleased)
            playerId.append("S");
        if (g_skKeyEvent[K_T].keyReleased)
            playerId.append("T");
        if (g_skKeyEvent[K_U].keyReleased)
            playerId.append("U");
        if (g_skKeyEvent[K_V].keyReleased)
            playerId.append("V");
        if (g_skKeyEvent[K_W].keyReleased)
            playerId.append("W");
        if (g_skKeyEvent[K_X].keyReleased)
            playerId.append("X");
        if (g_skKeyEvent[K_Y].keyReleased)
            playerId.append("Y");
        if (g_skKeyEvent[K_Z].keyReleased)
            playerId.append("Z");
    }
    if (g_skKeyEvent[K_BACKSPACE].keyReleased)
        if (playerId != "")
            playerId.pop_back();
    if (g_mouseEvent.mousePosition.X < 99 && g_mouseEvent.mousePosition.X > 85 && g_mouseEvent.mousePosition.Y == 17 && g_mouseEvent.buttonState == FROM_LEFT_1ST_BUTTON_PRESSED) {
        leaderboard.add_new_score(playerId, points);
        g_eGameState = S_LEADERBOARD;
    }
}

void renderPreGameAnimation() {
    COORD c;
    if ((int)g_pregameElapsedtime % 2 == 0) {
        for (int i = 0; i < 22; i++) {
            c.X = 0;
            c.Y = i;
            g_Console.writeToBuffer(c, newsopen[i], BACKMATCHTEXT);
        }
    }
    else {
        for (int i = 0; i < 22; i++) {
            c.X = 0;
            c.Y = i;
            g_Console.writeToBuffer(c, newsclosed[i], BACKMATCHTEXT);
        }
    }
    if (g_pregameElapsedtime > 3.0) {
        g_Console.writeToBuffer(73, 20, "CLICK ANYWHERE TO SKIP", BACKMATCHTEXT);
    }
}

void animationInteraction() {
    if (g_pregameElapsedtime > 3.0 && g_mouseEvent.buttonState == FROM_LEFT_1ST_BUTTON_PRESSED) {
        level_map.generateNewMap();
        g_eGameState = S_GAME;
    }
}
