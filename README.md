binary-tree---ip-adresses
Samoreferencirajuća struktura podataka, koja se kreira i održava u skladu sa disciplinom binarnog stabla: #define IPLENGTH 4 typedef struct tnode * Treeptr; typedef struct tnode { unsigned char ipadresa[IPLENGTH]; int brojpaketa; Treeptr lijevo; Treeptr desno; } Treenode; Značenje / namjena polja u navedenom slogu je sljedeća: • ipadresa: niz od 4 bajta (byte), koji suže za smještaj 4 elementa IPv4 adrese • brojpaketa: cijeli broj koji sadrži podatak koliko je mrežnih paketa stiglo sa date adrese • lijevo: pointer na "lijevo" podstablo, u kom su elementi ovog tipa, sa "manjom" IP adresom • desno: pointer na "desno" podstablo, u kom su elementi ovog tipa, sa "većom“ IP adresom

2.1 Funkcija poređenje koja služi za poređenje dvije IP adrese: int poredjenjeip(unsigned char ip1[], unsigned char ip2[]) Funkcionalni zahtjevi: • Funkcija koristi dva parametra, koji su po svom tipu kompatibilni sa prvim navedeninm elementom gore opisane strukture, ipadresa. • Rezultat funkcije: o -1, ako je prvonavedena IP adresa (t.j. ona smijenjena kroz prvi parametar funkcije) "manja" od drugonavedene (t.j. one koja je smijenjena kroz drugi parametar funkcije), o 0, ako su adrese jednake, o 1, ako je prvonavedena adresa "veća" od drugonavedene. • Da li je IP adresa "manja" ili "veća" određuje se tako da se: o porede bajti koji čine IP adresu, prvi bajt iz jedne sa prvim bajtom iz druge adrese, pa potom drugi iz prve adrese i drugi iz druge i tako dalje do posljednjeg, četvrtog; o čim se pronađe par bajta (byte) koji se razlikuju, njihov odnos određuje koja adresa je "veća", te nema potrebe da se dalje provjeravaju sljedeći parovi.

2.2 Funkcija "Konstruktor" zadanog binarnog stabla: Treeptr kreiraj(Treeptr ptr, unsigned char ipadr[]) Funkcija će za zadani "korijen" gore specificirane strukture podataka binarnog drveta omogućiti upis podataka o IP adresama u navedenu strukturu, tako što će za zadani pointer i zadanu IP adresu: • kreirati novi "čvor" (slog koji sadrži zadanu IP adresu, "null" pointere na oba podstabla i vrijednost 1 u polje "broj paketa“), ukoliko je ulazni pointer NULL, • inkrementirati "broj paketa", u odgovarajućem čvoru, ukoliko je ta adresa već upisana u zadano stablo, • ažurirati podatke u "lijevom" podstablu, ukoliko je zadana adresa "manja" od adrese u čvoru na koji pokazuje ulazni pointer, pri čemu se za poređenje adresa koristi funkcija specificirana u 2.1, • analogno, ažurirati podatke u "desnom" podstablu, ukoliko je zadana adresa "veća" od adrese čvora na koji pokazuje ulazni pointer, • funkcija kao svoj rezultat vraća: o isti pointer koji joj je smijenjen kao ulazni parametar, ukoliko taj ulazni parametar nije bio NULL pointer, o pointer na novokreirani "čvor", ukoliko je ulazni parametar bio NULL pointer.

2.3 Funkcija za parsiranje IPv4 adrese: int parseip(char ipstring[], unsigned char ipadr[]) Funkcija će: • kao parametar prihvatati string (niz karaktera) za koji "podrazumijeva" da predstavlja tačno jednu IPv4 adresu u svom uobičajenom formatu, nnn.nnn.nnn.nnn, • provjeriti da li je struktura adrese i navedene vrijednosti svakog bajta (byte) korektni i ukoliko nisu treba na standardni izlaz ispisati poruku sa objašnjenjem šta je pogrešno i vratiti rezultat 0, • ukoliko je provjera prošla uspješno (string predstavlja korektnu IP adresu), kroz drugi parametar, koji je po tipu kompatibilan sa poljem ipadresa u gore zadanoj strukturi podataka, vratiti niz od 4 bajta (byte), koji sadrže 4 "broja" iz zadane IP adrese iz parsiranog ulaznog stringa i u tom slučaju funkcija kao svoj rezultat vrati 1; 2.4 C/C++ program za upis i ispis podataka o IP adresama i paketima: Program će sadržavati specifikacije svih gore navedenih funkcija (2.1, 2.2, 2,3) i imati sljedeću funkcionalnost: • učitavati IP adrese sa standardnog ulaza, red po red, tako da se u svakom upisanom redu nalazi tačno jedna IP adresa, • korištenjem funkcije pod 2.3 pretvarati taj string u niz od 4 bajta (byte), • ukoliko je konverzija uspjela, korištenjem funkcije kreirane pod 2.2, upisivati tu adresu u strukturu stabla, čiji korijen je privatna pointerska varijabla u main sekciji programa,

4/6

• ovaj proces učitavanja prekinuti kada se standardnog ulaza stigne EOF, • potom: o ispisati sve dostavljene IP adrese, od "najmanje" do "najveće", tako da se u jednom redu ispisuje jedna IP adresa i njoj propadajući broj paketa,