using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using Generator.Resources;

namespace Generator.Generators
{
    internal class Lozko
    {
        public int CisloLozka { get; set; }
        public int IdOddelenia { get; set; }

    }

    internal class LozkoGenerator : Generator<Lozko>
    {
        private readonly string _oddeleniaFilePath;
        public LozkoGenerator(string filePath, int numberOfRecords) : base("LOZKO", 
            "{0}, {1}",
            Path.Combine(filePath, SQLRes.LozkoFileName),
            numberOfRecords)
        {
            _oddeleniaFilePath = Path.Combine(filePath, SQLRes.OddelenieFileName);
        }

        public override List<string> CreateStringCollection(List<Lozko> collection)
        {
            var res = new List<string>();
            foreach (var c in collection)
            {
                res.Add(string.Format(_insertStr, c.CisloLozka, c.IdOddelenia));
            }
            return res;
        }

        public override void Generate()
        {
            var lozka = new List<Lozko>();
            var oddelenia = OddelenieGenerator.ConvertScriptToObject(FileWriter.Read(_oddeleniaFilePath).SkipLast(1).ToList());

            for (int i = 0; i < _numberOfRecords; i++)
            {
                lozka.Add(new Lozko()
                {
                    CisloLozka = i,
                    IdOddelenia = oddelenia[Common.RND.Next(oddelenia.Count)].IdOddelenia
                });
            }
            var str = CreateStringCollection(lozka);
            FileWriter.Write(str, _filePath);
        }

        public static List<Lozko> ConvertScriptToObject(List<string> list)
        {
            var res = new List<Lozko>();
            foreach (var line in list)
            {
                var lines = line.Remove(line.Length - 3, 3)[(line.IndexOf("(") + 1)..].Replace("'", "").Split(", ");
                res.Add(new Lozko()
                {
                    CisloLozka = Convert.ToInt32(lines[0]),
                    IdOddelenia = Convert.ToInt32(lines[1])
                });
            }
            return res;
        }
    }
}
