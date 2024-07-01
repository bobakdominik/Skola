using Generator.Resources;
using System;
using System.Collections.Generic;
using System.IO;
using System.Text;

namespace Generator.Generators
{
    internal class VyjazdovyTym
    {
        public int IdVozidla { get; set; }
        public int OsCisloPersonalu { get; set; }
    }

    // TODO VyjazdovyTym
    internal class VyjazdovyTymGenerator : Generator<VyjazdovyTym>
    {
        
        public VyjazdovyTymGenerator(string filePath, int numberOfRecords) : base("VYJAZDOVY_TYM", 
            "{0}, {1}",
            Path.Combine(filePath, SQLRes.VyjazdovyTymFileName),
            numberOfRecords)
        {
        }

        public override List<string> CreateStringCollection(List<VyjazdovyTym> collection)
        {
            throw new NotImplementedException();
        }

        public override void Generate()
        {
            throw new NotImplementedException();
        }

    }
}
