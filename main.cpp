//simple PONG clone


//SFML headers
#include <SFML/Graphics.hpp>

//for debug, remove later
#include <iostream>

//for random generator
#include "random.h"

//for string conversion
#include "stringnumberconvert.h"




int main()
{
    //initiate random generator
    setRandomSeed();

    //game plays in fullscreen, make fullscreen window
    sf::RenderWindow window(sf::VideoMode::getFullscreenModes()[0], "", sf::Style::Default);

    window.setMouseCursorVisible(false);

    //set fps limit
    window.setFramerateLimit(33);

    //create paddle objects, dimensions and positioning based off of window size

    sf::RectangleShape paddle1(sf::Vector2f(window.getSize().x/100, window.getSize().y/10));
    paddle1.setPosition(0, window.getSize().y/2 - paddle1.getSize().y/2);
    paddle1.setFillColor(sf::Color::White);

    sf::RectangleShape paddle2(sf::Vector2f(window.getSize().x/100, window.getSize().y/10));
    paddle2.setPosition(window.getSize().x - paddle2.getSize().x, window.getSize().y/2 - paddle2.getSize().y/2);
    paddle2.setFillColor(sf::Color::White);

    //create ball
    sf::CircleShape ball(paddle1.getSize().x/2, 30);
    ball.setPosition(window.getSize().x/2 - ball.getRadius(), window.getSize().y/2 - ball.getRadius());
    ball.setFillColor(sf::Color(randomRange(100, 255), randomRange(100, 255), randomRange(100, 255)));

    sf::CircleShape particles[40];

    for (int i = 0; i < 40; i++)
    {
        particles[i].setPosition(-1000, -1000);
        particles[i].setFillColor(sf::Color(ball.getFillColor().r - ball.getFillColor().r/39*i, ball.getFillColor().g - ball.getFillColor().g/39*i, ball.getFillColor().b - ball.getFillColor().b/39*i));
        particles[i].setRadius(ball.getRadius());
        particles[i].setPointCount(30);
    }

    //create scale of window to make text look the same
    sf::Vector2f windowScale(window.getSize().x/1600, window.getSize().y/900);

    //create texts

    //score texts

    sf::Font font;

    font.loadFromFile("font.ttf");

    sf::Text scoreText1("0", font);
    scoreText1.setOrigin(scoreText1.getGlobalBounds().width/2, scoreText1.getGlobalBounds().height/2);
    scoreText1.setPosition(window.getSize().x/2.5, window.getSize().y/6);
    scoreText1.setCharacterSize(50);
    scoreText1.scale(windowScale);
    scoreText1.setColor(sf::Color::White);

    sf::Text scoreText2("0", font);
    scoreText2.setOrigin(scoreText2.getGlobalBounds().width/2, scoreText2.getGlobalBounds().height/2);
    scoreText2.setPosition((window.getSize().x/2.5)*1.5, window.getSize().y/6);
    scoreText2.setCharacterSize(50);
    scoreText2.scale(windowScale);
    scoreText2.setColor(sf::Color::White);

    //create halfway line

    sf::CircleShape halfLine[100];

    for (int i = 0; i < 100; i++)
    {
        halfLine[i].setRadius(((window.getSize().y/100)*1/4)/2);
        halfLine[i].setPointCount(30);
        halfLine[i].setOrigin(halfLine[i].getRadius(), halfLine[i].getRadius());
        halfLine[i].setPosition(window.getSize().x/2, (window.getSize().y/100)*i);
        halfLine[i].setFillColor(sf::Color::White);
    }


    //title text
    sf::Text titleText("Pong!", font);
    titleText.setCharacterSize(50);
    titleText.scale(windowScale);
    titleText.setOrigin(titleText.getGlobalBounds().width/2, titleText.getGlobalBounds().height/2);
    titleText.setPosition(window.getSize().x/2, window.getSize().y/10);
    titleText.setColor(sf::Color::White);

    //declaring some data now

    sf::Vector2f ballSpeed(0, 0);

    int player1Score = 0;

    int player2Score = 0;

    float ballSpeedScale = 1;

    int players = 0;

    sf::Clock move;

    //determine whether we are starting as single or multiplayer, and display title

    window.clear(sf::Color::Black);

    window.draw(titleText);

    window.display();

    for (sf::Clock timer; timer.getElapsedTime().asSeconds() < 2;)
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            return 0;

    sf::Text choiceText("To play singleplayer, press \'S\', to play multiplayer, press \'M\'", font);
    choiceText.setCharacterSize(20);
    choiceText.scale(windowScale);
    choiceText.setOrigin(choiceText.getGlobalBounds().width/2, choiceText.getGlobalBounds().height/2);
    choiceText.setPosition(window.getSize().x/2, window.getSize().y/2);
    choiceText.setColor(sf::Color::White);

    window.draw(choiceText);

    window.display();

    while (true)
    {
        //check for quit
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            return 0;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            players = 1;
            break;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::M))
        {
            players = 2;
            break;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::N))
        {
            players = 0;
            break;
        }
    }

    //initialize ball

    ballSpeed.x = randomRange(1, window.getSize().x/99);
    ballSpeed.y = randomRange(1, window.getSize().y/99);

    if (randomRange(0, 1) == 0)
        ballSpeed.x = -ballSpeed.x;

    if (randomRange(0, 1) == 0)
        ballSpeed.y = -ballSpeed.y;

    window.clear(sf::Color::Black);

    window.draw(paddle1);

    window.draw(paddle2);

    for (int i = 0; i < 100; i++)
        window.draw(halfLine[i]);

    window.draw(ball);

    window.draw(scoreText1);

    window.draw(scoreText2);

    window.display();

    int counter = 0;

    int direction = 1;

    char turn = 'r';

    //main loop
    while (true)
    {
        counter++;

        //check for exit
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            return 0;

        if (move.getElapsedTime().asSeconds() > 0.03)
        {
            move.restart();

            //draw everything

            //clear window

            window.clear(sf::Color::Black);

            //particles
            for (int i = 0; i < 40; i++)
                window.draw(particles[i]);

            //paddles

            window.draw(paddle1);
            window.draw(paddle2);

            //scores

            window.draw(scoreText1);
            window.draw(scoreText2);

            //ball

            window.draw(ball);

            if (counter >= 6)
            {
                counter = 0;

                particles[0].setPosition(ball.getPosition());

                for (int i = 39; i > 0; i--)
                    particles[i].setPosition(particles[i - 1].getPosition());
            }

            //halfline

            for (int i = 0; i < 100; i++)
                window.draw(halfLine[i]);

            //display
            window.display();

            sf::Color c = ball.getFillColor();

            int r = c.r, b = c.b, g = c.g;

            if (direction == 1)
            {
                if (turn == 'r')
                    r += randomRange(-5, 0);

                if (turn == 'b')
                    b += randomRange(-5, 0);

                if (turn == 'g')
                    g += randomRange(-5, 0);
            }

            if (direction == 0)
            {
                if (turn == 'r')
                    r += randomRange(0, 5);

                if (turn == 'b')
                    b += randomRange(0, 5);

                if (turn == 'g')
                    g += randomRange(0, 5);
            }

            if (r > 255)
            {
                r = 255;
                turn = 'b';
            }

            if (g > 255)
            {
                g = 255;
                turn = 'r';
            }

            if (b > 255)
            {
                b = 255;
                turn = 'g';
            }

            if (r < 100)
            {
                r = 100;
                turn = 'b';
            }

            if (b < 100)
            {
                b = 100;
                turn = 'g';
            }

            if (g < 100)
            {
                g = 100;
                turn = 'r';
            }

            if (r == 100 && g == 100 && b == 100)
                direction = 0;

            if (r == 255 && g == 255 && b == 255)
                direction = 1;


            ball.setFillColor(sf::Color(r, g, b));

            for (int i = 0; i  < 40; i++)
                particles[i].setFillColor(sf::Color(ball.getFillColor().r - (ball.getFillColor().r/39)*i, ball.getFillColor().g - (ball.getFillColor().g/39)*i, ball.getFillColor().b - (ball.getFillColor().b/39)*i));


            //move players

            //first player
            if (players != 0)
            {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
                {
                        paddle2.move(0, -(static_cast <int> (window.getSize().y)/60));

                    if (paddle2.getPosition().y < 0)
                        paddle2.setPosition(paddle2.getPosition().x, 0);
                }

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
                {
                        paddle2.move(0, window.getSize().y/60);

                    if (paddle2.getPosition().y + paddle2.getSize().y >= window.getSize().y)
                        paddle2.setPosition(paddle2.getPosition().x, window.getSize().y - 1 - paddle2.getSize().y);
                }
            }
            else
            {
                //players = 1 or 0, so the other must be a computer, so this is CPU

                //calculate distance to move

                float distance = 0;

                distance = -((paddle2.getPosition().y + paddle2.getSize().y/2) - (ball.getPosition().y + ball.getRadius() + ballSpeed.y));

                if ((distance > 0 ? distance : -distance) > paddle2.getSize().y/2)
                {
                    int absDistance = (distance > 0 ? distance : -distance);

                    if (absDistance > window.getSize().y/45)
                    {
                        paddle2.move(0, distance > 0 ? window.getSize().y/45 : -(static_cast <float> (window.getSize().y)/45));
                    }
                    else
                    {
                        paddle2.move(0, distance);
                    }
                }

                if (paddle2.getPosition().y < 0)
                    paddle2.setPosition(paddle2.getPosition().x, 0);

                if (paddle2.getPosition().y + paddle2.getSize().y >= window.getSize().y)
                    paddle2.setPosition(paddle2.getPosition().x, window.getSize().y - 1 - paddle2.getSize().y);
            }

            //second player
            if (players == 2)
            {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
                {
                    paddle1.move(0, -(static_cast <int> (window.getSize().y)/60));

                    if (paddle1.getPosition().y < 0)
                        paddle1.setPosition(paddle1.getPosition().x, 0);
                }

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
                {
                    paddle1.move(0, window.getSize().y/60);

                    if (paddle1.getPosition().y + paddle1.getSize().y >= window.getSize().y)
                        paddle1.setPosition(paddle1.getPosition().x, window.getSize().y - 1 - paddle1.getSize().y);
                }
            }
            else
            {
                //players is 0, so the first player is a CPU

                //calculate distance to move

                float distance = 0;

                distance = -((paddle1.getPosition().y + paddle1.getSize().y/2) - (ball.getPosition().y + ball.getRadius() + ballSpeed.y));

                if ((distance > 0 ? distance : -distance) > paddle1.getSize().y/2)
                {
                    int absDistance = (distance > 0 ? distance : -distance);

                    if (absDistance > window.getSize().y/45)
                    {
                        paddle1.move(0, distance > 0 ? window.getSize().y/45 : -(static_cast <float> (window.getSize().y)/45));
                    }
                    else
                    {
                        paddle1.move(0, distance);
                    }
                }
            }

            //make ball faster

            ballSpeed.x += ballSpeed.x/833;
            ballSpeed.y += ballSpeed.y/833;

            //move ball

            if (ball.getPosition().x > paddle1.getPosition().x + paddle1.getSize().x && ball.getPosition().x + ballSpeed.x <= paddle1.getPosition().x + paddle1.getSize().x)
            {
                //we are going to go past the paddle. See if we hit it
                if (ball.getPosition().y + ball.getRadius()*2 > paddle1.getPosition().y && ball.getPosition().y < paddle1.getPosition().y + paddle1.getSize().y)
                {
                    //ball hit paddle
                    ball.setPosition(paddle1.getPosition().x + paddle1.getSize().x, ball.getPosition().y);
                    ballSpeed.x = -ballSpeed.x;
                }
                else
                {
                    ball.move(ballSpeed.x, 0);
                }
            }
            else if (ball.getPosition().x + ball.getRadius()*2 < paddle2.getPosition().x && ball.getPosition().x + ball.getRadius()*2 + ballSpeed.x >= paddle2.getPosition().x)
            {
                //we are going to go past the paddle. See if we hit it
                if (ball.getPosition().y + ball.getRadius()*2 > paddle2.getPosition().y && ball.getPosition().y < paddle2.getPosition().y + paddle2.getSize().y)
                {
                    //ball hit paddle
                    ball.setPosition(paddle2.getPosition().x, ball.getPosition().y);
                    ballSpeed.x = -ballSpeed.x;
                }
                else
                {
                    ball.move(ballSpeed.x, 0);
                }
            }
            else
            {
                ball.move(ballSpeed.x, 0);
            }

            if (ball.getGlobalBounds().top + ballSpeed.y < 0)
            {
                ball.setPosition(ball.getPosition().x, 0);

                ballSpeed.y = -ballSpeed.y;
            }
            else if (ball.getGlobalBounds().top + ball.getRadius()*2 + ballSpeed.y >= window.getSize().y)
            {
                ball.setPosition(ball.getPosition().x, window.getSize().y - 1 - ball.getRadius()*2);

                ballSpeed.y = -ballSpeed.y;
            }
            else
            {
                ball.move(0, ballSpeed.y);
            }

            //checking for score
            if (ball.getPosition().x + ball.getRadius()*2 < 0)
            {
                //player right gets point
                player2Score++;

                //adjust counter display
                scoreText2.setString(toString(player2Score));

                //reset positions

                paddle1.setPosition(0, window.getSize().y/2 - paddle1.getSize().y/2);
                paddle2.setPosition(window.getSize().x - 1 - paddle2.getSize().x, window.getSize().y/2 - paddle1.getSize().y/2);
                ball.setPosition(window.getSize().x/2 - ball.getRadius(), window.getSize().y/2 - ball.getRadius());

                //get new ball speed

                ballSpeed.x = randomRange(1, window.getSize().x/99);
                ballSpeed.y = randomRange(1, window.getSize().y/99);

                if (randomRange(0, 1) == 0)
                    ballSpeed.x = -ballSpeed.x;

                if (randomRange(0, 1) == 0)
                    ballSpeed.y = -ballSpeed.y;


                //reset scores

                for (sf::Clock timer, move; timer.getElapsedTime().asSeconds() < 2;)
                {
                    if (move.getElapsedTime().asSeconds() > 0.03)
                    {
                        //draw everything

                        //clear window

                        window.clear(sf::Color::Black);

                        //paddles

                        window.draw(paddle1);
                        window.draw(paddle2);

                        //scores

                        window.draw(scoreText1);
                        window.draw(scoreText2);

                        //ball

                        window.draw(ball);

                        //halfline

                        for (int i = 0; i < 100; i++)
                            window.draw(halfLine[i]);

                        //display
                        window.display();

                        //move players

                        //first player
                        if (players != 0)
                        {
                            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
                            {
                                paddle2.move(0, -(static_cast <int> (window.getSize().y)/60));

                                if (paddle2.getPosition().y < 0)
                                    paddle2.setPosition(paddle2.getPosition().x, 0);
                            }

                            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
                            {
                                paddle2.move(0, window.getSize().y/60);

                                if (paddle2.getPosition().y + paddle2.getSize().y >= window.getSize().y)
                                    paddle2.setPosition(paddle2.getPosition().x, window.getSize().y - 1 - paddle2.getSize().y);
                            }
                        }
                        else
                        {
                            //players = 1 or 0, so the other must be a computer, so this is CPU
                            paddle2.setPosition(paddle2.getPosition().x, ball.getPosition().y - paddle2.getGlobalBounds().height/2);
                        }

                        //second player
                        if (players == 2)
                        {
                            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
                            {
                                paddle1.move(0, -(static_cast <int> (window.getSize().y)/60));

                                if (paddle1.getPosition().y < 0)
                                    paddle1.setPosition(paddle1.getPosition().x, 0);
                            }

                            if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
                            {
                                paddle1.move(0, window.getSize().y/60);

                                if (paddle1.getPosition().y + paddle1.getSize().y >= window.getSize().y)
                                    paddle1.setPosition(paddle1.getPosition().x, window.getSize().y - 1 - paddle1.getSize().y);
                            }
                        }
                        else
                        {
                            //players is 0, so the first player is a CPU
                            paddle1.setPosition(paddle1.getPosition().x, ball.getPosition().y - paddle1.getGlobalBounds().height/2);
                        }


                    }
                }
            }

            if (ball.getPosition().x >= window.getSize().x)
            {
                //player left gets point
                player1Score++;

                //adjust counter display
                scoreText1.setString(toString(player1Score));

                //reset positions

                paddle1.setPosition(0, window.getSize().y/2 - paddle1.getSize().y/2);
                paddle2.setPosition(window.getSize().x - 1 - paddle2.getSize().x, window.getSize().y/2 - paddle1.getSize().y/2);
                ball.setPosition(window.getSize().x/2 - ball.getRadius(), window.getSize().y/2 - ball.getRadius());

                //get new ball speed

                ballSpeed.x = randomRange(1, window.getSize().x/99);
                ballSpeed.y = randomRange(1, window.getSize().y/99);

                if (randomRange(0, 1) == 0)
                    ballSpeed.x = -ballSpeed.x;

                if (randomRange(0, 1) == 0)
                    ballSpeed.y = -ballSpeed.y;


                //reset scores

                for (sf::Clock timer, move; timer.getElapsedTime().asSeconds() < 2;)
                {
                    if (move.getElapsedTime().asSeconds() > 0.03)
                    {
                        //draw everything

                        //clear window

                        window.clear(sf::Color::Black);

                        //paddles

                        window.draw(paddle1);
                        window.draw(paddle2);

                        //scores

                        window.draw(scoreText1);
                        window.draw(scoreText2);

                        //ball

                        window.draw(ball);

                        //halfline

                        for (int i = 0; i < 100; i++)
                            window.draw(halfLine[i]);

                        //display
                        window.display();

                        //move players

                        //first player
                        if (players != 0)
                        {
                            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
                            {
                                paddle2.move(0, -(static_cast <int> (window.getSize().y)/60));

                                if (paddle2.getPosition().y < 0)
                                    paddle2.setPosition(paddle2.getPosition().x, 0);
                            }

                            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
                            {
                                paddle2.move(0, window.getSize().y/60);

                                if (paddle2.getPosition().y + paddle2.getSize().y >= window.getSize().y)
                                    paddle2.setPosition(paddle2.getPosition().x, window.getSize().y - 1 - paddle2.getSize().y);
                            }
                        }
                        else
                        {
                            //players = 1 or 0, so the other must be a computer, so this is CPU
                            paddle2.setPosition(paddle2.getPosition().x, ball.getPosition().y - paddle2.getGlobalBounds().height/2);
                        }

                        //second player
                        if (players == 2)
                        {
                            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
                            {
                                paddle1.move(0, -(static_cast <int> (window.getSize().y)/60));

                                if (paddle1.getPosition().y < 0)
                                    paddle1.setPosition(paddle1.getPosition().x, 0);
                            }

                            if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
                            {
                                paddle1.move(0, window.getSize().y/60);

                                if (paddle1.getPosition().y + paddle1.getSize().y >= window.getSize().y)
                                    paddle1.setPosition(paddle1.getPosition().x, window.getSize().y - 1 - paddle1.getSize().y);
                            }
                        }
                        else
                        {
                            //players is 0, so the first player is a CPU
                            paddle1.setPosition(paddle1.getPosition().x, ball.getPosition().y - paddle1.getGlobalBounds().height/2);
                        }
                    }
                }
            }

            //check for restart

            if (player1Score == 10 || player2Score == 10)
            {
                //player has won display text

                sf::Text winText;

                if (player2Score == 10)
                    winText.setString("Right player wins!");
                else
                    winText.setString("Left player wins!");

                winText.setCharacterSize(30);
                winText.scale(windowScale);
                winText.setOrigin(winText.getGlobalBounds().width/2, winText.getGlobalBounds().height/2);
                winText.setPosition(window.getSize().x/2, window.getSize().y/8);
                winText.setColor(sf::Color::White);

                //play again text
                sf::Text playAgain("If you want to play again, press space. Press escape to quit.", font);
                playAgain.setCharacterSize(20);
                playAgain.scale(windowScale);
                playAgain.setOrigin(playAgain.getGlobalBounds().width/2, playAgain.getGlobalBounds().height/2);
                playAgain.setPosition(window.getSize().x/2, window.getSize().y/5);
                playAgain.setColor(sf::Color::White);

                window.clear(sf::Color::Black);

                window.draw(winText);

                window.draw(playAgain);

                sf::sleep(sf::seconds(1));

                window.display();

                bool quitLoop = false;

                while (!quitLoop)
                {
                    //check for escape
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                        return 0;

                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
                    {
                        //to play again, we first decide what kind of game to play

                        //create text for choice

                        window.clear(sf::Color::Black);

                        window.draw(choiceText);

                        window.display();

                        //reset stuff
                        player1Score = 0;
                        player2Score = 0;

                        ball.setPosition(window.getSize().x/2 - ball.getRadius(), window.getSize().y/2 - ball.getRadius());

                        paddle1.setPosition(0, window.getSize().y/2 - paddle1.getGlobalBounds().height/2);
                        paddle2.setPosition(window.getSize().x - paddle2.getGlobalBounds().width, window.getSize().y/2 - paddle2.getGlobalBounds().height/2);

                        while (true)
                        {
                            //check for escape
                            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                                return 0;

                            if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
                            {
                                players = 1;
                                quitLoop = true;
                                break;
                            }

                            if (sf::Keyboard::isKeyPressed(sf::Keyboard::M))
                            {
                                players = 2;
                                quitLoop = true;
                                break;
                            }

                            sf::Event event;

                            while (window.pollEvent(event))
                                ;
                        }
                    }
                }
            }
        }
    }
}
