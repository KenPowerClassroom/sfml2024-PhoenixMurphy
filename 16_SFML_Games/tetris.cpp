 #include <SFML/Graphics.hpp>
#include <time.h>
using namespace sf;

const int BOARD_HEIGHT = 20; // the height of the board (colum)
const int BOARD_WIDTH = 10; // the width of the board (row)

int field[BOARD_HEIGHT][BOARD_WIDTH] = {0}; //the amount of boards there is

struct Point
{int x,y;} shapeWidth[4], shapeHeight[4]; //co ordinates of the shapes

int figures[7][4] = // matrix that controls the shapes
{
    1,3,5,7, // I 
    2,4,5,7, // Z
    3,5,4,6, // S
    3,5,4,7, // T
    2,3,5,7, // L
    3,5,7,6, // J
    2,3,4,5, // O
};

bool check() // collision detection
{
   for (int i=0;i<4;i++)
      if (shapeWidth[i].x<0 || shapeWidth[i].x>=BOARD_WIDTH || shapeWidth[i].y>=BOARD_HEIGHT) return 0;
      else if (field[shapeWidth[i].y][shapeWidth[i].x]) return 0;

   return 1;
};


int tetris()
{
    srand(time(0));     

    RenderWindow window(VideoMode(320, 480), "The Game!");

    Texture tetrisBlockTexture,backgroundTexture,boardFrameTexture;
    tetrisBlockTexture.loadFromFile("images/tetris/tiles.png");
    backgroundTexture.loadFromFile("images/tetris/background.png");
    boardFrameTexture.loadFromFile("images/tetris/frame.png");

    Sprite sprite(tetrisBlockTexture), background(backgroundTexture), frame(boardFrameTexture);

    int dx=0; bool rotate=0; int colorNum=1;
    float timer=0,delay=0.3; 

    Clock clock;

    while (window.isOpen())
    {
        float time = clock.getElapsedTime().asSeconds();
        clock.restart();
        timer+=time;

        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();

            if (event.type == Event::KeyPressed)
              if (event.key.code==Keyboard::Up) rotate=true;
              else if (event.key.code==Keyboard::Left) dx=-1; //moves it right
              else if (event.key.code==Keyboard::Right) dx=1; //moves it left
        }

    if (Keyboard::isKeyPressed(Keyboard::Down)) delay=0.05; //makes the shape go faster

    //// <- Move -> ///
    for (int i=0;i<4;i++)  { shapeHeight[i]=shapeWidth[i]; shapeWidth[i].x+=dx; }
    if (!check()) for (int i=0;i<4;i++) shapeWidth[i]=shapeHeight[i];

    //////Rotate//////
    if (rotate)
      {
        Point p = shapeWidth[1]; //center of rotation
        for (int i=0;i<4;i++)
          {
            int x = shapeWidth[i].y-p.y;
            int y = shapeWidth[i].x-p.x;
            shapeWidth[i].x = p.x - x;
            shapeWidth[i].y = p.y + y;
           }
           if (!check()) for (int i=0;i<4;i++) shapeWidth[i]=shapeHeight[i]; 
      }

    ///////Tick//////
    if (timer>delay)
      {
        for (int i=0;i<4;i++) { shapeHeight[i]=shapeWidth[i]; shapeWidth[i].y+=1; }

        if (!check())
        {
         for (int i=0;i<4;i++) field[shapeHeight[i].y][shapeHeight[i].x]=colorNum;

         colorNum=1+rand()%7; // gets a random colour for the shape
         int randomisedShape=rand()%7; // randomises the different shapes that appear 
         for (int i=0;i<4;i++)
           {
            shapeWidth[i].x = figures[randomisedShape][i] % 2;
            shapeWidth[i].y = figures[randomisedShape][i] / 2;
           }
        }

         timer=0;
      }

    ///////check lines//////////
    int k=BOARD_HEIGHT-1;
    for (int i=BOARD_HEIGHT-1;i>0;i--)
    {
        int count=0;
        for (int j=0;j<BOARD_WIDTH;j++)
        {
            if (field[i][j]) count++;
            field[k][j]=field[i][j];
        }
        if (count<BOARD_WIDTH) k--;
    }

    dx=0; rotate=0; delay=0.3;

    /////////draw//////////
    window.clear(Color::White);    
    window.draw(background);
          
    for (int i=0;i<BOARD_HEIGHT;i++) //when the block isn't at the bottom  
     for (int j=0;j<BOARD_WIDTH;j++) //when the block isn't at the side
       {
         if (field[i][j]==0) continue;
         sprite.setTextureRect(IntRect(field[i][j]*18,0,18,18));
         sprite.setPosition(j*18,i*18); 
         sprite.move(28,31); //offset
         window.draw(sprite);
       }

    for (int i=0;i<4;i++)
      {
        sprite.setTextureRect(IntRect(colorNum*18,0,18,18));
        sprite.setPosition(shapeWidth[i].x*18,shapeWidth[i].y*18);
        sprite.move(28,31); //offset
        window.draw(sprite);
      }

    window.draw(frame);
    window.display();
    }

    return 0;
}
