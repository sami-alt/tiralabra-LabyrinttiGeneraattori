## Viikko 3

Suunnittelin graafin, minimivirittävän puun (Minimum Spanning Tree, MST) ja Union-Find-tietorakenteen toteutukset sekä näiden tarvitsemat tietorakenteet. Näiden tarkoituksena on muodostaa pohja labyrintin käytävärakenteelle.

Toteutin Kruskalin algoritmin, jota käytetään minimivirittävän puun muodostamiseen. Algoritmi hyödyntää Union-Find-tietorakennetta selvittääkseen, kuuluvatko kaksi solmua jo samaan yhtenäiseen komponenttiin. Näin algoritmi pystyy valitsemaan graafin reunat siten, ettei muodostuvaan puuhun synny syklejä. Labyrintin muodostuksessa graafin solmut edustavat huoneita ja reunat niiden välisiä mahdollisia käytäviä. Minimivirittävä puu toimii labyrintin käytävärakenteen pohjana.

Koodin ylläpidettävyyden ja laadun tarkasteluun valitsin työkaluiksi Cppcheckin ja Clang-Tidyn. Näiden avulla voidaan tarkastella koodin mahdollisia virheitä, ongelmakohtia ja parannuskohteita.

Testikattavuuden seuraamiseen otin käyttöön GCC:n gcov-työkalun, jonka avulla voidaan tarkastella, kuinka suuri osa ohjelman koodista suoritetaan testien aikana. Tämänhetkinen testikattavuus on noin 90 %. Suurin osa kattavuuden ulkopuolelle jäävästä koodista liittyy poikkeustilanteiden käsittelyyn, kuten muistinvarauksen epäonnistumiseen. Näiden tilanteiden testaaminen vaatii erillistä huomiota.

## Tuntikirjaus

* Union-Find-tietorakenteen toteutus: 3 h
* Kruskalin algoritmin toteutus: 5 h
* Union-Findin, Kruskalin ja geometristen elementtien alustava integrointi: 2 h
* Yksikkötestien kirjoittaminen: 5 h

**Yhteensä: 15 h**