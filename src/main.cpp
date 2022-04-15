#include "Bat.h"
#include "Ball.h"
#include <sstream>
#include <cstdlib>
#include <SFML/Graphics.hpp>


int main()
{
    // Create a video mode object
    VideoMode vm(1366, 768);
    
    // Create and open a window for the game
    RenderWindow window(vm, "Pong", Style::Fullscreen);

    int score = 0;
    int lives = 3;

    // Create a bat at the bottom center of the screen
    Bat bat(1366 / 2, 768 - 15);

    // Create a ball
    Ball ball(1366 /2, 0);

    // We will add a ball in the next chapter

    // Create a Text object challed HUD
    Text hud;

    // A cool retro-style font
    Font font;
    font.loadFromFile("./font/ka1.ttf");

    // Set the font t our retro-style
    hud.setFont(font);

    // Make nice and big
    hud.setCharacterSize(43);

    // Choose a color
    hud.setFillColor(Color::White);

    hud.setPosition(15, 15);

    // Here is our clock for timing everything
    Clock clock;

    while(window.isOpen())
    {
        /*
        <-- Handle the player input -->
        */
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
    
            // Quit the game when the window is closed
            window.close();
        }

        // Handle the player quitting
        if (Keyboard::isKeyPressed(Keyboard::Escape))
        {
            window.close();
        }

        // Handle the pressing and releasing of the arrow keys
        if (Keyboard::isKeyPressed(Keyboard::Left))
        {
            bat.moveLeft();
        }
        else
        {
            bat.stopLeft();
        }

        if (Keyboard::isKeyPressed(Keyboard::Right))
        {
            bat.moveRight();
        }
        else
        {
            bat.stopRight();
        }
        /* 
        <-- Update the bat, the ball and the HUD
        */

        // Update the delta time
        Time dt = clock.restart();
        bat.update(dt);
        ball.update(dt);

        // Update the HUD text
        std::stringstream ss;
        ss << "Score: " << score << "   Lives: " << lives;
        hud.setString(ss.str());

        // Handle ball hitting the bottom
        if (ball.getPosition().top > window.getSize().y)
        {
            // reverse the ball direction
            ball.reboundBottom();

            // remove a life
            lives--;

            // Check for cero lives
            if (lives < 1)
            {
                // reset the score
                score = 0;
                // reset lives
                lives = 3;
                ball.resetVelocity();
            }
        }

        // Handle ball hitting top
        if  (ball.getPosition().top < 0)
        {
            ball.reboundBatOrTop();

            // Add a point to the player score
            score++;
            ball.increaseVelocity(score);
        }
        
        // Handle the ball hitting sides
        if (ball.getPosition().left < 0 || ball.getPosition().left + ball.getPosition().width > window.getSize().x)
        {
            ball.reboundSides();
        }

        // Has the ball hit the bat?
        if (ball.getPosition().intersects(bat.getPosition()))
        {
            // Hit detected so reverse the ball and score a point
            ball.reboundBatOrTop();
        }
        /*
        <-- Draw the bat, the ball and the HUD -->
        */

       window.clear();
       window.draw(hud);
       window.draw(ball.getShape());
       window.draw(bat.getShape()); 
       window.display();
    }

    return 0;
}