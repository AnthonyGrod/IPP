/** @file 
 * Interfejs klasy przechowującej funkcje pomocnicze.
 * 
 * @author: Antoni Grodowski <ag438477@students.mimuw.edu.pl>
 * @date: 2022
 */

#ifndef __ADJUNCTIVE_FUNCTIONS_H__
#define __ADJUNCTIVE_FUNCTIONS_H__

#include <stdbool.h>
#include <stdio.h>

/** @brief Sprawdza i zwraca długość napisu
 * Iteracyjnie sprawdza i zwraca długość napisu wskazywanego przez @p num.
 * @param[in] num   – wskaźnik na napis którego długość chcemy sprawdzić
 *                     przekierowywanych;
 * @return Długość napisu wskazywanego przez @p num
 */
size_t checkLength(char const *num);

/** @brief Zwraca reprezentacje numeryczną znaku
 * @param[in] c - znak
 * @return Numeryczna reprezentacja znaku `c`
 */
int charIntoInt(char const c);

/** @brief Sprawdza, czy podany napis jest prawidłowym numerem telefonu
 * @param[in] num - napis, który chcemy sprawdzić
 * @return Wartość @p true jeśli napis jest prawidłowym numerem telefonu lub
 *         @p false jeśli napis nie jest prawidłowy
 */
bool isValidNumber(char const *num);

#endif