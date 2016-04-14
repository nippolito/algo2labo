#ifndef CARTAS_ENLAZADAS_H_
#define CARTAS_ENLAZADAS_H_

#include <iostream>
#include <cassert>
using namespace std;
#include <string>

typedef unsigned long Nat;
/* 
 * Se puede asumir que el tipo T tiene constructor por copia y operator==
 * No se puede asumir que el tipo T tenga operator=
 */
template <typename T>

class CartasEnlazadas {

  public:

	/**
	 * Crea un nuevo juego.
	 */	
	CartasEnlazadas();

	/**
	 * Una vez copiada, ambos juegos deben ser independientes, 
	 * es decir, cuando se borre una no debe borrar la otra.
	 */	
	CartasEnlazadas(const CartasEnlazadas<T>&);
	
	/**
	 * Acordarse de liberar toda la memoria!
	 */	 
	~CartasEnlazadas();  
	
	/**
	* Agrega un jugador a la mesa. El mismo debe sentarse en la posición 
	* siguiente a la posición del jugador con el mazo azul. Por ejemplo si en la
	* mesa hay 3 jugadores sentados de la siguiente forma: [j1 j2 j3], y el 
	* mazo rojo lo tiene el jugador j3, la mesa debe quedar: [j1 j2 j3 j4].
	* PRE: el jugador a agregar no existe.
	*/
	void agregarJugador(const T& jugador);
	
	/**
	* Adelanta el mazo rojo n posiciones. Por ejemplo: si en la mesa hay 3 
	* jugadores sentados de la siguiente forma: [j1 j2 j3] y el jugador j2
	* tiene el mazo rojo, si se adelanta 1 posicion el mazo rojo pasa al jugador j3. En
	* cambio si el mazo rojo se adelanta 2 posiciones el mazo rojo pasa al jugador j1.
	* En caso de que n sea negativo debe retroceder el mazo rojo -n posiciones.
	* PRE: existe al menos un jugador
	*/
	void adelantarMazoRojo(int n);
	
	/**
	* Adelanta el mazo azul n posiciones. Por ejemplo: si en la mesa hay 3 
	* jugadores sentados de la siguiente forma: [j1 j2 j3] y el jugador j2
	* tiene el mazo azul, si se adelanta 1 posicion el mazo azul pasa al jugador j3. En
	* cambio si el mazo azul se adelanta 2 posiciones el mazo azul pasa al jugador j1.
	* En caso de que n sea negativo debe retroceder el mazo azul -n posiciones.
	* PRE: existe al menos un jugador
	*/
	void adelantarMazoAzul(int n);
	
	/**
	* Devuelve el jugador que tiene el mazo Rojo actualmente.
	* PRE: existe al menos un jugador
	*/
	const T& dameJugadorConMazoRojo() const;
	
	/**
	* Devuelve el jugador que tiene el mazo Azul actualmente.
	* PRE: existe al menos un jugador
	*/
	const T& dameJugadorConMazoAzul() const;
	
	/**
	* Devuelve el jugador que se encuentra n posiciones adelante a la posicion 
	* del jugador con el mazo rojo. En caso de que n sea negativo deberia devolver 
	* el jugador que se encuentra -n posiciones atrás.
	* PRE: existe al menos un jugador
	*/
	const T& dameJugador(int n) const;
	
	/**
	* Devuelve el jugador que se encuentra enfreantado al jugador que tiene el 
	* mazo rojo. Por ejemplo si en la mesa hay cuatros jugadores sentados de la
	* siguiente forma: [J1 J2 J3 J4] y el el jugador J2 tiene el mazo rojo, el
	* resultado debe ser J4.
	* PRE: cantidad de jugadores par, al menos un jugador
	*/
	const T& dameJugadorEnfrentado() const;
	
