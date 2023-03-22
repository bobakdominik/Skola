Byte 0xFD ; -
Byte 0x03 ; 0
Byte 0x9F ; 1
Byte 0x25 ; 2
Byte 0x0D ; 3
Byte 0x99 ; 4 
Byte 0x49 ; 5
Byte 0x41 ; 6
Byte 0x1F ; 7
Byte 0x01 ; 8
Byte 0x09 ; 9
Byte 0x61 ; E

; display z prava
; Display 1 - 0xE0
; Display 2 - 0xD0
; Display 3 - 0xB0
; Display 4 - 0x70


mvi a, 0
out 0xFB, a
eit
Start: ; Pociatocny nekonecny 
jmp Vypis


Sucet:
mvi a, 3
ldr b, a
shr b, 4
cmi b, 0x0F ; Skontroluje ci bolo stare cislo kladne
jnz Scitaj 
jmp PripravNaOdcitanie

Scitaj:
mvi a, 2
ldr d, a
sbi a, 2
ldr c, a
SucetKontrolaJednotiek:
	ani c, 0x0F
	ani d, 0x0F
	add c, d
	cmi c, 0x09
	jle SucetUlozenieJednotiek
	sbi c, 0x0A
	adi c, 0x10
		SucetUlozenieJednotiek:
		ldr d, a
		ani d, 0xF0
		add d, c
		str a, d
SucetKontrolaDesiatot:
	mvi a, 2
	ldr d, a
	sbi a, 2
	ldr c, a
	shr c, 4
	shr d, 4
	add c, d
	cmi c, 0x09
	jle SucetUlozenieDesiatok
	sbi c, 0x0A
	mvi a, 1
	ldr b, a
	inc b
	str a, b
	mvi a, 0
		SucetUlozenieDesiatok:
		shl c, 4
		ldr d, a
		ani d, 0x0F
		add d, c
		str a, d
		mvi b, 0
		mvi a, 2
		str a, b
SucetKontrolaStoviek:
	mvi a, 3
	ldr d, a
	sbi a, 2
	ldr c, a
	ani c, 0x0F
	ani d, 0x0F
	add c, d
	cmi c, 0x09
	jle SucetUlozenieStoviek
	sbi c, 0x0A
	adi c, 0x10
		SucetUlozenieStoviek:
		ldr d, a
		ani d, 0xF0
		add d, c
		str a, d
SucetKontrolaTisicok:
	mvi a, 3
	ldr d, a
	sbi a, 2
	ldr c, a
	shr c, 4
	shr d, 4
	add c, d
	cmi c, 0x09
	jg UlozChybu
		SucetUlozenieTisicok:
		shl c, 4
		ldr d, a
		ani d, 0x0F
		add d, c
		str a, d
		mvi b, 0
		mvi a, 3
		str a, b
jmp ZalohaCisla


PripravNaOdcitanie:
mvi a, 3
mvi b, 1
ldr c, a
ldr d, b
ani c, 0x0F
str b, c
str a, d
dec a
dec b
ldr c, a
ldr d, b
str b, c
str a, d
jmp Odcitanie


SucetZapornych: 
mvi a, 2
ldr d, a
sbi a, 2
ldr c, a
SucetZapornychKontrolaJednotiek:
	ani c, 0x0F
	ani d, 0x0F
	add c, d
	cmi c, 0x09
	jle SucetZapornychUlozenieJednotiek
	sbi c, 0x0A
	adi c, 0x10
		SucetZapornychUlozenieJednotiek:
		ldr d, a
		ani d, 0xF0
		add d, c
		str a, d
SucetZapornychKontrolaDesiatot:
	mvi a, 2
	ldr d, a
	sbi a, 2
	ldr c, a
	shr c, 4
	shr d, 4
	add c, d
	cmi c, 0x09
	jle SucetZapornychUlozenieDesiatok
	sbi c, 0x0A
	mvi a, 1
	ldr b, a
	inc b
	str a, b
	mvi a, 0
		SucetZapornychUlozenieDesiatok:
		shl c, 4
		ldr d, a
		ani d, 0x0F
		add d, c
		str a, d
		mvi b, 0
		mvi a, 2
		str a, b
