/** @file 
 * Plik implementujący funkcje pozwalające operować na numerach telefonow
 * 
 * @author: Antoni Grodowski <ag438477@students.mimuw.edu.pl>
 * @date: 2022
 */

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "phone_forward.h"
#include "adjunctive_functions.h"

PhoneForward *phfwdNew(void) {
   PhoneForward *pf = malloc(sizeof(PhoneForward));
   if (pf != NULL) {
      pf->root = createNode(NULL);
   }
   return pf;
}

void phfwdDelete(PhoneForward *pf) {
   if (pf == NULL) {
      return;
   }
	trieNode *pom1 = pf->root;
	trieNode *pom2 = NULL;
   if (pom1 != NULL) {
      pom1->father = NULL;
   }
	while (pom1 != NULL) {
      /// schodzimy jak najbardziej "w lewo" w drzewie @p pf->root
		while (!isLeaf(pom1)) {
         /// szukamy pierwszego dziecka @p pom1 od lewej
			for (size_t i = 0; i < 10; i++) {
				if ((pom1->children)[i] != NULL) {
               /// ustawiamy drugi pomocniczy wskaźnik @p pom2 na znalezione dziecko
               pom2 = (pom1->children)[i];
               /// trzymając znalezione dziecko przez @p pom2, usuwamy wskaźnik na dziecko 
               (pom1->children)[i] = NULL;
               pom1 = pom2;
					break;
				}
			}
		}
      /// usuwamy liść wskazywany przez @p pom1
		pom2 = pom1->father;
		clearNode(pom1);
		pom1 = pom2; 
	}
   /// usuwamy strukturę @p PhoneForward wskazywaną przez @p pf
   free(pf);
}

void phfwdRemove(PhoneForward *pf, char const *num) {
   if (pf == NULL) {
      return;
   }
   trieNode *trav = pf->root;
   if (!isValidNumber(num) || pf == NULL || trav == NULL) {
      return;
   }
   size_t numLength = checkLength(num);
   size_t numIndex = 0;
   /// Schodzimy ścieżką wyznaczoną przez @p num (dopóki istnieje)
   while (trav != NULL && numIndex < numLength) {
      if ((trav->children)[charIntoInt(num[numIndex])] != NULL) {
         trav = (trav->children)[charIntoInt(num[numIndex])];
         numIndex++;
      }
      else {
         /** Jeśli nie ma dokładnie takiej ścieżki w strukturze @p pf, jak wyznaczona została
          * wyznacozna przez @p num, to kończymy wykonywanie funkcji */
         return;
      }
   }
   for (size_t i = 0; i < 10; i++) {
      /// Szukamy wskaźnik u ojca @p trav na @p trav
      if ((((trav)->father)->children)[i] == trav) {
            (((trav)->father)->children)[i] = NULL;
            break;
         }
   }
   /// W tym miejscu algorytmu mamy już zapewnione to, że zeszliśmy ścieżką @p num
   PhoneForward *pf2 = phfwdNew();
   clearNode(pf2->root);
   pf2->root = trav;
   /// Wywoułujemy phfwdDelete(), by usunąć poddrzewo
   phfwdDelete(pf2);
}

