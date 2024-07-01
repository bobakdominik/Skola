-- Vypis osob, ktore trpia smrtelnymi chorobami
SELECT osoba.meno, osoba.priezvisko, osoba.rod_cislo, choroba.nazov_choroby, choroba.kod_choroby,zoznam_ochoreni.datum_od
FROM osoba
JOIN pacient
ON osoba.rod_cislo = pacient.rod_cislo
JOIN zdravotna_karta
ON pacient.os_cislo_pacienta=zdravotna_karta.os_cislo_pacienta
JOIN zoznam_ochoreni
ON zdravotna_karta.id_karty=zoznam_ochoreni.id_karty
JOIN choroba
ON zoznam_ochoreni.id_choroby=choroba.id_choroby
WHERE choroba.kod_choroby LIKE '%�%' AND zoznam_ochoreni.datum_do IS NULL
ORDER BY osoba.meno, osoba.priezvisko, osoba.rod_cislo;

create or replace procedure osoby_so_smrtelnymi_chorobami(
    result_cursor out SYS_REFCURSOR)
is
begin
    open result_cursor for
    SELECT osoba.meno, osoba.priezvisko, osoba.rod_cislo, choroba.nazov_choroby, choroba.kod_choroby,zoznam_ochoreni.datum_od
        FROM osoba
            JOIN pacient
            ON osoba.rod_cislo = pacient.rod_cislo
            JOIN zdravotna_karta
            ON pacient.os_cislo_pacienta=zdravotna_karta.os_cislo_pacienta
            JOIN zoznam_ochoreni
            ON zdravotna_karta.id_karty=zoznam_ochoreni.id_karty
            JOIN choroba
            ON zoznam_ochoreni.id_choroby=choroba.id_choroby
                WHERE choroba.kod_choroby LIKE '%�%' AND zoznam_ochoreni.datum_do IS NULL
                    ORDER BY osoba.meno, osoba.priezvisko, osoba.rod_cislo;
end;
/

-- Vypis oddelenia a pocet osob momentalne osetrovanych - kapacita ?
SELECT oddelenie.id_oddelenia, oddelenie.nazov_oddelenia, count(zabrate_lozka.os_cislo_pacienta) as pocet_pacientov, count(lozko.cislo_lozka) as pocet_lozok
FROM oddelenie
LEFT JOIN lozko
ON oddelenie.id_oddelenia=lozko.id_oddelenia 
LEFT JOIN zabrate_lozka
ON lozko.cislo_lozka=zabrate_lozka.cislo_lozka and zabrate_lozka.datum_do IS NOT NULL
GROUP BY oddelenie.id_oddelenia, oddelenie.nazov_oddelenia
ORDER BY id_oddelenia;

create or replace procedure aktualny_pocet_obsadenych_lozok_podla_oddelenia(
    result_cursor out SYS_REFCURSOR)
is
begin
    open result_cursor for
    SELECT oddelenie.id_oddelenia, oddelenie.nazov_oddelenia, count(zabrate_lozka.os_cislo_pacienta) as pocet_pacientov, count(lozko.cislo_lozka) as pocet_lozok
FROM oddelenie
LEFT JOIN lozko
ON oddelenie.id_oddelenia=lozko.id_oddelenia 
LEFT JOIN zabrate_lozka
ON lozko.cislo_lozka=zabrate_lozka.cislo_lozka and zabrate_lozka.datum_do IS NOT NULL
GROUP BY oddelenie.id_oddelenia, oddelenie.nazov_oddelenia
ORDER BY id_oddelenia;
end;
/

-- 10% osob, ktore su najviac chore - najviac chorob
SELECT meno, priezvisko, rod_cislo, os_cislo_pacienta,id_karty, pocet_chorob FROM(
SELECT osoba.meno, osoba.priezvisko, osoba.rod_cislo, zdravotna_karta.id_karty, pacient.os_cislo_pacienta,count(zoznam_ochoreni.id_choroby) as pocet_chorob, (row_number() over (order by count(zoznam_ochoreni.id_choroby) desc)) as rnk
FROM osoba
JOIN pacient
ON osoba.rod_cislo=pacient.rod_cislo
JOIN zdravotna_karta
ON pacient.os_cislo_pacienta=zdravotna_karta.os_cislo_pacienta
JOIN zoznam_ochoreni
ON zdravotna_karta.id_karty=zoznam_ochoreni.id_karty
GROUP BY osoba.meno, osoba.priezvisko, osoba.rod_cislo, pacient.os_cislo_pacienta,zdravotna_karta.id_karty 
ORDER BY pocet_chorob desc) sel
WHERE rnk <= 0.1 * (SELECT count(distinct os.rod_cislo) FROM osoba os
                    JOIN pacient pac
                    ON os.rod_cislo=pac.rod_cislo
                    JOIN zdravotna_karta zk
                    ON pac.os_cislo_pacienta=zk.os_cislo_pacienta);
                    
