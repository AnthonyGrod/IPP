/*
#ifdef NDEBUG
#undef NDEBUG
#endif

#include "phone_forward.h"
#include <assert.h>
#include <string.h>

#define MAX_LEN 23

int main() {
  
  char num1[MAX_LEN + 1], num2[MAX_LEN + 1];
  PhoneForward *pf;
  PhoneNumbers *pnum;

  pf = phfwdNew();

  strcpy(num1, "123");
  strcpy(num2, "9");
  assert(phfwdAdd(pf, num1, num2) == true);
  memset(num1, 0, sizeof num1);
  memset(num2, 0, sizeof num2);
  
  
  pnum = phfwdGet(pf, "1234");
  assert(strcmp(phnumGet(pnum, 0), "94") == 0);
  assert(phnumGet(pnum, 1) == NULL);
  phnumDelete(pnum);

  pnum = phfwdGet(pf, "12");
  assert(strcmp(phnumGet(pnum, 0), "12") == 0); 
  phnumDelete(pnum);

  strcpy(num1, "123456");
  strcpy(num2, "777777");
  assert(phfwdAdd(pf, num1, num2) == true);

  pnum = phfwdGet(pf, "12345");
  assert(strcmp(phnumGet(pnum, 0), "945") == 0);
  phnumDelete(pnum);
  
  pnum = phfwdGet(pf, "123456");
  assert(strcmp(phnumGet(pnum, 0), "777777") == 0);
  phnumDelete(pnum);

  pnum = phfwdGet(pf, "997");
  assert(strcmp(phnumGet(pnum, 0), "997") == 0);
  phnumDelete(pnum);

  assert(phfwdAdd(pf, "431", "432") == true);
  assert(phfwdAdd(pf, "432", "433") == true);
  pnum = phfwdGet(pf, "431");
  assert(strcmp(phnumGet(pnum, 0), "432") == 0);
  phnumDelete(pnum);
  pnum = phfwdGet(pf, "432");
  assert(strcmp(phnumGet(pnum, 0), "433") == 0);
  phnumDelete(pnum);

  phfwdRemove(pf, "12");
  pnum = phfwdGet(pf, "123456");


  assert(strcmp(phnumGet(pnum, 0), "123456") == 0);
  phnumDelete(pnum);

  assert(phfwdAdd(pf, "567", "0") == true);
  assert(phfwdAdd(pf, "5678", "08") == true);

  assert(phfwdAdd(pf, "A", "1") == false);
  assert(phfwdAdd(pf, "1", "A") == false);

  phfwdRemove(pf, "");
  phfwdRemove(pf, NULL);

  pnum = phfwdGet(pf, "A");
  assert(phnumGet(pnum, 0) == NULL);
  phnumDelete(pnum);

  phfwdAdd(pf, "12", "123");
  pnum = phfwdGet(pf, "123");
  assert(strcmp(phnumGet(pnum, 0), "1233") == 0);
  phnumDelete(pnum);

  phfwdDelete(pf);
  return 1;
}
*/

#include <stdio.h>

#include "phone_forward.h"

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

int main(void) {
    //      UWAGA, TEN TEST NIE JEST WYDAJNOŚCIOWY!!!!!!!!!
    //      NIE PRZEJMUJCIE SIĘ CZASAMI

    /*
     *                      TEST STACK OVERFLOW
     *
     * Jeśli zrobisz długiego DFSa - np. na drzewie o głębokości 10^7, to stos
     * zajmie więcej niż 16MB. Przekroczenie stosu to jest błąd to którego
     * nie można dopuścić - trzeba albo iterować się po drzewie whilami,
     * albo nie wiem. Nie można w ogóle robić baardzo długich rekurencji.
     */

    #define TREE_DEPTH 20000000 // 20 MB - więcej niż stos
    // Próbujemy zrobić 2 bardzo długie napisy
    char *a = calloc(TREE_DEPTH + 1, sizeof(char));
    char *b = calloc(TREE_DEPTH + 1, sizeof(char));
    if(a == NULL || b == NULL) {
        printf("Błąd testu. Być może twoja wina, być może jest za mało pamięci.\n");
        assert(false);
    }
    for (int i = 0; i < TREE_DEPTH; ++i) {
        a[i] = '1';
        b[i] = '2';
    }
    a[TREE_DEPTH] = '\0';
    b[TREE_DEPTH] = '\0';

    PhoneForward * pf = phfwdNew();

    phfwdAdd(pf, a, b);

    PhoneNumbers * pn = phfwdGet(pf, a);

    assert(pn != NULL);
    assert(strcmp(phnumGet(pn, 0), b) == 0);
    assert(phnumGet(pn, 1) == NULL);
    phnumDelete(pn);

    // Usunięcie drzewa nie może być robione klasycznym DFSem.
    phfwdDelete(pf);
    free(a);
    free(b);

}