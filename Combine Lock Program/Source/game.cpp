// This is the main file for the game logic and function
//
//
#include "game.h"
#include "Framework\console.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include "Player.h"
#include "Money.h"
#include "Pillar.h"
#include "Jewel.h"
#include "Layout.h"
#include "Design.h"
#include "GameObject.h"
#include "CLP.h"
#include "CloseButtonField.h"
#include <fstream>

double  g_dElapsedTime;
double  g_dDeltaTime;
SKeyEvent g_skKeyEvent[K_COUNT];
SMouseEvent g_mouseEvent;

// Game specific variables here
SGameChar   g_sChar;
EGAMESTATES g_eGameState = S_SPLASHSCREEN; // initial state

// Console object
Console g_Console(80, 25, "SP1 Framework");

// Implemented by denniswong10 (Define a player object)
GameObject* myPlayer;
CLP* program;

// Suggestion by denniswong10 (Define Pillar, Item and Jewel)
Layout* currentMap;
GameObject* myPillar[1200];
GameObject* myItem[1200];

int totalPillar;
int totalItem;

// Implemented by denniswong10 (Combine Code Program)
GameObject* myPlayer;
CLP* program;

bool minigame_played;
bool mouseInput_Released;

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

    // sets the initial state for the game
    g_eGameState = S_MINIGAME_2; // S_SPLASHSCREEN;

    g_sChar.m_cLocation.X = g_Console.getConsoleSize().X / 2;
    g_sChar.m_cLocation.Y = g_Console.getConsoleSize().Y / 2;
    g_sChar.m_bActive = true;
    // sets the width, height and the font name to use in the console
    g_Console.setConsoleFont(0, 16, L"Consolas");

    // remember to set your keyboard handler, so that your functions can be notified of input events
    g_Console.setKeyboardHandler(keyboardHandler);
    g_Console.setMouseHandler(mouseHandler);

    // Implemented by denniswong10 (Combine Code Program)
    program = nullptr;
    minigame_played = false;
    mouseInput_Released = false;

    LoadMap();
}

void LoadMap()
{
    // Implemented by denniswong10 (Create player)
    currentMap = new Design("test.txt");
    myPlayer = new Player(currentMap->GetObjectPosition(0, 'P', 'x'), currentMap->GetObjectPosition(0, 'P', 'y'));

    // Suggestion by denniswong10 (Create Pillar and Item)
    for (int i = 0; i < currentMap->GetTotalItem(); i++)
    {
        (i == currentMap->GetTotalItem() - 1)
            ?
            myItem[i] = new Jewel(currentMap->GetObjectPosition(i, 'J', 'x'), currentMap->GetObjectPosition(i, 'J', 'y'))
            : myItem[i] = new Money(currentMap->GetObjectPosition(i, 'M', 'x'), currentMap->GetObjectPosition(i, 'M', 'y'));
    }

    for (int i = 0; i < currentMap->GetTotalTile(); i++) myPillar[i] = new Pillar(currentMap->GetObjectPosition(i, '#', 'x'), currentMap->GetObjectPosition(i, '#', 'y'));

    totalPillar = Pillar::GetPillarCount();
    totalItem = ((Jewel::FindForJewel()) ? Money::GetMoneyCount() + 1 : Money::GetMoneyCount());
}

void ClearMap()
{
    delete currentMap;
    currentMap = nullptr;

    delete myPlayer;
    myPlayer = nullptr;

    delete[] myPillar;
    for (int i = 0; i < 1200; i++) { myPillar[i] = nullptr; }

    delete[] myItem;
    for (int i = 0; i < 1200; i++) { myItem[i] = nullptr; }
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
    case S_SPLASHSCREEN: // don't handle anything for the splash screen
        break;
    case S_GAME: gameplayMouseHandler(mouseEvent); // handle gameplay mouse event
        break;
    case S_MINIGAME_2: gameplayMouseHandler(mouseEvent);
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

        case S_MINIGAME_2:
            MiniGame2_Function();
            break;
    }
}

void splashScreenWait()    // waits for time to pass in splash screen
{
    if (g_dElapsedTime > 3.0) // wait for 3 seconds to switch to game mode, else do nothing
        g_eGameState = S_GAME;
}