create or replace procedure najviac_chorych_osob_podiel(
    percenta number,
    result_cursor out SYS_REFCURSOR)
is
    v_percento number;
begin
    v_percento := percenta;
    if v_percento < 0 then v_percento := 0;
    else if v_percento > 100 then v_percento := 100;
    end if;
    end if;
    
    open result_cursor for
    SELECT meno, priezvisko, rod_cislo, os_cislo_pacienta,id_karty, pocet_chorob FROM(
        SELECT osoba.meno, osoba.priezvisko, osoba.rod_cislo, zdravotna_karta.id_karty, pacient.os_cislo_pacienta,count(zoznam_ochoreni.id_choroby) as pocet_chorob, (row_number() over (order by count(zoznam_ochoreni.id_choroby) desc)) as rnk
        FROM osoba
        JOIN pacient
        ON osoba.rod_cislo=pacient.rod_cislo
        JOIN zdravotna_karta
        ON pacient.os_cislo_pacienta=zdravotna_karta.os_cislo_pacienta
        JOIN zoznam_ochoreni
        ON zdravotna_karta.id_karty=zoznam_ochoreni.id_karty
        GROUP BY osoba.meno, osoba.priezvisko, osoba.rod_cislo, pacient.os_cislo_pacienta,zdravotna_karta.id_karty 
        ORDER BY pocet_chorob desc) sel
        WHERE rnk <= v_percento / 100 * (SELECT count(distinct os.rod_cislo) FROM osoba os
                            JOIN pacient pac
                            ON os.rod_cislo=pac.rod_cislo
                            JOIN zdravotna_karta zk
                            ON pac.os_cislo_pacienta=zk.os_cislo_pacienta);
end;
/

-- Statistika - ktore mesiace su najviac vytazene v nemocnici, hospitalizovani jednotlive mesiace
SELECT 
count(case extract(month from zabrate_lozka.datum_od) when 1 then 1 else null end) as pocet_januar,
count(case extract(month from zabrate_lozka.datum_od) when 2 then 1 else null end) as pocet_februar,
count(case extract(month from zabrate_lozka.datum_od) when 3 then 1 else null end) as pocet_marec,
count(case extract(month from zabrate_lozka.datum_od) when 4 then 1 else null end) as pocet_april,
count(case extract(month from zabrate_lozka.datum_od) when 5 then 1 else null end) as pocet_maj,
count(case extract(month from zabrate_lozka.datum_od) when 6 then 1 else null end) as pocet_jun,
count(case extract(month from zabrate_lozka.datum_od) when 7 then 1 else null end) as pocet_jul,
count(case extract(month from zabrate_lozka.datum_od) when 8 then 1 else null end) as pocet_august,
count(case extract(month from zabrate_lozka.datum_od) when 9 then 1 else null end) as pocet_september,
count(case extract(month from zabrate_lozka.datum_od) when 10 then 1 else null end) as pocet_oktober,
count(case extract(month from zabrate_lozka.datum_od) when 11 then 1 else null end) as pocet_november,
count(case extract(month from zabrate_lozka.datum_od) when 12 then 1 else null end) as pocet_december
FROM zabrate_lozka
WHERE extract(year from datum_od) = extract(year from sysdate);

create or replace procedure najviac_vytazene_mesiace_statistika(
    rok number,
    result_cursor out SYS_REFCURSOR)
is
    v_rok number;
