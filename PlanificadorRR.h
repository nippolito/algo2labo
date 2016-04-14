#ifndef PLANIFICADOR_RR_H_
#define PLANIFICADOR_RR_H_

#include <iostream>
#include <cassert>
using namespace std;

/**
 * Se puede asumir que el tipo T tiene constructor por copia y operator==
 * No se puede asumir que el tipo T tenga operator=
 */
template<typename T>
class PlanificadorRR {	

  public:

	/**
	 * Crea un nuevo planificador de tipo Round Robin.
	 */	
	PlanificadorRR();

	// *
	//  * Una vez copiado, ambos planificadores deben ser independientes, 
	//  * es decir, por ejemplo, que cuando se borra un proceso en uno
	//  * no debe borrarse en el otro.
	 	
	PlanificadorRR(const PlanificadorRR<T>&);

	// /**
	//  * Acordarse de liberar toda la memoria!
	//  */	 
	~PlanificadorRR();

	/**
	 * Agrega un proceso al planificador. El mismo debe ubicarse,
	 * dentro del orden de ejecución, inmediatamente antes del que está
	 * siendo ejecutado actualmente. Si no hubiese ningún proceso en ejecución,
	 * la posición es arbitraria y el proceso pasa a ser ejecutado automáticamente.
	 * PRE: El proceso no está siendo planificado por el planificador.
	 */
	void agregarProceso(const T&);

	/**
	 * Elimina un proceso del planificador. Si el proceso eliminado
	 * está actualmente en ejecución, automáticamente pasa a ejecutarse
	 * el siguiente (si es que existe).
	 * PRE: El proceso está siendo planificado por el planificador.
	 */
	void eliminarProceso(const T&);

	// /**
	//  * Devuelve el proceso que está actualmente en ejecución.
	//  * PRE: Hay al menos un proceso activo en el planificador.
	//  */
	const T& procesoEjecutado() const;

	// /**
	//  * Procede a ejecutar el siguiente proceso activo,
	//  * respetando el orden de planificación.
	//  * PRE: Hay al menos un proceso activo en el planificador.
	//  */
	void ejecutarSiguienteProceso(); //CHEQUEAR

	// /**
	//  * Pausa un proceso por tiempo indefinido. Este proceso pasa
	//  * a estar inactivo y no debe ser ejecutado por el planificador.
	//  * Si el proceso pausado está actualmente en ejecución, automáticamente
	//  * pasa a ejecutarse el siguiente (si es que existe).
	//  * PRE: El proceso está siendo planificado por el planificador.
	//  * PRE: El proceso está activo.
	//  */
	void pausarProceso(const T&);

	// *
	//  * Reanuda un proceso previamente pausado. Este proceso pasa a estar
	//  * nuevamente activo dentro del planificador. Si no había ningún proceso
	//  * en ejecución, el proceso pasa a ser ejecutado automáticamente.
	//  * PRE: El proceso está siendo planificado por el planificador.
	//  * PRE: El proceso está inactivo.
	 
	void reanudarProceso(const T&);

	// /**
	//  * Detiene la ejecución de todos los procesos en el planificador
	//  * para atender una interrupción del sistema.
	//  * PRE: El planificador no está detenido.
	//  */
	void detener();

	// /**
	//  * Reanuda la ejecución de los procesos (activos) en el planificador
	//  * luego de atender una interrupción del sistema.
	//  * PRE: El planificador está detenido.
	//  */
	void reanudar();

	// /**
	//  * Informa si el planificador está detenido por el sistema operativo.
	//  */
	bool detenido() const;

	// /**
	//  * Informa si un cierto proceso está siendo planificado por el planificador.
	//  */
	bool esPlanificado(const T&) const; //CHEQUEAR

	/**
	 * Informa si un cierto proceso está activo en el planificador.
	 * PRE: El proceso está siendo planificado por el planificador.
	 */
	bool estaActivo(const T&) const; //CHEQUEAR

	/**
	 * Informa si existen procesos planificados.
	 */
	bool hayProcesos() const; //def

	/**
	 * Informa si existen procesos activos.
	 */
	bool hayProcesosActivos() const; //def

	/**
	 * Devuelve la cantidad de procesos planificados.
	 */
	int cantidadDeProcesos() const; //def

	/**
	 * Devuelve la cantidad de procesos planificados y activos.
	 */
	int cantidadDeProcesosActivos() const; //def

	/**
	 * Devuelve true si ambos planificadores son iguales.
	 */
	bool operator==(const PlanificadorRR<T>&) const;

