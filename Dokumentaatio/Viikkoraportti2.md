## Viikko 2

Tutustuin Bowyer–Watson-algoritmin toimintaan ja perehdyin Delaunay-triangulaation muodostumisen periaatteisiin. Tämän jälkeen aloin suunnitella algoritmin tarvitsemia tietorakenteita sekä koko ohjelman tiedosto- ja moduulirakennetta. Jaoin ohjelman toiminnallisuudet omiin moduuleihinsa niiden vastuualueiden perusteella. Geometrian käsittely on siis jaettu omiin moduuleihinsa.

Toteutin Bowyer–Watson-algoritmin, joka toimii ohjelman keskeisenä osana. Algoritmi muodostaa annetuista pisteistä Delaunay-triangulaation lisäämällä pisteitä vaiheittain ja päivittämällä muodostuvaa kolmioverkkoa. Testasin myös muodostetun triangulaation oikeellisuutta ja Delaunay-ehdon toteutumista erilaisilla pistejoukoilla.

Kirjoitin yksikkötestejä toteuttamilleni metodeille ja apufunktioille samanaikaisesti niiden kehittämisen kanssa. Näin pystyin testaamaan yksittäisten toimintojen oikeellisuutta jo toteutusvaiheessa. Testejä kirjoitettiin erillaisille pistejoukoille, kuten kollineaarisille pisteille ja ympyrän kehälle päätyville pisteille, joten testit käsittelevät myös poikkeus tapauksia.

Etsin C-kielelle sopivaa testikirjastoa, joka soveltuisi projektin tarpeisiin. Valitsin Unity-testikirjaston, koska se on kevyt ja tarjoaa tarvittavat työkalut kattavien yksikkötestien toteuttamiseen.

## Tuntikirjaus

* Bowyer–Watson-algoritmiin tutustuminen ja Delaunay-triangulaation toimintaperiaatteen ymmärtäminen: 4 h
* Bowyer–Watson-algoritmin sekä sen apufunktioiden ja metodien toteuttaminen: 10 h
* Yksikkötestien kirjoittaminen: 6 h

**Yhteensä: noin 20 h**
