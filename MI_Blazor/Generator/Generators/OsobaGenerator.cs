using Bogus;
using System;
using System.Collections.Generic;
using System.IO;
using Generator.Resources;
using System.Linq;

namespace Generator.Generators
{
    internal class Osoba
    {
        public string RodCislo { get; set; }
        public string Meno { get; set; }
        public string Priezvisko { get; set; }
        public string PSC { get; set; }
        public string Ulica { get; set; }
    }
    internal class OsobaGenerator : Generator<Osoba>
    {

        private readonly string _nemocnicaFilePath;

        public OsobaGenerator(string filePath, int numberOfRecords) : base("OSOBA",
            "\'{0}\', \'{1}\', \'{2}\', \'{3}\', \'{4}\'",
            Path.Combine(filePath, SQLRes.OsobaFileName),
            numberOfRecords)
        {
            _nemocnicaFilePath = Path.Combine(filePath, SQLRes.NemocnicaFileName);
        }

        public override void Generate()
        {
            var faker = new Faker<Osoba>("sk")
               .RuleFor(o => o.Meno, f => f.Name.FirstName())
               .RuleFor(o => o.Priezvisko, f => f.Name.LastName())
               .RuleFor(o => o.Ulica, f => f.Address.StreetName() + " " + f.Address.BuildingNumber());
            
            var nemocnice = NemocnicaGenerator.ConvertScriptToObject(FileWriter.Read(_nemocnicaFilePath).SkipLast(1).ToList());
            var oddeleniaCount = Data.Oddelenia.Length * nemocnice.Count;
            var osoba = faker.Generate(_numberOfRecords + oddeleniaCount);
            for (int i = 0; i < oddeleniaCount; i++)
            {
                DateTime datum = Common.RandomDay(DateTime.Now.Year-20, false);
                var mesiac = ((osoba[i].Meno[^1..] == "a") ? datum.Month + 50 : datum.Month).ToString();
                var rodCislo = datum.Year.ToString().Substring(2, 2) +
                        (mesiac.Length == 1 ? "0" + mesiac : mesiac).ToString() +
                        (datum.Day.ToString().Length < 2 ? "0" + datum.Day.ToString() : datum.Day.ToString()) +
                        "/" +
                        Common.RandomDigits(4);
                osoba[i].Priezvisko = (!osoba[i].Meno.EndsWith("a") && (osoba[i].Priezvisko.EndsWith("ová") || osoba[i].Priezvisko.EndsWith("á"))) ? osoba[i].Priezvisko.Replace("ová", "").Replace("á", "ý") : osoba[i].Priezvisko;
                osoba[i].PSC = Common.PSC[Common.RND.Next(Common.PSC.Length - 1)];
                osoba[i].RodCislo = rodCislo;
            }
            foreach (var o in osoba.Skip(oddeleniaCount))
            {
                DateTime datum = Common.RandomDay();
                var mesiac = ((o.Meno[^1..] == "a") ? datum.Month + 50 : datum.Month).ToString();
                var rodCislo = datum.Year.ToString().Substring(2, 2) +
                        (mesiac.Length == 1 ? "0" + mesiac : mesiac).ToString() +
                        (datum.Day.ToString().Length < 2 ? "0" + datum.Day.ToString() : datum.Day.ToString()) +
                        "/" +
                        Common.RandomDigits(4);
                o.Priezvisko = (!o.Meno.EndsWith("a") && (o.Priezvisko.EndsWith("ová") || o.Priezvisko.EndsWith("á"))) ? o.Priezvisko.Replace("ová", "").Replace("á", "ý") : o.Priezvisko;
                o.PSC = Common.PSC[Common.RND.Next(Common.PSC.Length - 1)];
                o.RodCislo = rodCislo;
            }
            var str = CreateStringCollection(osoba);
            FileWriter.Write(str, _filePath);
        }


        public override List<string> CreateStringCollection(List<Osoba> osoby)
        {
            var res = new List<string>();
            foreach (var o in osoby)
            {
                res.Add(string.Format(_insertStr, o.RodCislo, o.Meno, o.Priezvisko, o.PSC, o.Ulica));
            }
            return res;
        }

        public static List<Osoba> ConvertScriptToObject(List<string> list)
        {
            var res = new List<Osoba>();
            foreach (var line in list)
            {
                var lines = line.Remove(line.Length - 3, 3).Split("(").Last().Replace("'", "").Split(", ");
                res.Add(new Osoba()
                {
                    RodCislo = lines[0],
                    Meno = lines[1],
                    Priezvisko = lines[2],
                    PSC = lines[3],
                    Ulica = lines[4]
                });
            }
            return res;
        }
    }
}