void updateGame()       // gameplay logic
{
    processUserInput(); // Waiting to be Implemented (From denniswong10)
    if (Player::CheckOnPlayer()) { moveCharacter(); } // Implemented by denniswong10 (Update MoveCharacter)
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
    
    // Self-destruct
    if (g_skKeyEvent[K_SPACE].keyReleased)
    {
        delete myPlayer;
        myPlayer = nullptr;
    }

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
        
        // Player Direction (Collision is false then move)
        if (myPillar[index] == nullptr || (myPillar[index] != nullptr && !myPlayer->checkForCollision(myPillar[index], direction)))
        {
            if (direction != 0) Beep(1440, 30); 

            switch (direction)
            {
                case 1: // UP
                    
                    if (myPlayer->GetPosY() > 0) myPlayer->MoveObject(0, -1);
                    break;

                case 2: // LEFT
                    if (myPlayer->GetPosX() > 0) myPlayer->MoveObject(-1, 0);
                    break;

                case 3: // DOWN
                    if (myPlayer->GetPosY() < 24) myPlayer->MoveObject(0, 1);
                    break;

                case 4: // RIGHT
                    if (myPlayer->GetPosX() < 79) myPlayer->MoveObject(1, 0);
                    break;

                default: // STOP
                    break;
            }
        }

        // Player Movement (Only update player position and reset direction)
        direction = 0;
        g_sChar.m_cLocation.X = myPlayer->GetPosX();
        g_sChar.m_cLocation.Y = myPlayer->GetPosY();
        
        // Item Collector from Player (Money, Jewel)
        index = 0;

        for (int i = 0; i < totalItem; i++)
        {
            if (myItem[i] != nullptr && myPlayer->isCollided(myItem[i]))
            {
                myPlayer->Interact(myItem[i]);
                myItem[i]->Interact(myPlayer);
                myItem[i] = nullptr;
                break;
            }
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
    case S_SPLASHSCREEN: 
        renderSplashScreen();
        break;
    case S_GAME: 
        renderFramerate();
        renderGame();
        break;
    case S_MINIGAME_2:
        render_MiniGame2();
        break;
    }
    //renderFramerate();      // renders debug information, frame rate, elapsed time, etc
    renderInputEvents();    // renders status of input events
    renderToScreen();       // dump the contents of the buffer to the screen, one frame worth of game
}

void clearScreen()
{
    // Clears the buffer with this colour attribute
    g_Console.clearBuffer(0x1F);
}

void renderToScreen()
{
    // Writes the buffer to the console, hence you will see what you have written
    g_Console.flushBufferToConsole();
}

void renderSplashScreen()  // renders the splash screen
{
    COORD c = g_Console.getConsoleSize();
    c.Y /= 3;
    c.X = c.X / 2 - 9;
    g_Console.writeToBuffer(c, "Welcome to GG! Let's do this!", 0x03);
    c.Y += 1;
    c.X = g_Console.getConsoleSize().X / 2 - 20;
    g_Console.writeToBuffer(c, "Press <Space> to change character colour", 0x09);
    c.Y += 1;
    c.X = g_Console.getConsoleSize().X / 2 - 9;
    g_Console.writeToBuffer(c, "Press 'Esc' to quit", 0x09);
}

void renderGame()
{
    renderMap();        // Suggestion changes from denniswong10
    renderCharacter();  // Implemented by denniswong10 (Update renderCharacter)
}

void renderMap() // Suggestion by denniswong10 (Display object into the screen)
{
    // Set coordiate for object
    COORD pos;

    // Display Jewel (Can be destroyed)
    if (Jewel::FindForJewel())
    {
        if (myItem[totalItem - 1] != nullptr)
        {
            pos.X = myItem[totalItem - 1]->GetPosX();
            pos.Y = myItem[totalItem - 1]->GetPosY();
            g_Console.writeToBuffer(pos, myItem[totalItem - 1]->GetMarker());
        }
    }

    // Display Money (Can be destroyed)
    for (int i = 0; i < totalItem; i++)
    {
        if (myItem[i] != nullptr)
        {
            pos.X = myItem[i]->GetPosX();
            pos.Y = myItem[i]->GetPosY();
            g_Console.writeToBuffer(pos, myItem[i]->GetMarker());
        }
    }

    // Display Pillar
    for (int i = 0; i < totalPillar; i++)
    {
        pos.X = myPillar[i]->GetPosX();
        pos.Y = myPillar[i]->GetPosY();
        g_Console.writeToBuffer(pos, ' ', 0x00);
    }

    if (Player::CheckOnJewel()) { g_eGameState = S_MINIGAME_2; }
}

// Modified by denniswong10 (Display character into the screen)
void renderCharacter()
{
    // Draw the location of the character
    WORD charColor = 0x0C;
    if (g_sChar.m_bActive)
    {
        charColor = 0x0A;
    }
    if (myPlayer != nullptr) g_Console.writeToBuffer(g_sChar.m_cLocation, myPlayer->GetMarker(), charColor);
}