begin
    v_rok := rok;
    if v_rok > extract(year from sysdate) then v_rok := extract(year from sysdate);
    else if v_rok < 0 then v_rok := 0;
    end if;
    end if;
    
    if v_rok > 0 then 
    
    open result_cursor for
    SELECT 
        count(case extract(month from zabrate_lozka.datum_od) when 1 then 1 else null end) as pocet_januar,
        count(case extract(month from zabrate_lozka.datum_od) when 2 then 1 else null end) as pocet_februar,
        count(case extract(month from zabrate_lozka.datum_od) when 3 then 1 else null end) as pocet_marec,
        count(case extract(month from zabrate_lozka.datum_od) when 4 then 1 else null end) as pocet_april,
        count(case extract(month from zabrate_lozka.datum_od) when 5 then 1 else null end) as pocet_maj,
        count(case extract(month from zabrate_lozka.datum_od) when 6 then 1 else null end) as pocet_jun,
        count(case extract(month from zabrate_lozka.datum_od) when 7 then 1 else null end) as pocet_jul,
        count(case extract(month from zabrate_lozka.datum_od) when 8 then 1 else null end) as pocet_august,
        count(case extract(month from zabrate_lozka.datum_od) when 9 then 1 else null end) as pocet_september,
        count(case extract(month from zabrate_lozka.datum_od) when 10 then 1 else null end) as pocet_oktober,
        count(case extract(month from zabrate_lozka.datum_od) when 11 then 1 else null end) as pocet_november,
        count(case extract(month from zabrate_lozka.datum_od) when 12 then 1 else null end) as pocet_december
    FROM zabrate_lozka
        WHERE extract(year from datum_od) = v_rok;
    else 
        open result_cursor for
    SELECT 
        count(case extract(month from zabrate_lozka.datum_od) when 1 then 1 else null end) as pocet_januar,
        count(case extract(month from zabrate_lozka.datum_od) when 2 then 1 else null end) as pocet_februar,
        count(case extract(month from zabrate_lozka.datum_od) when 3 then 1 else null end) as pocet_marec,
        count(case extract(month from zabrate_lozka.datum_od) when 4 then 1 else null end) as pocet_april,
        count(case extract(month from zabrate_lozka.datum_od) when 5 then 1 else null end) as pocet_maj,
        count(case extract(month from zabrate_lozka.datum_od) when 6 then 1 else null end) as pocet_jun,
        count(case extract(month from zabrate_lozka.datum_od) when 7 then 1 else null end) as pocet_jul,
        count(case extract(month from zabrate_lozka.datum_od) when 8 then 1 else null end) as pocet_august,
        count(case extract(month from zabrate_lozka.datum_od) when 9 then 1 else null end) as pocet_september,
        count(case extract(month from zabrate_lozka.datum_od) when 10 then 1 else null end) as pocet_oktober,
        count(case extract(month from zabrate_lozka.datum_od) when 11 then 1 else null end) as pocet_november,
        count(case extract(month from zabrate_lozka.datum_od) when 12 then 1 else null end) as pocet_december
    FROM zabrate_lozka;
    end if;
end;
/

-- Kolko zaplatila osoba za ukony v nemocnici
SELECT osoba.meno, osoba.priezvisko, osoba.rod_cislo, sum(pl.suma) celkova_suma
FROM osoba
         join pacient p on osoba.rod_cislo = p.rod_cislo
         join zdravotna_karta zk on p.os_cislo_pacienta = zk.os_cislo_pacienta
         join lekarsky_ukon lu on zk.id_karty = lu.id_karty
         join platba pl on lu.id_ukonu = pl.id_ukonu and lu.datum_vykonania = pl.datum_vykonania
         WHERE p.os_cislo_pacienta = 326948
GROUP BY osoba.meno, osoba.priezvisko, osoba.rod_cislo
ORDER BY celkova_suma DESC;

create or replace procedure suma_platieb_danej_osoby(
    os_cislo number,
    result_cursor out SYS_REFCURSOR)
is
begin
    open result_cursor for
    SELECT osoba.meno, osoba.priezvisko, osoba.rod_cislo, sum(pl.suma) celkova_suma
    FROM osoba
         join pacient p on osoba.rod_cislo = p.rod_cislo
         join zdravotna_karta zk on p.os_cislo_pacienta = zk.os_cislo_pacienta
         join lekarsky_ukon lu on zk.id_karty = lu.id_karty
         join platba pl on lu.id_ukonu = pl.id_ukonu and lu.datum_vykonania = pl.datum_vykonania
         WHERE p.os_cislo_pacienta = os_cislo
    GROUP BY osoba.meno, osoba.priezvisko, osoba.rod_cislo
        ORDER BY celkova_suma DESC;
end;
/

