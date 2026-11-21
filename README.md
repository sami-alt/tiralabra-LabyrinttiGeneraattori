# LabyrinttiGeneraattori

Satunnaisesti generoitava labyrintti, joka muodostetaan graafialgoritmeilla:
Delaunay-triangulaatio (Bowyer–Watson) → virittävä minimipuu (Kruskal) →
ASCII-renderöinti.

## Vaatimukset

- C-kääntäjä (gcc tai clang), C11-standardin tuki
- `make`
- Unity-testikirjasto hakemistossa `../Unity` (testejä varten)

## Kääntäminen

```bash
cd labyrinthGenerator
make            # kääntää ohjelman ja testit
make labyrinth  # kääntää vain ohjelman
make test       # kääntää ja ajaa testit
make clean      # poistaa käännöstuotokset

```
## Ohjelman ajaminen

```bash
./labyrinth [huoneita] [leveys] [korkeus] [vähimmäisetäisyys] [siemen]
```