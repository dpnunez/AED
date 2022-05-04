#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Node {
  int value;
  struct Node *nodeLeft;
  struct Node *nodeRight;
} Node;

int addNode(Node **ppRoot, int value);
int isBalanced(Node **ppRoot);
int FB(Node *pRoot);
int treeHeight(Node *pRoot);
void RES(Node **ppRoot);	// Buscar nomenclatura em ingles para duplas rotacoes
void RDS(Node **ppRoot);	// Buscar nomenclatura em ingles para duplas rotacoes
int spinLeft(Node **ppRoot);
int spinRight(Node **ppRoot);
int isAVL(Node *pRoot);
void validationAVL(Node *ppRoot);
void freeTree(Node *ppRoot);
void secondSchema();
void case1a();
void case2a();
void case3a();
void case1b();
void case2b();
void case3b();

int main() {
  int 
		i = 0,
		nodeValue,
		nodeAmount;
  Node *ppRoot = NULL;

  printf("Quantidade de nós: ");
  scanf("%d", &nodeAmount);
  setbuf(stdin, NULL);

  srand(time(0));

	// Gerar randomicamente
  while (i < nodeAmount) {
    nodeValue = rand() % 100;
    addNode(&ppRoot, nodeValue);
    i++;
  }

	// Verificar se é avl
	validationAVL(ppRoot);

	// Limpar arvore
  freeTree(ppRoot);

  secondSchema();

  return 0;
}

int addNode(Node **ppRoot, int value) {
  if (*ppRoot == NULL) {
    *ppRoot = (Node *)malloc(sizeof(Node));
    (*ppRoot)->value = value;
    (*ppRoot)->nodeLeft = NULL;
    (*ppRoot)->nodeRight = NULL;
    return 1;
  } else if ((*ppRoot)->value > value) {
    if (addNode(&(*ppRoot)->nodeLeft, value)) {
      if (isBalanced(ppRoot)) {
        return 0;
      } else {
        return 1;
      }
    }
  } else if ((*ppRoot)->value < value) {
    if (addNode(&(*ppRoot)->nodeRight, value)) {
      if (isBalanced(ppRoot)) {
        return 0;
      } else {
        return 1;
      }
    }
  } else {
    return 0;
  }
}

int isBalanced(Node **ppRoot) {
  int fb = FB(*ppRoot);

  if (fb > 1) {
    return spinLeft(ppRoot);
  } else if (fb < -1) {
    return spinRight(ppRoot);
  } else {
    return 0;
  }
}

int FB(Node *pRoot) {
  if (pRoot == NULL) {
    return 0;
  }
  return treeHeight(pRoot->nodeLeft) - treeHeight(pRoot->nodeRight);
}

int treeHeight(Node *pRoot) {
  int Esq, Dir;

  if (pRoot == NULL) {
    return 0;
  }

  Esq = treeHeight(pRoot->nodeLeft);
  Dir = treeHeight(pRoot->nodeRight);

  if (Esq > Dir) {
    return Esq + 1;
  } else {
    return Dir + 1;
  }
}

void RES(Node **ppRoot) {
  Node *pAux;

  pAux = (*ppRoot)->nodeRight;
  (*ppRoot)->nodeRight = pAux->nodeLeft;
  pAux->nodeLeft = (*ppRoot);
  (*ppRoot) = pAux;
}

void RDS(Node **ppRoot) {
  Node *pAux;

  pAux = (*ppRoot)->nodeLeft;
  (*ppRoot)->nodeLeft = pAux->nodeRight;
  pAux->nodeRight = (*ppRoot);
  (*ppRoot) = pAux;
}

int spinLeft(Node **ppRoot) {
  int FBE = FB((*ppRoot)->nodeLeft);

  if (FBE > 0) {
    RDS(ppRoot);

    return 1;
  } else if (FBE < 0) {
    RES(&((*ppRoot)->nodeLeft));
    RDS(ppRoot);

    return 1;
  }
  return 0;
}

