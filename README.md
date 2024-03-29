# HtmlPage
## Turinys
[Turinys](https://github.com/user5427/ProProPro-modulis/tree/readme-dokumentacija?tab=readme-ov-file#turinys)  
[Aprašymas](https://github.com/user5427/ProProPro-modulis/tree/readme-dokumentacija/README.md#apra%C5%A1ymas)  
[Dokumentacija](https://github.com/user5427/ProProPro-modulis/tree/readme-dokumentacija#dokumentacija)
- [HtmlPage](https://github.com/user5427/ProProPro-modulis/tree/readme-dokumentacija?tab=readme-ov-file#htmlpage-1)
  - [initHtmlPage()](https://github.com/user5427/ProProPro-modulis/tree/readme-dokumentacija?tab=readme-ov-file#htmlpage-inithtmlpagechar-filename)
  - [addBodyElement()](https://github.com/user5427/ProProPro-modulis/tree/readme-dokumentacija?tab=readme-ov-file#htmlelement-addbodyelementhtmlpage-htmlpage-htmlelement-htmlelement)
  - [createHtmlPage()](https://github.com/user5427/ProProPro-modulis/tree/readme-dokumentacija?tab=readme-ov-file#void-createhtmlpagehtmlpage-htmlpage)
- [HtmlElement](https://github.com/user5427/ProProPro-modulis/tree/readme-dokumentacija?tab=readme-ov-file#htmlelement)
  - [initHtmlElement()](https://github.com/user5427/ProProPro-modulis/tree/readme-dokumentacija?tab=readme-ov-file#htmlelement-inithtmlelementchar-elementtype)
  - [addChild()](https://github.com/user5427/ProProPro-modulis/tree/readme-dokumentacija?tab=readme-ov-file#htmlelement-addchildhtmlelement-parent-htmlelement-child) 
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
Struktūra kuri aprašo visą html puslapį.
```c
typedef struct HtmlPage{
  char* cssFileName;
} HtmlPage;
```
`cssFileName` - css failo pavadinimas, jeigu nėra tada `NULL`

## `HtmlPage* initHtmlPage(char* fileName)`
Sukuria `HtmlPage` struktūrą
### Argumentai
`fileName` - kuriamo html failo pavadinimas
### Gražina
Adresą į sukurtą `HtmlPage` arba `NULL` jeigu nepavyko sukurti

## `HtmlElement* addBodyElement(HtmlPage* htmlPage, HtmlElement** htmlElement)`
Prideda `htmlElement` prie html `<body>` elementų
### Argumentai
`htmlPage` - prie šios struktūros bus pridėtas `htmlElement` \
`htmlElement` - pridedamas elementas
### Gražina
Adresą į pridėtą `HtmlElement` arba `NULL` jeigu nepavyko pridėti

## `void createHtmlPage(HtmlPage** htmlPage)`
Sugeneruoja html puslapį, pagal nurodytą sukurtą struktūrą \
**SVARBU: po funkcijos iškvietimo `htmlPage` elementas nebegali būti naudojamas!** 
```c
createHtmlPage(htmlPage);
addChild(htmlPage, htmlElement); //htmlPage -> sicia lygus NULL
```
### Argumentai
`htmlPage` - adresas į pointerį, kuriame norimas sukurti puslapis

## HtmlElement
Struktūra kuri aprašo visus html elementus.
```c
typedef struct HtmlElement{
  char* text;
  char* id;
  char* class;
} HtmlElement;
```
`char* text` - kintamasis, kuriame gali būti parašytas tekstas kuris būtų html tage.
`char* id` - html elemento id
`char* class` - html elemento class
```c
HtmlElement* p = initHtmlElement("p");
p->text = "Hello World!";
```
Gautas html kodas bus:
```html
<p>Hello World!
</p>
```

## `HtmlElement* initHtmlElement(char* htmlTag)`
Sukuria `HtmlElement` struktūrą
### Argumentai
`htmlTag` - [html tago](https://www.w3schools.com/tags/default.asp) pavadinimas 
### Gražina
Adresą į sukurtą `HtmlElement` arba `NULL` jeigu nepavyko sukurti

## `HtmlElement* addChild(HtmlElement* parent, HtmlElement** child)`
Prideda duotajam `parent` elementui, `child` elementą
```c
HtmlElement* div = initHtmlElement("div");
HtmlElement* p = initHtmlElement("p");
p->text = "Hello World!";
addChild(div, p);
```
Gautas html kodas bus:
```html
<div>
  <p>Hello World!
  </p>
</div>
```
### Argumentai
`parent` - adresas į `HtmlElement`, į kurį bus pridėtas `child` \
`child` - adresas į pointerį `HtmlElement`, kurį pridėti
### Gražina
Adresą i pridėtą `HtmlElement` arba `NULL` jeigu nepavyko pridėti

