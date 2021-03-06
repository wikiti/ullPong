/**
 * @file
 * @brief Definici�n de CPelota_MJ_CPU
 *
 */


#include "pelota_cpu.h"

/**
 * @brief Obtener velocidad del eje X
 *
 * @return Devuelve el valor almacenado por #xVel
 */
float CPelota_MJ_CPU::getxVel()
{
  return (stop)? 0 : xVel;
}

/**
 * @brief Obtener velocidad del eje Y
 *
 * @return Devuelve el valor almacenado por #yVel
 */
float CPelota_MJ_CPU::getyVel()
{
  return (lock)? 0: yVel;
}

int CPelota_MJ_CPU::mover(CPad& A, CPad& B)
{
  if(stop)
  {
    B.setCalcular();
    return partido_jugando;
  }

  caja.x += xVel;
  if(caja.x <= 0) // Fin de la partida al salirse de rango. Pierda el pad izq. Gana el pad der (j2)
  {
    caja.x = 0;
    stop = true;
    Mix_PlayChannel( -1, snd_pung, 0 );
    return partido_ganaJ2;
  }
  else if(caja.x + caja.w >= opciones->PANTALLA_ANCHO) // Gana el pad izq (j1)
  {
    caja.x = opciones->PANTALLA_ANCHO - opciones->PELOTA_ANCHO;
    stop = true;
    Mix_PlayChannel( -1, snd_pung, 0 );
    return partido_ganaJ1;
  }
  // Si la pelota est� bloqueada, ignora a los rebotes con los pads. La partida sigue en curso hasta que toque un borde.
  // Tambi�n ignora el movimiento vertical.
  if(lock)
  {
    yVel = 0;
    return partido_jugando;
  }

  caja.y += yVel;
  // Si choca contra los bordes superiores, rebota sin m�s.
  if(caja.y < PANTALLA_MARGEN_SUPERIOR + TABLERO_LINEAS_GROSOR || caja.y + caja.h > opciones->PANTALLA_ALTO - PANTALLA_MARGEN_INFERIOR - TABLERO_LINEAS_GROSOR)
  {
    caja.y -= yVel;
    yVel = -yVel;
    Mix_PlayChannel( -1, snd_pong, 0 );
  }

  SDL_Rect Pad1 = A.getCaja();
  SDL_Rect Pad2 = B.getCaja();
  int pos = 0;

  // Si choca con el pad izquierdo
  if(caja.x < Pad1.x + Pad1.w)
  {
    pos = getPos(this->getCaja(), Pad1);
    if(pos == OUT_RANGE)
    {
      lock = true;
      color = SDL_MapRGB(pantalla->format, 0xFF, 0x00, 0x00); // te�ir la pelota de rojo (visible)
    }
    else
    {
      // Calcular velocidades
      setVel(yVel, xVel, pos, A.getMomento());
      // Adem�s, vamos a hacer que la pelota no "atraviese" el pad coloc�ndola justo en frente de �ste.
      caja.x = Pad1.x + Pad1.w;

      Mix_PlayChannel( -1, snd_pong, 0 );
    }
  }
  // Si choca contra el pad derecho
  else if(caja.x + caja.w > Pad2.x)
  {
    pos = getPos(this->getCaja(), Pad2);
    if(pos == OUT_RANGE)
    {
      color = SDL_MapRGB(pantalla->format, 0xFF, 0x00, 0x00); // te�ir la pelota de rojo (visible)
      lock = true;
    }
    else
    {
      // Calcular velocidades
      setVel(yVel, xVel, pos, B.getMomento());
      // Adem�s, vamos a hacer que la pelota no "atraviese" el pad coloc�ndola justo en frente de �ste.
      caja.x = Pad2.x - caja.w;

      Mix_PlayChannel( -1, snd_pong, 0 );
    }
  }
  return partido_jugando;
}



