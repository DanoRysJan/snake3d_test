#ifndef SNAKE_H
#define SNAKE_H



class Snake
{
	//Esta libreria nos servira para el manejo de coordenadas en todo el cubo de todo el 
	//snake
    public:
        Snake(int x,int y,int z);
        int getXSnake();
        int getYSnake();
        int getZSnake();
        void setXSnake(int coordx);
        void setYSnake(int coordv);
        void setZSnake(int coordz);
};

#endif // SNAKE_H
