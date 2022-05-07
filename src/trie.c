/** @file 
 * Plik implementujący funkcje pozwalające na podstawowe operacje na drzewach
 * prefiksowych.
 * 
 * @author: Antoni Grodowski <ag438477@students.mimuw.edu.pl>
 * @date: 2022
 */

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "trie.h"

trieNode *createNode(trieNode *fatherNode) {
   trieNode *node = malloc(sizeof(trieNode));
   if (node != NULL) {
      node->children = calloc(10, sizeof(trieNode));
      if (node->children == NULL) {
         free(node);
         return NULL;
      }
      node->forward = NULL;
      node->father = fatherNode;
   }
   return node;
}

void clearNode(trieNode *node) {
   if (node == NULL) {
      return;
   }
   free(node->forward);
   free(node->children);
   if (node->father != NULL) {
      /// Iterujemy się po wszystkich dzieciach ojca
      for (int i = 0; i < 10; i++) {
         /** Sprawdzamy, czy pole @p ((node->father)->children)[i] wskazuje
          * na usuwany przez nas wierzchołek.
         */
         if (((node->father)->children)[i] == node) {
            /// Jeśli tak, to ustawiamy to pole na wartość @p NULL i wychodzimy z pętli
            ((node->father)->children)[i] = NULL;
            break;
         }
      } 
   }
   free(node);
}

bool isLeaf(trieNode *node) {
   if (node == NULL) {
      return false;
   }
   for (int i = 0; i < 10; i++) {
      if ((node->children)[i] != NULL) {
         return false;
      }
   }
   return true;
}