// Modified by denniswong10 (Display UI into the screen)
void renderFramerate()
{
    COORD c;
    // displays the framerate
    std::ostringstream ss;

    // Show Player Position
    if (Player::CheckOnPlayer())
    {
        ss.str("");
        ss << "Pillar Found (#): " << Pillar::GetPillarCount();
        c.X = 0;
        c.Y = 0;
        g_Console.writeToBuffer(c, ss.str());

        ss.str("");
        ss << "Money Found ($): $ " << Money::GetMoneyCount();
        c.X = 0;
        c.Y = 1;
        g_Console.writeToBuffer(c, ss.str());

        ss.str("");
        ss << "Current Location: " << currentMap->GetCurrentLocation();
        c.X = 0;
        c.Y = 2;
        g_Console.writeToBuffer(c, ss.str());

        ss.str("");
        ss << "X: " << myPlayer->GetPosX();
        c.X = 0;
        c.Y = 23;
        g_Console.writeToBuffer(c, ss.str());

        ss.str("");
        ss << "Y: " << myPlayer->GetPosY();
        c.X = 0;
        c.Y = 24;
        g_Console.writeToBuffer(c, ss.str());
    }
    else
    {
        ss.str("");
        ss << "GG! Your player have been killed!";
        c.X = 0;
        c.Y = 1;
        g_Console.writeToBuffer(c, ss.str());
    }
}

// Implemented by denniswong10 (Get Function for program)
void MiniGame2_Function()
{
    // If mini game haven't played, you will play it
    if (program == nullptr && !minigame_played) { program = new CLP; }

    // If only program is created
    if (program != nullptr)
    {
        // Check if the status change
        program->CheckStatus();

        // Find for mouse input key
        if (g_mouseEvent.buttonState == FROM_LEFT_1ST_BUTTON_PRESSED)
        {
            mouseInput_Released = true;
            program->UpdateInput(g_mouseEvent.mousePosition.X, g_mouseEvent.mousePosition.Y);

            // If the program is secure then terminate program
            if (CloseButtonField::GetCloseCalled() && program->CheckOnSecure())
            {
                minigame_played = true;

                delete program;
                program = nullptr;
            }
        }

        // Find for more input key
        if (!mouseInput_Released && g_mouseEvent.buttonState & 0xFF000000)
        {
            mouseInput_Released = true;
            program->UpdateInput(g_mouseEvent.mousePosition.X, g_mouseEvent.mousePosition.Y);
            mouseInput_Released = false;
        }
    }

    // Return to main game
    if (minigame_played) { g_eGameState = S_GAME; }
}

// Implemented by denniswong10 (Get Render for program)
void render_MiniGame2()
{
    // If only program is created, then render
    if (program != nullptr)
    {
        COORD pos;
        int index_number = 0;
        int index_expression = 0;

        // Render: Layout
        for (int row = 0; row < 9; row++)
        {
            for (int col = 0; col < 18; col++)
            {
                pos.X = col; // 4
                pos.Y = row; // 3

                if (row == 0 && col < 17) g_Console.writeToBuffer(pos, '#');
                else if (row == 8 && col < 17) g_Console.writeToBuffer(pos, '#');
                else if (col == 0) g_Console.writeToBuffer(pos, '#');
                else if (col == 17) g_Console.writeToBuffer(pos, '#');
                else g_Console.writeToBuffer(pos, ' ');
            }
        }

        // Render: 1st Pattern Code
        for (int i = 0; i < 2; i++)
        {
            pos.X = (i * 2) + 5;
            pos.Y = 1;

            g_Console.writeToBuffer(pos, '0' + program->GetOutput_Number(&index_number));
            index_number++;
        }

        // Render: 1st Pattern Code (Expression)
        pos.X = 6, pos.Y = 1;
        g_Console.writeToBuffer(pos, program->GetOutput_Expression(&index_expression));
        index_expression++;

        // Render: 2nd Pattern Code
        for (int i = 0; i < 3; i++)
        {
            pos.X = (i * 2) + 4;
            pos.Y = 2;

            g_Console.writeToBuffer(pos, '0' + program->GetOutput_Number(&index_number));
            index_number++;
        }

        // Render: 2st Pattern Code (Expression)
        for (int i = 0; i < 2; i++)
        {
            pos.X = (i * 2) + 5;
            pos.Y = 2;

            g_Console.writeToBuffer(pos, program->GetOutput_Expression(&index_expression));
            index_expression++;
        }

        // Render: 3rd Pattern Code
        for (int i = 0; i < 4; i++)
        {
            pos.X = (i * 2) + 3;
            pos.Y = 3;

            g_Console.writeToBuffer(pos, '0' + program->GetOutput_Number(&index_number));
            index_number++;
        }

        // Render: 3rd Pattern Code (Expression)
        for (int i = 0; i < 3; i++)
        {
            pos.X = (i * 2) + 4;
            pos.Y = 3;

            g_Console.writeToBuffer(pos, program->GetOutput_Expression(&index_expression));
            index_expression++;
        }

        // Render: Fixed Pattern
        pos.X = 13, pos.Y = 1;
        g_Console.writeToBuffer(pos, '0' + program->GetOutputFixed(0));
    
        pos.X = 13, pos.Y = 2;
        g_Console.writeToBuffer(pos, '0' + program->GetOutputFixed(1));

        pos.X = 13, pos.Y = 3;
        g_Console.writeToBuffer(pos, '0' + program->GetOutputFixed(2));

        // Show status sign
        COORD pos_bb;
        pos_bb.X = 3;
        pos_bb.Y = 5;

        std::ostringstream bb;
        bb << ((program->CheckOnSecure()) ? "- SECURE! -" : "- HACKED! -");
        g_Console.writeToBuffer(pos_bb, bb.str());

        // Show close sign
        COORD pos_cc;
        pos_cc.X = 3;
        pos_cc.Y = 7;

        std::ostringstream cc;
        cc << ((program->CheckOnSecure()) ? "X  OPEN! X" : "X  LOCK! X");
        g_Console.writeToBuffer(pos_cc, cc.str());
    }
}