	/**
	* Elimina el jugador pasado como parámetro.
	* En el caso de que el jugador no exista, el método no debe hacer nada.
	* En el caso de que el jugador tenga algún mazo, se le pasa el mazo al 
	* siguiente jugador en la ronda.
	*/
	void eliminarJugador(const T&);
	
	/**
	* Elimina al jugador que tiene el mazo azul.
	* Por ejemplo si los jugadores estan sentadods de la siguiente forma: 
	* [J1 J2 J3 J4 J5] y el mazo lo tiene el jugador J3. Cuando se eliminan al 
	* jugador con  del mazo, la mesa * debería quedar de la siguiente forma 
	* [J1 J2 J4 J5].
	* En el caso de que algún jugador tenga algún mazo, se le pasa el mazo al 
	* siguiente jugador en la ronda.
	* PRE: al menos un jugador
	*/
	void eliminarJugadorConMazoAzul();
	
	/**
	* Dice si el jugador existe.
	*/
	bool existeJugador(const T&) const;

	/**
	* Le suma los puntos al jugador.
	* PRE: el jugador existe
	*/
	void sumarPuntosAlJugador(const T&, int);
	
	/**
	* Devuelve la cantidad de puntos que tiene el jugador pasado como 
	* parámetro.
	* PRE: el jugador existe
	*/
	int puntosDelJugador(const T&) const;
	
	/**
	* Devuelve al jugador que más puntos tiene.
	* PRE: hay un único jugador que tiene más puntos que todos los demás.
	*/
	const T& ganador() const;
	
	/*
	 * Dice si hay jugadores en la mesa.
	 */
	bool esVacia() const;

	/*
	 * Devuelve la cantidad de jugadores.
	 */
	int tamanio() const;	

	/*
	 * Devuelve true si los juegos son iguales.
	 */
	bool operator==(const CartasEnlazadas<T>&) const;	
	
	/*
	 * Debe mostrar la ronda por el ostream (y retornar el mismo).
	 * CartasEnlazadas vacio: []
	 * CartasEnlazadas con 1 elementos (e1 tiene el mazo azul y el rojo, p es el puntaje): [(e1,p)*]
	 * CartasEnlazadas con 2 elementos (e2 tiene el mazo azul y e1 el mazo rojo, p es el puntaje): [(e2,p), (e1,p)*]
	 * CartasEnlazadas con 3 elementos (e1 tiene el mazo, e3 fue agregado después que e2,
	 * e1 fue agregado antes que e2): [(e1, 0)*, (e3, 0), (e2, 0)]
	 */
	ostream& mostrarCartasEnlazadas(ostream&) const;
  private:
  
	/*
	 * No se puede modificar esta funcion.
	 */
	CartasEnlazadas<T>& operator=(const CartasEnlazadas<T>& otra) {
		assert(false);
		return *this;
	}

	/*
	 * Aca va la implementación del nodo.
	 */
    struct Nodo {
    	T jugador;
    	Nodo* siguiente;
    	Nodo* anterior;
    	int puntaje;
    	Nodo (const T& a) :jugador(a) , puntaje(0), siguiente(NULL), anterior(NULL){};
    	
 
    };

    Nat len;
	Nodo* jMazoAzul;
	Nodo* jMazoRojo;
};


template<class T>
ostream& operator<<(ostream& out, const CartasEnlazadas<T>& a) {
	return a.mostrarCartasEnlazadas(out);
}




// Implementación a hacer por los alumnos.


template <typename T>
CartasEnlazadas<T>::CartasEnlazadas(){
	this->len=0;
	this->jMazoAzul=NULL;
	this->jMazoRojo=NULL;
}

template <typename T>
CartasEnlazadas<T>::~CartasEnlazadas(){
	int i=this->len;
	while(i>0){
		eliminarJugadorConMazoAzul();
		i--;
	}
}

