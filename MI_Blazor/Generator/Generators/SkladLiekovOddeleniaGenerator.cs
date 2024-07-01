using System.Collections.Generic;
using System.IO;
using Generator.Resources;
using System.Linq;
using System.Globalization;
using System;

namespace Generator.Generators
{
    internal class SkladLiekovOddelenia
    {
        public string IdSkladu { get; set; }
        public string DatumExpiracie { get; set; }
        public string KodLieku { get; set; }
        public string IdOddelenia { get; set; }
        public string Mnozstvo { get; set; }
        public string MinMnozstvo { get; set; }      
    }

    internal class SkladLiekovOddeleniaGenerator : Generator<SkladLiekovOddelenia>
    {
        private readonly string _oddelenieFilePath;
        private readonly string _liekFilePath;
        public SkladLiekovOddeleniaGenerator(string filePath, int numberOfRecords) : base("SKLAD_LIEKOV_ODDELENIA",
            "{0}, '{1}', {2}, {3}, {4}, TO_DATE('{5}', 'dd.mm.yy')", 
            Path.Combine(filePath, SQLRes.SkladLiekovOddeleniaFileName), 
            numberOfRecords)
        {
            _liekFilePath = Path.Combine(filePath, SQLRes.LiekFileName);
            _oddelenieFilePath = Path.Combine(filePath, SQLRes.OddelenieFileName);          
        }

        public override void Generate()
        {
            var liekyStr = FileWriter.Read(_liekFilePath).SkipLast(1).ToList();
            var oddelenieStr = FileWriter.Read(_oddelenieFilePath).SkipLast(1).ToList();
            var skladLiekov = new List<SkladLiekovOddelenia>();
            //var num = chorobyStr.Count < _numberOfRecords ? chorobyStr.Count : _numberOfRecords;         
            int mnozstvo;
            int minMnozstvo;
            DateTime datumSpotreby;

            for (int i = 0; i < oddelenieStr.Count; i++)
            {
                for (int j = 0; j < liekyStr.Count; j++)
                {
                    if (Common.RandomPercentage() < 99)
                    {
                        continue;
                    }
                    else
                    {
                        

                        if (Common.RandomPercentage() <= 50)
                        {
                            datumSpotreby = DateTime.Now.AddDays(Common.RandomMinMax(1, 1500));
                        }
                        else
                        {
                            datumSpotreby = DateTime.Now.AddDays(-Common.RandomMinMax(1, 1500));
                        }

                        mnozstvo = Common.RandomMinMax(0, 20);
                        minMnozstvo = Common.RandomMinMax(1, 10);
                        skladLiekov.Add(new SkladLiekovOddelenia()
                        {
                            IdSkladu = (i+1).ToString(),
                            DatumExpiracie = datumSpotreby.ToString("dd.MM.yy",
                            CultureInfo.InvariantCulture),
                            KodLieku = liekyStr[j].Split("'")[1].Split("'")[0],
                            IdOddelenia = oddelenieStr[i].Split("(")[1].Split(",")[0],
                            Mnozstvo = mnozstvo.ToString(),
                            MinMnozstvo = minMnozstvo.ToString()                           
                        });;
                    }
                }
            }
            var str = CreateStringCollection(skladLiekov);
            FileWriter.Write(str, _filePath);
        }

        public override List<string> CreateStringCollection(List<SkladLiekovOddelenia> collection)
        {
            var res = new List<string>();
            foreach (var c in collection)
            {
                res.Add(string.Format(_insertStr, c.IdSkladu, c.KodLieku, c.IdOddelenia, c.Mnozstvo, c.MinMnozstvo, c.DatumExpiracie));
            }
            return res;
        }
    }
}
