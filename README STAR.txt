For å bygge firmware, må du per 7. juni 2013 være på en Linux maskin.

Start med denne introduksjonen:
https://pixhawk.ethz.ch/px4/dev/start

make archives (bygger nuttx etc)

Enten:

make px4fmu_star (bygger star firmware)

eller:

make px4fmu_default (bygger "vanilla" firmware)

make upload px4fmu_[ditt valg]


----------------

for IO:

make px4io_default

make upload px4io_default

gi fila nytt navn: px4io.bin
kopier til minnekort
endre RC-skript (fjern oppstart av bb_handler og exit)
sett minnekort i PX4IO
start opp mens du holder arming switch inne
koble terminal til FMU med putty, baud: 57600
kjør kommando:
	px4io update (eller var det upgrade?? bruk px4io --help)
	
	