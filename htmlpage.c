#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//--------- HtmlElement FUNCTIONS ----------------------

typedef struct HtmlElement{
  char* _elementType;
  char* text;

  struct HtmlElement** _children;
  unsigned int _childrenCount;
  unsigned int _childrenSize;
  
  //CLASS, ID dar prideti reikes

} HtmlElement;

//FUNKCIJA GRAZINA ADRESA JEIGU VISKAS SEKMINGAI PAVYKO, KITU ATVEJU GRAZINA NULL
HtmlElement* initHtmlElement(char* elementType) {
  HtmlElement* htmlElement = malloc(sizeof(HtmlElement));
  
  if (htmlElement == NULL || elementType == NULL) {
    return NULL;
  }
  
  htmlElement->_elementType = elementType;
  htmlElement->text = NULL;
  htmlElement->_childrenCount = 0;
  htmlElement->_childrenSize = 2;

  htmlElement->_children =
      malloc(sizeof(HtmlElement*) * htmlElement->_childrenSize);

  if (htmlElement->_children == NULL) {
    return NULL;
  }
  
  return htmlElement;
}

HtmlElement* addChild(HtmlElement* parent, HtmlElement* child) {
  if (parent == NULL || child == NULL) {
    return NULL;
  }
  
  //JEIGU UZPILDYTAS MASYVAS, REALOKUOJAMA DAR VIETOS (NAUJOS_DYDIS = PRAEITOS_DYDIS * 2)
  if (parent->_childrenCount >= parent->_childrenSize) {
    parent->_childrenSize *= 2;
    parent->_children = realloc(parent->_children, sizeof(HtmlElement*) * parent->_childrenSize);

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

  return child;
}

void freeHtmlElement(HtmlElement* htmlElement) {
  for (int i = 0; i < htmlElement->_childrenCount; i++) {
    HtmlElement* child = *(htmlElement->_children + i);
    
    freeHtmlElement(child);
  }

  free(htmlElement);
}

//--------- HtmlElement FUNCTIONS ----------------------

//--------- HtmlPage FUNCTIONS ----------------------

typedef struct {
  FILE *_htmlFile;
  //CSS FILE prideti
 
  HtmlElement* _htmlHead;
  HtmlElement* _htmlBody;
  
} HtmlPage;


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

HtmlElement* addBodyElement(HtmlPage* htmlPage, HtmlElement* htmlElement) {
  if (htmlPage == NULL || htmlElement == NULL) {
    return NULL;
  }

  // Prideda nauja elementa i body
  if (addChild(htmlPage->_htmlBody, htmlElement) == NULL) {
    return NULL;
  }

  return htmlElement;
}

void writeHtmlElement(HtmlPage* htmlPage, HtmlElement* htmlElement, unsigned short depth) {
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
    HtmlElement* child = *(htmlElement->_children + i);
    
    writeHtmlElement(htmlPage, child, depth+1);
  }

  // tarpu pridejimas
  for (int i = 0; i < depth; i++) {
    fprintf(htmlFile, "  ");
  }
  
  fprintf(htmlFile, "</%s>\n", htmlElement->_elementType);
}

void freeHtmlPage(HtmlPage* htmlPage) {
  if (htmlPage == NULL) {
    return;
  }

  freeHtmlElement(htmlPage->_htmlHead);
  freeHtmlElement(htmlPage->_htmlBody);
}

void createHtmlPage(HtmlPage* htmlPage) {
  if (htmlPage == NULL) {
    return;
  }
  
  FILE *htmlFile = htmlPage->_htmlFile;

  fprintf(htmlFile, "<!DOCTYPE html>\n");

  HtmlElement* htmlHead = htmlPage->_htmlHead;

  // sukuria i html visa head
  writeHtmlElement(htmlPage, htmlHead, 0);
  
  HtmlElement *htmlBody = htmlPage->_htmlBody;
  
  // sukuria i html visa body
  writeHtmlElement(htmlPage, htmlBody, 0);

  //TODO: GAL FREE PALIKTI NAUDOTOJUI PACIAM NAUDOTI?
  freeHtmlPage(htmlPage);
}

//--------- HtmlPage FUNCTIONS ----------------------

int main() {
  HtmlPage *htmlPage = initHtmlPage("failas.html");

  HtmlElement *div = initHtmlElement("div");
  
  HtmlElement *p = initHtmlElement("p");
  HtmlElement *p2 = initHtmlElement("p");
  HtmlElement *p3 = initHtmlElement("p");
  HtmlElement *p4 = initHtmlElement("p");
  

  if (htmlPage == NULL) {
    printf("HTML PAGE NULLIS\n");
    return 1;
  }
  
  if (p == NULL) {
    printf("Ivyko klaida\n");
    return 1;
  }

  p->text = "Hello World!";
  p2->text = "123123";
  p3->text = "asdasd";
  p4->text = "wadasdaw";

  addChild(div, p);
  addChild(div, p2);
  addChild(div, p3);
  addChild(div, p4);

  addBodyElement(htmlPage, div);
  
  createHtmlPage(htmlPage);
  
  return 0;
}
