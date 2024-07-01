using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using Generator.Resources;

namespace Generator.Generators
{
    internal class Choroba
    {
        public string IdChoroby { get; set; }
        public string NazovChoroby { get; set; }
        public string KodChorooby { get; set; }
    }

    internal class ChorobaGenerator : Generator<Choroba>
    {
        
        private readonly string _zoznamChorob;
        public ChorobaGenerator(string filePath, int numberOfRecords) : base("CHOROBA",
            "{0}, \'{1}\', \'{2}\'",
            Path.Combine(filePath, SQLRes.ChorobaFileName),
            numberOfRecords)
        {
            _zoznamChorob = Path.Combine(filePath, SQLRes.ZoznamChorobFileName);
        }

        public override void Generate()
        {
            var choroby = FileWriter.Read(_zoznamChorob).SkipLast(0).ToList();
            var choroba = new List<Choroba>();
            var num = choroby.Count < _numberOfRecords ? choroby.Count : _numberOfRecords;
            var startNumber = 1;
            
            for (int i = 0; i < num; i++)
            {               
                choroba.Add(new Choroba()
                {
                    IdChoroby = startNumber++.ToString(),
                    NazovChoroby = choroby[i + 1].Split(";")[1].Replace("\r", "").Replace("\n", "").Replace("'", "''"),
                    KodChorooby = choroby[i + 1].Split(";")[0]
                });
            }
            var str = CreateStringCollection(choroba);
            FileWriter.Write(str, _filePath);
        }

        public override List<string> CreateStringCollection(List<Choroba> collection)
        {
            var res = new List<string>();
            foreach (var c in collection)
            {
                res.Add(string.Format(_insertStr, c.IdChoroby, c.NazovChoroby, c.KodChorooby));
            }
            return res;
        }
    }
}
