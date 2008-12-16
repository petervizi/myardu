v 20080127 1
C 40000 40000 0 0 0 title-B.sym
T 54000 40100 9 10 1 0 0 0 1
Peter Vizi
C 44100 45000 1 0 0 connector8-1.sym
{
T 44200 48200 5 10 0 0 0 0 1
device=CONNECTOR_8
T 44200 47600 5 10 1 1 0 0 1
refdes=J2
}
T 50100 40100 9 10 1 0 0 0 1
1
T 51600 40100 9 10 1 0 0 0 1
1
C 52200 42500 1 0 0 LCM-S01602DSFC.sym
{
T 54000 48700 5 10 1 1 0 6 1
refdes=LCD?
T 52600 48900 5 10 0 0 0 0 1
device=LCM-S01602DSF/C
}
C 44100 41200 1 0 0 connector6-1.sym
{
T 45900 43000 5 10 0 0 0 0 1
device=CONNECTOR_6
T 44200 43200 5 10 1 1 0 0 1
refdes=POWER
}
N 45800 42000 48000 42000 4
C 46900 42400 1 0 0 pot-1.sym
{
T 47700 43300 5 10 0 0 0 0 1
device=VARIABLE_RESISTOR
T 47500 42800 5 10 1 1 0 0 1
refdes=R?
T 47700 43900 5 10 0 0 0 0 1
footprint=none
}
N 47400 43000 52300 43000 4
N 45800 42300 46700 42300 4
N 46700 42500 46700 42300 4
N 47800 42500 48000 42500 4
N 46700 42500 46900 42500 4
T 44900 42400 9 10 1 0 0 0 1
+5V
T 44900 42100 9 10 1 0 0 0 1
GND
T 50500 40900 9 10 1 0 0 0 1
LCD and Temperature sensor wiring
C 40600 43000 1 0 0 SHT75.sym
{
T 42400 45200 5 10 1 1 0 6 1
refdes=T?
T 41000 45400 5 10 0 0 0 0 1
device=SHT75
}
N 42700 43500 46200 43500 4
N 45800 42600 46200 42600 4
T 44900 42700 9 10 1 0 0 0 1
+3V
N 42700 44300 43100 44300 4
N 43100 40700 43100 44300 4
N 43100 40700 48000 40700 4
C 44600 44600 1 270 0 resistor-1.sym
{
T 45000 44300 5 10 0 0 270 0 1
device=RESISTOR
T 44900 44400 5 10 1 1 270 0 1
refdes=Rp
}
N 44700 43700 44700 43500 4
N 42700 44700 44700 44700 4
N 44700 44700 44700 44600 4
T 50000 40400 9 10 1 0 0 0 1
tempLCD.sch
T 54000 40400 9 10 1 0 0 0 1
0.2
C 44100 48100 1 0 0 connector8-1.sym
{
T 44200 51300 5 10 0 0 0 0 1
device=CONNECTOR_8
T 44200 50700 5 10 1 1 0 0 1
refdes=J1
}
N 45800 48600 51500 48600 4
N 51500 48600 51500 45800 4
N 51500 45800 52300 45800 4
N 45800 48300 51200 48300 4
N 51200 45400 51200 48300 4
N 51200 45400 52300 45400 4
N 45800 47300 50900 47300 4
N 50900 45000 50900 47300 4
N 50900 45000 52300 45000 4
N 45800 47000 50500 47000 4
N 50500 44600 50500 47000 4
N 50500 44600 52300 44600 4
N 45800 46700 50200 46700 4
N 50200 46700 50200 43400 4
N 50200 43400 52300 43400 4
N 45800 46400 49800 46400 4
N 49800 46400 49800 43800 4
N 49800 43800 52300 43800 4
N 45800 46100 49400 46100 4
N 49400 46100 49400 44200 4
N 49400 44200 52300 44200 4
N 46200 42600 46200 48900 4
N 46200 48900 52000 48900 4
N 52000 48900 52000 48200 4
N 52000 48200 52300 48200 4
N 48000 40700 48000 49200 4
N 48000 49200 51800 49200 4
N 51800 49200 51800 47800 4
N 51800 47800 52300 47800 4