# Laboratoire 04 – Utilisation d’un timer avec les interruptions <!-- omit in toc -->

## Table des matières

- [Code pour lancer le preloader](#code-pour-lancer-le-preloader)
- [Analyse](#analyse)
  - [Plan d'adressage](#plan-dadressage)
  - [Configuration utilisée dans le périphérique PIO 0](#configuration-utilisée-dans-le-périphérique-pio-0)
  - [Configuration utilisée dans le périphérique PIO 1](#configuration-utilisée-dans-le-périphérique-pio-1)
  - [Constante ID 32 bits](#constante-id-32-bits)
  - [Périphérique PIO](#périphérique-pio)
  - [timer module 0](#timer-module-0)
- [Programme](#programme)
  - [Démarrage](#démarrage)
  - [Pression sur KEY0](#pression-sur-key0)
  - [Pression sur KEY1](#pression-sur-key1)
  - [Pression sur KEY2](#pression-sur-key2)
  - [Conditions](#conditions)

# Code pour lancer le preloader

```bash

python3 pgm_fpga.py -s=../eda/output_files/DE1_SoC_top.sof
python3 upld_hps.py -a=../../soft/proj/Labo_4/Debug/Labo_4.axf

```


# Analyse

## Plan d'adressage

| Adresse               | read                       | write                |
| --------------------- | -------------------------- | -------------------- |
| 0x00_0000 - 0x00_0003 | Design standart ID 32 bits | reserved             |
| 0x00_0004 - 0x00_00FF | reserved                   | reserved             |
| 0x00_0100 - 0x00_0103 | PIO 0 data                 | PIO 0 data           |
| 0x00_0104 - 0x00_0107 | PIO 0 direction            | PIO 0 direction      |
| 0x00_0108 - 0x00_010B | PIO 0 interrupt mask       | PIO 0 interrupt mask |
| 0x00_010C - 0x00_010F | PIO 0 edge capture         | PIO 0 edge capture   |
| 0x00_0110 - 0x00_0113 | reserved                   | PIO 0 outset         |
| 0x00_0114 - 0x00_0117 | reserved                   | PIO 0 outclear       |
| 0x00_0120 - 0x00_0123 | PIO 1 data                 | PIO 1 data           |
| 0x00_0124 - 0x00_0127 | PIO 1 direction            | PIO 1 direction      |
| 0x00_0128 - 0x00_012B | PIO 1 interrupt mask       | PIO 1 interrupt mask |
| 0x00_012C - 0x00_012F | PIO 1 edge capture         | PIO 1 edge capture   |
| 0x00_0130 - 0x00_0133 | reserved                   | PIO 1 outset         |
| 0x00_0134 - 0x00_0137 | reserved                   | PIO 1 outclear       |

## Configuration utilisée dans le périphérique PIO 0

| PIO Bits      | 31-24  | 23-20    | 19-10      | 9-0            |
| ------------- | ------ | -------- | ---------- | -------------- |
| E/S connectés | unused | Key[3:0] | LEDs[9..0] | Switches[9..0] |

## Configuration utilisée dans le périphérique PIO 1

| PIO Bits      | 31-28  | 27-21      | 20-14      | 13-7       | 6-0        |
| ------------- | ------ | ---------- | ---------- | ---------- | ---------- |
| E/S connectés | unused | Hex3[6..0] | Hex2[6..0] | Hex1[6..0] | Hex0[6..0] |

## Constante ID 32 bits 

0xCAFE1234	

## Périphérique PIO

![Register Map PIO](img/Register%20Map%20PIO.png)

## timer module 0

p.670

201 Timer2 
timer_osc1_0_IRQ This interrupt combines: TIMINT1 and TIMINT2.

202 Timer3 
timer_osc1_1_IRQ This interrupt combines: TIMINT1 and TIMINT2.


# Programme

## Démarrage

- [ ] Eteindre les 10 LEDs
- [ ] Hex0, Hex1, Hex2, Hex3 affiche 0
- [ ] Afficher l'ID 32 bits en hexadécimal dans la console
- [ ] Minuteur est arrêté

## Pression sur KEY0

- [ ] Démarre le minuteur

## Pression sur KEY1

- [ ] Arrête le minuteur

## Pression sur KEY2

- [ ] Charge la valeur des switches comme valeur de départ
- [ ] Affiche la valeur sur les afficheurs hexadécimaux
  - [ ] Hex0 affiche le dixième de seconde

## Conditions

- [ ] chaque 100ms l'affichage est mis à jour
- [ ] L'état de la LED8 montre si le minuteur est actif ou non
- [ ] Chaque 100ms, la LED9 est inversée
