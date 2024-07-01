using System;
using System.Collections.Generic;
using System.Globalization;
using System.IO;
using System.Linq;
using Generator.Resources;

namespace Generator.Generators
{
    internal class Pristroj
    {
        public string IdPristroja { get; set; }
        public string IdOddelenia { get; set; }
        public string Nazov { get; set; }
        public string Stav { get; set; }
        public string Servis { get; set; }
    }

    internal class PristrojGenerator : Generator<Pristroj>
    {
        private readonly string _oddelenieFilePath;

        private readonly string[] _funkcnostPristroja = new string[]
        {
            "f", //funckny
            "n" //nefunckny
        }; 

        //treba este pretridit co je pristroj a co medicinsky nastroj
        private readonly string[] _pristroje = new string[] {
        "teplomer bez ortuti",
        "teplomer digitálny",
        "teplomer ušný",
        "teplomer bezkontaktný",
        "teplomer flexibilný",
        "svetlo na zobrazenie žíl",
        "lampa s modrým svetlom ručná",
        "glukomer",
        "CRP",
        "hematologický automat",
        "laboratórna centrifúga",
        "malý laboratoórny inkubátor",
        "mikroskop s fáz. kontrastom",
        "binokulárny mikroskop",
        "anoskop",
        "anoskop plastový",
        "proktoskop",
        "sigmoidoskop",
        "svetelný kábel",
        "spirometer",
        "smokerlyzer",
        "výdychomer",
        "trenažér pľúc",
        "audiometrické komory",
        "audiometer",
        "tympanometer",
        "trenažér pľúc",
        "tonometer s rovnou stupnicou",
        "tonometer so šikmou stupnicou",
        "alkoholtester",
        "chladnička na lieky",
        "teplomer do chladničky",
        "hustomer kostí",
        "dynamometer",
        "footscan",
        "ultrazvuk",
        "EKG",
        "EKG holter",
        "ABPM holter",
        "monitor spánku",
        "pulzoximeter",
        "sterilizátor",
        "ultrazvuková čistička",
        "zariadenie na čistenie a dezinfekciu",
        "fonendoskop",
        "tlakomer",
        "váha",
        "výškomer",
        "otoskop",
        "dermatoskop",
        "oftalmoskop",
        "oftalmometer",
        "kolposkop",
        "elektrokauter",
        "fyzioterapeutický prístroj",
        "biolampa",
        "defibrilátor",
        "dýchací vak",
        "odsávačka",
        "inhalátor",
        "čistička vzduchu",
        "infúzna pumpa",
        "CT prístroj",
        "RTG prístroj",
        "MR prístroj"
        };
        public PristrojGenerator(string filePath, int numberOfRecords) : base("PRISTROJ",
            "{0}, {1}, '{2}', '{3}', TO_DATE('{4}', 'dd.mm.yy')", 
            Path.Combine(filePath, SQLRes.PristrojFileName),
            numberOfRecords)
        {
            _oddelenieFilePath = Path.Combine(filePath, SQLRes.OddelenieFileName);
        }   

        public override void Generate()
        {
            var oddelenieStr = FileWriter.Read(_oddelenieFilePath).SkipLast(1).ToList();
            var pristroje = new List<Pristroj>();
            var num = _numberOfRecords;
            var startNumber = 1;
            DateTime today;
            int idOddelenia;
            for (int i = 0; i < num; i++)
            {
                idOddelenia = Common.RandomMinMax(1, oddelenieStr.Count);
                today = DateTime.Now.AddDays(Common.RandomMinMax(150, 500));
                pristroje.Add(new Pristroj()
                {
                    IdPristroja = startNumber++.ToString(),
                    IdOddelenia = idOddelenia.ToString(),
                    Nazov = _pristroje[Common.RND.Next(_pristroje.Length)],
                    Stav = _funkcnostPristroja[Common.RND.Next(_funkcnostPristroja.Length)],
                    Servis = today.ToString("dd.MM.yy",
                    CultureInfo.InvariantCulture)
                });
            }
            var str = CreateStringCollection(pristroje);
            FileWriter.Write(str, _filePath);
        }

        public override List<string> CreateStringCollection(List<Pristroj> collection)
        {
            var res = new List<string>();
            foreach (var c in collection)
            {
                res.Add(string.Format(_insertStr, c.IdPristroja, c.IdOddelenia, c.Nazov, c.Stav, c.Servis));
            }
            return res;
        }
    }
}
