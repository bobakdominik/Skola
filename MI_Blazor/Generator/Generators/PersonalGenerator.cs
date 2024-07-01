using Bogus;
using Generator.Resources;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;

namespace Generator.Generators
{
    internal class Personal
    {
        public int OsCislo { get; set; }
        public string RodCislo { get; set; }
        public int IdOddelenia { get; set; }
        public string TypPrace { get; set; }
        public DateTime DatumOd { get; set; }
        public DateTime? DatumDo { get; set; }
        public string PouzivatelskeMeno { get; set; }
        public string Heslo { get; set; }
    }

    internal class PersonalGenerator : Generator<Personal>
    {
        private readonly string _osobaFilePath;
        private readonly string _nemocnicaFilePath;
        

        public PersonalGenerator(string filePath, int numberOfRecords) : base("PERSONAL",
            "{0}, \'{1}\', {2}, \'{3}\', TO_DATE(\'{4}\', 'dd.mm.yy'), TO_DATE('{5}', 'dd.mm.yy'), '{6}', '{7}'",
            Path.Combine(filePath, SQLRes.PersonalFileName),
            numberOfRecords)
        {
            _osobaFilePath = Path.Combine(filePath, SQLRes.OsobaFileName);
            _nemocnicaFilePath = Path.Combine(filePath, SQLRes.NemocnicaFileName);
        }

        public override List<string> CreateStringCollection(List<Personal> collection)
        {
            var res = new List<string>();
            foreach (var item in collection)
            {
                res.Add(string.Format(_insertStr, item.OsCislo, item.RodCislo, item.IdOddelenia, item.TypPrace, item.DatumOd.ToString("dd.MM.yy"), item.DatumDo != null ? item.DatumDo?.ToString("dd.MM.yy") : "NULL", item.PouzivatelskeMeno, item.Heslo));
            }
            return res;
        }

        public override void Generate()
        {
            var osoby = OsobaGenerator.ConvertScriptToObject(FileWriter.Read(_osobaFilePath).SkipLast(1).ToList());
            var nemocnice = NemocnicaGenerator.ConvertScriptToObject(FileWriter.Read(_nemocnicaFilePath).SkipLast(1).ToList());
            var num = osoby.Count() < _numberOfRecords ? osoby.Count() : _numberOfRecords;
            var personal = new List<Personal>();
            int id = 1;
            int oddeleniaCount = Data.Oddelenia.Length * nemocnice.Count < num ? Data.Oddelenia.Length * nemocnice.Count : num;            
            for (int i = 0; i < oddeleniaCount; i++)
            {
                var osoba = osoby[i];
                if (Common.GetDateFromRodCislo(osoba.RodCislo).Year < DateTime.Now.Year - 20)
                {
                    var per = new Personal()
                    {
                        OsCislo = id++,
                        RodCislo = osoba.RodCislo,
                        IdOddelenia = i+1,// nemocnice[Common.RND.Next(nemocnice.Count())].IdNemocnice,
                        TypPrace = Data.TypPrace[0],
                        DatumOd = Common.RandomDay(Common.GetDateFromRodCislo(osoba.RodCislo).Year + 20),
                        DatumDo = (DateTime?) null,
                        PouzivatelskeMeno = osoba.RodCislo,
                        Heslo = String.Format("{0}{1}{2}", osoba.Meno[0], osoba.Priezvisko[0], osoba.RodCislo.Split("/").Last())
                    };
                    //if (Common.RND.Next(100) > 75 && per.DatumOd.Year < DateTime.Now.Year - 1)
                    //{
                    //    per.DatumDo = Common.RandomDay(per.DatumOd.Year + 1);
                    //}
                    personal.Add(per);
                }
            }
            for (int i = oddeleniaCount; i < num; i++)
            {
                if (i >= osoby.Count())
                {
                    break;
                }
                var osoba = osoby[i];
                if (Common.GetDateFromRodCislo(osoba.RodCislo).Year < DateTime.Now.Year - 20)
                {
                    var per = new Personal()
                    {
                        OsCislo = id++,
                        RodCislo = osoba.RodCislo,
                        IdOddelenia = Common.RND.Next(oddeleniaCount),// nemocnice[Common.RND.Next(nemocnice.Count())].IdNemocnice,
                        TypPrace = !osoba.Meno.EndsWith("a") ? Data.TypPrace[1] : Data.TypPrace[Common.RND.Next(Data.TypPrace.Length - 1) + 1],
                        DatumOd = Common.RandomDay(Common.GetDateFromRodCislo(osoba.RodCislo).Year + 20),
                        PouzivatelskeMeno = osoba.RodCislo,
                        Heslo = String.Format("{0}{1}{2}", osoba.Meno[0], osoba.Priezvisko[0], osoba.RodCislo.Split("/").Last())
                    };
                    if (Common.RND.Next(100) > 75 && per.DatumOd.Year < DateTime.Now.Year - 1)
                    {
                        per.DatumDo = Common.RandomDay(per.DatumOd.Year + 1);
                    }
                    personal.Add(per);
                }
            }
            FileWriter.Write(CreateStringCollection(personal), _filePath);
        }

        public static List<Personal> ConvertScriptToObject(List<string> list)
        {
            var res = new List<Personal>();
            foreach (var line in list)
            {
                var lines = line.Remove(line.Length - 3, 3)[(line.IndexOf("(") + 1)..].Replace("'", "").Split(", ");
                //var lines = line.Remove(line.Length - 3, 3).Split("(").Last().Replace("'", "").Split(", ");
                res.Add(new Personal()
                {
                    OsCislo = Convert.ToInt32(lines[0]),
                    RodCislo = lines[1],
                    IdOddelenia = Convert.ToInt32(lines[2]),
                    TypPrace = lines[3],
                    DatumOd = DateTime.ParseExact(lines[4].Split("(")[1], "dd.MM.yy",
                                           System.Globalization.CultureInfo.InvariantCulture),
                    DatumDo = lines[6].Split("(")[1] == "NULL" ? (DateTime?) null : DateTime.ParseExact(lines[6].Split("(")[1], "dd.MM.yy",
                                           System.Globalization.CultureInfo.InvariantCulture),
                    PouzivatelskeMeno = lines[8],
                    Heslo = lines[9]
                });
            }
            return res;
        }
    }
}
