using Generator.Resources;
using System.Collections.Generic;
using System.IO;

    namespace Generator.Generators
    {
    internal class Ockovanie
    {
        public string IdVakciny { get; set; }
        public string NazovOckovania { get; set; }
        public string TypOckovania { get; set; }
    }

    internal class OckovanieGenerator : Generator<Ockovanie>
    {
        private readonly string[] _ockovanie = new string[] {
        "Záškrt",
        "Tetanus",
        "Čierny kašeľ",
        "Haemofilus",
        "Detská obrna",
        "Žltačka B",
        "Pneumokok",
        "Osýpky",
        "Ružienka",
        "Covid-19"
        };

        private readonly string[] _typVakciny = new string[]
        {
        "Kombinovaná DTaP+VHB+HIB+IPV",
        "Kombinovaná DTaP+VHB+HIB+IPV",
        "Kombinovaná DTaP+VHB+HIB+IPV",
        "Kombinovaná DTaP+VHB+HIB+IPV",
        "Kombinovaná DTaP+VHB+HIB+IPV",
        "Kombinovaná DTaP+VHB+HIB+IPV",
        "13-valentná Adsorbovaná PCV",
        "Živá, oslabená",
        "MMR",
        "Vaxzervia"
        };
        public OckovanieGenerator(string filePath, int numberOfRecords) : base("OCKOVANIE",
            "{0}, '{1}', '{2}'",
            Path.Combine(filePath, SQLRes.OckovanieFileName),
            numberOfRecords)
        {
        }       

        public override void Generate()
        {         
            var ockovanie = new List<Ockovanie>();
            var num = _ockovanie.Length < _numberOfRecords ? _ockovanie.Length : _numberOfRecords;
            var startNumber = 1;

            for (int i = 0; i < num; i++)
            {
                ockovanie.Add(new Ockovanie()
                {
                    IdVakciny = startNumber++.ToString(),
                    NazovOckovania = _ockovanie[i],
                    TypOckovania = _typVakciny[i]
                });
            }
            var str = CreateStringCollection(ockovanie);
            FileWriter.Write(str, _filePath);
        }

        public override List<string> CreateStringCollection(List<Ockovanie> collection)
        {
            var res = new List<string>();
            foreach (var c in collection)
            {
                res.Add(string.Format(_insertStr, c.IdVakciny, c.NazovOckovania, c.TypOckovania));
            }
            return res;
        }
    }
}