	/**
	 * Debe mostrar los procesos planificados por el ostream (y retornar el mismo).
	 * Los procesos deben aparecer en el mismo orden en el que son ejecutados
	 * por el planificador. Como la lista es circular, se decidió que el primer
	 * proceso que se muestra debe ser el que está siendo ejecutado en ese momento.
	 * En el caso particular donde exista al menos un proceso planificado,
	 * pero estén todos pausados, se puede comenzar por cualquier proceso.
	 * Un proceso inactivo debe ser identificado con el sufijo ' (i)'
	 * y el proceso que está siendo ejecutado, de existir, debe ser identificado
	 * con el sufijo '*'.
	 * PlanificadorRR vacio: []
	 * PlanificadorRR con 1 elemento activo: [p0*]
	 * PlanificadorRR con 2 elementos inactivos: [p0 (i), p1 (i)]
	 * PlanificadorRR con 3 elementos (p0 inactivo, p2 siendo ejecutado: [p2*, p0 (i), p1]
	 *
	 * OJO: con pX (p0, p1, p2) nos referimos a lo que devuelve el operador <<
	 * para cada proceso, es decir, cómo cada proceso decide mostrarse en el sistema.
	 * El sufijo 'X' indica el orden relativo de cada proceso en el planificador.
	 */
	ostream& mostrarPlanificadorRR(ostream&) const;

  private:
  
	/**
	 * No se puede modificar esta funcion.
	 */
	PlanificadorRR<T>& operator=(const PlanificadorRR<T>& otra) {
		assert(false);
		return *this;
	
}
	/**
	 * Aca va la implementación del nodo.
	 */
	struct Nodo {
		Nodo* sig;
		Nodo* ant;
		bool activo;
		T nombre;
		Nodo (const T& a) :nombre(a) , activo(true), sig(NULL), ant(NULL){};
	};

	unsigned int lon;
	Nodo* ejec;
	bool estado;

};


template<typename T>
PlanificadorRR<T>::PlanificadorRR(): lon(0), ejec(NULL), estado(true){}

template<typename T>
PlanificadorRR<T>::PlanificadorRR(const PlanificadorRR<T>& proc){
    int i = proc.lon;
	if(i == 0){
		lon = 0;
		ejec = NULL;
	}else{
		lon = 0;
		ejec = NULL;
		Nodo* pcopiar = proc.ejec;
		Nodo* nuevo = NULL;
		while(pcopiar->sig != proc.ejec){
				agregarProceso(pcopiar->nombre);
				nuevo->sig = pcopiar;
				nuevo->sig->activo = pcopiar->activo;
				pcopiar = pcopiar->sig;
		}
		agregarProceso(pcopiar->nombre);
	}
	lon = i;
}

template<typename T>
PlanificadorRR<T>::~PlanificadorRR(){
	while(ejec != NULL){
		eliminarProceso(ejec->nombre);
	}
}

template<typename T>
void PlanificadorRR<T>::agregarProceso(const T& nom){
	assert(esPlanificado(nom) == false);
	Nodo* nuevo = new Nodo(nom);
	if(lon == 0){
		nuevo->sig = nuevo;
		nuevo->ant = nuevo;
		ejec = nuevo;
	}else{
			Nodo* ejecutado = ejec;
			nuevo->ant = ejec->ant;
			nuevo->sig = ejec;
			ejecutado->ant->sig = nuevo;
			ejecutado->ant = nuevo;
				if(ejecutado->activo == false){
					ejec = nuevo;
				}
			}
	lon++;
}


template<typename T>
void PlanificadorRR<T>::eliminarProceso(const T& procAelim){
	assert(esPlanificado(procAelim));
	if(lon != 1){
	Nodo* iterador = ejec;
		while(iterador->nombre != procAelim){
			iterador = iterador->sig;
		}
		if(iterador->nombre == ejec->nombre){
			ejec = iterador->sig;
		}
		iterador->ant->sig = iterador->sig;
		iterador->sig->ant = iterador->ant;
		delete iterador;
	}else{
		Nodo* iterador = ejec;
		delete iterador;
		ejec = NULL;
	}
	lon--;
}

template<typename T>
const T& PlanificadorRR<T>::procesoEjecutado() const{
	assert(hayProcesosActivos() == true);
	return ejec;
}

template<typename T>
void PlanificadorRR<T>::ejecutarSiguienteProceso(){
	assert(hayProcesosActivos());
	Nodo* iterador = ejec->sig;
	int i = lon;
	bool c = true;
	while(i > 1 && c){  //chequear este while, por ahí i tiene que ser >= 1
		if(iterador->activo == true){
			c = false; 
		}else{
		i--;
		iterador = iterador->sig;
		}
	}
	ejec = iterador;
}