SucetZapornychKontrolaStoviek:
	mvi a, 3
	ldr d, a
	sbi a, 2
	ldr c, a
	ani c, 0x0F
	ani d, 0x0F
	add c, d
	cmi c, 0x09
	jle SucetZapornychUlozenieStoviek
	sbi c, 0x0A
	adi c, 0x10
		SucetZapornychUlozenieStoviek:
		ldr d, a
		ani d, 0xF0
		add d, c
		str a, d
SucetZapornychKontrolaZnamienka:
	mvi a, 3
	ldr d, a
	sbi a, 2
	ldr c, a
	shr c, 4
	shr d, 4
	add c, d
	cmi c, 0x0F
	jnz UlozChybu
	shl c, 4
	ldr d, a
	add c, d
	str a, c
	jmp ZalohaCisla

Odcitanie:
mvi a, 3
ldr b, a
shr b, 4
cmi b, 0x0F ; Skontroluje ci bolo stare cislo kladne
jnz Odcitaj 
jmp SucetZapornych
Odcitaj:
	PorovnanieTisicok:
		mvi a, 1
		ldr c, a
		adi a, 2
		ldr d, a
		cmp c, d ; Zistenie ktore cislo je vacsie
		jl PorovnanieStareCisloVacsie
		jg PorovnanieNoveCisloVacsie
	PorovnanieDesiatok:
		mvi a, 0
		ldr c, a
		adi a, 2
		ldr d, a
		cmp c, d ; Zistenie ktore cislo je vacsie
		jg PorovnanieNoveCisloVacsie
		jl PorovnanieStareCisloVacsie
		jmp VynulovaniePamate	
	PorovnanieStareCisloVacsie: ; Register a ukazuje na vacsie cislo, b na mensie
	mvi a, 2
	mvi b, 0
	jmp OdcitanieJednotiek
	PorovnanieNoveCisloVacsie:
	mvi a, 0
	mvi b, 2
	jmp OdcitanieJednotiek

	OdcitanieJednotiek:
		ldr c, a
		ldr d, b
		ori c, 0xF0
		ani d, 0x0F
		sub c, d
		cmi c, 0xF0
		jge OdcitanieJednotiekUlozenie
		ldr d, b
		adi d, 0x10 
		str b, d
		sbi c, 6
			OdcitanieJednotiekUlozenie:
			ani c, 0x0F
			ldr d, a
			ani d, 0xF0
			add d, c
			str a, d
	OdcitanieDesiatok:
		ldr c, a
		ldr d, b
		inc b
		shr c, 4
		shr d, 4
		ori c, 0xF0
		sub c, d
		cmi c, 0xF0
		jge OdcitanieDesiatokUlozenie
		ldr d, b
		inc d 
		str b, d
		sbi c, 6
			OdcitanieDesiatokUlozenie:
			shl c, 4
			ldr d, a
			ani d, 0x0F
			add d, c
			str a, d
			inc a
	OdcitanieStoviek:
		ldr c, a
		ldr d, b
		ori c, 0xF0
		ani d, 0x0F
		sub c, d
		cmi c, 0xF0
		jge OdcitanieStoviekUlozenie
		ldr d, b
		adi d, 0x10 
		str b, d
		sbi c, 6
			OdcitanieStoviekUlozenie:
			ani c, 0x0F
			ldr d, a
			ani d, 0xF0
			add d, c
			str a, d
	OdcitanieTisicok:
		ldr c, a
		ldr d, b
		shr c, 4
		shr d, 4
		sub c, d
		cmp a, b
		jg OdcitanieTisicokUlozenie
		cmi c, 0
		jnz UlozChybu
		mvi c, 0x0F; Ulozenie zaporneho znamienka
			OdcitanieTisicokUlozenie:
			shl c, 4
			ldr d, a
			ani d, 0x0F
			add d, c
			str a, d
		cmp a,b
		jl ZalohaCisla
		mvi a, 2
		mvi b, 0
		ldr c, a
		str b, c
		inc a
		inc b
		ldr c, a
		str b, c
		jmp ZalohaCisla

Nasobenie:
	mvi a, 3 
	ldr b, a
	cmi b, 0xF0
	jge NasobenieZaporne
	mvi a, 0
	pus a
	jmp NasobenieJednotkouKontrolaHodnoty
	NasobenieZaporne:
	sbi b, 0xF0
	str a, b
	mvi a, 1
	pus a
