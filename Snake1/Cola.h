#ifndef COLA_H
#define COLA_H


class Cola
//Esta libreria nos servira para el manejo de coordenadas en todo el cubo de la cola
	// del snake
{
    int xCola,yCola,zCola;
    public:
        Cola(int x,int y,int z);
        int getXCola() { return xCola; }
        int getYCola() { return yCola; }
        int getZCola() { return zCola; }
        void setXCola( int coordx) { xCola = coordx; }
        void setYCola( int coordy) { yCola = coordy; }
        void setZCola( int coordz) { zCola = coordz; }
};

#endif // COLA_H