int spinRight(Node **ppRoot) {
  int FBD = FB((*ppRoot)->nodeRight);

  if (FBD <= 0) {
    RES(ppRoot);

    return 1;
  } else if (FBD > 0) {
    RDS(&((*ppRoot)->nodeRight));
    RES(ppRoot);

    return 1;
  }
  return 0;
}

void validationAVL(Node *ppRoot) {
	if(isAVL(ppRoot)) {
		printf("\nSucesso! É uma arvore AVL\n");
	} else { 
		printf("\nNao respeitando o algoritimo AVL!\n");
	}
}

int isAVL(Node *ppRoot) {
  int fb;
  fb = FB(ppRoot);

  if (ppRoot == NULL)
    return 1;

  if (!isAVL(ppRoot->nodeLeft)) {
    return 0;
  }
  if (!isAVL(ppRoot->nodeRight)) {
    return 0;
  }

  if ((fb > 1) || (fb < -1)) {
    return 0;
  } else {
    return 1;
  }
}

void secondSchema() {
  printf("\n--caso 1A--\n");
  case1a();
  printf("\n--caso 2A--\n");
  case2a();
  printf("\n--caso 3A--\n");
  case3a();
  printf("\n--caso 1B--\n");
  case1b();
  printf("\n--caso 2B--\n");
  case2b();
  printf("\n--caso 3B--\n");
  case3b();
}

void freeTree(Node *ppRoot) {
  if (ppRoot == NULL) return;

  freeTree(ppRoot->nodeLeft);
  freeTree(ppRoot->nodeRight);

  free(ppRoot);
}

void case1a() {
  Node *ppRoot = NULL;
  int nodeValue;
  nodeValue = 20;
  addNode(&ppRoot, nodeValue);
  nodeValue = 4;
  addNode(&ppRoot, nodeValue);
	validationAVL(ppRoot);

  printf("\n\n");
  nodeValue = 15;
  addNode(&ppRoot, nodeValue);

	validationAVL(ppRoot);
  freeTree(ppRoot);
}

void case2a() {
  Node *ppRoot = NULL;
  int values[6] = {20, 4, 26, 3, 9, 15};
  int i;

  for (i = 0; i < 5; i++) {
    addNode(&ppRoot, values[i]);
  };


	validationAVL(ppRoot);
  printf("\n\n");

  addNode(&ppRoot, values[5]);
	validationAVL(ppRoot);

  freeTree(ppRoot);
}

void case3a() {
  Node *ppRoot = NULL;
  int values[11] = {20, 4, 26, 3, 9, 2, 7, 11, 21, 30, 15};
  int i;

  for (i = 0; i < 10; i++) {
    addNode(&ppRoot, values[i]);
  };


	validationAVL(ppRoot);
  printf("\n\n");

  addNode(&ppRoot, values[11]);
	validationAVL(ppRoot);

  freeTree(ppRoot);
}

void case1b() {
  Node *ppRoot = NULL;
  int nodeValue;
  nodeValue = 20;
  addNode(&ppRoot, nodeValue);
  nodeValue = 4;
  addNode(&ppRoot, nodeValue);
	validationAVL(ppRoot);
  printf("\n\n");
  nodeValue = 8;
  addNode(&ppRoot, nodeValue);
	validationAVL(ppRoot);
  freeTree(ppRoot);
}

void case2b() {
  Node *ppRoot = NULL;
  int values[6] = {20, 4, 26, 3, 9, 8};
  int i;

  for (i = 0; i < 5; i++) {
    addNode(&ppRoot, values[i]);
  };

	validationAVL(ppRoot);
  printf("\n\n");

  addNode(&ppRoot, values[5]);
	validationAVL(ppRoot);

  freeTree(ppRoot);
}

void case3b() {
  Node *ppRoot = NULL;
  int values[11] = {20, 4, 26, 3, 9, 2, 7, 11, 21, 30, 8};
  int i;

  for (i = 0; i < 10; i++) {
    addNode(&ppRoot, values[i]);
  };

	validationAVL(ppRoot);
  printf("\n\n");

  addNode(&ppRoot, values[11]);
	validationAVL(ppRoot);

  freeTree(ppRoot);
}

