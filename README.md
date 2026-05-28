# Sistem de Avertizare a Distanței cu ATmega328p

Acesta este un proiect de tip "senzor de parcare" bazat pe un microcontroler ATmega328p (Arduino Nano). Sistemul folosește un senzor ultrasonic pentru a măsura distanța până la cel mai apropiat obiect și oferă feedback vizual și auditiv utilizatorului în funcție de proximitatea acestuia.

Proiectul este dezvoltat **fără a folosi bibliotecile standard Arduino (fără framework-ul Arduino)**, interacționând direct cu registrele microcontrolerului printr-un strat de abstractizare hardware (HAL) propriu. Acest lucru oferă control maxim și eficiență.

## Funcționalitate

Sistemul măsoară constant distanța și reacționează astfel:
- **Peste 15 cm:** Zona este liberă. LED-ul verde este aprins, buzzerul este oprit, iar pe LCD este afișat mesajul `"Liber"`.
- **Între 10 cm și 15 cm:** Zonă de atenție. LED-ul roșu se aprinde și buzzerul emite un sunet cu o frecvență rară (bip rar). Pe LCD este afișat `"ATENTIE!"`.
- **Între 5 cm și 10 cm:** Zonă de pericol. LED-ul roșu se aprinde și buzzerul emite un sunet cu o frecvență rapidă (bip rapid). Pe LCD este afișat `"PERICOL!!!"`.
- **Sub 5 cm:** Oprire iminentă. LED-ul roșu este aprins, buzzerul emite un sunet continuu, iar pe LCD este afișat `"STOP!!!!"`.

Distanța exactă măsurată de senzor este afișată în permanență pe prima linie a ecranului LCD (ex: `Dist: 12 cm`).

## Componente Hardware

Pentru a replica acest proiect, aveți nevoie de următoarele componente:
- **1x** Placă de dezvoltare Arduino Nano (ATmega328p)
- **1x** Senzor Ultrasonic (ex: HC-SR04)
- **1x** Ecran LCD compatibil I2C (ex: 16x2)
- **1x** Buzzer activ/pasiv
- **1x** LED Roșu
- **1x** LED Verde
- **2x** Rezistențe (220Ω - 330Ω) pentru LED-uri
- Fire de conexiune (Jumper wires) și un Breadboard

### Conexiuni implicite pini
*Configurația pinilor poate fi modificată din fișierul `src/main.c` sau drivere.*
- **LED Roșu:** Pin D3
- **LED Verde:** Pin D4
- **Buzzer, Senzor Ultrasonic, LCD:** Conform fișierelor de configurare din `drivers/`

## Structura Proiectului

Proiectul este organizat modular, separând logica aplicației de driverele hardware:

```text
├── bsp/            # Definiții specifice plăcii (nano.h)
├── drivers/        # Strat de Abstractizare Hardware (HAL)
│   ├── buzzer/     # Controlul buzzer-ului
│   ├── gpio/       # Inițializare și control pini I/O
│   ├── i2c/        # Comunicație I2C (pentru LCD)
│   ├── lcd/        # Control afișaj LCD
│   ├── pwm/        # Generare semnal PWM
│   └── ultrasonic/ # Citire senzor ultrasonic
├── src/            # Codul sursă al aplicației principale
│   └── main.c      # Logica de funcționare a senzorului de distanță
├── utils/          # Funcții utilitare (ex: delay.h)
└── Makefile        # Configurația pentru compilare și încărcare
```

## Compilare și Încărcare (Build & Flash)

Proiectul folosește un `Makefile` robust pentru automatizarea procesului de build.

### Cerințe preliminare
- Toolchain-ul `avr-gcc`
- Utilitarul `avrdude` pentru scrierea codului pe placă
- `make`

### Comenzi disponibile

| Comandă | Descriere |
|---------|-------------|
| `make all BOARD=nano` | Compilează întregul proiect pentru Arduino Nano. |
| `make flash` | Încarcă (flashing) firmware-ul rezultat pe placa conectată. |
| `make clean` | Șterge fișierele generate în urma compilării (`.o`, `.elf`, `.hex`). |

## Contribuitori
Diaconu Andra-Gabriela
Tecuța Elena-Simona