-- Pocet pacientov s danou chorobou
SELECT choroba.id_choroby, choroba.nazov_choroby, count(zoznam_ochoreni.id_karty) as pocet
FROM choroba
JOIN zoznam_ochoreni
ON choroba.id_choroby=zoznam_ochoreni.id_choroby
GROUP BY choroba.id_choroby, choroba.nazov_choroby
ORDER BY pocet DESC;

create or replace procedure pocet_pacientov_s_danou_chorobou(
    p_id_choroby number,
    result_cursor out SYS_REFCURSOR)
is
begin
    open result_cursor for
    SELECT choroba.id_choroby, choroba.nazov_choroby, count(zoznam_ochoreni.id_karty) as pocet
    FROM choroba
        LEFT JOIN zoznam_ochoreni
        ON choroba.id_choroby=zoznam_ochoreni.id_choroby
            WHERE choroba.id_choroby = p_id_choroby
                GROUP BY choroba.id_choroby, choroba.nazov_choroby
                    ORDER BY pocet DESC;
end;
/

commit;

-- Ohodnotit paciantov ktori boli najdlhsie chori
select os.meno, os.priezvisko, os.rod_cislo, sel.datum_od, sel.datum_do, sel.id_choroby,trunc(dni) from
(select ch.nazov_choroby, ch.id_choroby,zo.id_karty, zo.datum_od, zo.datum_do, (case when zo.datum_do is null then sysdate else zo.datum_do end) - zo.datum_od as dni, dense_rank() over( partition by zo.id_karty  order by (case when zo.datum_do is null then sysdate else zo.datum_do end) - zo.datum_od desc) as rank
from choroba ch
join zoznam_ochoreni zo on (ch.id_choroby=zo.id_choroby)
group by ch.nazov_choroby, ch.id_choroby, zo.datum_od, zo.datum_do, zo.id_karty) sel
join zdravotna_karta zk2 on (sel.id_karty=zk2.id_karty)
join pacient p on (p.os_cislo_pacienta=zk2.os_cislo_pacienta)
join osoba os on (os.rod_cislo=p.rod_cislo)
where sel.rank = 1 AND sel.id_choroby = 0
group by os.meno, os.priezvisko, os.rod_cislo, sel.datum_od, sel.datum_do, sel.id_choroby, dni
order by dni;

create or replace procedure zoradenie_pacientov_podla_trvania_choroby(
    zorad_vzostupne in boolean,
    id_choroby number,
    result_cursor out SYS_REFCURSOR)
is
    val_choroba number;