template <typename T>
CartasEnlazadas<T>::CartasEnlazadas(const CartasEnlazadas<T>& otroJuego){
	int i=otroJuego.len;
	if(i==0){
		this->len=i;
		this->jMazoAzul=NULL;
		this->jMazoRojo=NULL;
	}else{
		this->len=0;
		this->jMazoAzul=NULL;
		this->jMazoRojo=NULL;
		Nodo* original=otroJuego.jMazoAzul;
		this->agregarJugador(original->jugador);
		this->sumarPuntosAlJugador(original->jugador,original->puntaje);
		original=original->siguiente;
		Nodo* aux=this->jMazoAzul;
		while(i-1>0){
			this->agregarJugador(original->jugador);
			this->sumarPuntosAlJugador(original->jugador,original->puntaje);
			aux=aux->siguiente;
			if(otroJuego.jMazoRojo==original){
				this->jMazoRojo=aux;
			}
			original=original->siguiente;
			this->adelantarMazoAzul(1);
			i--;

		}
		this->adelantarMazoAzul(1);
	}
}


template <typename T>
void CartasEnlazadas<T>::agregarJugador(const T& jugadorNuevo) {
	Nodo* nuevo= new Nodo(jugadorNuevo);
	if(this->len==0){
		this->jMazoAzul=nuevo;
		this->jMazoRojo=nuevo;
		nuevo->siguiente=nuevo;
		nuevo->anterior=nuevo;
	}else{
		nuevo->siguiente=this->jMazoAzul->siguiente;
		nuevo->anterior=jMazoAzul;
		this->jMazoAzul->siguiente->anterior=nuevo;
		this->jMazoAzul->siguiente=nuevo;
	}
	this->len=this->len+1;
}

template <typename T>

ostream& CartasEnlazadas<T>::mostrarCartasEnlazadas(std::ostream& os ) const {
	os<<"[";
	Nodo* n = this->jMazoAzul;
	if(n!=NULL){
		os<<"("<<n->jugador<<","<<n->puntaje<<")";
		if(this->jMazoRojo->jugador==n->jugador){
			os<<"*";
			}
		n=n->siguiente;
		if(n != jMazoAzul){
			os<<",";
		}
		while (n != jMazoAzul) {
			os<<"("<<n->jugador<<","<<n->puntaje<<")";
			if(this->jMazoRojo->jugador==n->jugador){
			os<<"*";
			}
			n = n->siguiente;
			if(n != jMazoAzul){os<<",";}
		}
	}
	os<<"]";
	}

template <typename T>
void CartasEnlazadas<T>::adelantarMazoRojo(int n){
	int i=n;
	if(i>0){
		while(i>0){
	 		this->jMazoRojo=this->jMazoRojo->siguiente;
	 		i--;
	 	}
	}else{
		while(i<0){
			this->jMazoRojo=this->jMazoRojo->anterior;
			i++;
		}
	}
}

template <typename T>
void CartasEnlazadas<T>::adelantarMazoAzul(int n){
	int i=n;
	if(i>0){
		while(i>0){
	 		this->jMazoAzul=this->jMazoAzul->siguiente;
	 		i--;
	 	}
	}else{
		while(i<0){
			this->jMazoAzul=this->jMazoAzul->anterior;
			i++;
		}
	}
}

template<typename T>
const T& CartasEnlazadas<T>::dameJugadorConMazoRojo() const{
	return this->jMazoRojo->jugador;
}

template<typename T>
const T& CartasEnlazadas<T>::dameJugadorConMazoAzul() const{
	return this->jMazoAzul->jugador;
}


template<typename T>
const T& CartasEnlazadas<T>::dameJugador(int n) const{
	int i=n;
	Nodo* nuevo= this->jMazoRojo;
	if(i>0){
		while(i>0){
	 		nuevo=nuevo->siguiente;
	 		i--;
	 	}
	}else{
		while(i<0){
			nuevo=nuevo->anterior;
			i++;
		}
	}
	return nuevo->jugador;
}

