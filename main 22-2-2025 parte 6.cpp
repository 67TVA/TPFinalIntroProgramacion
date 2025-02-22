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
	cout<<"> Vidas: "<<vidas<<endl;
	cout<<"> Puntaje: "<<puntaje<<endl;
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
	y= 6;
	
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


	setY (PosY() + 1);

}	

class X: public EstructuraDePosicion {
private:
	
public:
	void dibujar();
	X(int velocidad , int color ) : EstructuraDePosicion(velocidad, color) {};
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

class Disparo : public EstructuraDePosicion{
private:
	
public:
	Disparo(int velocidad = 8, int color = 3) : EstructuraDePosicion(velocidad, color) {};
	void dibujar();
	void mover();
};

void Disparo::dibujar(){
	gotoxy(PosX(),PosY());
	cout<<'Y';
}
void Disparo::mover(){
	
	
	
	if (PosY() == bordeSup) {
	}
	
	//if (y >= bordeInf) {
	//	direccionY = -1;
	
	setY (PosY() - 1);
	
}	




int main(int argc, char *argv[]) {
	int vidas = 5;
	int puntaje = 0;
	bool DisparoActivo = false;
    Sistema sistema;
	sistema.DibujarPlantilla();
	NaveJugador NaveJ;
	NaveJ.resetposicion();
	EstructuraDePosicion *p1 = new X(20,31);
	EstructuraDePosicion *p2 = new X(30,32);
	p2->setY(7);
	EstructuraDePosicion *m1 = new Meteorito;
	EstructuraDePosicion *d1 = new Disparo;
	
	
	while(vidas > 0){
		p1->start();
		p2->start();
		m1->start();
		if (m1->PosX() == NaveJ.X && m1->PosY() == NaveJ.Y){
			NaveJ.resetposicion();
			vidas--;
			gotoxy(10,17);
			textcolor(7);
			cout<<vidas;
		};
		if (DisparoActivo){
			d1->start();
			if (d1->PosY() == bordeSup-1){
				DisparoActivo = false;
				gotoxy(d1->PosX(), bordeSup-1);
				textcolor(7);
				cout<<"-";
			}
			if(d1->PosX() == p1->PosX() && d1->PosY() == p1->PosY() || d1->PosX() == p2->PosX() && d1->PosY() == p2->PosY()){
				puntaje += 100;
				DisparoActivo = false;
				gotoxy(12,18);
				textcolor(7);
			    cout<<puntaje;
			};
			
		};

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
				if (!DisparoActivo){
					d1->setX(NaveJ.X);
					d1->setY(NaveJ.Y-1);
					DisparoActivo = true;
				}
				break;
			};
			
		};
	};
	
	
	return 0;
}
