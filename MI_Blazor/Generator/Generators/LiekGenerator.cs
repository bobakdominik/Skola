using System.Collections.Generic;
using System.IO;
using Generator.Resources;
using System.Linq;
using System;
using System.Globalization;

namespace Generator.Generators
{
    internal class Liek
    {
        public string KodLieku { get; set; } //PK
        public string ATC { get; set; }
        public string Predpis { get; set; }
        public string Nazov { get; set; }
        public string Doplnok { get; set; }
        public string Standartna_davka_lieku { get; set; }
        public string Cena { get; set; }
        //public string DatumSpotreby { get; set; }
    }

    internal class LiekGenerator : Generator<Liek>
    {
        private readonly string _zoznamLiekov;
       
        public LiekGenerator(string filePath, int numberOfRecords) : base("LIEK",
            "'{0}', detail('{1}', '{2}', '{3}', '{4}', '{5}', {6})",
            Path.Combine(filePath, SQLRes.LiekFileName),
            numberOfRecords)
        {
            _zoznamLiekov = Path.Combine(filePath, SQLRes.ZoznamLiekovFileName2);
        }

        public override void Generate()
        {
            var lieky = FileWriter.Read(_zoznamLiekov).SkipLast(0).ToList();
            var liek = new List<Liek>();
            var num = lieky.Count < _numberOfRecords ? lieky.Count : _numberOfRecords;
            //DateTime datumSpotreby;
            for (int i = 0; i < num; i++)
            {
                //datumSpotreby = DateTime.Now.AddDays(Common.RandomMinMax(300, 800));
                liek.Add(new Liek()
                {
                    KodLieku = lieky[i + 1].Split(";")[1],                
                    ATC = lieky[i + 1].Split(";")[0],
                    Predpis = lieky[i + 1].Split(";")[2],
                    Nazov = lieky[i + 1].Split(";")[3],
                    Doplnok = lieky[i + 1].Split(";")[4],
                    Cena = lieky[i + 1].Split(";")[5].Replace(",", "."),
                    Standartna_davka_lieku = lieky[i + 1].Split(";")[6] + " " + lieky[i + 1].Split(";")[7].Replace("\r", "").Replace("\n", "").Replace("'", "''")
                    //DatumSpotreby = datumSpotreby.ToString("dd.MM.yy",
                            //CultureInfo.InvariantCulture)
                });
            }
            
            foreach (var l in liek)
            {
                if (l.Predpis == "")
                {
                    l.Predpis = "n";
                }
                else
                {
                    l.Predpis = "a";
                }
            }

            var str = CreateStringCollection(liek);
            FileWriter.Write(str, _filePath);
        }
        public override List<string> CreateStringCollection(List<Liek> collection)
        {
            var res = new List<string>();
            foreach (var c in collection)
            {
                res.Add(string.Format(_insertStr, c.KodLieku, c.ATC, c.Predpis, c.Nazov, c.Doplnok, c.Standartna_davka_lieku, c.Cena));
            }
            return res;
        }
    }
}
