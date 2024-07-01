using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text.RegularExpressions;
using Generator.Resources;

namespace Generator.Generators
{
    internal class ZdravotnaKarta
    {
        public string IdKarty { get; set; }
        public string OsCisloPacienta { get; set; }
    }

    internal class ZdravotnaKartaGenerator : Generator<ZdravotnaKarta>
    {
        private readonly string _pacientFilePath;       

        public ZdravotnaKartaGenerator(string filePath, int numberOfRecords) : base("ZDRAVOTNA_KARTA",
            "{0}, {1}",
            Path.Combine(filePath, SQLRes.ZdravotnaKartaFileName),
            numberOfRecords)
        {
            _pacientFilePath = Path.Combine(filePath, SQLRes.PacientFileName);
        }

        public override void Generate()
        {
            var pacientiStr = FileWriter.Read(_pacientFilePath).SkipLast(1).ToList();
            var zdravotnaKarta = new List<ZdravotnaKarta>();
            var num = pacientiStr.Count < _numberOfRecords ? pacientiStr.Count : _numberOfRecords;
            var startNumber = 1001;           
            for (int i = 0; i < num; i++)
            {
                zdravotnaKarta.Add(new ZdravotnaKarta()
                {
                    IdKarty = startNumber++.ToString(),                   
                    OsCisloPacienta = pacientiStr[i].Split("(")[1].Split(",")[0]                    
                });
            }
            var str = CreateStringCollection(zdravotnaKarta);
            FileWriter.Write(str, _filePath);
        }

        public override List<string> CreateStringCollection(List<ZdravotnaKarta> collection)
        {
            var res = new List<string>();
            foreach (var c in collection)
            {
                res.Add(string.Format(_insertStr, c.IdKarty, c.OsCisloPacienta));
            }
            return res;
        }

        public static List<ZdravotnaKarta> ConvertScriptToObject(List<string> list)
        {
            var res = new List<ZdravotnaKarta>();
            foreach (var line in list)
            {
                var lines = line.Remove(line.Length - 3, 3)[(line.IndexOf("(") + 1)..].Replace("'", "").Split(", ");
                res.Add(new ZdravotnaKarta()
                {
                    IdKarty= lines[0],
                    OsCisloPacienta= lines[1]
                });
            }
            return res;
        }
    }
}
