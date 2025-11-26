#pragma once

const int BOARD_HEIGHT = 20; // the height of the board (colum)
const int BOARD_WIDTH = 10; // the width of the board (row)
const int MAX_SIZE = 4;

int field[BOARD_HEIGHT][BOARD_WIDTH] = { 0 }; //the amount of boards there is

struct Point
{
    int x, y;
} shape[4], shapeHeight[4];

class TetrisPlayer
{
public:
    TetrisPlayer() = default;
    bool check()
    {
        for (int i = 0; i < MAX_SIZE; i++)
        {
            if (shape[i].x < 0 || shape[i].x >= BOARD_WIDTH || shape[i].y >= BOARD_HEIGHT)
            {
                return false;
            }
            if (field[shape[i].y][shape[i].x])
            {
                return false;
            }
        }
        return true;
    }
    bool rotatePlayer()
    {
        rotate = true;
        if (rotate)
        {
            Point pointCoordinate = shape[1]; //center of rotation
            for (int i = 0; i < MAX_SIZE; i++)
            {
                int x = shape[i].y - pointCoordinate.y;
                int y = shape[i].x - pointCoordinate.x;
                shape[i].x = pointCoordinate.x - x;
                shape[i].y = pointCoordinate.y + y;
                return true;
            }
            if (!check())
            {
                for (int i = 0; i < 4; i++) shape[i] = shapeHeight[i];
            }
        }
        return false;
    }
private:
    bool rotate = false;
};