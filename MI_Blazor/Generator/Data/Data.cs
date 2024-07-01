using System;
using System.Collections.Generic;
using System.Text;

namespace Generator
{
    internal class Data
    {
        private static readonly string[] _oddelenia = new string[]
        {
            "Urgentný príjem",
            "Centrálna sterilizácia",
            "Centrálne operačné sály",
            "Dermatovenerologická klinika",
            "Geriatrické a doliečovacie oddelenie",
            "Gynekologicko-pôrodnícka klinika",
            "Chirurgická klinika",
            "Klinika anesteziológie a intenzívnej medicíny",
            "Klinika vnútorného lekárstva I.",
            "Klinika vnútorného lekárstva II.",
            "Nemocničná lekáreň",
            "Neomatologická klinika",
            "Neurochirurgická klinika",
            "Neurologická klinika",
            "Klinika fyziatrie, balneológie a liečebnej rehabilitácie",
            "Klinika klinickej farmakológie",
            "Oddelenie klinickej onkológie",
            "Oddelenie liečebnej výživy a stravovania",
            "Oddelenie úrazovej chirurgie",
            "Oftalmologické oddelenie",
            "Ortopedické oddelenie",
            "Otorinolaryngologická klinika",
            "Patologické oddelenie",
            "Pediatrická klinika",
            "Psychiatrické oddelenie",
            "Rádiologické oddelenie",
            "Urologická klinika",
            "Ústav klinickej mikrobiológie",
            "Verejná lekáreň",
            "Oddelenie hygieny a epidemiológie"
        };
        private static readonly string[] _typPrace = new string[]
        {
            "Primár",
            "Lekár",
            "Sestrička"
        };

        private static readonly string[] _lekarskyUkon = new string[] {
        "zaťažovanie EKG pri fyzickej námahe",
        "echokardiografia komplexná",
        "transezofageálna echokardiografia",
        "vonkajšia elektroimpulzoterapia srdcového rytmu",
        "RTG vyšetrenie kostného thoraxu",
        "USG vyšetrenie brucha",
        "USG vyšetrenie hlbokého žilového systému",
        "CT hlavy",
        "CT v oblasti hrudníka",
        "CT pulmoangiografia",
        "MR v oblasti hlavy",
        "transfúzia erytrocytov",
        "mamografia",
        "RTG vyšetrenie lumbálnej chrbtice",
        "RTG vyšetrenie končatín",
        "monitorovanie perfúzie mozgu transkraniálnym dopplerom",
        "duplexné vyšetrenie tepien dolnej končatiny",
        "USG vyšetrenie prsníkov",
        "CT v oblasti malej panvy",
        "HRCT pľúc",
        "MR hrudníka",
        "MR srdca v pokoji",
        "MR hrudnej chrbtice",
        "MR chrbtice a miechy",
        "transfúzia trombocytov z celej krvi",
        "transfúzia plazmy čerstvo zmrazenej z celej krvi",
        "parciálna kolonoskopia",
        "diagnostická laparoskopia",
        "cystoskopia",
        "riadená umelá ventilácia pľúc",
        "nazotracheálna intubácia",
        "kontiuálne monitorovanie klinického stavu"
        };

        public static string[] Oddelenia => _oddelenia;
        public static string[] TypPrace => _typPrace;

        public static string[] LekarskyUkon => _lekarskyUkon;
    }
}
