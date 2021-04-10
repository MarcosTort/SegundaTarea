
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
  if(!esVaciaCadena(cad)){
    nodoCadena *prox_a_borrar;
    while(cad->inicio != NULL)
    {
        prox_a_borrar = cad->inicio;
        cad->inicio = cad->inicio->siguiente;
        liberarInfo(prox_a_borrar->dato);
        delete(prox_a_borrar);
    }
  }
  delete cad;
}

bool esVaciaCadena(TCadena cad) {
    return cad->inicio == NULL;
}

TLocalizador inicioCadena(TCadena cad) {
    if (esVaciaCadena(cad)) {
      return NULL;
    } else {
      return cad->inicio;
    }
}

TLocalizador finalCadena(TCadena cad) {
    if (esVaciaCadena(cad)) {
      return NULL;
    } else {
      return cad->final;
    }
}

TInfo infoCadena(TLocalizador loc, TCadena cad) {
  if (localizadorEnCadena(loc, cad)){
    return loc->dato;
  }
  else{return NULL;}
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
  if (localizadorEnCadena(loc, cad)){
  nodoCadena *entrante = new nodoCadena;
  entrante->dato = i;
  if(esInicioCadena(loc, cad)){
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
  return cad;
}

TCadena removerDeCadena(TLocalizador loc, TCadena cad) {
  assert(localizadorEnCadena);
  TLocalizador aux = loc;

	if (esInicioCadena(loc, cad)) {
		//inicio
		if (esLocalizador(loc->siguiente)) {
      cad->inicio = aux->siguiente; 
			aux->siguiente->anterior = NULL; 
			liberarInfo(loc->dato);
			delete loc;
		} else {
      cad->inicio = NULL;
			cad->final = NULL;
			liberarInfo(loc->dato);
			delete loc;
		}

	} else {
		if (!esFinalCadena(loc, cad)) {
       //medio 
			aux->anterior->siguiente = aux->siguiente;
			aux->siguiente->anterior = aux->anterior;
			liberarInfo(loc->dato);
			delete loc;
		} else {
      //final 
			cad->final = aux->anterior;
			aux->anterior->siguiente = NULL;
			liberarInfo(loc->dato);
			delete loc;
		}
	}		
  return cad;
}

void imprimirCadena(TCadena cad) {
  TCadena a = cad;
  TLocalizador l = a->inicio;
  if(!esVaciaCadena(cad)){
    if(l->siguiente!=NULL){

      while (esLocalizador(l->siguiente)){
        char *dat = infoATexto(l->dato);
        printf("%s", dat);
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
  nat j = 1;
  while((reco->siguiente != NULL )&& (j != k)){
    reco = reco->siguiente;
    j++;
  }
  if (k>0 || k > j){
    return NULL;
  }
  else{
    if ((j == k )&& (reco != NULL)){
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
    TLocalizador loc = desde;
    while(loc != siguiente(hasta, cad)){
      TInfo dato;
      dato = copiaInfo((loc->dato));//no comparte memoria con cad
      insertarAlFinal(dato, copia);
      loc = siguiente(loc, cad);
    }
  }
  return copia;
}

TCadena borrarSegmento(TLocalizador desde, TLocalizador hasta, TCadena cad) {
  TLocalizador eliminado;
  while (hasta != desde){
    eliminado = desde;
    desde = desde->siguiente;
    removerDeCadena(eliminado, cad);
  }
  removerDeCadena(hasta, cad);
  return cad;
}

TCadena cambiarEnCadena(TInfo i, TLocalizador loc, TCadena cad) {
  assert(localizadorEnCadena);
  loc->dato = i;
  return cad;
}

TCadena intercambiar(TLocalizador loc1, TLocalizador loc2, TCadena cad) {
  assert(localizadorEnCadena(loc1, cad)&&localizadorEnCadena(loc1, cad));
  TInfo mem = infoCadena(loc1, cad);
  loc1->dato = infoCadena(loc2, cad);
  loc2->dato = mem;
  return cad;
}

bool localizadorEnCadena(TLocalizador loc, TCadena cad) {
  if(esVaciaCadena(cad)){
    return false;
  }
  else{
    TLocalizador aux = cad->inicio;
    while (esLocalizador(aux) && aux != loc){
      aux = aux->siguiente;
    }
    return aux == loc;
  }
}

bool precedeEnCadena(TLocalizador loc1, TLocalizador loc2, TCadena cad) {
  if(esVaciaCadena(cad) || localizadorEnCadena(loc1, cad)){
    return false;
  }
  else{
    TLocalizador precursor = loc1;
    while(esLocalizador(precursor) && (loc2 != precursor)){
      precursor = precursor->siguiente;
    }
    return precursor == loc2;
  }
}

TLocalizador siguienteClave(nat clave, TLocalizador loc, TCadena cad) {
  assert(localizadorEnCadena(loc, cad));

  if(esVaciaCadena(cad)){return NULL;}
  else{
    TLocalizador rec = loc;
    while(esLocalizador(loc) && (natInfo(rec->dato) != clave)){
      rec = rec->siguiente;
    }
    if(natInfo(rec->dato) == clave)
      {return rec;}
    else
      {return NULL;}
  }
}

TLocalizador anteriorClave(nat clave, TLocalizador loc, TCadena cad) {
  assert(localizadorEnCadena(loc, cad));

  if(esVaciaCadena(cad)){return NULL;}
  else{
    TLocalizador rec = loc;
    while(esLocalizador(loc) && (natInfo(rec->dato) != clave)){
      rec = rec->anterior;
    }
    if(natInfo(rec->dato) == clave)
      {return rec;}
    else
      {return NULL;}
  }
}

TLocalizador menorEnCadena(TLocalizador loc, TCadena cad) {
  assert(localizadorEnCadena(loc, cad));
  TLocalizador res = loc;
	while (esLocalizador(siguiente(loc, cad))) {
	 loc = siguiente(loc, cad);
	 if (natInfo(infoCadena(loc, cad)) < natInfo(infoCadena(res, cad)))
	  res = loc;
	 }
	return res;
	}
