#include "Snake.h"
int xSnake,ySnake,zSnake;
//programa para el uso de las coordenadas del snake
Snake::Snake(int x,int y,int z)
{
    xSnake = x;
    ySnake = y;
    zSnake = z;
}
//solo se retorna cada una de las coordenas para su uso dentro del main

int Snake::getXSnake(){
    return xSnake;
}

int Snake::getYSnake(){
    return ySnake;
}

int Snake::getZSnake(){
    return zSnake;
}

void Snake::setXSnake( int coordy ){
        xSnake = coordy;
}

void Snake::setYSnake( int coordx ){
    ySnake = coordx;
}

void Snake::setZSnake( int coordz ){
    zSnake = coordz;
}