bool phfwdAdd(PhoneForward *pf, char const *num1, char const *num2) {
   if (pf == NULL) {
      return false;
   }
   trieNode *trav = pf->root;
   if (!(isValidNumber(num1) && isValidNumber(num2))) {
      return false;
   }
   size_t num1Index = 0;
   size_t num1Length = checkLength(num1);
   size_t num2Length = checkLength(num2);
   if (num1Length == num2Length) {
      bool areTheSame = true;
      for (size_t i = 0; i < num1Length; i++) {
         if (num1[i] != num2[i]) {
            areTheSame = false;
         }
      }
      if (areTheSame) {
         return false;
      }
   }
   /** Pętle wykonujemy dopóki istnieje scieżka wyznaczona przez @p num1
    * tą ścieżką (tak długo jak istnieje) w dół drzewa @p pf->root
    */
   while (!isLeaf(trav) && num1Index < num1Length) { 
      if (((trav->children))[charIntoInt(num1[num1Index])] == NULL) {
         break;
      }
      else {
         trav = (trav->children)[charIntoInt(num1[num1Index])];
         num1Index++;
      }
   }
   /** Tworzymy wskaźnik @p firstNodeCreated pomocniczy, który będzie wskazywać na pierwszy stworzony 
    * node tak, aby w razie błędu alokacji pamięci można było usunąć błędnie dodane wierzchołki
   */
   trieNode *firstNodeCreated = NULL;
   /// 
   if (num1Index < num1Length) {
      while (num1Index < num1Length) {
         (trav->children)[charIntoInt(num1[num1Index])] = createNode(trav);
         if (firstNodeCreated == NULL) {
            firstNodeCreated = (trav->children)[charIntoInt(num1[num1Index])];
         }
         /// Sprawdzamy, czy funkcja malloc się powiodła
         if ((trav->children)[charIntoInt(num1[num1Index])] == NULL) {
            /** Jeśli się nie powiodła to usuwamy ewentualnie dodane wierzchołki, których początek
             * jest wskazywany przez @p firstNodeCreated.
            */
            PhoneForward *pf2 = phfwdNew();
            if (pf2 != NULL) {
               clearNode(pf2->root);
               pf2->root = firstNodeCreated;
               phfwdDelete(pf2);
            }
            return false;
         }
         trav = (trav->children)[charIntoInt(num1[num1Index])];
         num1Index++;
      }
   }
	/// Jeśli wcześniej zostało dodane przekierowanie, to je usuwamy
	if (trav->forward != NULL) {
		free(trav->forward);
		trav->forward = NULL;
	}
   /// Alokujemy pamięć dla przekierowania
   trav->forward = malloc((num2Length + 1) * sizeof(char));
   /// Sprawdzamy, czy funkcja malloc() się powiodła
   if (trav->forward == NULL) {
      /// Jeśli nie, to usuwamy przekierowanie, które chcieliśmy dodać
      PhoneForward *pf2 = phfwdNew();
      if (pf2 != NULL) {
         clearNode(pf2->root);
         pf2->root = firstNodeCreated;
         phfwdDelete(pf2);
      }
      return false;
	}
   /// Kopiujemy prefiks przekierowania do @p trav->forward
   for (size_t i = 0; i < num2Length; i++) {
      (trav->forward)[i] = num2[i];
   }
   (trav->forward)[num2Length] = '\0';
   return true;
}

