using Bogus;
using Generator.Resources;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;

namespace Generator.Generators
{
    internal class Nemocnica
    {
        public int IdNemocnice { get; set; }
        public string NazovNemocnice { get; set; }
        public string PSC { get; set; }
        public string Ulica { get; set; }
    }

    internal class NemocnicaGenerator : Generator<Nemocnica>
    {
        public NemocnicaGenerator(string filePath, int numberOfRecords) : base("NEMOCNICA", 
            "{0}, '{1}', '{2}', '{3}'", 
            Path.Combine(filePath, SQLRes.NemocnicaFileName),
            numberOfRecords)
        {
        }

        public override List<string> CreateStringCollection(List<Nemocnica> collection)
        {
            var res = new List<string>();
            foreach (var item in collection)
            {
                res.Add(string.Format(_insertStr, item.IdNemocnice, item.NazovNemocnice, item.PSC, item.Ulica));
            }
            return res;
        }

        public override void Generate()
        {
            var faker = new Faker<Nemocnica>("sk")
                .RuleFor(n => n.Ulica, f => f.Address.StreetAddress());
            var nemocnice = faker.Generate(_numberOfRecords - 1);
            var id = 1;
            foreach (var n in nemocnice)
            {
                n.PSC = Common.PSC[Common.RND.Next(Common.PSC.Length)];
                n.NazovNemocnice = String.Format("Nemocnica {0}", n.Ulica.Split(" ").First());
                n.IdNemocnice = id++;
            }
            nemocnice.Insert(0, new Nemocnica()
            {
                IdNemocnice = 1,
                NazovNemocnice = "Nemocnica u sv. Diega",
                Ulica = "Bábätkusova 1",
                PSC = Common.PSC[0]
            });
            FileWriter.Write(CreateStringCollection(nemocnice), _filePath);
        }

        public static List<Nemocnica> ConvertScriptToObject(List<string> list)
        {
            var res = new List<Nemocnica>();
            foreach (var line in list)
            {
                var lines = line.Remove(line.Length - 3, 3).Split("(").Last().Replace("'", "").Split(", ");
                res.Add(new Nemocnica()
                {
                    IdNemocnice = Convert.ToInt32(lines[0]),
                    NazovNemocnice = lines[1],
                    PSC = lines[2],
                    Ulica = lines[3]
                });
            }
            return res;
        }
    }
}