begin
    val_choroba := id_choroby;
    if val_choroba is null then
        if zorad_vzostupne then
        
            open result_cursor for
            select os.meno, os.priezvisko, os.rod_cislo, sel.datum_od, sel.datum_do, sel.id_choroby,trunc(dni) as pocet_dni from
            (select ch.nazov_choroby, ch.id_choroby,zo.id_karty, zo.datum_od, zo.datum_do, (case when zo.datum_do is null then sysdate else zo.datum_do end) - zo.datum_od as dni, dense_rank() over( partition by zo.id_karty  order by (case when zo.datum_do is null then sysdate else zo.datum_do end) - zo.datum_od desc) as rank
            from choroba ch
                join zoznam_ochoreni zo on (ch.id_choroby=zo.id_choroby)
                group by ch.nazov_choroby, ch.id_choroby, zo.datum_od, zo.datum_do, zo.id_karty) sel
                join zdravotna_karta zk2 on (sel.id_karty=zk2.id_karty)
                join pacient p on (p.os_cislo_pacienta=zk2.os_cislo_pacienta)
                join osoba os on (os.rod_cislo=p.rod_cislo)
                    where sel.rank = 1 
                        group by os.meno, os.priezvisko, os.rod_cislo, sel.datum_od, sel.datum_do, sel.id_choroby, dni
                            order by dni asc;
        else
            
            open result_cursor for
            select os.meno, os.priezvisko, os.rod_cislo, sel.datum_od, sel.datum_do, sel.id_choroby,trunc(dni) as pocet_dni from
            (select ch.nazov_choroby, ch.id_choroby,zo.id_karty, zo.datum_od, zo.datum_do, (case when zo.datum_do is null then sysdate else zo.datum_do end) - zo.datum_od as dni, dense_rank() over( partition by zo.id_karty  order by (case when zo.datum_do is null then sysdate else zo.datum_do end) - zo.datum_od desc) as rank
            from choroba ch
                join zoznam_ochoreni zo on (ch.id_choroby=zo.id_choroby)
                group by ch.nazov_choroby, ch.id_choroby, zo.datum_od, zo.datum_do, zo.id_karty) sel
                join zdravotna_karta zk2 on (sel.id_karty=zk2.id_karty)
                join pacient p on (p.os_cislo_pacienta=zk2.os_cislo_pacienta)
                join osoba os on (os.rod_cislo=p.rod_cislo)
                    where sel.rank = 1 
                        group by os.meno, os.priezvisko, os.rod_cislo, sel.datum_od, sel.datum_do, sel.id_choroby, dni
                            order by dni desc;
            
        end if;
    else 
        if zorad_vzostupne then
        
            open result_cursor for
            select os.meno, os.priezvisko, os.rod_cislo, sel.datum_od, sel.datum_do, sel.id_choroby,trunc(dni) as pocet_dni from
                (select ch.nazov_choroby, ch.id_choroby,zo.id_karty, zo.datum_od, zo.datum_do, (case when zo.datum_do is null then sysdate else zo.datum_do end) - zo.datum_od as dni, dense_rank() over( partition by zo.id_karty  order by (case when zo.datum_do is null then sysdate else zo.datum_do end) - zo.datum_od desc) as rank
                from choroba ch
                    join zoznam_ochoreni zo on (ch.id_choroby=zo.id_choroby and ch.id_choroby=val_choroba)
                    group by ch.nazov_choroby, ch.id_choroby, zo.datum_od, zo.datum_do, zo.id_karty) sel
                    join zdravotna_karta zk2 on (sel.id_karty=zk2.id_karty)
                    join pacient p on (p.os_cislo_pacienta=zk2.os_cislo_pacienta)
                    join osoba os on (os.rod_cislo=p.rod_cislo)
                        where sel.rank = 1 AND sel.id_choroby = val_choroba
                            group by os.meno, os.priezvisko, os.rod_cislo, sel.datum_od, sel.datum_do, sel.id_choroby, dni
                                order by dni asc;
        else
            
            open result_cursor for
            select os.meno, os.priezvisko, os.rod_cislo, sel.datum_od, sel.datum_do, sel.id_choroby,trunc(dni) as pocet_dni from
                (select ch.nazov_choroby, ch.id_choroby,zo.id_karty, zo.datum_od, zo.datum_do, (case when zo.datum_do is null then sysdate else zo.datum_do end) - zo.datum_od as dni, dense_rank() over( partition by zo.id_karty  order by (case when zo.datum_do is null then sysdate else zo.datum_do end) - zo.datum_od desc) as rank
                from choroba ch
                    join zoznam_ochoreni zo on (ch.id_choroby=zo.id_choroby and ch.id_choroby=val_choroba)
                    group by ch.nazov_choroby, ch.id_choroby, zo.datum_od, zo.datum_do, zo.id_karty) sel
                    join zdravotna_karta zk2 on (sel.id_karty=zk2.id_karty)
                    join pacient p on (p.os_cislo_pacienta=zk2.os_cislo_pacienta)
                    join osoba os on (os.rod_cislo=p.rod_cislo)
                        where sel.rank = 1 AND sel.id_choroby = val_choroba
                            group by os.meno, os.priezvisko, os.rod_cislo, sel.datum_od, sel.datum_do, sel.id_choroby, dni
                                order by dni desc;
            
        end if;
    end if;
end;
/

commit;

select os.meno, os.priezvisko, os.rod_cislo, sel.datum_od, sel.datum_do, sel.id_choroby,trunc(dni) as pocet_dni from
            (select ch.nazov_choroby, ch.id_choroby,zo.id_karty, zo.datum_od, zo.datum_do, (case when zo.datum_do is null then sysdate else zo.datum_do end) - zo.datum_od as dni, dense_rank() over( partition by zo.id_karty  order by (case when zo.datum_do is null then sysdate else zo.datum_do end) - zo.datum_od desc) as rank
            from choroba ch
                join zoznam_ochoreni zo on (ch.id_choroby=zo.id_choroby)
                group by ch.nazov_choroby, ch.id_choroby, zo.datum_od, zo.datum_do, zo.id_karty) sel
                join zdravotna_karta zk2 on (sel.id_karty=zk2.id_karty)
                join pacient p on (p.os_cislo_pacienta=zk2.os_cislo_pacienta)
                join osoba os on (os.rod_cislo=p.rod_cislo)
                    where sel.rank = 1 
                        group by os.meno, os.priezvisko, os.rod_cislo, sel.datum_od, sel.datum_do, sel.id_choroby, dni
                            order by dni desc;


