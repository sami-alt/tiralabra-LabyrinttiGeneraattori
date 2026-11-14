## Testausdokumentti

Projektin yksikkötestaukseen käytetään Unity-testikirjastoa ja testikattavuuden seurantaan GCC:n gcov-työkalua.

Projektin staattiseen analyysiin käytetään Cppcheck- ja Clang-Tidy-työkaluja. Analyysit suoritetaan projektin omien `src/`- ja `tests/`-hakemistojen tiedostoille, eikä Unity-testikirjaston lähdekoodia analysoida.

Staattiset analyysit voidaan suorittaa `labyrinthGenerator`-hakemistossa komennolla:

```bash
make static-analysis
```

Työkalut voidaan suorittaa myös erikseen komennoilla `make cppcheck` ja `make clang-tidy`. Molempien työkalujen tulee olla asennettuina ennen komentojen suorittamista.

`static-analysis`-kohde suorittaa molemmat analyysit ja palauttaa onnistuneen
lopputuloksen, kun komento ajetaan `labyrinthGenerator`-hakemistossa.

Bowyer–Watson-algoritmi, joka muodostaa ohjelman geometrisen ytimen, on kattavasti yksikkötestattu. Myös Union-Find-tietorakenne, Kruskalin algoritmi ja graafin muodostamiseen liittyvät toiminnot on testattu yksikkötesteillä. Testeissä tarkastellaan yksittäisten toimintojen oikeellisuuden lisäksi algoritmien tarvitsemien tietorakenteiden toimintaa.

Varsinaisia integraatiotestejä ei ole vielä toteutettu, sillä kaikkia ohjelmiston osia ei ole vielä integroitu toisiinsa. Integraatiotestauksen tarkoituksena on myöhemmin varmistaa, että ohjelmiston eri osat toimivat oikein yhdessä.

Kolmannen viikkoraportin aikaan rivien testikattavuus on 90,79 %. Testaamatta jäänyt koodi liittyy pääasiassa poikkeustilanteiden käsittelyyn, kuten muistinvarauksen epäonnistumiseen. Näiden tilanteiden testaaminen vaatii erillisiä testausjärjestelyjä, eikä niitä ole vielä toteutettu.