// this is an example of how you would use the input events
void renderInputEvents()
{
    /* keyboard events
    COORD startPos = {50, 2};
    std::ostringstream ss;
    std::string key;
    for (int i = 0; i < K_COUNT; ++i)
    {
        ss.str("");
        switch (i)
        {
        case K_UP: key = "UP";
            break;
        case K_DOWN: key = "DOWN";
            break;
        case K_LEFT: key = "LEFT";
            break;
        case K_RIGHT: key = "RIGHT";
            break;
        case K_SPACE: key = "SPACE";
            break;
        default: continue;
        }
        if (g_skKeyEvent[i].keyDown)
            ss << key << " pressed";
        else if (g_skKeyEvent[i].keyReleased)
            ss << key << " released";
        else
            ss << key << " not pressed";

        COORD c = { startPos.X, startPos.Y + i };
        g_Console.writeToBuffer(c, ss.str(), 0x17);
    }

    // mouse events    
    ss.str("");
    ss << "Mouse position (" << g_mouseEvent.mousePosition.X << ", " << g_mouseEvent.mousePosition.Y << ")";
    g_Console.writeToBuffer(g_mouseEvent.mousePosition, ss.str(), 0x59);
    ss.str("");
    switch (g_mouseEvent.eventFlags)
    {
    case 0:
        if (g_mouseEvent.buttonState == FROM_LEFT_1ST_BUTTON_PRESSED)
        {
            ss.str("Left Button Pressed");
            g_Console.writeToBuffer(g_mouseEvent.mousePosition.X, g_mouseEvent.mousePosition.Y + 1, ss.str(), 0x59);
        }
        else if (g_mouseEvent.buttonState == RIGHTMOST_BUTTON_PRESSED)
        {
            ss.str("Right Button Pressed");
            g_Console.writeToBuffer(g_mouseEvent.mousePosition.X, g_mouseEvent.mousePosition.Y + 2, ss.str(), 0x59);
        }
        else
        {
            ss.str("Some Button Pressed");
            g_Console.writeToBuffer(g_mouseEvent.mousePosition.X, g_mouseEvent.mousePosition.Y + 3, ss.str(), 0x59);
        }
        break;
    case DOUBLE_CLICK:
        ss.str("Double Clicked");
        g_Console.writeToBuffer(g_mouseEvent.mousePosition.X, g_mouseEvent.mousePosition.Y + 4, ss.str(), 0x59);
        break;        
    case MOUSE_WHEELED:
        if (g_mouseEvent.buttonState & 0xFF000000)
            ss.str("Mouse wheeled down");
        else
            ss.str("Mouse wheeled up");
        g_Console.writeToBuffer(g_mouseEvent.mousePosition.X, g_mouseEvent.mousePosition.Y + 5, ss.str(), 0x59);
        break;
    default:        
        break;
    }
    */
}