-- platby - zvolit mesiac/rok, vypisat platby spolu
create or replace procedure suma_platieb_danej_nemocnici_dany_rok_a_mesiac(
    nemocnica number,
    mesiac number, rok number,
    result_cursor out SYS_REFCURSOR)
    is
begin
    if mesiac is null and rok is not null then
        open result_cursor for
            select o.id_nemocnice, extract(month from datum_platby) as mesiac, extract(year from datum_platby) as rok, sum(suma)
            from nemocnica nm
                     join oddelenie o on nm.id_nemocnice = o.id_nemocnice
                     join lekarsky_ukon lu on o.id_oddelenia = lu.id_oddelenia
                     join platba p on lu.id_ukonu = p.id_ukonu and lu.datum_vykonania = p.datum_vykonania
            where o.id_nemocnice = nemocnica
              and extract(year from datum_platby) = rok
            group by o.id_nemocnice, extract(month from datum_platby), extract(year from datum_platby)
            order by mesiac;
    elsif mesiac is not null and rok is null then
        open result_cursor for
            select o.id_nemocnice, extract(month from datum_platby) as mesiac, extract(year from datum_platby) as rok, sum(suma)
            from nemocnica nm
                     join oddelenie o on nm.id_nemocnice = o.id_nemocnice
                     join lekarsky_ukon lu on o.id_oddelenia = lu.id_oddelenia
                     join platba p on lu.id_ukonu = p.id_ukonu and lu.datum_vykonania = p.datum_vykonania
            where o.id_nemocnice = nemocnica
              and extract(year from datum_platby) = extract(year from sysdate)
              and extract(month from datum_platby) = mesiac
            group by o.id_nemocnice, extract(month from datum_platby), extract(year from datum_platby)
            order by mesiac;
    elsif mesiac is not null and rok is not null then
        open result_cursor for
            select o.id_nemocnice, extract(month from datum_platby) as mesiac, extract(year from datum_platby) as rok, sum(suma)
            from nemocnica nm
                     join oddelenie o on nm.id_nemocnice = o.id_nemocnice
                     join lekarsky_ukon lu on o.id_oddelenia = lu.id_oddelenia
                     join platba p on lu.id_ukonu = p.id_ukonu and lu.datum_vykonania = p.datum_vykonania
            where o.id_nemocnice = nemocnica
              and extract(year from datum_platby) = rok
              and extract(month from datum_platby) = mesiac
            group by o.id_nemocnice, extract(month from datum_platby), extract(year from datum_platby)
            order by mesiac;
    elsif mesiac is null and rok is null then
        open result_cursor for
            select o.id_nemocnice, extract(month from datum_platby) as mesiac, extract(year from datum_platby) as rok, sum(suma)
            from nemocnica nm
                     join oddelenie o on nm.id_nemocnice = o.id_nemocnice
                     join lekarsky_ukon lu on o.id_oddelenia = lu.id_oddelenia
                     join platba p on lu.id_ukonu = p.id_ukonu and lu.datum_vykonania = p.datum_vykonania
            where o.id_nemocnice = nemocnica
              and extract(year from datum_platby) = extract(year from sysdate)
              and extract(month from datum_platby) = (extract(month from sysdate) - 1)
            group by o.id_nemocnice, extract(month from datum_platby), extract(year from datum_platby)
            order by mesiac;
    end if;
end;
/

-- vystup - lieky v sklade, ktore maju datum expiracie v aktualnom mesiaci

create or replace procedure get_expired_medicine_by_department_in_current_month(
    department varchar2,
    result_cursor out SYS_REFCURSOR)
