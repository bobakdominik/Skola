using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using Generator.Resources;

namespace Generator.Generators
{
    internal class Platba
    {
        public int IdPlatby { get; set; }
        public int IdUkonu { get; set; }
        public int Suma { get; set; }
        public DateTime Datum { get; set; }
        public DateTime DatumVykonania { get; set; }
    }

    internal class PlatbaGenerator : Generator<Platba>
    {
        private readonly string _ukonFilePath;
        private readonly string _cennikFilePath;

        public PlatbaGenerator(string filePath, int numberOfRecords) : base("PLATBA",
            "{0}, {1}, {2}, TO_DATE('{3}', 'dd.mm.yy'), TO_DATE('{4}', 'dd.mm.yy HH:MI:ss')",
            Path.Combine(filePath, SQLRes.PlatbaFileName),
            numberOfRecords)
        {
            _ukonFilePath = Path.Combine(filePath, SQLRes.LekarskyUkonFileName);
            _cennikFilePath = Path.Combine(filePath, SQLRes.CennikUkonovFileName);
        }

        public override List<string> CreateStringCollection(List<Platba> collection)
        {
            var res = new List<string>();
            foreach (var item in collection)
            {
                res.Add(string.Format(_insertStr, item.IdPlatby, item.IdUkonu, item.Suma, item.Datum.ToString("dd.MM.yy "), item.DatumVykonania.ToString("dd.MM.yy HH:mm:ss")));
            }
            return res;
        }

        public override void Generate()
        {
            var ukony = LekarskyUkonGenerator.ConvertScriptToObject(FileWriter.Read(_ukonFilePath).SkipLast(1).ToList());
            var cenniky = CennikUkonovGenerator.ConvertScriptToObject(FileWriter.Read(_cennikFilePath).SkipLast(1).ToList());
            var platby = new List<Platba>();
            int id = 1;
            foreach (var ukon in ukony.SkipLast(ukony.Count() - _numberOfRecords))
            {
                if (ukon.DatumVykonania > DateTime.Now.AddMonths(-6) && Common.RND.Next(100) > 35)
                {
                    continue;
                }
                var cena = cenniky.Where(c => c.IdUkonu == ukon.IdUkonu && c.DatumVykonania <= ukon.DatumVykonania).FirstOrDefault();
                var c = cenniky.Where(c => c.IdUkonu == ukon.IdUkonu);
                platby.Add(new Platba()
                {
                    IdPlatby = id++,
                    IdUkonu = ukon.IdUkonu,
                    Suma = cena.Cena,
                    Datum = ukon.DatumVykonania.AddDays(Common.RND.Next(25)),
                    DatumVykonania = ukon.DatumVykonania
                });
            }
            FileWriter.Write(CreateStringCollection(platby), _filePath);
        }
    }
}
