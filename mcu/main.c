/**
 * Autor: Ondřej Pavlacký (xpavla15)
 * 2020/21 3BIT VUT FIT
 */

/*******************************************************************************
   main.c: LCD + keyboard demo
   Copyright (C) 2009 Brno University of Technology,
                      Faculty of Information Technology
   Author(s): Zdenek Vasicek <vasicek AT stud.fit.vutbr.cz>

   LICENSE TERMS

   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions
   are met:
   1. Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
   2. Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in
      the documentation and/or other materials provided with the
      distribution.
   3. All advertising materials mentioning features or use of this software
      or firmware must display the following acknowledgement:

        This product includes software developed by the University of
        Technology, Faculty of Information Technology, Brno and its
        contributors.

   4. Neither the name of the Company nor the names of its contributors
      may be used to endorse or promote products derived from this
      software without specific prior written permission.

   This software or firmware is provided ``as is'', and any express or implied
   warranties, including, but not limited to, the implied warranties of
   merchantability and fitness for a particular purpose are disclaimed.
   In no event shall the company or contributors be liable for any
   direct, indirect, incidental, special, exemplary, or consequential
   damages (including, but not limited to, procurement of substitute
   goods or services; loss of use, data, or profits; or business
   interruption) however caused and on any theory of liability, whether
   in contract, strict liability, or tort (including negligence or
   otherwise) arising in any way out of the use of this software, even
   if advised of the possibility of such damage.

   $Id$


 *******************************************************************************/

#include <stdbool.h>
#include <fitkitlib.h>  
#include <keyboard/keyboard.h> 
#include <lcd/display.h>

char last_ch; //naposledy precteny znak

/**
 * Vypis uzivatelske napovedy (funkce se vola pri vykonavani prikazu "help")
 */
void print_user_help(void) {
    term_send_str("Ahoj");
}

/**
 * Inicializace periferii/komponent po naprogramovani FPGA
 */
void fpga_initialized() {
    LCD_init();
    LCD_clear();
    LCD_append_string("IMP Otackomer");
}

unsigned char decode_user_cmd(char *cmd_ucase, char *cmd) {
    return CMD_UNKNOWN;
}


unsigned char setBit(unsigned char array, int offset, int value);
void writeMode(bool terminal);


/**
 * Obsluha klavesnice
 */
int keyboard_idle() {
    char ch;
    ch = key_decode(read_word_keyboard_4x4());
    if (ch != last_ch) {
        last_ch = ch;
        if (ch != 0) {
            switch (ch) {
                case 'A':
                    set_led_d6(1); // rozsviceni D6
    				set_led_d5(1); // rozsviceni D5
                    LCD_clear();
    				LCD_append_string("Je mu hodne");
                    break;
                case 'B':
                    set_led_d6(0); // rozsviceni D6
    				set_led_d5(0); // rozsviceni D5
					LCD_clear();
    				LCD_append_string("Neni mu nic");
                    break;
                
            }
        }
    }
    return 0;
}

/*******************************************************************************
 * Hlavni funkce
 *******************************************************************************/
int main(void) {

    last_ch = 0;

    initialize_hardware();
    keyboard_init();

    // Signalaizace stojiciho vytahu
    set_led_d6(0); // rozsviceni D6
    set_led_d5(0); // rozsviceni D5

    while (1) {

        keyboard_idle(); // obsluha klavesnice
        terminal_idle(); // obsluha terminalu
    }
}
