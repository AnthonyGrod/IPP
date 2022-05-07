/** @file 
 * Plik implementujący funkcje pozwalające pomocnicze do funkcji pozwalających 
 * operować na numerach telefonow
 * 
 * @author: Antoni Grodowski <ag438477@students.mimuw.edu.pl>
 * @date: 2022
 */

#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include "adjunctive_functions.h"

size_t checkLength(char const *num) {
   if (num == NULL) {
      return 0;
   }
   char c = num[0];
   size_t numIndex = 0;
   size_t length = 0;
   // wykonujemy pętle, aż natrafimy na znak oznaczający koniec napisu
   while (c != '\0') {
      numIndex++;
      length++;
      c = num[numIndex];
   }
return length;
}

int charIntoInt(char const c) {
   return c - '0';
}

bool isValidNumber(char const *num) {
	if (num == NULL || *num == '\0') {
      return false;
	}
   char c = num[0];
   size_t index = 0;
   while (c != '\0') {
      if (!isdigit(c)) {
         return false;
      }
      index++;
      c = num[index];
   }
   return true;
}

