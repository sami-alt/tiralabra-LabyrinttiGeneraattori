# Toteutusdokumentti

## Projektin rakenne

Projekti on jaettu useisiin moduuleihin, joista jokaisella on oma selkeä vastuualueensa. Tavoitteena on ollut pitää tietorakenteiden toteutukset, algoritmit ja ohjelman muu toiminnallisuus erillään toisistaan. Tämä helpottaa koodin ylläpitoa, testaamista ja jatkokehitystä.

Geometriset tietorakenteet, kuten pisteet, särmät ja kolmiot, on toteutettu omissa moduuleissaan. Näiden moduulien tehtävänä on tarjota yksinkertaiset operaatiot tietorakenteiden käsittelyyn. Esimerkiksi `point`-moduuli vastaa pisteiden käsittelystä ja `triangle`-moduuli kolmioihin liittyvistä geometrisista operaatioista.

Algoritmit on erotettu omiin moduuleihinsa. `triangulation`-moduuli toteuttaa Bowyer–Watson-algoritmin, jolla muodostetaan Delaunay-triangulaatio. `union_find`-moduuli tarjoaa Union-Find-tietorakenteen, jota `kruskal`-moduuli hyödyntää minimivirittävän puun muodostamisessa.

Muut moduulit vastaavat labyrintin muodostamisen ja tulostamisen eri vaiheista. `rooms`-moduuli huolehtii huoneiden sijoittelusta, `graph`-moduuli graafin käsittelystä, `generator`-moduuli yhdistää labyrintin muodostamiseen tarvittavat vaiheet ja `render`-moduuli vastaa valmiin labyrintin ASCII-visualisoinnista.

Modulaarisen rakenteen ansiosta yksittäisiä osia voidaan kehittää ja testata erillään muusta ohjelmasta. Esimerkiksi geometrisia operaatioita ja algoritmeja voidaan testata yksikkötesteillä ilman, että koko labyrinttigeneraattoria tarvitsee suorittaa.

Testejä on kirjoitettu samaan aikaan kuin niiden testaamia toiminnallisuuksia joten projektin testi kattavuus on ollut koko projektin ajan hyvä. Olen pyrkinyt nimeämään funktiot kuvaavasti että koodi olisi mahdollisimman itseään dokumentoivaa.

|-- labyrinthGenerator
|   |-- Makefile
|   |-- src
|   |   |-- edge.c
|   |   |-- edge.h
|   |   |-- edge_list.c
|   |   |-- edge_list.h
|   |   |-- generator.c
|   |   |-- generator.h
|   |   |-- graph.c
|   |   |-- graph.h
|   |   |-- kruskal.c
|   |   |-- kruskal.h
|   |   |-- main.c
|   |   |-- point.c
|   |   |-- point.h
|   |   |-- render.c
|   |   |-- render.h
|   |   |-- rooms.c
|   |   |-- rooms.h
|   |   |-- triangle.c
|   |   |-- triangle.h
|   |   |-- triangulation.c
|   |   |-- triangulation.h
|   |   |-- union_find.c
|   |   `-- union_find.h
|   |-- tests
|   |   |-- test_edge.c
|   |   |-- test_edge_list.c
|   |   |-- test_generator.c
|   |   |-- test_graph.c
|   |   |-- test_integration.c
|   |   |-- test_kruskal.c
|   |   |-- test_main.c
|   |   |-- test_point.c
|   |   |-- test_render.c
|   |   |-- test_rooms.c
|   |   |-- test_triangle.c
|   |   |-- test_triangulation.c
|   |   `-- test_union_find.c

## Aika- ja tilavaatimukset

Aika- ja tilavaatimuksia ei ole vielä tutkittu kattavasti. Algoritmien teoreettisia aikavaativuuksia on käsitelty projektin määrittelydokumentissa. Toteutuneen ohjelman suorituskykyä ja muistinkäyttöä on tarkoitus arvioida tarkemmin projektin viimeistelyvaiheessa.

## Puutteet ja parannusehdotukset

Projektin puutteita ja mahdollisia parannuskohteita arvioidaan tarkemmin toteutuksen ja testauksen edetessä. Erityisesti huomiota kiinnitetään algoritmien suorituskykyyn, muistinhallintaan, virhetilanteiden käsittelyyn sekä koodin ylläpidettävyyteen.

## LLM:n käyttö

Olen käyttänyt suuria kielimalleja (LLM) apuna projektin eri vaiheissa.

Projektin alkuvaiheessa hyödynsin ChatGPT:tä Delaunay-triangulaation ja Bowyer–Watson-algoritmin toiminnan opiskelussa ja ymmärtämisessä. Käytin sitä myös projektin rakenteen ja moduulijaon suunnittelun tukena.

Testauksen suunnittelussa hyödynsin GitHub Copilotia mahdollisten testaamatta jääneiden tapausten tunnistamiseen. Sen avulla sain ideoita lisätesteihin, joilla pystyin parantamaan testikattavuutta.

LLM-työkalut ovat toimineet ensisijaisesti opiskelun, suunnittelun ja testauksen tukena. Olen itse arvioinut ehdotuksia ja vastannut niiden soveltamisesta projektin toteutukseen.

## Linkit

- **Xorshift32-satunnaislukugeneraattori:** [How does xorshift32 work?](https://stackoverflow.com/questions/53886131/how-does-xorshift32-works)