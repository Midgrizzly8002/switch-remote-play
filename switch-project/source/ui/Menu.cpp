#include "Menu.h"

Menu::Menu() : highlightColour{.r = 200, .g = 200, .b = 50, .a = 255}, 
    title{.x = 440, .y = 160, .colour = {255,255,255,255}}
{ }

void Menu::ProcessInput(PadState const & pad)
{ }

void Menu::Render(SDL_Renderer * const renderer, FC_Font * const font)
{ }
