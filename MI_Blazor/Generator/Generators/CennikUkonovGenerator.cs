using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using Generator.Resources;

namespace Generator.Generators
{
    internal class CennikUkonov
    {
        public DateTime DatumVykonania { get; set; }
        public int IdUkonu { get; set; }
        public int Cena { get; set; }        
    }

    internal class CennikUkonovGenerator : Generator<CennikUkonov>
    {
        private readonly string _ukonFilePath;
        public CennikUkonovGenerator(string filePath, int numberOfRecords) : base("CENNIK_UKONOV",
            "TO_DATE('{0}', 'dd.mm.yy HH:MI:ss'), {1}, {2}", 
            Path.Combine(filePath, SQLRes.CennikUkonovFileName),
            numberOfRecords)
        {
            _ukonFilePath = Path.Combine(filePath, SQLRes.LekarskyUkonFileName);
        }

        public override void Generate()
        {
            var ukony = LekarskyUkonGenerator.ConvertScriptToObject(FileWriter.Read(_ukonFilePath).SkipLast(1).ToList());
            var zoznamCennikov = new List<CennikUkonov>();                     
            foreach (var ukon in ukony)
            {
                zoznamCennikov.Add(new CennikUkonov()
                {   
                    DatumVykonania = ukon.DatumVykonania,
                    IdUkonu = ukon.IdUkonu,
                    Cena = Common.RandomMinMax(50,500)
                }) ;
                                     
            }
            var str = CreateStringCollection(zoznamCennikov);
            FileWriter.Write(str, _filePath);
        }
        public override List<string> CreateStringCollection(List<CennikUkonov> collection)
        {
            var res = new List<string>();
            foreach (var c in collection)
            {
                res.Add(string.Format(_insertStr, c.DatumVykonania.ToString("dd.MM.yy HH:mm:ss"), c.IdUkonu, c.Cena));
            }
            return res;
        }

        public static List<CennikUkonov> ConvertScriptToObject(List<string> list)
        {
            var res = new List<CennikUkonov>();
            foreach (var line in list)
            {
                var lines = line.Remove(line.Length - 3, 3)[(line.IndexOf("(") + 1)..].Replace("'", "").Split(", ");
                //var lines = line.Remove(line.Length - 3, 3).Split("(").Last().Replace("'", "").Split(", ");
                res.Add(new CennikUkonov()
                {
                    DatumVykonania = DateTime.ParseExact(lines[0].Split("(")[1], "dd.MM.yy HH:mm:ss",
                                           System.Globalization.CultureInfo.InvariantCulture),
                    IdUkonu = Convert.ToInt32(lines[2]),
                    Cena = Convert.ToInt32(lines[3])                    
                });
            }
            return res;
        }

    }
}
