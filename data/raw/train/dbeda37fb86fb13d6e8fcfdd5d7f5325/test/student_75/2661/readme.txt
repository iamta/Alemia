In cerintele pe care le-am avut de rezolvat, am reusit implementarea urmatoarelor functionalitati:
- crearea tuturor plantelor care detin urmatoarele desene:
	-& -> floarea soarelui
	-% -> mazare
	-%% -> mazare inghetata
	-* -> bomba cireasa
	-|| -> nuca perete
- crearea tuturor entitatilor cu urmatoarele functionalitati si desene:
	-"\\_(*!*)_/ " -> zombie simplu(15hp)
	-"\\~(.-.)~/ " -> zombie cu galeata in cap(25hp)
 	-"\\=(*-*)=/ " -> pole_vaulting zombie(20hp)(sare peste primul obiect)
	-"|=(+_+)=| " -> super zombie(30hp)(poate sarip peste prima planta)
- implementarea tuturor aspectelor ce cuprind:
	- generarea aleatoare a resurselor de tip sun(am folosit un destructor si constructor privat si am restrictionat crearea a maxim 9 resurse de tip sun)
	- disparitia acestora dupa un interval de timp daca nu au fost colectate
	- mentinerea scorului(la fiecare hit se va adauga +50 la score)
- realizarea unui sistem LOG care stocheaza informatii privind logarea si actiunile pe care le face utilizatorul in timpul jocului, cat si desfasurarea actiunii jocului(generarea de zombie, plantarea si distrugerea oaspertilor)
- jocul are implementat un mecanism de exceptii, fara existenta unei clase specializate pentru tratarea acestor
- pentru fiecare utilizator se va crea un fisier de tip .txt care va avea ca nume "log"+numele utilizatorului, si care va contine pe prima linie parola si pe a doua linie scorul obtinut.

Jocul nu are o finitutine, se va juca cat timp utilizatorul reuseste sa supravietuiasca. Prin urmare, enitatea Super Zombie se va genera o singura data in mod aletoriu pe tot parcursul jocului.

MOD DE UTILIZARE:
	aplicatia ca incepe cu un sistem de log.
	daca nu aveti cont, la scrierea pentru prima data a Id-ului si parolei se va crea automat un cont
	dupa ce treceti contul, selectati nivelul pe care doriti sa-l jucati
	HAVE FUN!

Erori ce trebuiesc reparate: 
	- daca a fost distrusa o planta care folosea proiectile, proiectilele deja create de aceasta si nedistruse vor ramane afisate pe consola.
	- posibilitatea incalcarii unei plante infara terenului care va induce o dezaranjare a spatiului de joc prin afisarea aleatoare a proiectitlelor.
	- posibilitatea incarcarii a doua plante una peste alta.