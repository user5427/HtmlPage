# Html modulis

## Funkcijos

Darbui su **html elementu**:
- HtmlElement* initHtmlElement(char* elementType);
- HtmlElement* addChild(HtmlElement* parent, HtmlElement* child);
- void freeHtmlElement(HtmlElement* htmlElement);

Darbui su **html puslapiu**:
- HtmlPage* initHtmlPage(char* fileName);
- HtmlElement* addBodyElement(HtmlPage* htmlPage, HtmlElement* htmlElement);
- void writeHtmlElement(HtmlPage* htmlPage, HtmlElement* htmlElement, unsigned short depth);
- void freeHtmlPage(HtmlPage* htmlPage);
- void createHtmlPage(HtmlPage* htmlPage);

### Funkcijų paaiškinimai
- initHtmlElement() - sukuria html elementą.
- addChild() - prie nurodyto html elemento prideda gilesnį html elementą.
- freeHtmlElement() - atlaisvina html elementą su visais gilesniais html elementais.

- initHtmlPage() - sukuria html puslapį.
- addBodyElement() - prie html body prideda html elementą su visais gilesniais elementais.
- writeHtmlElement() - išsaugoja html elementą su visais gilesniais html elementais į failą. Naudojama **rekursija**.
- freeHtmlPage() - atlaisvina html puslapio atmintį su visais html elementais.
- createHtmlPage() - sukuria html puslapį, išsaugoja jame head ir body.
