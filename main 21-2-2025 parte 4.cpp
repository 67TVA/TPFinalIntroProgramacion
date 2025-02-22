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
	void setX(int a){ x = a;};
	void setY(int b){ y = b;};
	virtual void resetposicion();
	virtual void dibujar();
	virtual void mover();
	void start();
};
EstructuraDePosicion::EstructuraDePosicion(int velocidad, int color=WHITE){
	
	paso=CLOCKS_PER_SEC/velocidad;
	tempo=clock();
	col=color;
	direccion = 1;
	x=rand()%20+1;
	y= 5;
	
}

void EstructuraDePosicion::start(){
	textcolor(col);
	
	
	if(tempo+paso<clock()){
		borrar();
		mover();
		dibujar();
		tempo=clock();
	}
}



void EstructuraDePosicion::borrar(){
	gotoxy(x,y);
	textcolor(7);
	cout<<' ';
	textcolor(col);
}

void EstructuraDePosicion::resetposicion(){}

void EstructuraDePosicion::dibujar(){
	gotoxy(x,y);
	cout<<'x';
}

void EstructuraDePosicion::mover(){
	
	if (x >= bordeDer) {
		direccion = -1;
	}
	if (x <= bordeIzq) {
		direccion = 1;
	}
	//if (y <= bordeSup) {
	//	direccionY = 1;
	//}
	//if (y >= bordeInf) {
	//	direccionY = -1;
	//}
	x = x + (1 * direccion);
	//y = y + (1 * direccionY);
}	

class Meteorito: public EstructuraDePosicion{
private:
	
public:
	Meteorito(int velocidad = 4, int color = 6) : EstructuraDePosicion(velocidad, color) {}
	void dibujar();
	void mover();
};
void Meteorito::dibujar(){
	gotoxy(PosX(),PosY());
	cout<<'O';
}
void Meteorito::mover(){
	

	
	if (PosY() >=bordeInf) {
		setX (rand()%24+2);
		setY (4);
	}

	//if (y >= bordeInf) {
	//	direccionY = -1;

	setY (PosY() + 1);

}	

class X: public EstructuraDePosicion {
private:
	
public:
	void dibujar();
};

void X::dibujar(){
	gotoxy(PosX(),PosY());
	cout<<'X';
}


class NaveJugador{
public:
	int X,Y;
	void resetposicion (){
		borrar();
		X = 13;
		Y = 14;
		gotoxy(X,Y);
		dibujar();
	};
	void borrar();
	void dibujar();
};
void NaveJugador::borrar(){
	gotoxy(X,Y);
	textcolor(7);
	cout<<' ';
}
void NaveJugador::dibujar(){
	gotoxy(X,Y);
	cout<<'T';
}

class Disparo{
private:
	
public:
};






int main(int argc, char *argv[]) {
    Sistema sistema;
	sistema.DibujarPlantilla();
	NaveJugador NaveJ;
	NaveJ.resetposicion();
	EstructuraDePosicion *p1 = new EstructuraDePosicion(20,32);
	EstructuraDePosicion *p2 = new EstructuraDePosicion(20,32);
	EstructuraDePosicion *m1 = new Meteorito;
	
	
	while(true){
		p1->start();
		p2->start();
		m1->start();
		if (kbhit()) {
			
			int tecla= getch();
			switch(tecla){
			case 'w':
				if (NaveJ.Y > bordeSup){
					NaveJ.borrar();
					NaveJ.Y -= 1;
					NaveJ.dibujar();
				};
                break;
			case 'a':
				if (NaveJ.X > bordeIzq){
					NaveJ.borrar();
					NaveJ.X -= 1;
					NaveJ.dibujar();
				};
				break;
			case 's':
				if (NaveJ.Y < bordeInf){
					NaveJ.borrar();
					NaveJ.Y += 1;
					NaveJ.dibujar();
				};
				break;
			case 'd':
				if (NaveJ.X < bordeDer) {
					NaveJ.borrar();
					NaveJ.X += 1;
					NaveJ.dibujar();
				};
				break;
			case ' ':
				break;
			};
			
		};
	};
	
	
	
	return 0;
}
