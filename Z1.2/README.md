# Z1.2 Prosty Protokół Transmisji Danych z Symulacją Utraty Pakietów

## Opis projektu

Projekt implementuje uproszczony protokół niezawodnej transmisji danych oparty na **Bit Alternating Protocol (BAP)**. Komunikacja odbywa się za pomocą protokołu **UDP** z mechanizmami wykrywania brakujących pakietów oraz ich retransmisji. Projekt wykorzystuje Docker do uruchomienia klienta i serwera w środowisku z symulacją warunków sieciowych (opóźnienia, utrata pakietów).

## Struktura projektu

- **`pyserver1_2/`**  
  Katalog zawierający kod serwera oraz plik `Dockerfile` do budowy obrazu serwera.

- **`pyclient1_2/`**  
  Katalog zawierający kod klienta oraz plik `Dockerfile` do budowy obrazu klienta.

- **`docker-compose.yml`**  
  Plik konfiguracji Docker Compose definiujący serwisy klienta, serwera oraz ich wspólną sieć.

- **`run.sh`**  
  Skrypt do uruchamiania projektu, konfiguracji symulacji warunków sieciowych oraz zapisywania wyników.

## Jak uruchomić?

1. Zbuduj obrazy serwera i klienta oraz uruchom kontenery za pomocą Docker Compose:
   ```bash
   ./run.sh
2. Wyniki działania programu zostaną zapisane w pliku result1_2.txt
   
