#include "html_modulis.h"
#include "stdio.h"
//--------- HtmlPage FUNCTIONS examples/tests ----------------------
int main() {
    // example
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

    /* ----------- Tests 1 ----------- */
    HtmlPage *htmlTest = initHtmlPage("tests.html");
    HtmlElement *main = initHtmlElement("main");
    HtmlElement *h1 = initHtmlElement("h1");
    h1->text = "CatPhotoApp";
    HtmlElement *section = initHtmlElement("section");
    HtmlElement *h2 = initHtmlElement("h2");
    h2->text = "Cat Photos";
    for (int i = 0; i < 10; ++i) {
        addChild(section, h2);
    }
    addChild(h1, section);
    addChild(main, h1);
    addBodyElement(htmlTest, main);
    createHtmlPage(htmlTest);
    freeHtmlPage(htmlTest); //FIXME
    createHtmlPage(htmlTest);
    freeHtmlPage(htmlPage); //FIXME
    createHtmlPage(htmlPage);

    /* ----------- Tests 2 ----------- */
    HtmlPage *htmlTest2 = initHtmlPage("tests2.html");
    HtmlElement *p2_1 = initHtmlElement("h1");
    HtmlElement *a = initHtmlElement("a");
    a->text = "cat photos";
    p2_1->text = "CatPhotoApp";
    addChild(p2_1, a);
    //addChild(a, p2_1); //FIXME infinite loop?
    addBodyElement(htmlTest2, p2_1);
    createHtmlPage(htmlTest2);
    return 0;
}