NasobenieJednotkouKontrolaHodnoty:
	
	mvi a, 0
	ldr b, a
	ani b, 0x0F
	cmi b, 0
	jzr NasobenieDesiatkouKontrolaHodnoty
	NasobenieJednotkou:
	dec b
	pus b
		mvi a, 2
		mvi b, 5
		ldr c, a
		ldr d, b
		ani c, 0x0F
		ani d, 0x0F
		add c, d
		cmi c, 10
		jl NasobenieJednotkouUlozJednotky
		sbi c, 10
		adi c, 0x10
		NasobenieJednotkouUlozJednotky:
			ldr d, b
			ani d, 0xF0
			add d, c
			str b, d

		ldr c, a
		ldr d, b
		shr c, 4
		shr d, 4
		add c, d
		cmi c, 10
		jl NasobenieJednotkouUlozDesiatky
		sbi c, 10
		inc b
		ldr d, b
		inc d
		str b, d
		dec b
		NasobenieJednotkouUlozDesiatky:
			shl c, 4
			ldr d, b
			ani d, 0x0F
			add d, c
			str b, d

		inc a
		inc b
		ldr c, a
		ldr d, b
		ani c, 0x0F
		ani d, 0x0F
		add c, d
		cmi c, 10
		jl NasobenieJednotkouUlozStovky
		sbi c, 10
		adi c, 0x10
		NasobenieJednotkouUlozStovky:
			ldr d, b
			ani d, 0xF0
			add d, c
			str b, d

		ldr c, a
		ldr d, b
		shr c, 4
		shr d, 4
		add c, d
		cmi c, 10
		jl NasobenieJednotkouUlozTisicky
		jmp UlozChybuSPopnutim
		NasobenieJednotkouUlozTisicky:
			shl c, 4
			ldr d, b
			ani d, 0x0F
			add d, c
			str b, d
	pop b
	cmi b, 0
	jg NasobenieJednotkou
NasobenieDesiatkouKontrolaHodnoty:
	mvi a, 0
	ldr b, a
	shr b, 4
	cmi b, 0
	jzr NasobenieStovkouKontrolaHodnoty
	NasobenieDesiatkou:
	dec b
	pus b
		mvi a, 2
		mvi b, 5
		ldr c, a
		ldr d, b
		ani c, 0x0F
		shr d, 4
		add c, d
		cmi c, 10
		jl NasobenieDesiatkouUlozJednotky
		sbi c, 10
		inc b
		ldr d, b
		inc d
		str b, d
		dec b
		NasobenieDesiatkouUlozJednotky:
			shl c, 4
			ldr d, b
			ani d, 0x0F
			add d, c
			str b, d
		
		inc b
		ldr c, a
		ldr d, b
		shr c, 4
		ani d, 0x0F
		add c, d
		cmi c, 10
		jl NasobenieDesiatkouUlozDesiatky
		sbi c, 10
		adi c, 0x10
		NasobenieDesiatkouUlozDesiatky:
			ldr d, b
			ani d, 0xF0
			add d, c
			str b, d

		inc a
		ldr c, a
		ldr d, b
		ani c, 0x0F
		shr d, 4
		add c, d
		cmi c, 10
		jl NasobenieDesiatkouUlozStovky
		jmp UlozChybuSPopnutim
		NasobenieDesiatkouUlozStovky:
			shl c, 4
			ldr d, b
			ani d, 0x0F
			add d, c
			str b, d

		ldr c, a
		shr c, 4 
		cmi c, 0
		jnz UlozChybuSPopnutim
	pop b
	cmi b, 0
	jg NasobenieDesiatkou
NasobenieStovkouKontrolaHodnoty:
	mvi a, 1
	ldr b, a
	ani b, 0x0F
	cmi b, 0
	jzr NasobenieTisickouKontrolaHodnoty
	NasobenieStovkou:
	dec b
	pus b
		mvi a, 2
		mvi b, 6
		ldr c, a
		ldr d, b
		ani c, 0x0F
		ani d, 0x0F
		add c, d
		cmi c, 10
		jl NasobenieStovkouUlozJednotky
		sbi c, 10
		adi c, 0x10
		NasobenieStovkouUlozJednotky:
			ldr d, b
			ani d, 0xF0
			add d, c
			str b, d

		ldr c, a
		ldr d, b
		shr c, 4
		shr d, 4
		add c, d
		cmi c, 10
		jl NasobenieStovkouUlozDesiatky
		jmp UlozChybuSPopnutim
		NasobenieStovkouUlozDesiatky:
			shl c, 4
			ldr d, b
			ani d, 0x0F
			add d, c
			str b, d

		inc a
		ldr c, a
		cmi c, 0
		jnz UlozChybuSPopnutim
	pop b
	cmi b, 0
	jg NasobenieStovkou

