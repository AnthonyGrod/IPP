/** @file 
 * Interfejs implementujący strukturę drzewa prefiksowego
 * 
 * @author: Antoni Grodowski <ag438477@students.mimuw.edu.pl>
 * @date: 2022
 */

#ifndef __TRIE_H__
#define __TRIE_H__

#include <stdio.h>

/**
 * Deklaracja struktury trieNode.
 */
typedef struct trieNode trieNode;
/** 
 * Struktura implementująca wierzchołek drzewa prefiksowego
 */
struct trieNode {
   /** 
    * @p children - wskaźnik na tablicę wskaźników przechowujących synów danego wierzchołka
    */
   trieNode **children;
   /** 
    * @p father - wskażnik na ojca danego wierzchołka. Dla korzenia jest to @p NULL
    */
   trieNode *father;
   /** 
    * @p forward - wskaźnik na tablicę znaków, które przechowują przekierowanie.
    */
   char *forward;
};

/** @brief Tworzy wierzchołek drzewa prefiksowego
 * Tworzy wierzchołek drzewa prefiksowego, ustawiając jego pola @p children, 
 * @p forward na NULL oraz pole @p father na @p fatherNode.
 * @param[in] fatherNode – wskaźnik na ojca dodawanego wierzchołka. Jest to
 *                         @p NULL, gdy wierzchołek jest korzeniem.
 * @return Wskaźnik na nowo stworzony wierzhołek.
 */
trieNode *createNode(trieNode *fatherNode);

/** @brief Usuwa liść drzewa prefiksowego
 * Czyści pamięc zaalokowaną dla wierzchołka typu @p trieNode @p node, 
 * będącego równocześnie liściem drzewa prefiksowego.
 * @param[in] node – wskaźnik na usuwany liść drzewa prefiksowego
 */
void clearNode(trieNode *node);

/** @brief Sprawdza czy podany wierzchołek drzewa prefiksowego jest liściem.
 * Poprzez sprawdzenie, czy wszystkie wskaźniki w tablicy @p children mają 
 * wartość @p NULL, wierzchołka @p node funkcja ustala, czy wierzchołek @p node
 * jest liściem.
 * @param[in] node – wskaźnik na wierzchołek, który chcemy sprawdzić, czy ma
 *                   wartośc @p NULL
 * @return Wartość @p true, jeśli wierzchołek @p node jest liściem lub wartość
 * @p false w przeciwnym przypadku.
 */
bool isLeaf(trieNode *node);

#endif