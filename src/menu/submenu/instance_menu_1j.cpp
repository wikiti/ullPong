/**
 * @file
 * @brief Definici�n de CInstance_Menu_1J
 *
 * Para m�s informaci�n sobre el funcionamiento de las estancias, vea las clases CInstance_Menu_Main, CInstance, CEngine, CMenu y CBoton.
 * Un ejemplo del men�, con un dise�o minimalista, es el siguiente:
 *
 * @image html menu_1.png
 */


#include "instance_menu_1j.h"

const int FRAMES_PER_SECOND = 60;

CInstance_Menu_1J::CInstance_Menu_1J()
{
  color_negro.r = color_negro.g = color_negro.b = 0x00;
  color_blanco.r = color_blanco.g = color_blanco.b = 0xFF;

  botones = NULL;
  menu = NULL;
}

bool CInstance_Menu_1J::Init()
{
  if(!LoadFiles())
    return false;

  SDL_Rect cajas = {100, 200, 180, 25};

  botones = new CBoton[3];
  botones[0] = CBoton(ttf_consolas, &color_negro, &color_blanco, &cajas, "Modo Historia");cajas.y += 30;
  botones[1] = CBoton(ttf_consolas, &color_negro, &color_blanco, &cajas, "Modo Infinito");cajas.y += 30;
  botones[2] = CBoton(ttf_consolas, &color_negro, &color_blanco, &cajas, "Volver");

  menu = new CMenu(botones, 3);

  i_running = true;
  botones = new CBoton[4];

  return true;
}

bool CInstance_Menu_1J::LoadFiles()
{

  fondo = SDL_CreateRGBSurface(SDL_SWSURFACE, opciones->PANTALLA_ANCHO, opciones->PANTALLA_ALTO, opciones->PANTALLA_BPP, 0x00, 0x00, 0x00, 0x00);
  if(fondo == NULL)
  {
    cout << ERROR_STR_SURFACE << "MENU_1J -> fondo" << endl;
    return false;
  }

  ttf_consolas = TTF_OpenFont("media/ttf/consolab.ttf", 16);

  if(ttf_consolas == NULL)
  {
    cout << ERROR_STR_FILE << "media/ttf/consolab.ttf" << endl;
    return false;
  }

  // Linea blanca para dar un estilo minimalista
  SDL_Rect caja = {80, 200, 8, 115};
  SDL_FillRect(fondo, &caja, SDL_MapRGB(pantalla->format, 0xFF, 0xFF, 0xFF) );

  return true;
}

void CInstance_Menu_1J::Close()
{
  UnLoadFiles();

  delete []botones;
  delete menu;
}

void CInstance_Menu_1J::UnLoadFiles()
{
  SDL_FreeSurface(fondo);
  TTF_CloseFont(ttf_consolas);
}



int CInstance_Menu_1J::OnExecute()
{
  if(!Init())
  {
    cout << ERROR_STR_INIT << " MENU_1J" << endl;
    return ERROR_CODE_GENERAL;
  }

  int frame = 0;
  CTemporizador fps;

  int salida = I_SALIDA;

  while(i_running)
  {
    fps.empezar();
    while(SDL_PollEvent(&event))
    {
      OnEvent(salida);
    }
    OnLoop(salida);
    OnRender();

    frame++;
    if((fps.getTicks() < (1000 / FRAMES_PER_SECOND)))
      SDL_Delay((1000 / FRAMES_PER_SECOND ) - fps.getTicks());
  }

  Close();

  return salida;
}

void CInstance_Menu_1J::OnEvent(int& caso)
{
  caso = menu->eventuar();
  if(event.type == SDL_QUIT)
  {
    caso = I_SALIDA;
    i_running = false;
  }
  if(event.type == SDL_KEYDOWN)
  {
    if(event.key.keysym.sym == SDLK_ESCAPE)
    {
      caso = I_MENU_MAIN;
      i_running = false;
    }
  }
}

void CInstance_Menu_1J::OnLoop(int& caso)
{
  switch(caso)
  {
    case 1:
      caso = I_1J_HISTORIA;
      i_running = false;
    break;
    case 2:
      caso = I_1J_INF;
      i_running = false;
    break;
    case 3:
      caso = I_MENU_MAIN;
      i_running = false;
    break;
    default: break;
  }
}

void CInstance_Menu_1J::OnRender()
{
  aplicar_superficie(0, 0, fondo, pantalla);
  menu->mostrar();

  if(SDL_Flip(pantalla) == -1)
  {
    cerr << ERROR_STR_FLIP << endl;
    i_running = false;
  }
}
