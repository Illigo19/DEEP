/*
 * ecran.c
 *
 *  Created on: Jun 12, 2025
 *      Author: chinabni
 */

#ifndef ECRAN_C_
#define ECRAN_C_

#include "./tft_ili9341/stm32g4_ili9341.h"

void ecranInit(){
	ILI9341_Fill(ILI9341_COLOR_WHITE);
}

void ecranBienvenue(){
	ecranInit();
	ILI9341_Puts(60,60, "Bienvenue chez Rent a Ball",&Font_11x18, ILI9341_COLOR_BLUE, ILI9341_COLOR_WHITE);
	ILI9341_Puts(60,60, "Merci de saisir l'heure",&Font_11x18, ILI9341_COLOR_BLUE, ILI9341_COLOR_WHITE);
}

void ecranAttenteCarte(){
	ecranInit();
	ILI9341_Puts(60,60, "Bienvenue chez Rent a Ball",&Font_11x18, ILI9341_COLOR_BLUE, ILI9341_COLOR_WHITE);
	ILI9341_Puts(60,100, "En attente de la carte",&Font_11x18, ILI9341_COLOR_BLUE, ILI9341_COLOR_WHITE);
}

void ecranAttenteBalle(){
	ecranInit();
	ILI9341_Puts(60,60, "En attente de la balle",&Font_11x18, ILI9341_COLOR_BLUE, ILI9341_COLOR_WHITE);
}

void ecranPartie(){
	ecranInit();
	ILI9341_Puts(60,60, "Bonne partie !",&Font_11x18, ILI9341_COLOR_GREEN, ILI9341_COLOR_WHITE);
}

void ecranBalleRecup(){
	ecranInit();
	ILI9341_Puts(60,60, "La carte a ete inseree ! Vous pouvez prendre la balle", &Font_11x18, ILI9341_COLOR_GREEN, ILI9341_COLOR_WHITE);
}

void ecranCarteRecup(){
	ecranInit();
	ILI9341_Puts(60,60, "La balle a ete introduite !Vous pouvez prendre votre carte", &Font_11x18, ILI9341_COLOR_GREEN, ILI9341_COLOR_WHITE);
}

void ecranEnService(){
	ILI9341_Puts(60,60, "Desole, la balle est deja en utilisation", &Font_11x18, ILI9341_COLOR_BLUE, ILI9341_COLOR_WHITE);
}


#endif /* ECRAN_C_ */
