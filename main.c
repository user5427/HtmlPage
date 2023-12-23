#include "html_modulis.h"
#include "stdio.h"
//--------- HtmlPage FUNCTIONS examples/tests ----------------------
int main() {
    // Write tests here
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
