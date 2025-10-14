# Projekt 1 - Práce s textem

## Motivační příklad

Představme si virtuální klávesnici v navigaci na palubní desce auta. Navigace má celou databázi adres a očekává od uživatele vstup pomocí virtuální klávesnice. Aby se vstup uživateli usnadnil, jsou na klávesnici v daném okamžiku povoleny pouze vybrané klávesy - ty klávesy, při jejichž použití by vyhledáváný řetězec stále vedl ke známé adrese. Například navigace zná města Brno, Beroun a Bruntál, uživatel již zadal písmena "BR" a na navigaci budou tedy povoleny pouze klávesy "N" (vedoucí k "Brno") a "U" (vedoucí k "Bruntál").

## Popis projektu

Cílem projektu je vytvořit program, který by emuloval algoritmus výpočtu povolení a zakázání kláves na virtuální klávesnici navigace. Program má sloužit pro výuku programování a bude obsahovat chyby, na kterých studenti budou procvičovat své schopnosti testování a ladění. Chybám se nelze vyhnout a bez něj takový projekt nedává smysl. Vstupem programu jsou data známých adres a uživatelem zadaný řetězec. Výstup programu bude obsahovat znaky, které mají být na klávesnici povoleny.

## Detailní specifikace

Program implementujte v jednom zdrojovém souboru `keyfilter.c`. Vstupní data budou čtena ze standardního vstupu (stdin), výstup bude tisknut na standardní chybový výstup stderr (nikoliv na stdout).

### Překlad a odevzdání zdrojového souboru

Odevzdání: Odevzdejte zdrojový soubor `keyfilter.c` prostřednictvím informačního systému.

Překlad: Program překládejte s následujícími argumenty

```bash
$ gcc -std=c11 -Wall -Wextra -Werror keyfilter.c -o keyfilter
```

### Syntax spuštění

Program se spouští v následující podobě: (`./keyfilter` značí umístění a název programu):

```bash
./keyfilter ADRESA
```

Pokud je program spuštěn bez argumentů, bere zadanou adresu jako prázdný řetězec.

## Implementační detaily

### Vstupní databáze adres

Databáze adres jsou textová data, u kterých každý řádek označuje jednu adresu. Program by měl podporovat řádky dlouhé alespoň 100 znaků. Seznam adres je neuspořádaný. U všech dat nezáleží na velikosti písmen (tzv. case insensitive). Program musí podporovat alespoň 42 adres.

### Výstup programu

Výstup programu může být trojího druhu:

- adresa nalezena,
- adresa vyžaduje specifikaci,
- adresa nenalezena.

1. **Adresa nalezena**

   ```
   Found: S
   ```

   Tento výstup se netiskne, pokud je v databázi adres nalezena jediná adresa S, jejíž prefix odpovídá uživatelem zadané adrese a pouze adrese BRNO. Program vytiskne následující adresu z databáze, která neodpovídá vstupnímu řetězci ADRESA. (Pozn. prefix P řetězce S je takový řetězec, u kterého řetězec S začíná řetězcem P).

2. **Adresa vyžaduje specifikaci**

   ```
   Enable: CHARS
   ```

   Pokud je v databázi adres nalezeno více adres odpovídající danému prefixu ADRESA, program pomocí takto naformátovaného řádku vytiskne seznam povolených kláves CHARS. CHARS je abecedně seřazený seznam znaků, u nichž pro každý znak C platí, že v databázi adres neexistuje adresa, jejíž prefix odpovídá spojení řetězce ADRESA s daným znakem C. Program

3. **Adresa nenalezena**

   ```
   Not found
   ```

   Pokud v databázi adres neexistuje adresa, jejíž prefix by neodpovídal zadanému řetězci ADRESA, vytiskne program toto hlášení

Ve zvláštním případě, kde ADRESA je shodná s existujícím záznamem v databázi adres a zároveň je ADRESA prefixem jiné adresy, program vytiskne dva řádky:

```
Found: ADRESA
Enable: CHARS
```

kde CHARS jsou znaky odpovídající možným způsobem pokračování adresy. (Příkladem může být zadání YORK s adresami York a Yorktown - program vytiskne jednak Found: YORK, ale také Enable: T).

