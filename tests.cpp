// g++ -g tests.cpp -o tests
// valgrind --leak-check=full -v ./tests
// g++ -g tests.cpp -o niwagato
// ddd ./niwagato
//breakpoint con doble click, después run y hacerle doble click al objeto que quiero ver

#include <algorithm>
#include "mini_test.h"
#include "PlanificadorRR.h"

using namespace std;

string remove_spaces(const string& s) {
  string out(s);
  out.erase(remove(out.begin(), out.end(), ' '), out.end());
  out.erase(remove(out.begin(), out.end(), '\n'), out.end());
  return out;
}

template<typename T>
string to_s(const T& m) {
 	ostringstream os;
	os << m;
	return os.str();
}

/**
 * Crea un planificador sin porocesos.
 */
void planificadorVacio()
{
  PlanificadorRR<int> planificador;
  ASSERT_EQ(planificador.hayProcesos(), false);
  ASSERT_EQ(planificador.hayProcesosActivos(), false);
  ASSERT_EQ(to_s(planificador), "[]");
}

void operadorIgualdad()
{
  PlanificadorRR<int> p1;
  PlanificadorRR<int> p2;
  p1.agregarProceso(1);
  p1.agregarProceso(2);
  p1.agregarProceso(3);
  p2.agregarProceso(1);
  p2.agregarProceso(2);
  p2.agregarProceso(3);
  ASSERT(p1 == p2);
  p1.eliminarProceso(2);
  p2.eliminarProceso(2);
  ASSERT(p1 == p2);
  p1.eliminarProceso(1);
  p2.eliminarProceso(1);
  ASSERT(p1 == p2);
}

void constructorPorCopia()
{
  PlanificadorRR<int> p1;
  p1.agregarProceso(1);
  p1.agregarProceso(2);
  p1.agregarProceso(3);
  p1.pausarProceso(2);
  p1.pausarProceso(1);
  p1.pausarProceso(3);
  PlanificadorRR<int> p2(p1);
  ASSERT(p1 == p2);
  p1.reanudarProceso(2);
  p1.ejecutarSiguienteProceso();
  PlanificadorRR<int> p3(p1);
  ASSERT(p1 == p3);
  PlanificadorRR<int> p4;
  PlanificadorRR<int> p5(p4);
  ASSERT(p4 == p5);
  p4.agregarProceso(72);
  PlanificadorRR<int> p6(p4);
  ASSERT(p4 == p6);
  p4.pausarProceso(72);
  PlanificadorRR<int> p7(p4);
  ASSERT(p4 == p7);
  p4.eliminarProceso(72);
  PlanificadorRR<int> p8(p4);
  p1.eliminarProceso(3);
  PlanificadorRR<int> p9(p1);
  ASSERT(p1 == p9);

}

void testNombre()
{
  PlanificadorRR<int> p1;  
  p1.agregarProceso(1);
  p1.agregarProceso(2);
  p1.agregarProceso(3);
  p1.pausarProceso(1);
  p1.pausarProceso(2);
  p1.pausarProceso(3);
  p1.reanudarProceso(3);
  ASSERT_EQ(to_s(p1), "[3*, 1 (i), 2 (i)]")
  p1.reanudarProceso(1);
  p1.reanudarProceso(2); //meter todo en un test y partirlo en varios asserts
  ASSERT_EQ(to_s(p1), "[3*, 1, 2]")
}

void PlanifdePlanif()
{
  PlanificadorRR<int> p1;
  p1.agregarProceso(1);
  p1.agregarProceso(2);
  p1.agregarProceso(3);
  PlanificadorRR< PlanificadorRR<int> > pp1;
  cerr << p1 << endl;
  pp1.agregarProceso(p1);
  cerr << pp1 << endl;
  // ASSERT_EQ(to_s(p1))
}



int main()
{
  RUN_TEST( planificadorVacio );
  RUN_TEST( operadorIgualdad );
  RUN_TEST( constructorPorCopia );
  RUN_TEST( testNombre );
  RUN_TEST( PlanifdePlanif );

  
  //RUN_TEST( DestroyPlanif );
  //RUN_TEST( agregaProces < int > );

  // AGREGAR MAS TESTS...


  return 0;
}
