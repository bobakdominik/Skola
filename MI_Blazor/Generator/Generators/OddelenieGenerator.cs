using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;
using Generator.Resources;

namespace Generator.Generators
{
    internal class Oddelenie
    {
        public int IdOddelenia { get; set; }
        public int IdNemocnice { get; set; }
        public string NazovOddelenia { get; set; }
        public string TypOddelenia { get; set; }
        public DateTime ZmenaOd { get; set; }
        public DateTime ZmenaDo { get; set; }
    }


    internal class OddelenieGenerator : Generator<Oddelenie>
    {
        
        private readonly string _nemocnicaFilePath;
        private readonly string _personalFilePath;


        public OddelenieGenerator(string filePath) : base("ODDELENIE", 
            "{0}, {1}, '{2}', '{3}', TO_DATE('{4}', 'HH24:MI'), TO_DATE('{5}', 'HH24:MI')",
            Path.Combine(filePath, SQLRes.OddelenieFileName),
            0)
        {
            _nemocnicaFilePath = Path.Combine(filePath, SQLRes.NemocnicaFileName);
            _personalFilePath = Path.Combine(filePath, SQLRes.PersonalFileName);
        }

        public override List<string> CreateStringCollection(List<Oddelenie> collection)
        {
            var res = new List<string>();
            foreach (var item in collection)
            {
                res.Add(string.Format(_insertStr, item.IdOddelenia, item.IdNemocnice, item.NazovOddelenia, item.TypOddelenia, item.ZmenaOd.ToString("HH:mm"),  item.ZmenaDo.ToString("HH:mm")));
            }
            return res;
        }

        public override void Generate()
        {
            var nemocnice = NemocnicaGenerator.ConvertScriptToObject(FileWriter.Read(_nemocnicaFilePath).SkipLast(1).ToList());
            var oddelenia = new List<Oddelenie>();
            foreach (var n in nemocnice)
            {
                for (int i = 0; i < Data.Oddelenia.Length; i++)
                {
                    oddelenia.Add(new Oddelenie() {
                        IdOddelenia = i + 1,
                        IdNemocnice = n.IdNemocnice,
                        NazovOddelenia = Data.Oddelenia[i],
                        TypOddelenia = Data.Oddelenia[i],
                        ZmenaOd = new DateTime(DateTime.Now.Year, 1, 1, Common.RND.Next(3) + 6, 0 , 0),
                        ZmenaDo = new DateTime(DateTime.Now.Year, 1, 1, Common.RND.Next(6) + 18, 0, 0),
                    });
                }
            }
            var str = CreateStringCollection(oddelenia);
            FileWriter.Write(str, _filePath);
        }

        public static List<Oddelenie> ConvertScriptToObject(List<string> list)
        {
            var res = new List<Oddelenie>();
            foreach (var line in list)
            { 
                var newLine = line.Remove(line.Length - 3, 3)[(line.IndexOf("(") + 1)..].Replace("'", "");
                var lines = Regex.Split(newLine, @"(, )(?=[']*[A-ZÁ-Ž0-9])");
                res.Add(new Oddelenie()
                {
                    IdOddelenia = Convert.ToInt32(lines[0]),
                    IdNemocnice = Convert.ToInt32(lines[2]),
                    NazovOddelenia = lines[4],
                    TypOddelenia = lines[6],
                    ZmenaOd = DateTime.ParseExact(lines[8].Split("(")[1], "HH:mm",
                                           System.Globalization.CultureInfo.InvariantCulture),
                    ZmenaDo = DateTime.ParseExact(lines[12].Split("(")[1], "HH:mm",
                                           System.Globalization.CultureInfo.InvariantCulture),
                });
            }
            return res;
        }
    }
}
