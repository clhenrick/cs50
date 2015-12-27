//
// breakout.c
//
// Computer Science 50
// Problem Set 3
//

// standard libraries
#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Stanford Portable Library
#include <spl/gevents.h>
#include <spl/gobjects.h>
#include <spl/gwindow.h>

// height and width of game's window in pixels
#define HEIGHT 600
#define WIDTH 400
// margins
#define MTOP 30
#define MBOTTOM 70

// height and width of paddle
#define PHEIGHT 10
#define PWIDTH 60

// height, width, and padding of bricks
#define BHEIGHT 10
#define BWIDTH 40
#define BPADDING 2

// number of rows of bricks
#define ROWS 5

// number of columns of bricks
#define COLS 10

// radius of ball in pixels
#define RADIUS 10

// lives
#define LIVES 3

// prototypes
void initBricks(GWindow window);
GOval initBall(GWindow window);
GRect initPaddle(GWindow window);
GLabel initScoreboard(GWindow window);
void updateScoreboard(GWindow window, GLabel label, int points);
GObject detectCollision(GWindow window, GOval ball);

int main(void)
{
    // seed pseudorandom number generator
    srand48(time(NULL));

    // instantiate window
    GWindow window = newGWindow(WIDTH, HEIGHT);

    // instantiate bricks
    initBricks(window);

    // instantiate ball, centered in middle of window
    GOval ball = initBall(window);

    // instantiate paddle, centered at bottom of window
    GRect paddle = initPaddle(window);

    // instantiate scoreboard, centered in middle of window, just above ball
    GLabel label = initScoreboard(window);

    // number of bricks initially
    int bricks = COLS * ROWS;

    // number of lives initially
    int lives = LIVES;

    // number of points initially
    int points = 0;

    // set velocity for X and Y to random values
    float velocityX = drand48() * 0.1;
    float velocityY = 0.02;

    // keep playing until game over
    while (lives > 0 && bricks > 0)
    {
        // set up listener for mouse move
        GEvent event = getNextEvent(MOUSE_EVENT);

        if (event != NULL)
        {
                if (getEventType(event) == MOUSE_MOVED)
                {
                        double x = getX(event) - getWidth(paddle) / 2;
                        setLocation(paddle, x, HEIGHT - MBOTTOM);
                }
        }

        // logic for moving the ball around the window
        move(ball, velocityX, velocityY);

        if (getX(ball) + getWidth(ball) >= getWidth(window))
        {
            velocityX = -velocityX;
        }
        else if (getX(ball) <= 0)
        {
            velocityX = -velocityX;
        }
        else if (getY(ball) + getWidth(ball) >= getHeight(window))
        {

            // if the ball passes the paddle remove a life, reset the ball, 
            // & wait for the user's click
            lives -= 1;
            
            if (lives)
            {
                setLocation(ball, WIDTH / 2 - RADIUS / 2, HEIGHT / 2);
                velocityX = drand48() * 0.1;
                waitForClick();
            }
            else 
            {
                break;
            }
            
        }
        else if (getY(ball) <= 0)
        {
            velocityY = -velocityY;
        }

        // detect collision with the paddle or bricks 
        // update the score and number of bricks accordingly
        GObject object = detectCollision(window, ball);

        if (object == NULL)
        {
            // pass
        }
        else if (object == paddle)
        {
            // velocityY = -velocityY;
            printf("collided with paddle \n");
            velocityY = -velocityY;
        }
        else if (strcmp(getType(object), "GRect") == 0)
        {
            printf("collided with brick\n");
            velocityY = -velocityY;
            removeGWindow(window, object);
            bricks -= 1;
            points += 1;
            updateScoreboard(window, label, points);
        } 
        else if (strcmp(getType(object), "GLabel") == 0)
        {
            // pass
        }
    }

    // wait for click before exiting
    waitForClick();

    // game over
    closeGWindow(window);
    return 0;
}

/**
 * Initializes window with a grid of bricks.
 */
void initBricks(GWindow window)
{
    int i, j;
    for (i = 0; i < COLS; i++)
    {
        for (j = 0; j<ROWS; j++)
        {
            GRect brick = newGRect(i * BWIDTH + BPADDING, j * BHEIGHT + BPADDING + MTOP, BWIDTH - BPADDING * 2, BHEIGHT - BPADDING * 2);
            
            if (j == 0) 
            {
                setColor(brick, "BLUE");
            }
            else if (j == 1)
            {
                setColor(brick, "ORANGE");
            }
            else if (j == 2)
            {
                setColor(brick, "GREEN");
            }
            else if (j == 3)
            {
                setColor(brick, "YELLOW");
            }
            else if (j == 4)
            {
                setColor(brick, "RED");
            }
            

            setFilled(brick, true);
            add(window, brick);
        }
    }
}

/**
 * Instantiates ball in center of window.  Returns ball.
 */
GOval initBall(GWindow window)
{
    GOval ball = newGOval(WIDTH / 2 - RADIUS / 2, HEIGHT / 2, RADIUS, RADIUS);
    setColor(ball, "BROWN");
    setFilled(ball, true);
    add(window, ball);
    return ball;
}

/**
 * Instantiates paddle in bottom-middle of window.
 */
GRect initPaddle(GWindow window)
{
    GRect paddle = newGRect(WIDTH/2 - PWIDTH/2, HEIGHT - MBOTTOM, PWIDTH, PHEIGHT);
    setColor(paddle, "BLACK");
    setFilled(paddle, true);
    add(window, paddle);
    return paddle;
}

/**
 * Instantiates, configures, and returns label for scoreboard.
 */
GLabel initScoreboard(GWindow window)
{
    GLabel score = newGLabel("0");
    setFont(score, "SansSerif");
    double x = WIDTH / 2 - getWidth(score) / 2;
    double y = HEIGHT / 2 - getHeight(score) / 2;
    setLocation(score, x, y);
    add(window, score);
    return score;
}

/**
 * Updates scoreboard's label, keeping it centered in window.
 */
void updateScoreboard(GWindow window, GLabel label, int points)
{
    // update label
    char s[12];
    sprintf(s, "%i", points);
    setLabel(label, s);

    // center label in window
    double x = (getWidth(window) - getWidth(label)) / 2;
    double y = (getHeight(window) - getHeight(label)) / 2;
    setLocation(label, x, y);
}

/**
 * Detects whether ball has collided with some object in window
 * by checking the four corners of its bounding box (which are
 * outside the ball's GOval, and so the ball can't collide with
 * itself).  Returns object if so, else NULL.
 */
GObject detectCollision(GWindow window, GOval ball)
{
    // ball's location
    double x = getX(ball);
    double y = getY(ball);

    // for checking for collisions
    GObject object;

    // check for collision at ball's top-left corner
    object = getGObjectAt(window, x, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's top-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-left corner
    object = getGObjectAt(window, x, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // no collision
    return NULL;
}