is
begin
    if department = 'Vsetky' then
        open result_cursor for
        select lk.detail.nazov, lk.detail.atc, lk.detail.doplnok, datum_expiracie, nazov_oddelenia from sklad_liekov_oddelenia
            join liek lk using(kod_lieku)
            join oddelenie using(id_oddelenia)
                where substr(to_char(datum_expiracie),4,3) = substr(to_char(sysdate),4,3);
    else
        open result_cursor for
        select lk.detail.nazov, lk.detail.atc, lk.detail.doplnok, datum_expiracie from sklad_liekov_oddelenia
            join liek lk using(kod_lieku)
            join oddelenie using(id_oddelenia)
                where substr(to_char(datum_expiracie),4,3) = substr(to_char(sysdate),4,3) and
                extract(year from datum_expiracie) = extract(year from sysdate) and
                nazov_oddelenia = department;
    end if;
end;
/

-- vystup - lieky v sklade, ktore k aktualnemu datumu uz su po zaruke

create or replace procedure get_expired_medicine_by_department(
    department varchar2,
    result_cursor out SYS_REFCURSOR)
is
begin
    if department = 'Vsetky' then
        open result_cursor for
        select lk.detail.nazov, lk.detail.atc, lk.detail.doplnok, datum_expiracie, nazov_oddelenia from sklad_liekov_oddelenia
            join liek lk using(kod_lieku)
            join oddelenie using(id_oddelenia)
                where datum_expiracie <= sysdate;
    else
        open result_cursor for
        select lk.detail.nazov, lk.detail.atc, lk.detail.doplnok, datum_expiracie from sklad_liekov_oddelenia
            join liek lk using(kod_lieku)
            join oddelenie using(id_oddelenia)
                where datum_expiracie <= sysdate and
                nazov_oddelenia = department;
    end if;
end;
/

-- vystup - pocty liekov na sklade (ak je menej ako minimalne mnozstvo, treba objednat)

create or replace procedure get_medicine_under_min_amount_by_department(
    department varchar2,
    result_cursor out SYS_REFCURSOR)
is
begin
    if department = 'Vsetky' then
        open result_cursor for
        select nazov_oddelenia, kod_lieku, sum(mnozstvo), minimalne_mnozstvo from sklad_liekov_oddelenia 
            join oddelenie using(id_oddelenia)
                group by nazov_oddelenia, kod_lieku, minimalne_mnozstvo 
                having sum(mnozstvo) < minimalne_mnozstvo 
                order by kod_lieku;
    else
        open result_cursor for
        select kod_lieku, sum(mnozstvo), minimalne_mnozstvo from sklad_liekov_oddelenia 
            join oddelenie using(id_oddelenia)
                where nazov_oddelenia = department
                group by kod_lieku, minimalne_mnozstvo 
                having sum(mnozstvo) < minimalne_mnozstvo 
                order by kod_lieku;
    end if;
end;
/

-- vystup - pristroje, ktore musia byt servisovane v danom mesiaci

create or replace procedure get_machines_for_control_by_department(
    department varchar2,
    result_cursor out SYS_REFCURSOR)
is
begin
    if department = 'Vsetky' then
        open result_cursor for
            select id_pristroja, nazov_pristroja, servis, nazov_oddelenia from pristroj
                join oddelenie using(id_oddelenia)
                    where substr(to_char(servis),4,3) = substr(to_char(sysdate),4,3);
    else
        open result_cursor for
            select id_pristroja, nazov_pristroja, servis from pristroj
                join oddelenie using(id_oddelenia)
                    where substr(to_char(servis),4,3) = substr(to_char(sysdate),4,3) and
                    nazov_oddelenia = department;
    end if;
end;
/

-- vystup - pokazene pristroje, poslat do servisu a opravit ich

create or replace procedure get_non_functional_machines_by_department(
    department varchar2,
    proc out SYS_REFCURSOR)
is
begin
    if department = 'Vsetky' then
        open proc for
        select id_pristroja, nazov_pristroja, servis, nazov_oddelenia from pristroj
            join oddelenie using(id_oddelenia)
                where stav = 'n';
    else
        open proc for
        select id_pristroja, nazov_pristroja, servis from pristroj
            join oddelenie using(id_oddelenia)
                where stav = 'n' and
                nazov_oddelenia = department;
    end if;
end;
/

-- vystup - medicinske nastroje, ktore maju po zivotnosti

create or replace procedure get_expired_instruments_by_department(
    department varchar2,
    result_cursor out SYS_REFCURSOR)
