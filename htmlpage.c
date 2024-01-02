#include "htmlpage.h"

//--------- HtmlElement FUNCTIONS ----------------------

//FUNKCIJA GRAZINA ADRESA JEIGU VISKAS SEKMINGAI PAVYKO, KITU ATVEJU GRAZINA NULL
HtmlElement* initHtmlElement(char* elementType) {
  HtmlElement* htmlElement = malloc(sizeof(HtmlElement));
  
  if (htmlElement == NULL || elementType == NULL) {
    return NULL;
  }
  
  // Initialize all variables with default values
  htmlElement->_elementType = elementType;
  htmlElement->text = NULL;
  htmlElement->_childrenCount = 0;
  htmlElement->_childrenSize = 2;
  
  // Initialize the pointer array to other HtmlElements
  htmlElement->_children =
      malloc(sizeof(HtmlElement**) * htmlElement->_childrenSize);
  
  if (htmlElement->_children == NULL) {
    return NULL;
  }
  
  return htmlElement;
}

HtmlElement* addChild(HtmlElement* parent, HtmlElement** child) {
  if (parent == NULL || *child == NULL) {
    return NULL;
  }
  
  //JEIGU UZPILDYTAS MASYVAS, REALOKUOJAMA DAR VIETOS (NAUJOS_DYDIS = PRAEITOS_DYDIS * 2)
  if (parent->_childrenCount >= parent->_childrenSize) {
    parent->_childrenSize *= 2;
    parent->_children = realloc(parent->_children, sizeof(HtmlElement**) * parent->_childrenSize);

    //JEIGU IVYKO KLAIDA
    if (parent->_children == NULL) {

      //NEPAVYKO REALOKUOTI NAUJOS VIETOS, DYDIS PALIEKAMAS KOKS BUVO
      parent->_childrenSize /= 2;
      return NULL;
    }
  }  
  
  // GALIMA DABAR PRIDETI NAUJA ELEMENTA
  *(parent->_children + parent->_childrenCount) = child;
  parent->_childrenCount += 1;

  return *child;
}

void _freeHtmlElement(HtmlElement **htmlElement) {
  // sitas if tiesiog, kad jeigu NULL net nebelistu i for loopa
  if (*htmlElement == NULL) {
    return;
  }
  
  for (int i = 0; i < (*htmlElement)->_childrenCount; i++) {
    HtmlElement** child = *((*htmlElement)->_children + i);
    
    _freeHtmlElement(child);
  }

  // sitas antras if irgi reikalingas in case parent elementas buvo
  // toks pat kaip ir jo kazkoks child
  if (*htmlElement == NULL) {
    return;
  }
  
  free(*htmlElement);
  *htmlElement = NULL;
}

//--------- HtmlElement FUNCTIONS ----------------------

//--------- HtmlPage FUNCTIONS ----------------------


//FUNKCIJA GRAZINA ADRESA JEIGU VISKAS SEKMINGAI PAVYKO, KITU ATVEJU GRAZINA NULL
HtmlPage* initHtmlPage(char* fileName) {
  HtmlPage* htmlPage = malloc(sizeof(HtmlPage));

  if (htmlPage == NULL) {
    return NULL;
  }
  
  FILE* htmlFile;

  htmlFile = fopen(fileName, "w");

  if(htmlFile == NULL){
    return NULL;
  }

  htmlPage->_htmlFile = htmlFile;

  //SUKURIA <HEAD> HTML ELEMENTA
  HtmlElement* htmlHead = initHtmlElement("head");
  if (htmlHead == NULL) {
    return NULL;
  }
  
  htmlPage->_htmlHead = htmlHead;

  //SUKURIA <BODY> HTML ELEMENTA
  HtmlElement* htmlBody = initHtmlElement("body");
  if (htmlBody == NULL) {
    return NULL;
  }

  htmlPage->_htmlBody = htmlBody;

  return htmlPage;
}

HtmlElement* addBodyElement(HtmlPage* htmlPage, HtmlElement** htmlElement) {
  if (htmlPage == NULL || *htmlElement == NULL) {
    return NULL;
  }
  
  // Prideda nauja elementa i body
  if (addChild(htmlPage->_htmlBody, htmlElement) == NULL) {
    return NULL;
  }

  return *htmlElement;
}

void _writeHtmlElement(HtmlPage* htmlPage, HtmlElement* htmlElement, unsigned short depth) {
  FILE* htmlFile = htmlPage->_htmlFile;

  // tarpu pridejimas
  for (int i = 0; i < depth; i++) {
    fprintf(htmlFile, "  ");
  }

  // elemento atspausdinimas
  fprintf(htmlFile, "<%s>", htmlElement->_elementType);

  // teksto, jei jis yra atspausdinimas
  if (htmlElement->text != NULL) {
    fprintf(htmlFile, "%s", htmlElement->text);
  }

  fprintf(htmlFile, "\n");
  
  // elemento 'children' atspausdinimas
  for (int i = 0; i < htmlElement->_childrenCount; i++) {
    HtmlElement** child = *(htmlElement->_children + i);
    
    _writeHtmlElement(htmlPage, *child, depth+1);
  }

  // tarpu pridejimas
  for (int i = 0; i < depth; i++) {
    fprintf(htmlFile, "  ");
  }
  
  fprintf(htmlFile, "</%s>\n", htmlElement->_elementType);
}

void _freeHtmlPage(HtmlPage** htmlPage) {
  if (htmlPage != NULL) {
      _freeHtmlElement(&(*htmlPage)->_htmlHead);
      _freeHtmlElement(&(*htmlPage)->_htmlBody);

      // pafreeinimas ir pats HtmlPage galiausiai
      free(*htmlPage); 
      *htmlPage = NULL;
  }
}

void createHtmlPage(HtmlPage** htmlPage) {
  if (*htmlPage == NULL) {
    return;
  }
  
  FILE *htmlFile = (*htmlPage)->_htmlFile;

  fprintf(htmlFile, "<!DOCTYPE html>\n");

  HtmlElement* htmlHead = (*htmlPage)->_htmlHead;

  // sukuria i html visa head
  _writeHtmlElement(*htmlPage, htmlHead, 0);
  
  HtmlElement *htmlBody = (*htmlPage)->_htmlBody;
  
  // sukuria i html visa body
  _writeHtmlElement(*htmlPage, htmlBody, 0);

  _freeHtmlPage(htmlPage);
}
