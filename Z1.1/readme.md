# README: Zadanie Z1.1 Komunikacja UDP

## Przegląd
Projekt obejmuje stworzenie i przetestowanie dwóch programów – klienta i serwera – używających protokołu UDP. Zadanie zostało zrealizowane zarówno w C, jak i Pythonie, co skutkuje czterema programami:
- **Klient UDP w C**
- **Serwer UDP w C**
- **Klient UDP w Pythonie**
- **Serwer UDP w Pythonie**

Głównym celem jest umożliwienie komunikacji między tymi programami oraz sprawdzenie funkcjonalności między-platformowej, np. uruchomienie klienta w C z serwerem w Pythonie i odwrotnie.

## Katalog Wyników Testów
Wszystkie wyniki testów są zapisywane w katalogu `z32_results`.

### Struktura Katalogu `z32_results`
- **`server_c.txt` / `client_c.txt`**: logi z testu, gdy serwer i klient są napisane w C.
- **`server_py.txt` / `client_py.txt`**: logi z testu, gdy serwer i klient są napisane w Pythonie.
- **`cross_server_c.txt` / `cross_client_py.txt`**: logi z testu, gdy serwer jest napisany w C, a klient w Pythonie.
- **`cross_server_py.txt` / `cross_client_c.txt`**: logi z testu, gdy serwer jest napisany w Pythonie, a klient w C.

## Tworzenie Katalogu i Zapisywanie Wyników
Podczas uruchamiania skryptu `run.sh`:
1. Usuwany jest istniejący katalog `z32_results` wraz z jego zawartością.
2. Tworzony jest nowy, pusty katalog `z32_results`.
3. Logi z działania kontenerów są zapisywane do odpowiednich plików w tym katalogu.



## Uruchamianie Skryptu
Aby uruchomić cały zestaw testów i zapisać wyniki w katalogu `z32_results`, wykonaj:
```bash
./run.sh
