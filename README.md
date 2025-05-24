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

---

# Aplikacja serwera chatu

## Cel projektu
Celem projektu było stworzenie serwera czatu oraz klienta czatu działających w języku C++, umożliwiających komunikację między wieloma użytkownikami. Aplikacja zapewnia:
- Obsługę wielu klientów jednocześnie (wielowątkowość).
- Przechowywanie historii czatu i jej wyświetlanie nowym użytkownikom.
- Identyfikację użytkowników za pomocą nazwy użytkownika.

## Wykorzystane technologie
Aplikacja została napisana języku c++, a do komunikacji sieciowej wykorzystano gniazda TCP/IP (biblioteka WinSock2 dla Windows).  
Wykorzystane technologie i mechanizmy:
- Biblioteka WinSock2 – obsługa gniazd sieciowych.
- Wielowątkowość (```std::thread```) – obsługa wielu klientów jednocześnie.
- Synchronizacja (```std::mutex```) – zapewnienie bezpiecznego dostępu do zasobów.

## Opis działania aplikacji

### Serwer czatu
1. Oczekuje na połączenia klientów.
2. Po nawiązaniu połączenia użytkownik podaje nazwę użytkownika.
3. Serwer wysyła historię czatu nowemu użytkownikowi.
4. Klient może wysyłać wiadomości – użytkownik wysyła wiadomość na serwer, a serwer przekazuje ją do wszystkich użytkowników.
5. Każda wiadomość zawiera datę i godzinę oraz nazwę nadawcy.
6. Gdy użytkownik wpisze ```/exit```, zostaje rozłączony.

### Klient czatu
1. Łączy się z serwerem i podaje nazwę użytkownika.
2. Odbiera historię czatu od serwera.
3. Może wysyłać wiadomości do innych użytkowników.
5. Wpisanie ```/exit``` powoduje zamknięcie połączenia.

## Uruchomienie aplikacji
### Serwer czatu:  
1. Pobierz plik ```server.exe```.  
2. Uruchom go – serwer oczekuje na klientów.  

### Klient czatu:  
1. Pobierz plik ```client.exe```.  
2. Uruchom i podaj nazwę użytkownika.  
3. Rozpocznij rozmowę, wpisując wiadomości.  
4. Aby zakończyć, wpisz ```/exit```.  

## Możliwe ulepszenia:  
- Zapisywanie historii czatu do pliku – aby przetrwała restart serwera.  
- Autoryzacja użytkowników – logowanie i hasła.  
- Wsparcie dla Linuxa – dodanie obsługi ```sys/socket.h```.  
