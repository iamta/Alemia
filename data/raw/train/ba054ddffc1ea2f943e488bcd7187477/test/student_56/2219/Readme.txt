Ierarhia pe clase:

Interfete:
	Am definit la nivelul codului 2 interfete.
		IGame: Interfata pentru toate jocurile fie ele in consola fie in GUI. Contine functii ca Begin(), Update() si End().
		IDrawable: Interfata pentru toate obiectele care sunt desenabile. Are o metoda Draw care deseneaza entitatea in teren la o anumita 
					coordonata. De asemenea contine metoda Clear() care goleste terenul la coordonatele desenate anterior.
	Game : Clasa care implementeaza IGame si incapsuleaza un joc de consola. Contine pe langa metodele interfetei o functie protected RenderScene()
		   care actualizeaza scena de lupta periodic. De asemenea clasa contine si detalii ce tin de configuratia jocului ( linii, coloane nivel etc)
		   precum si actiunile pe care le suportam de la User ( Click , Dublu Click etc ).

	GameStateMachine: Principala clasa in care se desfasoara actiunea este GameStateMachine. Aceasta clasa incapsuleaza resursele, 
	       plantele care sunt disponibilie si terenul. Are o functie principala care actualizeaza fiecare entitate la fiecare iteratie a jocului. Mai concret
		   la fiecare iteratie decid la entitatile din teren ar trebui sa se miste , sa traga , sa manance etc.

	TerrainEntity: Clasa de baza abstracta pentru toate entitatile care pot aparea pe teren. Im prezent am gandit ca pe teren sa apara Proiectile, Zombi si Plante.
				Am definit cateva metode la acest nivel precum : 
						ShouldMoveOn -- decid daca entitate trebuie mutata in teren
						IsReady -- decid daca entitatea este pregatita de a-si executa operatia : eg Planta de a trage din nou dupa ce tocmai a tras
						SpecialEfect -- Am pus aceasta metoda la acest nivel desi doar nu am implementata efecte speciale decat pentru plante. Pentru toate celelalte
							entitati se aplica default ca efect special. Pe viitor se poate extine astfel incat sa se atribuie acest lucru si proiectilelor sau zombilor.
	Plant: Clasa de baza pentru toate plantele de epe teren.Are functii ca:
						GetCost() -- returneaza costul achizitiei plante
						GetType() -- returneaza 1 pentru plante. Este o modalitate de a-mi determina tipul plantei fara a folosi polimorfismul
	Am definit cateva plante care extind clasa Plant : 
					SunFlower -- returneaza sori. Are un efect special care ii permite sa suprascrie setarile 
						globale de aparitie de sori.
					Peashooter - trage in zombi-uri de pe teren. Costul ei este 100 si are efect special de a verifica randul curent in ideea ca daca gaseste 
						cel putin un zombi va incepe sa traga.
					Wallnut : Are un damage mult mai mare decat celelalte plante. Nu are niciun efect special asupra terenului.

    Zombi - Clasa de baza pentru toti zombi. Are functie GetSpeed() care returneaza viteza zombiului.
			Am definit urmatoarele tpuri de zombi:
					BasicZombi - zombi basic nu face mare lucru
					BuckedHeadZombi - de doua ori mai rezistent ca zombi
					PoleVaultingZombi - nefinalizata implementarea
	ZombiFactory: Responsabila sa returneze 1 sau 0 zombi la fiecare iteratie.Contine o mapa cu zombi predefiniti pe care sa ii pot returna la fiecare iteratie a jocului,
				 precum si o lista prin care pot controla faptul ca in timpul levelului numarl de zombi sa creasca progresiv,
				 De asemenea aceasta clasa primeste si o strategie de returnare a zombilor care poate fi extinsa ulterior.

	Utils.h - Functii utilitare statice cu care am lucrat

			