is
begin
    if department = 'Vsetky' then
        open result_cursor for
        select id_nastroja, nazov_nastroja, zivotnost, nazov_oddelenia 
            from medicinsky_nastroj
                join oddelenie using(id_oddelenia)
                    where zivotnost <= sysdate;
    else
        open result_cursor for
        select id_nastroja, nazov_nastroja, zivotnost, nazov_oddelenia
            from medicinsky_nastroj
                join oddelenie using(id_oddelenia)
                    where zivotnost <= sysdate and
                    nazov_oddelenia = department;
    end if;
end;
/

-- vypisat lieky so zadanym atc (A, B, ...)
create or replace procedure get_medicine_by_atc(
    atc varchar2,
    result_cursor out SYS_REFCURSOR)
is
begin
    if atc = 'Vsetky' then
        open result_cursor for
        select lk.detail.nazov, lk.detail.atc, lk.detail.doplnok
            from liek lk;
    else
        open result_cursor for
        select lk.detail.nazov, lk.detail.atc, lk.detail.doplnok
            from liek lk
            where lk.detail.atc like upper(atc) || '%';
    end if;
end;
/

create or replace type xmlreporttab is table of xmltype;
/

create or replace function export_zdravotnych_kariet return xmlreporttab
is
    tabulka xmlreporttab;
begin
    tabulka := xmlreporttab();
    for zaznam in (select xmlelement("Osoba",
                                    xmlattributes(rod_cislo as "RC",
                                                    os_cislo_pacienta as "OC"),
                                    xmlelement("Meno", meno),
                                    xmlelement("Priezvisko", priezvisko),
                                    xmlelement("Krvna_skupina", krvna_skupina),
                                    xmlelement("Karta", 
                                            xmlattributes(id_karty as "ID_Karty"),
                                            xmlelement("Choroby", choroby),
                                            xmlelement("Ockovania", ockovania),
                                            xmlelement("Lieky", lieky),
                                            xmlelement("Lekarske_Ukony", lekarske_ukony))) as strom
                        from (select os.meno, os.priezvisko, os.rod_cislo, p.os_cislo_pacienta, p.krvna_skupina, zk.id_karty, 
                                    (select xmlagg(xmlelement("Choroba",
                                                                xmlattributes(zo_in.id_choroby as "ID_Choroby"),
                                                                xmlelement("Nazov", ch_in.nazov_choroby),
                                                                xmlelement("Kod", ch_in.kod_choroby)
                                                                )
                                                    )
                                    from choroba ch_in 
                                    join zoznam_ochoreni zo_in on (zo_in.id_choroby=ch_in.id_choroby)
                                    where zo_in.id_karty=zk.id_karty) as choroby,
                                    (select xmlagg(xmlelement("Ockovanie",
                                                                xmlattributes(oc_in.id_vakciny as "ID_Vakciny"),
                                                                xmlelement("Nazov", oc_in.nazov_ockovania),
                                                                xmlelement("Typ", oc_in.typ_ockovania)
                                                            )
                                                    )
                                    from ockovanie oc_in 
                                    join zoznam_ockovani zoc_in on (zoc_in.id_vakciny=oc_in.id_vakciny)
                                    where zoc_in.id_karty=zk.id_karty) as ockovania,
                                    (select xmlagg(xmlelement("Liek",
                                                                xmlattributes(zl_in.kod_lieku as "Kod_Lieku"),
                                                                xmlelement("Davkovanie", zl_in.davkovanie),
                                                                xmlelement("Datum_od", zl_in.datum_od)
                                                            )
                                                    )
                                    from zoznam_liekov zl_in 
                                    where zl_in.id_karty=zk.id_karty and zl_in.datum_do is null) as lieky,
                                    (select xmlagg(xmlelement("Lekarsky_Ukon",
                                                                xmlattributes(lu_in.id_ukonu as "ID_Ukonu",
                                                                    lu_in.id_oddelenia as "ID_Oddelenia"),
                                                                xmlelement("Nazov", lu_in.nazov_ukonu),
                                                                xmlelement("Datum_Vykonania", lu_in.datum_vykonania)
                                                            )
                                                    )
                                    from lekarsky_ukon lu_in 
                                    where lu_in.id_karty=zk.id_karty) as lekarske_ukony
                        from osoba os
                        join pacient p on (os.rod_cislo=p.rod_cislo)
                        join zdravotna_karta zk on(zk.os_cislo_pacienta=p.os_cislo_pacienta)))
        loop 
            tabulka.extend();
            tabulka(tabulka.last):=zaznam.strom;
        end loop;
                        
        return tabulka;
end;
/