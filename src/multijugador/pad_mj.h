/**
 * @file
 * @brief Declaraci�n de CPad_MJ
 *
 */

#ifndef PAD_MULTIJUGADOR_H_
#define PAD_MULTIJUGADOR_H_

#include "../pad.h"

// De momento, esta clase es inutil. Ya vere lo que hacemos con ella...
// Tal vez a�adiendole yVel y momento podemos hacer que CPad_MJ_Online y CPad_MJ_Online_Zombi deriven de esta.

/**
 * @brief Clase abstracta para clases CPad a nivel de multijugador
 *
 * Se usar� simplemente como clase base para generar clases de multijugador que comparten la velocidad vertical.
 */
class CPad_MJ: public CPad
{
  protected:
    float yVel; /**< Velocidad vertical*/
  public:
    /** @brief Constructor por defecto. */
	   CPad_MJ();
	   /** @brief Destructor. */
	   ~CPad_MJ();

	   /**
	    * @brief Obtener velocidad vertical
	    *
	    * @return Devuelve el valor almacenado por #yVel.
	    */
	   float getVel(){return yVel;};

	//void mostrar();
};



#endif /* PAD_MULTIJUGADOR_H_ */
