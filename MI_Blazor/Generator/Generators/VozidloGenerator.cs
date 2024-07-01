using Generator.Resources;
using System;
using System.Collections.Generic;
using System.IO;
using System.Text;

namespace Generator.Generators
{
    internal class Vozidlo
    {
        public int IdVozidla { get; set; }
        public int IdNemocnice { get; set; }
        public string TypVozidla { get; set; }
        public int Kapacita { get; set; }
    }

    // TODO Vozidlo
    internal class VozidloGenerator : Generator<Vozidlo>
    {
        
        public VozidloGenerator(string filePath, int numberOfRecords) : base("VOZIDLO",
            "{0}, {1}, '{2}', {3}",
            Path.Combine(filePath, SQLRes.VozidloFileName),
            numberOfRecords)
        {
        }

        public override List<string> CreateStringCollection(List<Vozidlo> collection)
        {
            throw new NotImplementedException();
        }

        public override void Generate()
        {
            throw new NotImplementedException();
        }
    }
}
