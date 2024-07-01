using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using Generator.Resources;
using Generator.Enums;

namespace Generator.Generators
{
    internal class Pacient
    {
        public int OsCislo { get; set; }
        public string RodCislo { get; set; }
        public int IdNemocnice { get; set; }
        public string KrvSkupina { get; set; }
        
    }

    internal class PacientGenerator : Generator<Pacient>
    {
        private readonly string[] _krv = new string[] {
        "A+",
        "A-",
        "B+",
        "B-",
        "AB+",
        "AB-",
        "0+",
        "0-"
        };

        private readonly string _osobaFilePath;
        
        private readonly int _osCisloLength = 6;

        public PacientGenerator(string filePath, int numberOfRecords) : base("PACIENT",
            "{0}, \'{1}\', {2}, '{3}'",
            Path.Combine(filePath, SQLRes.PacientFileName),
            numberOfRecords)
        {
            _osobaFilePath = Path.Combine(filePath, SQLRes.OsobaFileName);
        }

        public override void Generate()
        {
            var osobyStr = FileWriter.Read(_osobaFilePath).SkipLast(1).ToList();
            var pacienti = new List<Pacient>();
            var num = osobyStr.Count < _numberOfRecords ? osobyStr.Count : _numberOfRecords;
            for (int i = 0; i < num; i++)
            {
                pacienti.Add(new Pacient()
                {
                    OsCislo = Convert.ToInt32(Common.RandomDigits(_osCisloLength)),
                    RodCislo = osobyStr[i].Split("(")[1].Split("\'")[1],
                    IdNemocnice = 1,
                    KrvSkupina = _krv[Common.RND.Next(_krv.Length)]
                    //KrvSkupina = (BloodType)Common.RND.Next(Enum.GetNames(typeof(BloodType)).Length)
                });
            }
            var str = CreateStringCollection(pacienti);
            FileWriter.Write(str, _filePath);
        }

        public override List<string> CreateStringCollection(List<Pacient> collection)
        {
            var res = new List<string>();
            foreach (var c in collection)
            {
                res.Add(string.Format(_insertStr, c.OsCislo.ToString(), c.RodCislo, c.IdNemocnice, c.KrvSkupina));
            }
            return res;
        }

        public static List<Pacient> ConvertScriptToObject(List<string> list)
        {
            var res = new List<Pacient>();
            foreach (var line in list)
            {
                var lines = line.Remove(line.Length - 3, 3)[(line.IndexOf("(") + 1)..].Replace("'", "").Split(", ");
                res.Add(new Pacient()
                {
                    OsCislo = Convert.ToInt32(lines[0]),
                    RodCislo = lines[1],
                    IdNemocnice = Convert.ToInt32(lines[2]),
                    KrvSkupina = lines[2]
                });
            }
            return res;
        }
    }
}
