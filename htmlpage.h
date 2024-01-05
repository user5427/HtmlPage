//
// Created on 2023-12-23.
// TODO comment what each function does here

#ifndef PROPROPRO_MODULIS_HTMLPAGE_H
#define PROPROPRO_MODULIS_HTMLPAGE_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct HtmlElement{
    char* _elementType;
    char* text;

    struct HtmlElement*** _children; // An array of double pointers to Html element
    unsigned int _childrenCount; // Pointer array capacity
    unsigned int _childrenSize; // Pointer array current size

    //CLASS, ID dar prideti reikes

} HtmlElement;

HtmlElement* initHtmlElement(char* elementType);
HtmlElement* addChild(HtmlElement* parent, HtmlElement** child);
void _freeHtmlElement(HtmlElement** htmlElement);
typedef struct {
    FILE *_htmlFile;
    //CSS FILE prideti

    HtmlElement* _htmlHead;
    HtmlElement* _htmlBody;

} HtmlPage;
HtmlPage* initHtmlPage(char* fileName);
HtmlElement* addBodyElement(HtmlPage* htmlPage, HtmlElement** htmlElement);
HtmlElement* addHeadElement(HtmlPage* htmlPage, HtmlElement** htmlElement);
void _writeHtmlElement(HtmlPage* htmlPage, HtmlElement* htmlElement, unsigned short depth); //TODO ar reikia vartotojui sitos funkcijos?
void _freeHtmlPage(HtmlPage** htmlPage);
void createHtmlPage(HtmlPage** htmlPage);
#endif //PROPROPRO_MODULIS_HTMLPAGE_H
