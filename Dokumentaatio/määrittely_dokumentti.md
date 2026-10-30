# Määrittelydokumentti

Määritely dokumenti Helsingin Yliopiston Algoritmit & Tekoäly- kurssin 2026 harjoitus työlle.

Opinto-ohjelma: Tietojenkäsittelytiede

## Aihe

Harjoitustyön aiheena on satunnaisesti generoitavan labyrintin tuottaminen graafialgoritmien avulla.

Ohjelma luo ensin satunnaisesti sijoittettuja pisteitä jotka ovat labyrintin huoneita. Huoneet sijoiten siten että ne eivät ole päällekkäin tai toisissaan kiinni.

Huoneiden keskipisteistä muodostetaan Delaunay-triangulaatio Bowyer-Watson-algoritmin avulla. Näin muodostetut yteydet toimivat kaarina, ja niiden painot tulevat huoneiden välisistä etäisyyksistä.

Tämän jälkeen graafista muodostetaan virittävä minipuu (Minumum Spanning tree) Kruskalin algoritmilla. Näistä muodostuu huoneiden väliset yhteydet niin että kaikki huoneet ovat osa verkkoa, mutta siten että se ei sisällä syklejä. Näitä yhteyksiä käytetään labyrintin käytävinä.


## Ohjelman syötteet ja tulosteet

Ohjelmalle voidaan antaa seuraavat parametrit : Huondeiden lukumäärä, Labyrintin leveys ja korkeus, Huoneiden vähimmäis etäisyys, Siemenluku(seed)

## Ohjelmointikielet

Toteutuskieleksi valitsin C-kielen, mutta olen toteuttanut projekteja JavaScriptiä, Java, Python ja Haskell kieliä käyttämällä.

## Algoritmit ja tietorakenteet

Työssä käytettyt algoritmit

### Bowyer-Watson 

Algoritmia käytetään Delaunay-triangulaation muodostamiseen. Algoritmi lisää pisteitä triangulaatioon yksi kerrallaan ja päivittää kolmiorakennetta uusien pisteiden perusteella.

### Kruskalin algoritmi

Algoritmia käytetään virittävän minimipuun muodostamiseen. Graafin kaaret järjestetään painojensa mukaiseen järjestykseen, minkä jälkeen minimipuu muodostetaan valitsemalla kaaria, jotka eivät aiheuta sykliä.

## Union-Find

Kruskalin algoritmin yhteydessä toteutetaan Union-Find-tietorakenne, jonka avulla voidaan tehokkaasti tarkistaa, kuuluvatko kaksi solmua jo samaan komponenttiin.

Lisäksi toteutetaan tarvittavat tietorakenteet pisteiden, kolmioiden, graafin kaarien ja huoneiden tallentamiseen.

## Aika- ja tilavaativuudet

Bowyer–Watson-algoritmin yksinkertaisen toteutuksen tyypillinen aikavaativuus on O(n²). Optimoidulla toteutuksella voidaan saavuttaa odotettu O(n log n) -aikavaativuus.

Kruskalin algoritmin aikavaativuus on O(E log E), missä E tarkoittaa graafin kaarien lukumäärää. Algoritmin aikavaativuus muodostuu pääasiassa kaarien järjestämisestä.

Union-Find-tietorakenteen operaatioiden amortisoitu aikavaativuus on O(α(n)), kun käytetään polun tiivistämistä ja union by rank/size -optimointia.

Delaunay-triangulaation tallentamisen tilavaativuus on O(n) kaksiulotteisessa tapauksessa. Kruskalin algoritmin tilavaativuus on O(n + E), kun mukaan lasketaan graafin kaaret ja Union-Find-tietorakenne.

## Lähteet

Algoritmien suunnittelussa ja toteutuksessa käytetään alustavasti seuraavia lähteitä:

Bowyer–Watson algorithm – [Wikipedia](https://en.wikipedia.org/wiki/Bowyer%E2%80%93Watson_algorithm)
Delaunay triangulation – [Wikipedia](https://en.wikipedia.org/wiki/Delaunay_triangulation)
Kruskal's algorithm – [Wikipedia](https://en.wikipedia.org/wiki/Kruskal%27s_algorithm)
Disjoint-set data structure – [Wikipedia](https://en.wikipedia.org/wiki/Disjoint-set_data_structure)

Lisäksi toteutuksen aikana voidaan hyödyntää muita algoritmien toimintaa ja aikavaativuuksia käsitteleviä lähteitä.

## Dokumentaatio

Harjoitustyön dokumentaatio kirjoitetaan suomeksi. Ohjelmakoodissa muuttujat, funktiot ja tietorakenteet nimetään englanniksi.