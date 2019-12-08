#ifndef COMIDA_H
#define COMIDA_H


class Comida
{
	//Esta libreria nos servira para el manejo de coordenadas en todo el cubo de comidad
	// que saldra de manera aleatoria dentro del escenario
    int xComida,yComida,zComida;
    public:
        Comida(int x,int y,int z);
        int getXComida() { return xComida; }
        int getYComida() { return yComida; }
        int getZComida() { return zComida; }
        void setXComida( int coordx) { xComida = coordx; }
        void setYComida( int coordy) { yComida = coordy; }
        void setZComida( int coordz) { zComida = coordz; }

};

#endif // COMIDA_H