template<typename T>
void PlanificadorRR<T>::pausarProceso(const T& nom){
	assert(esPlanificado(nom));
	Nodo* ite = ejec;
	while(ite->nombre != nom){ //cambiar por not
		ite = ite->sig;
	}
	ite->activo = false;
	if(ejec == ite){
		if(hayProcesosActivos()){
			ejecutarSiguienteProceso();
		}
	}
}

template<typename T>
void PlanificadorRR<T>::reanudarProceso(const T& nom){
	assert(esPlanificado(nom));
	Nodo* ite = ejec;
	while(ite->nombre != nom){
		ite = ite->sig;
	}
	ite->activo = true;
	if(ejec->activo == false){
		cerr << "entro" << endl;
		ejec = ite;
	}

}


template<typename T>
void PlanificadorRR<T>::detener(){
	estado = false;
}

template<typename T>
void PlanificadorRR<T>::reanudar(){
	estado = true;
}

template<typename T>
bool PlanificadorRR<T>::detenido() const{
	if(estado == true){
		return false;
	}else{
		return true;
	}
}

template<typename T>
int PlanificadorRR<T>::cantidadDeProcesos() const{ //compiló
	return lon;
}

template<typename T>  
bool PlanificadorRR<T>::esPlanificado(const T& proc) const{
	if(lon == 0){
		return false;
	}else{
	Nodo* iterador = ejec;
	while(iterador->sig != ejec){
		if(iterador->nombre == proc){
			return true;
		}
		iterador = iterador->sig;
	}
	if(iterador->nombre == proc){
		return true;
	}
	return false;
	}
}

template<typename T>
bool PlanificadorRR<T>::estaActivo(const T& proc) const{
	assert(proc.esPlanificado());
	Nodo* proceso = ejec;
	int i = lon;
	bool s = true;
	while(i > 0 && s){ //chequear este while, por ahí i tiene que ser >= 0
		if(proceso->nombre == proc){
			s = false;
		}
	i--;
	proceso = proceso->sig;
	}
	return proceso->activo;
}

template<typename T>
bool PlanificadorRR<T>::hayProcesos() const{  //compiló
	if(lon == 0){
		return false;
	}else{
		return true;
	}
}

template<typename T>
bool PlanificadorRR<T>::hayProcesosActivos() const{ //me la estoy complicando demasiado?
	bool c = false;
	if(lon == 0){
		return false;
	}else{
		Nodo* iterador = ejec;
		if(iterador->activo == true){
			return true;
		}else{
			iterador = iterador->sig;
			while(iterador != ejec && !c){
				c = iterador->activo;
				iterador = iterador->sig;
			}
		}
	}
	return c;
} //compiló

template<typename T>
int PlanificadorRR<T>::cantidadDeProcesosActivos() const{ //compiló
	if(lon == 0){
 		return 0;
 	}
 	Nodo* iterador = ejec;
	int i = 0;
		while(iterador->sig != ejec){
			if(iterador->activo == true){
				i++;
			}
			iterador = iterador->sig;
		}
		if(iterador->activo == true){
			i++;
		}
	return i;
}

template<typename T>
ostream& PlanificadorRR<T>::mostrarPlanificadorRR(ostream& os) const{
	os << "[";
	if(lon != 0){
		Nodo* ite = ejec;
		if(ite->activo == false){
			os << ite->nombre << " (i)";
		}else{
		os << ite->nombre << "*";
		}
		ite = ite->sig;
		while(ite != ejec){
			if(ite->activo == false){
				os << ", " << ite->nombre << " (i)";
			}else{
				os << ", " << ite->nombre;
			}
			ite = ite->sig;
		}
	os << "]";
	}else{
		os << "]";
	}

}

template<typename T>
bool PlanificadorRR<T>::operator==(const PlanificadorRR<T>& copia) const{
	bool b = true;
	if(lon != copia.lon || estado != copia.estado){
		return false;
	}else{
		int i = lon;
		Nodo* izq = ejec;
		Nodo* der = copia.ejec;
		while(i > 0 && b){
		if((izq->activo != der->activo) || (izq->nombre != der->nombre)){
			b = false;
		}
			i--;
			izq = izq->sig;
			der = der->sig;
		}
	}
	return b;
}

template<class T>
ostream& operator<<(ostream& out, const PlanificadorRR<T>& a) {
	return a.mostrarPlanificadorRR(out);
}



#endif // PLANIFICADOR_RR_H_