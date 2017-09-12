Autor Krzyszczuk Michał
kontakt: e-mail: krzyszczuk.michal@gmail.com telefon 570 295 331

Slit_Guide:
  Program zaimplementowany na potrzebę projektu "Solaris", pod kierownictwem
  Profesor Macieja Konackiego Centrum Astronomicznego im. Mikołaja Kopernika
  Polskiej Akademii Nauk, odział w Toruniu.

  Zakładana funkcjonalność programu:


  Zadaniem aplikacji jest detekcja środka obiektu niebieskiego(gwiazdy), na
  podstawie zdjęć ze spektrografu BACHES, który wraz z kamerą, układem
  mikrokontrolerów, silnikami oraz komputerem Raspberry Pi stanowi zamkniętą
  pętlę sprzężenia zwrotnego. Kamera przesyła aktualny obraz ze spektrografu
  w postaci serii zdjęć. Dzięki analizie obrazu za pomocą różnych metod
  geometrycznych, analitycznych lub doświadczalnych możliwe jest wyznaczenie
  środka gwiazdy. Dzięki tej operacji możliwa jest manipulacja położeniem lustra
  spektrografu, tak aby obserwował on dokładnie porządany obiekt. Po przetworzeniu
  informacji zawartych na zdjęciu, komputer RPi przesyła współrzędne środka gwiazdy
  przy pomocy USART to mikrokontrolera, ten z kolei optymalizuje położenie lustra
  przy pomocy układu silników, w celu zooptymalizowania obserwacjii.

  Obecny stan technologiczny:


  Zaimplementowany i przetestowany został moduł do detekcji środka gwiazdy przy
  pomocy Transforamcji Hougha, środka ważonego macierzy obrazu, środka geometrycznego
  plamki światła. Przetestowany został moduł komunikacji RPi z mikrokontrolera, który
  reaguje na odbiegające od normy długości błedu pomiaru. Test serwera nginx do
  obrazowania aktualnych wyników pomiaru.


  Planowane zmiany:


  Rozwinięcie strony WWW obrazującej aktualne wyniki pomiarów
  Udoskonalenie komunikacjia RPI <> AVR w celu przesyłu współrzędnych środka gwiazdy
