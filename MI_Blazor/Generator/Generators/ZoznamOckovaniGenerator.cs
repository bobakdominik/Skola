using System;
using System.Collections;
using System.Collections.Generic;
using System.Globalization;
using System.IO;
using System.Linq;
using Generator.Resources;

namespace Generator.Generators
{
    internal class ZoznamOckovani
    {
        public string DatumOd { get; set; }
        public string IdVakciny { get; set; }
        public string IdKarty { get; set; }
        public string DatumDo { get; set; }
    }
    internal class ZoznamOckovaniGenerator : Generator<ZoznamOckovani>
    {
        private readonly string _ockovanieFilePath;
        private readonly string _zdravotnaKartaFilePath;
        private readonly string _pacientFilePath;

        private readonly ArrayList _datumOd = new ArrayList();
        private readonly ArrayList _datumDo = new ArrayList();
        private readonly ArrayList _datDoDef = new ArrayList();
        private readonly ArrayList _idVakciny = new ArrayList();
        public ZoznamOckovaniGenerator(string filePath, int numberOfRecords) : base("ZOZNAM_OCKOVANI",
            "TO_DATE('{0}', 'dd.mm.yyyy'), {1}, {2}, TO_DATE('{3}', 'dd.mm.yyyy')", 
            Path.Combine(filePath, SQLRes.ZoznamOckovaniFileName), 
            numberOfRecords)
        {
            _ockovanieFilePath = Path.Combine(filePath, SQLRes.OckovanieFileName);
            _zdravotnaKartaFilePath = Path.Combine(filePath, SQLRes.ZdravotnaKartaFileName);
            _pacientFilePath = Path.Combine(filePath, SQLRes.PacientFileName);
        }

        public override void Generate()
        {
            var ockovanieStr = FileWriter.Read(_ockovanieFilePath).SkipLast(1).ToList();
            var zoznamOckovani = new List<ZoznamOckovani>();
            //var num = chorobyStr.Count < _numberOfRecords ? chorobyStr.Count : _numberOfRecords;
            int idVakciny;
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
            int pocetGenerovanychOckovani;

            for (int i = 0; i < zdravotneKartyStr.Count; i++)
            {
                if (Common.RandomPercentage() < 30)
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

                    pocetGenerovanychOckovani = Common.RandomMinMax(1, 5);
                    for (int q = 0; q < pocetGenerovanychOckovani; q++)
                    {
                        idVakciny = Common.RandomMinMax(0, ockovanieStr.Count - 1);
                        while (_idVakciny.Contains(idVakciny))
                        {
                            idVakciny = Common.RandomMinMax(0, ockovanieStr.Count - 1);
                        }

                        _idVakciny.Add(idVakciny);
                    }

                    for (int q = 0; q < pocetGenerovanychOckovani; q++)
                    {
                        DateTime datOd;// = Common.RandomDay();
                        //while (DateTime.Compare(datOd, birth) <= 0 && !_datumOd.Contains(datOd))
                        //{
                        //    datOd = Common.RandomDay();
                        //}

                        datOd = birth.AddDays(Common.RandomMinMax(100, 5000));

                        if (_datumOd.Contains(datOd))
                        {
                            datOd = birth.AddDays(Common.RandomMinMax(20, 5000));
                        }


                        _datumOd.Add(datOd);
                    }


                    foreach (DateTime dOd in _datumOd)
                    {
                        DateTime datDo;// = Common.RandomDay();
                        //while (DateTime.Compare(datDo, dOd) <= 0)
                        //{

                        //    datDo = Common.RandomDay();
                        //}

                        datDo = dOd.AddDays(Common.RandomMinMax(4, 8000));

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


                    for (int q = 0; q < pocetGenerovanychOckovani; q++)
                    {
                        int x = (int)_idVakciny[q];
                        var y = (DateTime)_datumOd[q];
                        var z = (string)_datDoDef[q];
                        zoznamOckovani.Add(new ZoznamOckovani()
                        {
                            DatumOd = y.ToString("dd.MM.yyyy",
                            CultureInfo.InvariantCulture),
                            IdVakciny = ockovanieStr[x].Split("(")[1].Split(",")[0],
                            IdKarty = zdravotneKartyStr[i].Split("(")[1].Split(",")[0],                        
                            DatumDo = z
                        });
                    }
                    _datumOd.Clear();
                    _datumDo.Clear();
                    _idVakciny.Clear();
                    _datDoDef.Clear();                   
                }

            }
            var str = CreateStringCollection(zoznamOckovani);
            FileWriter.Write(str, _filePath);
        }

        public override List<string> CreateStringCollection(List<ZoznamOckovani> collection)
        {
            var res = new List<string>();
            foreach (var c in collection)
            {
                res.Add(string.Format(_insertStr, c.DatumOd, c.IdVakciny, c.IdKarty, c.DatumDo));
            }
            return res;
        }
    }
}
