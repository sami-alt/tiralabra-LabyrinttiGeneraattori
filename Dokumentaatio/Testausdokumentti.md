## Testausdokumentti

Testit toteutettu Unity kirjastolla sekä kattavuutta seurataan GCC gcov -työkalulla.

Projektin staattiseen analyysiin käytetään cppcheck- ja clang-tidy-työkaluja.
Analyysit suoritetaan projektin omille `src/`- ja `tests/`-hakemistojen
tiedostoille, eikä Unity-kirjaston lähdekoodia analysoida.

Analyysit voidaan suorittaa `labyrinthGenerator`-hakemistossa komennolla:

```bash
make static-analysis
```

Työkalut voidaan suorittaa myös erikseen komennoilla `make cppcheck` ja
`make clang-tidy`. Molempien työkalujen pitää olla asennettuina ennen
komentojen suorittamista.

Bowyer-Watson algorimint joka muodostaa ohjelman ydin alueen on kattavasti yksikkö testattu.
Union-find, kruskal ja graafin muodostu ovat myös yksikkö testattu ja niiden alustavata integraatio kantautuu yhden rakenteen testeistä seuraavan, sillä rakenteita ja 
niiden metodeja käytetään niistä riippuvissa algoritmeissa ja rakenteissa.

Varsinaisia integraation testejä ei ole vielä toteuttu, sillä kaikkia ohjelmiston osia ei ole vielä liitetty.

Testikattavuus on kolmannen viikkoraportin aikaan 90.79% ja testaamaton n 10%  on ohjelmiston ydintoiminnan kannalta epäolennaisia, kuten muistin varauksen epäonnistumisen käsittely.