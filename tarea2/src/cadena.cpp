
#include "../include/cadena.h"
#include "../include/info.h"
#include "../include/utils.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

struct nodoCadena {
  TInfo dato;
  TLocalizador anterior;
  TLocalizador siguiente;
};

struct _rep_cadena {
  TLocalizador inicio;
  TLocalizador final;
};

bool esLocalizador(TLocalizador loc) { return loc != NULL; }

TCadena crearCadena() {
  TCadena res = new _rep_cadena;
  res->inicio = res->final = NULL;
  return res;
}

void liberarCadena(TCadena cad) {
    nodoCadena *prox_a_borrar;
    while(cad->inicio != NULL)
    {
        prox_a_borrar = cad->inicio;
        cad->inicio = cad->inicio->siguiente;
        liberarInfo(prox_a_borrar->dato);
        delete(prox_a_borrar);
    };

}

bool esVaciaCadena(TCadena cad) {
    return cad->inicio = NULL;
}

TLocalizador inicioCadena(TCadena cad) {
  TLocalizador res;
    if (esVaciaCadena(cad)) {
      res = NULL;
    } else {
      res = cad->inicio;
    }
    return res;
}

TLocalizador finalCadena(TCadena cad) {
  TLocalizador res;
    if (esVaciaCadena(cad)) {
      res = NULL;
    } else {
      res = cad->final;
    }
    return res;
}

TInfo infoCadena(TLocalizador loc, TCadena cad) {
  assert(localizadorEnCadena(loc, cad));
  TInfo salida;
  salida = loc->dato;
  return salida;
}

TLocalizador siguiente(TLocalizador loc, TCadena cad) {
    assert(localizadorEnCadena(loc, cad));
    TLocalizador aux = loc->siguiente;
    return aux;
}

TLocalizador anterior(TLocalizador loc, TCadena cad) {
  assert(localizadorEnCadena(loc, cad));
    TLocalizador aux = loc->siguiente;
    return aux;
}

bool esFinalCadena(TLocalizador loc, TCadena cad) {
  if(esVaciaCadena(cad)){
    return false;
  }
  else{
    if (cad->final == loc){
      return true;
    }
    else{
      return false;
    }
  }
}

bool esInicioCadena(TLocalizador loc, TCadena cad) {
  if(esVaciaCadena(cad)){
    return false;
  }
  else{
    if (cad->inicio == loc){
      return true;
    }
    else{
      return false;
    }
  }
}


TCadena insertarAlFinal(TInfo i, TCadena cad) {
  nodoCadena *entrante = new nodoCadena;
  entrante->dato = i;
  entrante->anterior = cad->final;
  entrante->siguiente = NULL;
  if(esVaciaCadena(cad)){
    cad->inicio = entrante;
  }
  else{
    cad->final->siguiente = entrante;
  }
  cad->final = entrante;
  return cad;
}

TCadena insertarAntes(TInfo i, TLocalizador loc, TCadena cad) {
  assert(localizadorEnCadena(loc, cad));
  nodoCadena *entrante = new nodoCadena;
  entrante->dato = i;
  if(esInicioCadena){
    entrante->siguiente = loc;
    loc->anterior = entrante; 
    cad->inicio = entrante;
    entrante->anterior = NULL;
  }
  else{
    entrante->anterior = loc->anterior;
    entrante->siguiente = loc;
    loc->anterior = entrante;
    loc->anterior->siguiente = entrante;
  }
}

TCadena removerDeCadena(TLocalizador loc, TCadena cad) {
  assert(localizadorEnCadena);
  if(esInicioCadena(loc, cad)){
    liberarInfo(loc->dato);
    cad->inicio = loc->siguiente;
    loc->siguiente->anterior = NULL;
    delete loc;
  }
  return cad;
}

void imprimirCadena(TCadena cad) {
  TCadena a = cad;
  TLocalizador l = a->inicio;
  if(!esVaciaCadena){
    if(l->siguiente!=NULL){

      while (esLocalizador(l->siguiente)){
        char *dat = infoATexto(l->dato);
        printf(dat);
        l = l->siguiente;
        delete dat;
      }//end while
    }//end segundo if
    else{
      char *dat2 = infoATexto(a->inicio->dato);
      delete dat2;
    }//end segundo else
  }//end primer if
  else{
    printf("\n");
  }//end primer else
}

TLocalizador kesimo(nat k, TCadena cad) {
  TLocalizador reco = cad->inicio;
  int j = 1;
  while(reco->siguiente != NULL && j != k){
    reco = reco->siguiente;
    j++;
  }
  if (k>0 || k > j){
    return NULL;
  }
  else{
    if (j == k && reco != NULL){
      return reco;
    }
    else{
      return NULL;
    }
  }
}

TCadena insertarSegmentoDespues(TCadena sgm, TLocalizador loc, TCadena cad) {
  assert(localizadorEnCadena(loc, cad));
  if(!esVaciaCadena(sgm)){
    if(!esVaciaCadena(cad)){
      if(finalCadena(cad) != loc){
        sgm->inicio->anterior = loc->siguiente;
        sgm->final->siguiente = loc;
        loc->siguiente->anterior = sgm->final;
        loc->siguiente = sgm->inicio;
      }
      else{
        sgm->inicio->anterior = loc->siguiente;
        sgm->final->siguiente = loc;
        cad->final = sgm->final;
        loc->siguiente = sgm->inicio;
      }
    }
    else{
      //cuando la cad es vacia
    }
  }
  sgm->inicio = NULL;
  sgm->final = NULL;
  return cad;
}
TCadena copiarSegmento(TLocalizador desde, TLocalizador hasta, TCadena cad) {
  assert(esVaciaCadena(cad)||precedeEnCadena(desde, hasta, cad));
  TCadena copia = crearCadena();
  if(!esVaciaCadena(cad))
  {
    TInfo dato;
    TLocalizador loc = desde;
    while(loc != siguiente(hasta, cad)){
      dato = copiaInfo((loc->dato));//no comparte memoria con cad
      loc = siguiente(loc, cad);
    }
  }
  return copia;
}

TCadena borrarSegmento(TLocalizador desde, TLocalizador hasta, TCadena cad) {
  return NULL;
}

TCadena cambiarEnCadena(TInfo i, TLocalizador loc, TCadena cad) {
  return NULL;
}

TCadena intercambiar(TLocalizador loc1, TLocalizador loc2, TCadena cad) {
  return NULL;
}

bool localizadorEnCadena(TLocalizador loc, TCadena cad) {
  return false;
}

bool precedeEnCadena(TLocalizador loc1, TLocalizador loc2, TCadena cad) {
  return false;
}

TLocalizador siguienteClave(nat clave, TLocalizador loc, TCadena cad) {
  return NULL;
}

TLocalizador anteriorClave(nat clave, TLocalizador loc, TCadena cad) {
  return NULL;
}

TLocalizador menorEnCadena(TLocalizador loc, TCadena cad) {
  return NULL;
}













