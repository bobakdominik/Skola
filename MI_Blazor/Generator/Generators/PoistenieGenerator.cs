using System;
using System.Collections.Generic;
using System.Globalization;
using System.IO;
using System.Linq;
using Generator.Resources;

namespace Generator.Generators
{
    internal class Poistenie
    {
        public string OsCisloPacienta { get; set; }
        public string DatumOd { get; set; }
        public string TypPoistenia { get; set; }
        public string DatumDo { get; set; }
    }

    internal class PoistenieGenerator : Generator<Poistenie>
    {
        
        private readonly string _pacientFilePath;
        private readonly string[] _typPoistenia = new string[] {
        "urazove",
        "zdravotne"       
        };

        public PoistenieGenerator(string filePath, int numberOfRecords) : base("POISTENIE",
            "{0}, TO_DATE(\'{1}\', 'dd.mm.yyyy'), \'{2}\', TO_DATE(\'{3}\', 'dd.mm.yyyy')",
            Path.Combine(filePath, SQLRes.PoistenieFileName),
            numberOfRecords)
        {
            _pacientFilePath = Path.Combine(filePath, SQLRes.PacientFileName);
        }

        public override void Generate()
        {
            var pacientiStr = FileWriter.Read(_pacientFilePath).SkipLast(1).ToList();                      
            var poistenie = new List<Poistenie>();
            var num = pacientiStr.Count < _numberOfRecords ? pacientiStr.Count : _numberOfRecords;
            //var startNumber = 1;
            string date;
            string den;
            string mesiac;
            string rok;
            int result;
            string str2;
            DateTime birth;
            for (int i = 0; i < num; i++)
            {
                str2 = pacientiStr[i].Split("\'")[1].Split("\'")[0];
                rok = str2.Substring(0, 2);
                mesiac = str2.Substring(2, 2);
                result = Int32.Parse(mesiac) % 50;
                mesiac = result.ToString();
                if (mesiac.Length == 1)
                {
                    mesiac = "0" + mesiac;
                }
                den = str2.Substring(4, 2);
                str2 = rok + "." + mesiac + "." + den;
                birth = DateTime.ParseExact(str2, "yy.MM.dd",
                                       System.Globalization.CultureInfo.InvariantCulture);


                DateTime datOd;// = Common.RandomDay();
                                
                //while (DateTime.Compare(datOd, birth) <= 0)
                //{
                //datOd = Common.RandomDay();
                //}

                datOd = birth.AddDays(Common.RandomMinMax(10, 1000));


                DateTime datDo;// = Common.RandomDay();
                //while (DateTime.Compare(datOd, datDo) != 0 && (datDo - datOd).TotalDays < 10)
                //{
                //    datDo = Common.RandomDay();
                //}

                datDo = datOd.AddDays(Common.RandomMinMax(200, 5000));


                


                date = datDo.ToString("dd.MM.yyyy",
                    CultureInfo.InvariantCulture);
                if (Common.RandomPercentage() <= 20)
                {
                    date = "NULL";
                }

                poistenie.Add(new Poistenie()
                {
                    //IdPoistenca = startNumber++.ToString(),
                    TypPoistenia = _typPoistenia[Common.RND.Next(_typPoistenia.Length)],
                    OsCisloPacienta = pacientiStr[i].Split("(")[1].Split(",")[0],
                    DatumOd = datOd.ToString("dd.MM.yyyy",
                    CultureInfo.InvariantCulture),
                    DatumDo = date
                }) ;
            }
            var str = CreateStringCollection(poistenie);
            FileWriter.Write(str, _filePath);
        }

        public override List<string> CreateStringCollection(List<Poistenie> collection)
        {
            var res = new List<string>();
            foreach (var c in collection)
            {
                res.Add(string.Format(_insertStr, c.OsCisloPacienta.ToString(), c.DatumOd, c.TypPoistenia, c.DatumDo));
            }
            return res;
        }
    }
}