NasobenieTisickouKontrolaHodnoty:
	mvi a, 1
	ldr b, a
	shr b, 4
	cmi b, 0
	jzr KontrolaZapornehoCisla

	NasobenieTisickou:
	dec b
	pus b
		mvi a, 2
		mvi b, 6
		ldr c, a
		ldr d, b
		ani c, 0x0F
		shr d, 4
		add c, d
		cmi c, 10
		jl NasobenieTisickouUlozJednotky
		jmp UlozChybuSPopnutim
		NasobenieTisickouUlozJednotky:	
			shl c, 4
			ldr d, b
			ani d, 0x0F
			add d, c
			str b, d

		ldr c, a
		shr c, 4
		cmi c, 0
		jnz UlozChybuSPopnutim
		inc a
		ldr c, a
		cmi c, 0
		jnz UlozChybuSPopnutim
	pop b
	cmi b, 0
	jg NasobenieTisickou

KontrolaZapornehoCisla:
pop a 
cmi a, 0
jzr UlozeniePomocnehoVysledku
mvi c, 5
ldr d, c
cmi d, 0
jnz PokracujVKontrole
inc c
ldr d, c
cmi d, 0
jzr UlozeniePomocnehoVysledku
PokracujVKontrole:
mvi c, 6
ldr d, c
cmi d, 0x09
jg UlozChybu
adi d, 0xF0
str c, d
jmp UlozeniePomocnehoVysledku


Delenie:
mvi a, 0
mvi b, 1
ldr c, a
ldr d, b
cmi c, 0
jnz DelenieKontrolaZnamienka
cmi d, 0
jzr UlozChybu
DelenieKontrolaZnamienka:
mvi a, 3
ldr c, a
cmi c, 0xF0
jge DelenieZaporneCislo
mvi b, 0
pus b
jmp DelenieKontrolaVelkosti
DelenieZaporneCislo:
mvi b, 1
pus b
ani c, 0x0F
str a, c
DelenieKontrolaVelkosti:
mvi a, 1
mvi b, 3
ldr c, a
ldr d, b
cmp c, d
jg VynulovaniePamateSPopnutim
jl ZaciatokDelenia
dec a
dec b
ldr c, a
ldr d, b
cmp c, d
jg VynulovaniePamateSPopnutim
ZaciatokDelenia:
mvi a, 5
mvi b, 6
mvi c, 0
str a, c
str b, c
Vydel:
	DelenieOdcitanieJednotiek:
		mvi a, 2
		mvi b, 0
	DelenieZalohaCisla:
	ldr c, b
	pus c
	inc b
	ldr c, b
	pus c
	dec b			
		ldr c, a
		ldr d, b
		ori c, 0xF0
		ani d, 0x0F
		sub c, d
		cmi c, 0xF0
		jge DelenieUlozenieJednotiek
		ldr d, b
		adi d, 0x10 
		str b, d
		sbi c, 6
			DelenieUlozenieJednotiek:
			ani c, 0x0F
			ldr d, a
			ani d, 0xF0
			add d, c
			str a, d
	DelenieOdcitanieDesiatok:
		ldr c, a
		ldr d, b
		inc b
		shr c, 4
		shr d, 4
		ori c, 0xF0
		sub c, d
		cmi c, 0xF0
		jge DelenieUlozenieDesiatok
		ldr d, b
		inc d 
		str b, d
		sbi c, 6
			DelenieUlozenieDesiatok:
			shl c, 4
			ldr d, a
			ani d, 0x0F
			add d, c
			str a, d
			inc a
	DelenieOdcitanieStoviek:
		ldr c, a
		ldr d, b
		ori c, 0xF0
		ani d, 0x0F
		sub c, d
		cmi c, 0xF0
		jge DelenieUlozenieStoviek
		ldr d, b
		adi d, 0x10 
		str b, d
		sbi c, 6
			DelenieUlozenieStoviek:
			ani c, 0x0F
			ldr d, a
			ani d, 0xF0
			add d, c
			str a, d
	DelenieOdcitanieTisicok:
		ldr c, a
		ldr d, b
		shr c, 4
		shr d, 4
		sub c, d
			DelenieUlozenieTisicok:
			shl c, 4
			ldr d, a
			ani d, 0x0F
			add d, c
			str a, d

	DelenieZvacseniePoctu:
		mvi a, 5
		ldr c, a
		inc c
		str a, c
		ani c, 0x0F
		cmi c, 9
		jle DelenieObnovaCisla
		ldr c, a
		ani c, 0xF0
		adi c, 0x10
		str a, c
		cmi c, 0x90
		jle DelenieObnovaCisla
		mvi c, 0
		str a, c
		inc a
		ldr c, a
		inc c
		str a, c
		ani c, 0x0F
		cmi c, 0x09
		jle DelenieObnovaCisla
		ldr c, a
		ani c, 0xF0
		adi c, 0x10
		str a, c
		cmi c, 0x90
		jle DelenieObnovaCisla
		pop a
		jmp UlozChybuSPopnutim
	
	DelenieObnovaCisla:
	mvi b, 1
	pop c	
	str b, c
	dec b
	pop c	
	str b, c

	KoniecDeleniaKontrolaVelkosti:
	mvi a, 1
	mvi b, 3
	ldr c, a
	ldr d, b
	cmp c, d
	jg KontrolaZapornehoCisla
	jl Vydel
	dec a
	dec b
	ldr c, a
	ldr d, b
	cmp c, d
	jg KontrolaZapornehoCisla 