template<typename T>
const T& CartasEnlazadas<T>::dameJugadorEnfrentado() const{
	int i=this->len/2;
	return (dameJugador(i));

}

template<typename T>
void CartasEnlazadas<T>::eliminarJugador(const T& target){
	int i=this->len;
	Nodo* nuevo=this->jMazoAzul;
	Nodo* nuevo2=nuevo->siguiente;
	while(nuevo->jugador!=target){
		nuevo=nuevo->siguiente;
		nuevo2=nuevo->siguiente;
	}
	if(this->jMazoRojo==nuevo){
		this->jMazoRojo=nuevo2;
	}
	if(this->jMazoAzul==nuevo){
		this->jMazoAzul=nuevo2;
	}
	if(this->len==1){
		this->jMazoAzul=NULL;
		this->jMazoRojo=NULL;
	}
	nuevo->anterior->siguiente=nuevo->siguiente;
	nuevo->siguiente->anterior=nuevo->anterior;
	nuevo->siguiente=NULL;
	nuevo->anterior=NULL;
	this->len=this->len -1;
	delete nuevo;

}

template<typename T>
void CartasEnlazadas<T>::eliminarJugadorConMazoAzul(){
	eliminarJugador(dameJugadorConMazoAzul());
}

template<typename T>
bool CartasEnlazadas<T>::existeJugador(const T& target) const{
	bool res=false;
	int i=this->len;
	Nodo* nuevo=this->jMazoAzul;
	while(i>0){
		if(nuevo->jugador==target){
			res=res || true;
		}else{
			res= res || false;
	   	}
	   	nuevo=nuevo->siguiente;
	   	i--;
	}
	return res;
}

template<typename T>
void CartasEnlazadas<T>::sumarPuntosAlJugador(const T& target, int p){
	Nodo* nuevo=this->jMazoAzul;
	int i=this->len;
	while(i>0){
		if(nuevo->jugador==target){
			nuevo->puntaje=nuevo->puntaje+p;
		}
		i--;
		nuevo=nuevo->siguiente;
	}

}

template<typename T>
int CartasEnlazadas<T>::puntosDelJugador(const T& target) const{
	Nodo* nuevo=this->jMazoAzul;
	int res;
	int i=this->len;
	while(i>0){
		if(nuevo->jugador==target){
			res=nuevo->puntaje;
		}
		i--;
		nuevo=nuevo->siguiente;
	}
	return res;
}

template<typename T>
const T& CartasEnlazadas<T>::ganador() const{
	Nodo* maximo=this->jMazoAzul;
	Nodo* otro=maximo->siguiente;
	int i=this->len;
	while(i>0){
		if(maximo->puntaje < otro->puntaje){
			maximo=otro;
		}
		otro=otro->siguiente;
		i--;
	}
	return maximo->jugador;

}

template<typename T>
bool CartasEnlazadas<T>::esVacia() const{
	return this->len==0;
}

template<typename T>
int CartasEnlazadas<T>::tamanio() const{
	return this->len;
}	

template <typename T>
bool CartasEnlazadas<T>::operator==(const CartasEnlazadas<T>& juego2) const {
	bool res=false;
	if(this->len==0 && (juego2.tamanio())==0){res=true;}else{
		if((this->len==juego2.len) && (this->jMazoRojo->jugador == juego2.jMazoRojo->jugador)){
			res=true;
			Nodo* elementoThis=this->jMazoAzul;
			Nodo* elementoJuego2=juego2.jMazoAzul;
			int i=this->len;
			while(i>0 && res==true){
				res= res && ((elementoThis->jugador == elementoJuego2->jugador) && (elementoThis->puntaje == elementoJuego2->puntaje));
				elementoThis=elementoThis->siguiente;
				elementoJuego2=elementoJuego2->siguiente;
				i--;

			}			
		}
	}
	return res;
}


#endif //CARTAS_ENLAZADAS_H_


