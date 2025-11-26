 #include <SFML/Graphics.hpp>
#include <time.h>
#include "TetrisPlayer.h"
using namespace sf;


//struct Point
//{int x,y;} shapeWidth[MAX_SIZE], shapeHeight[MAX_SIZE]; //co ordinates of the shapes

int shapes[7][4] = // matrix that controls the shapes
{
    1,3,5,7, // I 
    2,4,5,7, // Z
    3,5,4,6, // S
    3,5,4,7, // T
    2,3,5,7, // L
    3,5,7,6, // J
    2,3,4,5, // O
};

void draw(RenderWindow &t_window, int t_colorNum)
{
    Texture tetrisBlockTexture, backgroundTexture, boardFrameTexture;
    tetrisBlockTexture.loadFromFile("images/tetris/tiles.png");
    backgroundTexture.loadFromFile("images/tetris/background.png");
    boardFrameTexture.loadFromFile("images/tetris/frame.png");

    Sprite sprite(tetrisBlockTexture), background(backgroundTexture), frame(boardFrameTexture);

    t_window.clear(Color::White);
    t_window.draw(background);
    for (int height = 0; height < BOARD_HEIGHT; height++) //when the block isn't at the bottom  
        for (int width = 0; width < BOARD_WIDTH; width++) //when the block isn't at the side
        {
            if (field[height][width] == 0)
            {
                continue;
            }
            sprite.setTextureRect(IntRect(field[height][width] * 18, 0, 18, 18));
            sprite.setPosition(width * 18, height * 18);
            sprite.move(28, 31); //offset
            t_window.draw(sprite);
        }

    for (int i = 0; i < MAX_SIZE; i++)
    {
        sprite.setTextureRect(IntRect(t_colorNum * 18, 0, 18, 18));
        sprite.setPosition(shape[i].x * 18, shape[i].y * 18);
        sprite.move(28, 31); //offset
        t_window.draw(sprite);
    }

    t_window.draw(frame);
    t_window.display();
}

int tetris()
{
    srand(time(0));     

    RenderWindow window(VideoMode(320, 480), "The Game!");

    TetrisPlayer player;

    /*Texture tetrisBlockTexture,backgroundTexture,boardFrameTexture;
    tetrisBlockTexture.loadFromFile("images/tetris/tiles.png");
    backgroundTexture.loadFromFile("images/tetris/background.png");
    boardFrameTexture.loadFromFile("images/tetris/frame.png");*/

    int dx=0; bool rotate=0; int colorNum=1;
    float timer=0,delay=0.3; 

    Clock clock;

    while (window.isOpen())
    {
        float time = clock.getElapsedTime().asSeconds();
        clock.restart();
        timer += time;

        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();

            if (event.type == Event::KeyPressed)
            {
                if (event.key.code == Keyboard::Up)
                {
                    player.rotatePlayer();
                }
                else if (event.key.code == Keyboard::Left)
                {
                    dx = -1; //moves it right
                }
                else if (event.key.code == Keyboard::Right)
                {
                    dx = 1; //moves it left
                }
            }
        }

        if (Keyboard::isKeyPressed(Keyboard::Down))
        {
            delay = 0.05; //makes the shape go faster
        }

        //// <- Move -> ///
        for (int i = 0; i < MAX_SIZE; i++) 
        { 
            shapeHeight[i] = shape[i]; shape[i].x += dx; 
        }
        if (!player.check())
        {
            for (int i = 0; i < MAX_SIZE; i++)
            {
                shape[i] = shapeHeight[i];
            }
        }

        //////Rotate//////
        //if (rotate)
        //{
        //    Point pointCoordinate = shapeWidth[1]; //center of rotation
        //    for (int i = 0; i < MAX_SIZE; i++)
        //    {
        //        int x = shapeWidth[i].y - pointCoordinate.y;
        //        int y = shapeWidth[i].x - pointCoordinate.x;
        //        shapeWidth[i].x = pointCoordinate.x - x;
        //        shapeWidth[i].y = pointCoordinate.y + y;
        //    }
        //    if (!player.check()) for (int i = 0; i < 4; i++) shapeWidth[i] = shapeHeight[i];
        //}

        ///////Tick//////
        if (timer > delay)
        {
            for (int i = 0; i < MAX_SIZE; i++) { shapeHeight[i] = shape[i]; shape[i].y += 1; }

            if (!player.check())
            {
                for (int i = 0; i < MAX_SIZE; i++) field[shapeHeight[i].y][shapeHeight[i].x] = colorNum;

                colorNum = 1 + rand() % 7; // gets a random colour for the shape
                int randomisedShape = rand() % 7; // randomises the different shapes that appear 
                for (int i = 0; i < MAX_SIZE; i++)
                {
                    shape[i].x = shapes[randomisedShape][i] % 2;
                    shape[i].y = shapes[randomisedShape][i] / 2;
                }
            }

            timer = 0;
        }

        ///////check lines//////////
        int line = BOARD_HEIGHT - 1;
        for (int height = BOARD_HEIGHT - 1; height > 0; height--)
        {
            int count = 0;
            for (int width = 0; width < BOARD_WIDTH; width++)
            {
                if (field[height][width])
                {
                    count++;
                }
                field[line][width] = field[height][width];
            }
            if (count < BOARD_WIDTH)
            {
                line--;
            }
        }

        dx = 0; rotate = 0; delay = 0.3;

        /////////draw//////////
        //window.clear(Color::White);    
        //window.draw(background);
        //      
        //for (int i=0;i<BOARD_HEIGHT;i++) //when the block isn't at the bottom  
        // for (int j=0;j<BOARD_WIDTH;j++) //when the block isn't at the side
        //   {
        //     if (field[i][j]==0) continue;
        //     sprite.setTextureRect(IntRect(field[i][j]*18,0,18,18));
        //     sprite.setPosition(j*18,i*18); 
        //     sprite.move(28,31); //offset
        //     window.draw(sprite);
        //   }

        //for (int i=0;i<4;i++)
        //  {
        //    sprite.setTextureRect(IntRect(colorNum*18,0,18,18));
        //    sprite.setPosition(shapeWidth[i].x*18,shapeWidth[i].y*18);
        //    sprite.move(28,31); //offset
        //    window.draw(sprite);
        //  }

        //window.draw(frame);
        //window.display();
        //}
        draw(window, colorNum);
    }

    return 0;
}

    
