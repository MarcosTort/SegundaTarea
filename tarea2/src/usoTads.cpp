#include "../include/usoTads.h"
#include "../include/cadena.h"
#include "../include/info.h"
#include "../include/utils.h"

#include <stddef.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
/*
  Devuelve 'true' si y solo si en 'cad' hay un elemento cuyo campo natural es
  'elem'.
  El tiempo de ejecución en el peor caso es O(n), siendo 'n' la cantidad de
  elementos de 'cad'.
 */
bool pertenece(nat elem, TCadena cad){
  TLocalizador rec = inicioCadena(cad);
  if(!esVaciaCadena(cad)){
  while((!esFinalCadena(rec, cad)) && (natInfo(infoCadena(rec, cad)) != elem)){
    rec = siguiente(rec, cad);
  }
  return natInfo(infoCadena(rec, cad)) == elem;
  }
  else{return false;}
}
/*
  Devuelve la cantidad de elementos de 'cad'.
  El tiempo de ejecución en el peor caso es O(n), siendo 'n' la cantidad de
  elementos de 'cad'.
 */
nat longitud(TCadena cad){
  if(esVaciaCadena(cad)){
    return 0;
  }
  else{
  nat contador = 1;
  TLocalizador rec = inicioCadena(cad);
  while(!esFinalCadena(rec, cad)){
    rec = siguiente(rec, cad);
    contador ++;
  }
  return contador;
  }
}

/*
  Devuelve 'true' si y solo si 'cad' está ordenada de forma no dereciente
  (creciente de manera no estricta) según las campos naturales de sus elementos.
  Si esVaciaVadena(cad) devuelve 'true'.
  El tiempo de ejecución en el peor caso es O(n), siendo 'n' la cantidad de
  elementos de 'cad'.
 */
bool estaOrdenadaPorNaturales(TCadena cad){
  TLocalizador ctr = inicioCadena(cad);
  if(esVaciaCadena(cad) || esFinalCadena(ctr, cad) ){
    return true;
  }
  else{
    bool ordenado = true;
    while(!esFinalCadena(ctr, cad) && ordenado){
      ordenado = natInfo(infoCadena(ctr, cad)) <= natInfo(infoCadena(siguiente(ctr, cad), cad));
      ctr = siguiente(ctr, cad);
    }
    return ordenado;
  }
}
/*
  Devuelve 'true' si y solo si los componentes naturales de algún par de
  elementos de 'cad' son iguales.
  El tiempo de ejecución en el peor caso es O(n^2), siendo 'n' la cantidad de
  elementos de 'cad'.
 */
bool hayNatsRepetidos(TCadena cad){
  TLocalizador fija = inicioCadena(cad);
  TLocalizador resto = inicioCadena(cad);
  if(esVaciaCadena(cad) || esFinalCadena(fija, cad) ){
    return false;
  }
  else{
    bool repetidos = false;
    while(!esFinalCadena(fija, cad) && !repetidos){
      while(!esFinalCadena(resto, cad)&& !repetidos){
        if((resto != fija) && (repetidos)){
          repetidos = true;
        }
        repetidos = natInfo(infoCadena(fija, cad)) == natInfo(infoCadena(resto, cad));
        resto = siguiente(resto, cad);
      }//end while resto
      fija = siguiente(fija, cad);
    }//end while fijo
  return repetidos;
  }//end else

}

/*
  Devuelve 'true' si y solo si 'c1' y 'c2' son iguales (es decir, si los
  elementos son iguales y en el mismo orden).
  Si esVaciaCadena(c1) y esVaciaCadena(c2) devuelve 'true'.
  El tiempo de ejecución en el peor caso es O(n1 + n2), siendo 'n1' u 'n2' la
  cantidad de elementos de 'c1' y 'c2' respectivamente.
 */
bool sonIgualesCadena(TCadena c1, TCadena c2){return true;}

/*
  Devuelve el resultado de concatenar 'c2' después de 'c1'.
  La 'TCadena' resultado no comparte memoria ni con 'c1' ni con 'c2'.
  El tiempo de ejecución en el peor caso es O(n1 + n2), siendo 'n1' u 'n2' la
  cantidad de elementos de 'c1' y 'c2' respectivamente.
 */
TCadena concatenar(TCadena c1, TCadena c2){return 0;}

/*
  Se ordena 'cad' de manera creciente según los componentes naturales de sus
  elementos.
  Devuelve 'cad'
  Precondición: ! hayNatsRepetidos(cad)
  No se debe obtener ni devolver memoria de manera dinámica.
  Se debe mantener las relaciones de precedencia entre localizadores.
  Si esVaciaCadena(cad) no hace nada.
  El tiempo de ejecución en el peor caso es O(n^2), siendo 'n' la cantidad de
  elementos de 'cad'.
 */
TCadena ordenar(TCadena cad){return 0;}

/*
  Cambia todas las ocurrencias de 'original' por 'nuevo' en los elementos
  de 'cad'.
  Devuelve 'cad'
  No debe quedar memoria inaccesible.
  El tiempo de ejecución en el peor caso es O(n), siendo 'n' la cantidad de
  elementos de 'cad'.
 */
TCadena cambiarTodos(nat original, nat nuevo, TCadena cad){return 0;}

/*
  Devuelve la 'TCadena' de elementos de 'cad' que cumplen
  "menor <= natInfo (elemento) <= mayor".
  El orden relativo de los elementos en la 'TCadena' resultado debe ser el mismo
  que en 'cad'.
  Precondición: estaOrdenadaPorNaturales (cad), 'menor' <= 'mayor',
  pertenece (menor, cad), pertenece (mayor, cad).
  La 'TCadena' resultado no comparte memoria con 'cad'.
  El tiempo de ejecución en el peor caso es O(n), siendo 'n' la cantidad de
  elementos de 'cad'.
 */
TCadena subCadena(nat menor, nat mayor, TCadena cad){return 0;}
