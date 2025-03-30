# Problem biesiadujących filozofów rozwiązany w c++
## Opis problemu
Problem biesiadujących filozofów to podstawowy problem w informatyce, idealnie obrazuje on trudności z podziałem i walką o zasoby przez różne wątki.
Problem jest opisany poprzez biesiadowanie n filozofów przy okrągłym stole (każdy z nich może jeść, rozmyslać lub czekać na wolny widelec).
Jeżeli filozof chciałby zjeść to potrzebuje dwóch widelców (jeden z lewej strony talerza, a drugi z prawej), widelców na stole jest tyle ile biesiadująceych
filozofów, więc dwóch filozofów (którzy siedzą obok siebie) nie będą w stanie jednocześnie jeść, bo współdzielą jeden widelec. Problem ten idealnie
odzwierciedla walkę wątków o zasoby w systemach operacyjnych, celem tego problemu jest znalezienie rozwiązania aby odpowiednio przydzielać wątki do zasobów
oraz żeby każdy miał możliwość skorzystania z zasobu podczas czasu swojego wykonywania.

## Zastosowany sposó rozwiązania
W programie zastosowano blokowanie mutexów oraz condition_variable. Filozof, który chce zjeść, najpierw sprawdzi dostępność widelców i jeżeli
są dostępne to zablokuje mutex i będzie czekał przez losową ilość czasu (symulacja jakiegoś zasobożernego procesu), następnie odblokowuje mutex i
powiadamia o dostępności poprzez condition_variable. Proces się zapętla.

## Analogie
**Filof** - reprezentuje wątek,
**Widelec** - reprezentuje zasób,

## Instalacja i uruchomienie programu
### Instalacja
W sekcji *Releases* na GitHub można znaleźć skompilowny program .exe dla windows 11 oraz kod źródłowy.
#### Uruchomienie pliku .exe
Plik .exe jest uruchamiany z poziomu konsoli z odpowiednimi argumentami

```./dining_phiolosophers.exe <n> --no-terminal-out```

- *n* - ilość biesiadujących filozofów. Nie mniej niż 3,
- *--no-terminal-out* - wyłącza komunikaty o stanie filozofów w konsoli
#### Kompilacja z kodu źródłowego
Program można skompilowac za pomocą CMake