jmp Vydel

UlozeniePomocnehoVysledku:
mvi a, 0
mvi b, 5
mvi d, 0 
ldr c, b
str a, c
str b, d
inc a
inc b
ldr c, b
str a, c
str b, d
jmp ZalohaCisla


VynulovaniePamateSPopnutim:
pop a
VynulovaniePamate:
mvi a, 0
mvi b, 0
str a, b ;Na 0 adresu ulozi 0
jmp VynulovanieUlozenychCisel
UlozChybuSPopnutim:
pop a
pop a
UlozChybu:
mvi a, 0
mvi b, 10
str a, b ;Na 0 adresu ulozi E
VynulovanieUlozenychCisel:
inc a 
mvi b, 0
str a, b ; Na 1 adresu ulozi 0
inc a
str a, b ; Na 2 adresu ulozi 0
inc a
str a, b ; Na 3 adresu ulozi 0
inc a
inc a
str a, b ; Na 5 adresu ulozi 0
inc a
str a, b ; Na 6 adresu ulozi 0
jmp NavratNaStart

ZalohovanieSNavratomNaUlozenie:
mvi a, 0
mvi c, 0
ldr d, a
str a, c
adi a, 2
str a, d
dec a
ldr d, a
str a, c
adi a, 2
str a, d
jmp NavratZoZalohovania

ZalohaCisla:
mvi a, 0
ldr b, a
adi a, 2
str a, b
dec a
ldr b, a
adi a, 2
str a, b
jmp NavratNaStart


Vypis:
	mvi a, 0; Ukazovatel ci predtym bolo cislo, 0 == nebolo, 1 == bolo
	mvi c, 0 ;Ukazovatel znamienka, 0 == +, 1 == -
	mvi d, 1 ;Ukazovatel na miesto v Ram
	ldr b, d ;Nacitana hodnota z Ram
	shr b, 4 ; posunutie tisicok do spodnych 4 bitov
	cmi b, 0x0F;
	jnz VypisTisicok
	inc c
	jmp VypisStoviek

; Vypis Tisicok
VypisTisicok:
	add a, b
	cmi a, 0
	jzr VypisStoviek
	inc b
	mmr b, b
	out 0x7C, b

; Vypis stoviek
VypisStoviek:
	ldr b, d
	ani b, 0x0F ; Ulozenie stoviek do spodnych 4 bitov
	add a, b
	cmi a, 0
	jzr VypisDesiatok
	mvi a, 1
	cmi c, 0
	jzr VypisStoviekNaDysplay
	mvi c,0
	mmr c,c
	out 0x7C, c ; Vypis - na predosly display 
	mvi c,0 ; Vynulovanie C pre nasledujuce vypisy
VypisStoviekNaDysplay:
	inc b
	mmr b,b
	out 0xBC, b

