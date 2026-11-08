#include "point.h"

Point create_point(double x, double y) {
    Point p;
    p.x = x;
    p.y = y;
    return p;
}

/*
    Funktiolla voidaan tarkistaa onko kolmiiden pisteet samat ja näin voidaan varmistaa että ei tuoteta sellaisia kolmitoita joiden kaksi kulmaa olisi samassa pisteessä sekä
    voidaan katsoa mitkä kolmiot jakavat pisteen.
*/

int point_equals(Point p1, Point p2) {
    return p1.x == p2.x && p1.y == p2.y;
}