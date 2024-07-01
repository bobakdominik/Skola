using System;
using System.Collections;
using System.Collections.Generic;
using System.Globalization;
using System.IO;
using System.Linq;
using Generator.Resources;

namespace Generator.Generators
{
    internal class ZoznamLiekov
    {
        public string DatumOd { get; set; }
        public string KodLieku { get; set; }
        public string IdKarty { get; set; }
        public string Davkovanie { get; set; }
        public string DatumDo { get; set; }
    }

    internal class ZoznamLiekovGenerator : Generator<ZoznamLiekov>
    {
        private readonly string _liekFilePath;
        private readonly string _zdravotnaKartaFilePath;
        private readonly string _pacientFilePath;

        private readonly ArrayList _datumOd = new ArrayList();
        private readonly ArrayList _datumDo = new ArrayList();
        private readonly ArrayList _datDoDef = new ArrayList();
        private readonly ArrayList _kodChoroby = new ArrayList();
        public ZoznamLiekovGenerator(string filePath, int numberOfRecords) : base("ZOZNAM_LIEKOV",
            "TO_DATE('{0}', 'dd.mm.yy'), '{1}', {2}, '{3}', TO_DATE('{4}', 'dd.mm.yy')", 
            Path.Combine(filePath, SQLRes.ZoznamLiekovFileName), 
            numberOfRecords)
        {
            _liekFilePath = Path.Combine(filePath, SQLRes.LiekFileName);
            _zdravotnaKartaFilePath = Path.Combine(filePath, SQLRes.ZdravotnaKartaFileName);
            _pacientFilePath = Path.Combine(filePath, SQLRes.PacientFileName);
        }
     
        public override void Generate()
        {
            var liekyStr = FileWriter.Read(_liekFilePath).SkipLast(1).ToList();
            var zoznamLiekov = new List<ZoznamLiekov>();
            //var num = chorobyStr.Count < _numberOfRecords ? chorobyStr.Count : _numberOfRecords;
            int kodChoroby;
            var zdravotneKartyStr = FileWriter.Read(_zdravotnaKartaFilePath).SkipLast(1).ToList();
            string osCisloPacientaZKarty;
            var pacientiStr = FileWriter.Read(_pacientFilePath).SkipLast(1).ToList();
            string str2;
            DateTime birth;
            string den;
            string mesiac;
            string rok;
            int result;
            string date;
            int indexPacienta = 0;
            int pocetGenerovaniLiekov = 0;
            int davka = 0;

            for (int i = 0; i < zdravotneKartyStr.Count; i++)
            {
                if (Common.RandomPercentage() < 35)
                {
                    continue;
                }
                else
                {
                    osCisloPacientaZKarty = zdravotneKartyStr[i].Split(",")[1].Split(")")[0];
                    string novyString = osCisloPacientaZKarty.Replace(" ", "");

                    for (int j = 0; j < zdravotneKartyStr.Count; j++)
                    {
                        if (novyString == pacientiStr[j].Split("(")[1].Split(",")[0])
                        {
                            indexPacienta = j;
                            break;
                        }
                    }

                    str2 = pacientiStr[indexPacienta].Split("\'")[1].Split("\'")[0];
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

                    pocetGenerovaniLiekov = Common.RandomMinMax(1, 5);
                    for (int q = 0; q < pocetGenerovaniLiekov; q++)
                    {
                        kodChoroby = Common.RandomMinMax(0, liekyStr.Count - 1);
                        while (_kodChoroby.Contains(kodChoroby))
                        {
                            kodChoroby = Common.RandomMinMax(0, liekyStr.Count - 1);
                        }

                        _kodChoroby.Add(kodChoroby);
                    }

                    for (int q = 0; q < pocetGenerovaniLiekov; q++)
                    {
                        DateTime datOd = Common.RandomDay();
                        while (DateTime.Compare(datOd, birth) <= 0 && !_datumOd.Contains(datOd))
                        {
                            datOd = Common.RandomDay();
                        }

                        _datumOd.Add(datOd);
                    }


                    foreach (DateTime dOd in _datumOd)
                    {
                        DateTime datDo = Common.RandomDay();
                        while (DateTime.Compare(datDo, dOd) <= 0)
                        {

                            datDo = Common.RandomDay();
                        }
                        _datumDo.Add(datDo);
                    }



                    foreach (DateTime dDo in _datumDo)
                    {
                        date = dDo.ToString("dd.MM.yy",
                           CultureInfo.InvariantCulture);
                        if (Common.RandomPercentage() <= 35)
                        {
                            date = "NULL";
                        }

                        _datDoDef.Add(date);
                    }

                    for (int q = 0; q < pocetGenerovaniLiekov; q++)
                    {
                        davka = Common.RandomMinMax(1, 4);
                        int x = (int)_kodChoroby[q];
                        var y = (DateTime)_datumOd[q];
                        var z = (string)_datDoDef[q];
                        zoznamLiekov.Add(new ZoznamLiekov()
                        {
                            DatumOd = y.ToString("dd.MM.yy",
                            CultureInfo.InvariantCulture),
                            KodLieku = liekyStr[1 + x].Split("'")[1].Split("'")[0],
                            IdKarty = zdravotneKartyStr[i].Split("(")[1].Split(",")[0],
                            Davkovanie = davka.ToString(),
                            DatumDo = z
                        });
                    }
                    _datumOd.Clear();
                    _datumDo.Clear();
                    _kodChoroby.Clear();
                    _datDoDef.Clear();
                }

            }
            var str = CreateStringCollection(zoznamLiekov);
            FileWriter.Write(str, _filePath);
        }

        public override List<string> CreateStringCollection(List<ZoznamLiekov> collection)
        {
            var res = new List<string>();
            foreach (var c in collection)
            {
                res.Add(string.Format(_insertStr, c.DatumOd, c.KodLieku, c.IdKarty, c.Davkovanie, c.DatumDo));
            }
            return res;
        }
    }
}