; Vypis desiatok
VypisDesiatok:
	dec d
	ldr b, d
	shr b, 4 ; posunutie desiatok na spodne 4 bity
	add a, b
	cmi a, 0
	jzr VypisJednotiek
	mvi a, 1
	cmi c, 0
	jzr VypisDesiatokNaDysplay
	mvi c,0
	mmr c,c
	out 0xBC, c ; Vypis - na predosly display 
	mvi c,0 ; Vynulovanie C pre nasledujuce vypisy
VypisDesiatokNaDysplay:
	inc b
	mmr b, b
	out 0xDC, b

; Vypis jednotiek
VypisJednotiek:
	ldr b, d
	ani b, 0x0F ; ulozenie jednotiek do spodnych 4 bitov
	cmi c, 0
	jzr VypisJednotiekNaDysplay
	mvi c,0
	mmr c,c
	out 0xDC, c ; Vypis - na predosly display 
	mvi c,0 ; Vynulovanie C pre nasledujuce vypisy
VypisJednotiekNaDysplay:
	inc b
	mmr b, b
	out 0xEC, b
jmp Start

int00:
	mvi a, 0111b ; aktivacia prveho 
	mvi b, 12
	out 0xFB, a
	inn c, 0
	ani c, 0x0F
	cmi c, 0x0F
	jnz UrcenieCisla
	mvi a, 1011b ; aktivacia druheho 
	sbi b, 4
	out 0xFB, a
	inn c, 0
	ani c, 0x0F
	cmi c, 0x0F
	jnz UrcenieCisla
	mvi a, 1101b ; aktivacia tretieho
	sbi b, 4 
	out 0xFB, a
	inn c, 0
	ani c, 0x0F
	cmi c, 0x0F
	jnz UrcenieCisla
	mvi a, 1110b ; aktivacia stvrteho
	sbi b, 4 
	out 0xFB, a
	inn c, 0
	ani c, 0x0F
	cmi c, 0x0F
	jnz UrcenieCisla
	jmp NavratNaStart

UrcenieCisla:
	cmi c, 0111b
	jzr UlozenieZnaku
	inc b
	cmi c, 1011b
	jzr UlozenieZnaku
	inc b
	cmi c, 1101b
	jzr UlozenieZnaku
	inc b
	jmp UlozenieZnaku

UlozenieZnaku:
	cmi b, 0x0F
	jzr Vynulovanie
	mvi a, 0
	ldr c, a
	cmi c, 10
	jzr NavratNaStart
	cmi b, 10
	jl Cisla	
	jmp Operacie
	Vynulovanie:
		mvi a, 4 ;pre vymazanie ulozenej operacie
		mvi b, 0
		str a, b
		jmp VynulovaniePamate
		
	Operacie:
		sbi b, 9
		mvi a, 4
		ldr c, a
		str a, b
		cmi c, 0x10
		jle NavratNaStart
		ani c, 0x0F
		cmi b, 5
		jnz VykonanieUlozenejOperacie
		str a, b
		VykonanieUlozenejOperacie:
			cmi c, 1
			jzr Sucet
			cmi c, 2
			jzr Odcitanie
			cmi c, 3
			jzr Nasobenie
			cmi c, 4
			jzr Delenie
			cmi c, 5
			jzr ZalohaCisla
			jmp NavratNaStart
			
	Cisla:
		mvi a, 4 ; zaznam o tom ze tlacidlo bolo stlacene
		ldr c, a
		cmi c, 0
		jzr UlozenieCisla
		cmi c, 0x10
		jg UlozenieCisla
		jmp ZalohovanieSNavratomNaUlozenie
		NavratZoZalohovania:
		mvi a, 4
		ldr c, a
		ori c, 0x10
		str a, c
	UlozenieCisla:
		mvi a, 1
		ldr c, a
		shl c, 4
		dec a
		ldr d, a
		shr d, 4
		add c, d
		inc a
		str a, c
		dec a
		ldr c, a
		shl c, 4
		add c, b
		str a,c 
		mvi a,0xF7

NavratNaStart:
mvi a, 0
out 0xFB, a
eit 
ret


;Osetrenie chyb z klavesnice
int01:
int02:
int03:
int04:
int05:
int06:
int07:
int08:
int09:
int10:
int11:
int12:
int13:
int14:
int15:
eit
ret 
