using System;
using System.Collections.Generic;
using System.Globalization;
using System.IO;
using System.Linq;
using Generator.Resources;
using static Generator.Generators.ZoznamOchoreniGenerator;
using System.Collections;

namespace Generator.Generators
{
    internal class ZoznamOchoreniGenerator : Generator<ZoznamOchoreni>
    {
        internal class ZoznamOchoreni
        {
            public string IdChoroby { get; set; }
            public string IdKarty { get; set; }
            public string DatumOd { get; set; }
            public string DatumDo { get; set; }
        }
        private readonly string _chorobaFilePath;
        private readonly string _zdravotnaKartaFilePath;
        private readonly string _pacientFilePath;

        private readonly ArrayList _datumOd = new ArrayList();
        private readonly ArrayList _datumDo = new ArrayList();
        private readonly ArrayList _datDoDef = new ArrayList();
        private readonly ArrayList _idChoroby = new ArrayList();
        

        public ZoznamOchoreniGenerator(string filePath, int numberOfRecords) : base("ZOZNAM_OCHORENI",
            "{0}, {1}, TO_DATE('{2}', 'dd.mm.yyyy'), TO_DATE('{3}', 'dd.mm.yyyy')",
            Path.Combine(filePath, SQLRes.ZoznamOchoreniFileName),
            numberOfRecords)
        {
            _chorobaFilePath = Path.Combine(filePath, SQLRes.ChorobaFileName);
            _zdravotnaKartaFilePath = Path.Combine(filePath, SQLRes.ZdravotnaKartaFileName);
            _pacientFilePath = Path.Combine(filePath, SQLRes.PacientFileName);
        }

        public override void Generate()
        {
            var chorobyStr = FileWriter.Read(_chorobaFilePath).SkipLast(1).ToList();
            var zoznamOchoreni = new List<ZoznamOchoreni>();
            //var num = chorobyStr.Count < _numberOfRecords ? chorobyStr.Count : _numberOfRecords;
            int idChoroby;
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
            int pocetGenerovaniChorob;          

            for (int i = 0; i < zdravotneKartyStr.Count; i++)
            {
                if (Common.RandomPercentage() < 20)
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

                    pocetGenerovaniChorob = Common.RandomMinMax(1, 5);
                    for (int q = 0; q < pocetGenerovaniChorob; q++)
                    {
                        idChoroby = Common.RandomMinMax(0, chorobyStr.Count - 1);
                        while (_idChoroby.Contains(idChoroby))
                        {
                            idChoroby = Common.RandomMinMax(0, chorobyStr.Count - 1);
                        }

                        _idChoroby.Add(idChoroby);
                    }

                    for (int q = 0; q < pocetGenerovaniChorob; q++)
                    {
                        DateTime datOd;// = Common.RandomDay();
                        //while (DateTime.Compare(datOd, birth) <= 0 && !_datumOd.Contains(datOd))
                        //{
                        //    datOd = Common.RandomDay();
                        //}
                        datOd = birth.AddDays(Common.RandomMinMax(20, 5000));

                        if (_datumOd.Contains(datOd))
                        {
                            datOd = birth.AddDays(Common.RandomMinMax(20, 5000));
                        }

                        _datumOd.Add(datOd);
                    }

                    
                    foreach(DateTime dOd in _datumOd)
                    {
                        DateTime datDo;// = Common.RandomDay();
                        //while (DateTime.Compare(datDo, dOd) <= 0)
                        //{

                        //    datDo = Common.RandomDay();
                        //}


                        datDo = dOd.AddDays(Common.RandomMinMax(4, 1500));


                        _datumDo.Add(datDo);
                    }



                    foreach (DateTime dDo in _datumDo)
                    {
                        date = dDo.ToString("dd.MM.yyyy",
                           CultureInfo.InvariantCulture);
                        if (Common.RandomPercentage() <= 35)
                        {
                            date = "NULL";
                        }

                        _datDoDef.Add(date);
                    }


                    for (int q = 0; q < pocetGenerovaniChorob; q++)
                    {
                        int x = (int)_idChoroby[q];
                        var y = (DateTime)_datumOd[q];
                        var z = (string)_datDoDef[q];
                        zoznamOchoreni.Add(new ZoznamOchoreni()
                        {
                            IdChoroby = chorobyStr[x].Split("(")[1].Split(",")[0],
                            IdKarty = zdravotneKartyStr[i].Split("(")[1].Split(",")[0],
                            DatumOd = y.ToString("dd.MM.yyyy",
                            CultureInfo.InvariantCulture),
                            DatumDo = z
                        });
                    }
                    _datumOd.Clear();
                    _datumDo.Clear();
                    _idChoroby.Clear();
                    _datDoDef.Clear();
                }
                
            }
            var str = CreateStringCollection(zoznamOchoreni);
            FileWriter.Write(str, _filePath);
        }

        public override List<string> CreateStringCollection(List<ZoznamOchoreni> collection)
        {
            var res = new List<string>();
            foreach (var c in collection)
            {
                res.Add(string.Format(_insertStr, c.IdChoroby, c.IdKarty, c.DatumOd, c.DatumDo));
            }
            return res;
        }
    }
}
