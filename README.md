# Tron.Experiments.Slave
Progetto per testare la comunicazione tra microcontrollori ESP32 sfruttando il protocollo proprietario ESP-NOW.
Anche se attiva la modalità bidirezionale, la scheda slave in questo primo esperimento è predisposta per l'invio di un pacchetto dati. Si tratta di una ESP32 lolin_d32_pro associata ad un modulo dotato di uno schermo oled SSD1315 0.96 ed una pulsantiera a 4 pulsanti.
- pulsante 1: invio di un pacchetto dati alla scheda Master.
- pulsante 4: attivazione di un invio perpetuo di un pacchetto ogni mezzo secondo.
Una volta che la scheda Slave è attiva, mi sposto con la scheda Master nei vari ambienti per misurare la portata del segnale e l'influenza degli ambienti.


- UI Visual Studio Code
- microcontroller ESP32 lolin_d32_pro
- display oled SSD1315 0.96

