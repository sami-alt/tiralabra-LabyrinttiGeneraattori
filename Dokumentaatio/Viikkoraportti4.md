## Viikko 4

Tällä viikolla keskityin labyrinttigeneraattorin varsinaisen toiminnallisuuden toteuttamiseen sekä aiemmin kehittämieni algoritmien integrointiin yhtenäiseksi ohjelmaksi.

Toteutin huoneiden eli graafin solmujen satunnaisen sijoittelun. Huoneet sijoitetaan käyttäjän määrittelemälle alueelle siten, että niiden välille jää vähintään määritelty etäisyys. Satunnaislukugeneraattori hyödyntää käyttäjän antamaa siemenlukua, minkä ansiosta samalla siemenluvulla voidaan tuottaa toistettavia tuloksia.

Toteutin myös ASCII-merkkeihin perustuvan visualisointitoiminnallisuuden. Sen avulla muodostettu labyrintti voidaan tulostaa tekstimuodossa. Visualisointi piirtää huoneet ja yhdistää ne käytävillä minimivirittävän puun määrittelemien yhteyksien mukaisesti.

Yhdistin aiemmin toteutetut algoritmit ja uudet toiminnallisuudet generaattoriksi, joka suorittaa labyrintin muodostamisen yhtenäisenä kokonaisuutena. Ohjelma muodostaa huoneista Delaunay-triangulaation, rakentaa sen perusteella painotetun graafin ja muodostaa Kruskalin algoritmilla minimivirittävän puun. Lopuksi tulos visualisoidaan ASCII-muodossa.

Aloitin myös integraatiotestauksen suunnittelun ja toteutuksen. Testien tarkoituksena on varmistaa, että ohjelmiston eri osat toimivat oikein yhdessä ja että muodostettu labyrintti täyttää sille asetetut vaatimukset.

## Tuntikirjaus

* Huoneiden satunnaisen sijoittelun toteutus ja testaus: 5 h
* Algoritmien integrointi yhtenäiseksi labyrinttigeneraattoriksi sekä ASCII-visualisoinnin toteutus: 6 h
* Integraatiotestien suunnittelu ja alustavien testien toteutus: 4 h

**Yhteensä: 15 h**