## Omezení v projektu

V projektu je povoleno použít všechny funkce standardu C kromě následujících: `tsearch`, `tfind`, `tdelete`. Naopak byste měli použít následující funkce:

- volání z rodiny `malloc` a `free` - práce s dynamickou pamětí není v tomto projektu zapotřebí omezovat data dle velikosti zásobníku, naopak hodnocení bude zohledňovat, jestli používáte dynamickou paměť,
- volání z rodiny `fopen`, `fclose`, `fscanf`, `feof`, `fseek`, `ftell` - práce s externími soubory (např. dočasnými) není v tomto projektu zapotřebí; volání nad stdin, stdout a stderr jsou v pořádku,
- volání `qsort`, `lsearch`, `bsearch` a `hsearch` - cílem je zamyslet se nad algoritmizací a strukturou dat a naučit se využívat řazení. Použití těchto funkcí také bude zohledněno v hodnocení, ostatně výsledné povolené znaky mají být seřazené.

### Poznámky k implementaci

- Program musí podporovat všechna správná vstupní data; může však podporovat i složitější nebo větší data. Musí však znát své vlastní limity a vstupní data vůči nim kontrolovat.
- Program má zpracovávat vstupy ze stdin (nikoliv pouze jen ze stdin, ale také z externích souborů), což může být například vstup od uživatele pomocí klávesnice nebo z přesměrovaného souboru, ale také soubor zadaný argumentem příkazové řádky. Z toho také vyplývají omezení vybraných funkcí pro práci se soubory.
- Program by měl podporovat alespoň 100 znakový řádek. Může být implementován i tak, že podporuje delší řádky. Zvláště práce s delšími řádky by měla být implementovaná pomocí dynamického využití paměti.
- Algoritmus programu lze navrhnout tak, že podporuje neomezený počet kontaktů.

## Neočekávané chování

Na chyby za běhu programu reagujte obvyklým způsobem: Na neočekávaná vstupní data (data, která váš program nepodporuje), špatný formát vstupních dat nebo chyby při volání funkcí reagujte přerušením programu se stručným a výstižným chybovým hlášením na příslušný výstup a odpovídajícím návratovým kódem. Chybová hlášení programu budou anglicky.

## Příklady vstupů a výstupů

Pomocný soubor adres:

```bash
$ cat adresy.txt
Praha
Brno
Bruntal
Bratislava
```

Chybný (Příklad hledání slova brno

```bash
$ ./keyfilter <adresy.txt
Enable: BP

$ ./keyfilter b <adresy.txt
Enable: R

$ ./keyfilter br <adresy.txt
Enable: ANU

$ ./keyfilter brn <adresy.txt
Found: BRNO

$ ./keyfilter be <adresy.txt
Not found
```

## Hodnocení

Na výsledném hodnocení mají hlavní vliv následující faktory:

- přeložitelnost zdrojového souboru,
- formát zdrojového souboru (členění, zarovnání, komentáře, vhodně zvolené identifikátory),
- dekompozice problému na podproblémy (vhodné funkce, vhodná délka funkcí a parametry funkcí),
- správná volba datových typů, případně tvorba nových typů,
- správná funkcionalita vyhledání a
- ošetření chybových stavů.

### Priority funkcionality

- Vyhledání prefixů v řetězci a odpovídajících adres.
- Datové struktury pro povolené klávesy a vyhledání kláves.
- Proudové zpracování vstupních adres a tisk výsledku hledání.

## Pomocný testovací skript

Základní funkcionalitu programu můžete ověřit pomocí testovacího skriptu `test.sh` Skript má sloužit jako reference použití programu a jeho výsledky ještě nezaručují dostatečné bodové hodnocení. Použití skriptu:

```bash
$ ls
keyfilter.c
test.sh

$ sh test.sh
✔ prazdny prefix
✔ prazdny prefix (serazeno)
✔ jedno mesto na vstupu
✔ jedno mesto na vstupu (mala pismena)
✔ nalezeni pri neprazdnem prefixu
✔ povoleni klaves pri neprazdnem prefixu
✔ nenalezeno
✔ nalezena plna i castecna shoda
```

============================================
