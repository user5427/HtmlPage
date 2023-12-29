# HtmlPage

## Aprašymas
**HtmlPage** modulis generuoja html failus, pagal sukurtus elementus. 
Modulio naudojimo pavyzdys: 
```c
#include "html_modulis.h"

int main() {
    HtmlPage *htmlPage = initHtmlPage("failas.html");

    HtmlElement *div = initHtmlElement("div");

    HtmlElement *p = initHtmlElement("p");
    HtmlElement *p2 = initHtmlElement("p");
    HtmlElement *p3 = initHtmlElement("p");
    HtmlElement *p4 = initHtmlElement("p");

    p->text = "Hello World!";
    p2->text = "123123";
    p3->text = "asdasd";
    p4->text = "wadasdaw";

    addChild(div, &p);
    addChild(div, &p2);
    addChild(div, &p3);
    addChild(div, &p4);

    addBodyElement(htmlPage, &div);
    
    createHtmlPage(&htmlPage);

    return 0;
}
```
Gautas sugeneruotas html failas atrodo taip:
```html
<!DOCTYPE html>
<head>
</head>
<body>
  <div>
    <p>Hello World!
    </p>
    <p>123123
    </p>
    <p>asdasd
    </p>
    <p>wadasdaw
    </p>
  </div>
</body>

```

# Dokumentacija

## HtmlPage

### ` HtmlPage* initHtmlPage(char* fileName); `
Sukuria `HtmlPage` struktūrą. 
#### Argumentai
`fileName` - kuriamo html failo pavadinimas. 
#### Gražina
Adresą į sukurtą `HtmlPage` arba `NULL` jeigu nepavyko sukurti.

### `HtmlElement* addBodyElement(HtmlPage* htmlPage, HtmlElement** htmlElement);`
Prideda `htmlElement` prie html `<body>` elementų.

#### Argumentai
`htmlPage` - prie šios struktūros bus pridėtas `htmlElement` \
`htmlElement` - pridedamas elementas. 
#### Gražina
Adresą į pridėtą `HtmlElement` arba NULL jeigu nepavyko pridėti.
## HtmlElement

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
