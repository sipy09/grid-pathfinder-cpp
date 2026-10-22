# Ghid rapid: Grid Pathfinder pe Mac + GitHub

## 1. Descarcă și extrage proiectul

Salvează `grid-pathfinder-cpp.zip` în `~/Downloads`, apoi rulează:

```bash
mkdir -p ~/Projects
cd ~/Projects
unzip ~/Downloads/grid-pathfinder-cpp.zip
cd grid-pathfinder-cpp
```

## 2. Compilează, testează, rulează

```bash
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
./build/grid_pathfinder
```

Rezultatul de așteptat: `100% tests passed` și un traseu marcat cu `*` pe harta implicită (19 mutări).

Testează și harta scurtă:

```bash
./build/grid_pathfinder maps/simple.txt
```

Aceasta este o aplicație în terminal: nu deschide o fereastră grafică.

## 3. Publică doar după ce verifici proiectul

Asigură-te că ești conectat în GitHub CLI (`gh auth status`).

```bash
git init -b main
git add .
git commit -m "Add C++ BFS grid pathfinder and tests"
gh repo create sipy09/grid-pathfinder-cpp --public --source=. --remote=origin --push
```

Dacă repository-ul există deja online, `gh repo create` nu va funcționa; în acest caz setează `origin` și folosește `git push -u origin main`.

## 4. Pentru interviu

- BFS (Breadth-First Search) explorează celulele cu ajutorul unei cozi (`std::queue`).
- Pentru o hartă cu cost egal pe fiecare pas, BFS găsește un drum cu număr minim de mutări.
- `parent` memorează de unde am ajuns în fiecare celulă, iar traseul este reconstruit de la `G` la `S`.
- Complexitatea este O(R × C) timp și memorie, pentru R rânduri și C coloane.
- Limitări: fără mutări diagonale, fără ponderi, fără UI grafic.

**Important:** citește codul, testează-l pe Mac și asigură-te că poți explica funcțiile și contribuția ta. Codul inițial a fost pregătit cu ajutorul AI.