PhoneNumbers *phfwdGet(PhoneForward const *pf, char const *num) {
   if (pf == NULL) {
      return NULL;
   }
   /** Alokujemy pamięć dla struktury @p PhoneNumbers i ustawiamy jego pole
	 *	@p pf->num na NULL.
   */
   PhoneNumbers *phoneNum = malloc(sizeof(PhoneNumbers));
   if (phoneNum == NULL) {
      /// Jeśli alokacja się nie powiodła to usuwamy strukturę
      phnumDelete(phoneNum);
      return NULL;
   }
   phoneNum->numbers = NULL;
   phoneNum->length = 0;
   /** Wskaźnik @p pfarthestForwardNode przechowuje informacje o 'najdalej' położonym
    * node na ścieżce wytyczonej przez @p num, którego pole @p forward nie jest puste. 
    */
   trieNode *farthestForwardNode = NULL;
   /// Sprawdzamy, czy @p num jest dobrym napisem
   if (!isValidNumber(num)) {
       return phoneNum;
   }
   size_t numIndex = 0;
   size_t numLength = checkLength(num);
	/** Zmienna @p prefixLenfth będzie trzymać informację o tym, jak długi prefiks
    * będzie przekierowywany 
    */
	size_t prefixLength = 0;
   size_t prefix = 0;
	/// Tworzymy wskaźnik, którym będziemy chodzić po drzewie
   trieNode *trav = pf->root;
   while (trav != NULL && numIndex < numLength) {
      if ((trav->children) != NULL) {
      }
      if ((trav->children)[charIntoInt(num[numIndex])] != NULL) {
         trav = (trav->children)[charIntoInt(num[numIndex])];
         numIndex++;
			prefix++;
      }
      else {
         break;
      }
      if (trav != NULL && trav->forward != NULL) {
         farthestForwardNode = trav;
         prefixLength = prefix;
      }
	}
	/** Po wykonaniu powyższej pętli while wskaźnik @p farthestForwardNode wskazuje
    * albo na @p NULL, jeśli @p trav nie natrafił na żadne przekierowanie lub na
    * najdalszy node, w którym pole forward nie jest @p NULL 
    */
   if (farthestForwardNode == NULL) {
		/// Zwracamy @p phoneNum z polem @p numbers ustawionym na wartosc @p num
		phoneNum->numbers = malloc(1 * sizeof(char*));
		(phoneNum->numbers)[0] = malloc((checkLength(num) + 1) * sizeof(char));
		(phoneNum->numbers)[0][checkLength(num)] = '\0';
		for (size_t i = 0; i < checkLength(num); i++) {
			(phoneNum->numbers)[0][i] = num[i];
		}
      phoneNum->length = 1;
		return phoneNum;
	}
	size_t farthestForwardLength = checkLength(farthestForwardNode->forward);
	/** Jeśli jednak natrafiliśmy jednak na jakieś przekierowanie (które jest
    * teraz zawarte w polu @p farthestForwardNodeNode->forward ), to musimy
    * je scalić z ścieżką zawartą w prefiksie
    */
	size_t forwardedNumberLength = farthestForwardLength + (checkLength(num) - prefixLength);

	phoneNum->numbers = malloc(1 * sizeof(char*));
   /// Sprawdzamy, czy funkcja malloc się powiodła
   if (phoneNum->numbers == NULL) {
      phnumDelete(phoneNum);
      return NULL;
   }
   phoneNum->length = 1;
	(phoneNum->numbers)[0] = malloc((forwardedNumberLength + 1) * sizeof(char));
   if ((phoneNum->numbers)[0] == NULL) {
      /// Sprawdzamy, czy funkcja malloc się powiodła
      phnumDelete(phoneNum);
      return NULL;
   }
   /** Zapewniamy, że tworzony przez nas napis będzie prawidłowy (czyli kończący
    * się na znak '\0'.
   */
	(phoneNum->numbers)[0][forwardedNumberLength] = '\0';
   /** Wkładamy pierwszą część przekierowania ze znalezionego 
    * @p farthestForwardNode->forward, czylinajdalszego prefiksu przekierowania
    */
	for (size_t i = 0; i < farthestForwardLength; i++) {
		(phoneNum->numbers)[0][i] = (farthestForwardNode->forward)[i];
	}
   /** Wkładamy drugą część, która została z podanej ścieżki @p num (o ile istnieje)
    */
	size_t i = farthestForwardLength;
	size_t j = 0;
	while (i < forwardedNumberLength) {
		(phoneNum->numbers)[0][i] = num[prefixLength + j];
		i++;
		j++;
	}
	return phoneNum;
}

void phnumDelete(PhoneNumbers *pnum){
   if (pnum == NULL) {
      return;
   }
   for (size_t i = 0; i < pnum->length; i++) {
      free((pnum->numbers[i]));
   }
   free(pnum->numbers);
   free(pnum);
}

char const * phnumGet(PhoneNumbers const *pnum, size_t idx) {
   if (pnum == NULL || pnum->length <= idx) {
      return NULL;
   }
   return (pnum->numbers)[idx];
}