#include <iostream>
#include <conio2.h>
#include <ctime>

using namespace std;

const int bordeSup = 5;
const int bordeIzq = 2;
const int bordeDer = 24;
const int bordeInf = 14;

class Pelota{
	
	clock_t tempo;
	clock_t paso;
	int direccionX;
	int direccionY;
	int col;
	int x,y;
	void borrar();
	void dibujar();
	void mover();
	
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
	int puntaje = 0;
	int vidas = 0;
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
	Pelota *p1 = new Pelota(20,32);
	Pelota *p2 = new Pelota(20,32);
	
	while(true){
		p1->start();
		p2->start();
	}
	
	
	
	return 0;
}
