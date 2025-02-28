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

void EstructuraDePosicion::resetposicion(){
	
}

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
	
	
	x = x + (1 * direccion);
	
}	

class Meteorito: public EstructuraDePosicion{
private:
	
public:
	Meteorito(int velocidad = 4, int color = 6) : EstructuraDePosicion(velocidad, color) {}
	void dibujar();
	void mover();
	void resetposicion();
};
void Meteorito::dibujar(){
	gotoxy(PosX(),PosY());
	cout<<'O';
}
void Meteorito::mover(){
	
	
	
	if (PosY() >=bordeInf) {
		resetposicion();
	}
	
	
	setY (PosY() + 1);
	
}	
void Meteorito::resetposicion(){
	setY (4);
	setX (rand()%24+2);
	if (PosX() > 24){setX(24);};
	
}

class X: public EstructuraDePosicion {
private:
	
public:
	void dibujar();
	void resetposicion();
	X(int velocidad , int color ) : EstructuraDePosicion(velocidad, color) {};
};

void X::dibujar(){
	gotoxy(PosX(),PosY());
	cout<<'X';
}

void X::resetposicion(){
	gotoxy(PosX(),PosY());
	textcolor(7);
	cout<<' ';
	int d = (rand()%2+1);
	switch(d){
	case 1:
		setX (2);
		break;
	case 2:
		setX(23);
		break;
	};
	setY (rand()%5+6);
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
	
	
	setY (PosY() - 1);
	
}	
class Sistema{
private:
	int puntaje = 0;
	int vidas = 5;
	int mensaje;
	bool DisparoActivo = false;
	EstructuraDePosicion *p1 = new X(20,31);
	EstructuraDePosicion *p2 = new X(30,32);
	EstructuraDePosicion *m1 = new Meteorito;
	EstructuraDePosicion *d1 = new Disparo;
	NaveJugador NaveJ;
	void DibujarPlantilla();
	void MensajePantalla();
	void Teclado();
	void gameover();
	void Logica();
	void Colisiones();
	
public:
	Sistema();
	void IniciarJuego();
};


Sistema::Sistema(){
	NaveJ.resetposicion();
	p2->setY(7);
}

void Sistema::DibujarPlantilla(){
	gotoxy(1,1);
	
	cout<<"Instrucciones:"<<endl;
	cout<<"Movimiento: WASD - Disparo: espacio"<<endl;
	cout<<"Muevete para esquivar los meteoritos y dispara a las X!"<<endl;
	cout<<"-------------------------"<<endl;
	for(int i = 0;i < 10;i++){
		cout<<"-                       -"<<endl;};
	cout<<"-------------------------"<<endl;
	cout<<"                         "<<endl;
	cout<<"> Vidas: "<<vidas<<endl;
	cout<<"> Puntaje: "<<puntaje<<endl;
	NaveJ.resetposicion();
}



void Sistema::Teclado(){
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
}

void Sistema::MensajePantalla(){
	DisparoActivo = false;
	gotoxy (27,10);
	mensaje = rand()%3+1;
	switch(mensaje){
	case 1:
		cout<<"Good shot!        ";
		break;
	case 2:
		cout<<"Bullseye!         ";
		break;
	case 3:
		cout<<"Amazing!         ";
		break;
		
	};
	gotoxy(12,18);
	textcolor(7);
	cout<<puntaje;
}

void Sistema::gameover(){
	gotoxy(9,9);
	textcolor(4);
	cout<<"GAMEOVER";
	gotoxy(9,10);
	cout<<"Puntaje: "<<puntaje;
	textcolor(7);
	gotoxy(1,17);
	
}

void Sistema::Logica(){
	p1->start();
	p2->start();
	m1->start();
}
void Sistema::Colisiones(){
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
		if(d1->PosX() == p1->PosX() && d1->PosY() == p1->PosY()){
			puntaje += 150;
			MensajePantalla();
			p1->resetposicion();
			
		};
		if(d1->PosX() == p2->PosX() && d1->PosY() == p2->PosY()){
			puntaje += 100;
			MensajePantalla();
			p2->resetposicion();
		};
		
	};
}


void Sistema::IniciarJuego(){
	DibujarPlantilla();
	while (vidas > 0){
		Logica();
		Colisiones();
		Teclado();
		
	}
	gameover();
}

int main(int argc, char *argv[]) {
	Sistema sistema;
	sistema.IniciarJuego();
	
	
	return 0;
}
