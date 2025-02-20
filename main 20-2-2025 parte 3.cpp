#include <iostream>
#include <ctime>
#include <cstdlib>
#include <climits>
#include <cmath>
#include <conio2.h>

using namespace std;

const int bordeSup = 5;
const int bordeIzq = 2;
const int bordeDer = 24;
const int bordeInf = 14;

class Sistema{
private:
	int puntaje = 0;
	int vidas = 5;
public:
	void DibujarPlantilla();
};

void Sistema::DibujarPlantilla(){
	cout<<"Instrucciones:"<<endl;
	cout<<"Movimiento: WASD"<<endl;
	cout<<"Muevete para esquivar los meteoritos y dispara a las X!(25)"<<endl;
	cout<<"-------------------------"<<endl;
	for(int i = 0;i < 10;i++){
	cout<<"-                       -"<<endl;};
	cout<<"-------------------------"<<endl;
	cout<<"                         "<<endl;
	cout<<"> Puntaje: "<<puntaje<<endl;
	cout<<"> Vidas: "<<vidas<<endl;
}

class EstructuraDePosicion{
private:
	
	clock_t tempo;
	clock_t paso;
	int direccion; //direccion xy
	int col;
	int x,y;
	void borrar();
	
public:
	EstructuraDePosicion(int velocidad,int color);
    int PosX(){return x;};
	int PosY(){return y;};
	virtual void resetposicion();
	virtual void dibujar();
	virtual void mover();
	void start();
};

class Meteorito: public EstructuraDePosicion{
private:
	
public:
};

class X: public EstructuraDePosicion {
private:
	
public:
};

class NaveJugador{
public:
	int X, Y;
	void resetposicion (){gotoxy(11,14);};
	void borrar(){};
	void dibujar(){};
};

class Disparo{
private:
	
public:
};
class Pelota{
	
	clock_t tempo;
	clock_t paso;
	int direccionX; //cambiar a 1
	int direccionY; //cambiar a 1
	int col;
	int x,y;
	void borrar();
	void dibujar(); //public virtual
	void mover(); // public virtual
	
public:
	
	Pelota(int velocidad,int color);
	void start();
	
	
	
};

Pelota::Pelota(int velocidad, int color=WHITE){
	
	paso=CLOCKS_PER_SEC/velocidad;
	tempo=clock();
	col=color;
	direccionX = 1;
	//direccionY = 1;
	x=rand()%20+1;
	y= 5;
	
}

void Pelota::start(){
	textcolor(col);
	
	
	if(tempo+paso<clock()){
		borrar();
		mover();
		dibujar();
		tempo=clock();
	}
}



void Pelota::borrar(){
	gotoxy(x,y);
	textcolor(7);
	cout<<' ';
	textcolor(col);
}

void Pelota::dibujar(){
	gotoxy(x,y);
	cout<<'X';
}

void Pelota::mover(){
	
	if (x >= bordeDer) {
		direccionX = -1;
	}
	if (x <= bordeIzq) {
		direccionX = 1;
	}
	//if (y <= bordeSup) {
	//	direccionY = 1;
	//}
	//if (y >= bordeInf) {
	//	direccionY = -1;
	//}
	x = x + (1 * direccionX);
	//y = y + (1 * direccionY);
}	






int main(int argc, char *argv[]) {
    Sistema sistema;
	sistema.DibujarPlantilla();
	NaveJugador NaveJ;
	Pelota *p1 = new Pelota(20,32);
	Pelota *p2 = new Pelota(20,32);
	
	while(true){
		p1->start();
		p2->start();
		if (kbhit()) {
			
			int tecla= getch();
			switch(tecla){
			case 'w':
				if (NaveJ.Y < bordeSup){
					
					NaveJ.Y += 1;
				};
                break;
			case 'a':
				if (NaveJ.X > bordeIzq){
					NaveJ.X -= 1;
				};
				break;
			case 's':
				if (NaveJ.Y > bordeInf){
					NaveJ.Y -= 1;
				};
				break;
			case 'd':
				if (NaveJ.X < bordeDer) {
					NaveJ.X += 1;
				};
				break;
			case ' ':
				break;
			};
			
		};
	};
	
	
	
	return 0;
}
