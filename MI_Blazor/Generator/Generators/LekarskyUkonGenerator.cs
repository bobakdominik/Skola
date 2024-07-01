using System;
using System.Collections;
using System.Collections.Generic;
using System.Globalization;
using System.IO;
using System.Linq;
using System.Text;
using Generator.Resources;

namespace Generator.Generators
{
    internal class LekarskyUkon
    {
        public int IdUkonu { get; set; }
        public string IdKarty { get; set; }
        public int IdOddelenia { get; set; }
        public DateTime DatumVykonania { get; set; }
        public string? Popis { get; set; }
        public string NazovUkonu { get; set; }
    }

    internal class LekarskyUkonGenerator : Generator<LekarskyUkon>
    {
        private readonly string _oddelenieFilePath;
        private readonly string _zdravotnaKartaFilePath;
        private readonly string _pacientFilePath;

        private readonly ArrayList _datumVykonania = new ArrayList();
        private readonly ArrayList _idUkonu = new ArrayList();

        public LekarskyUkonGenerator(string filePath, int numberOfRecords) : base("LEKARSKY_UKON",
            "{0}, {1}, {2}, TO_DATE('{3}', 'dd.mm.yy HH:MI:ss'), '{4}', '{5}'",
            Path.Combine(filePath, SQLRes.LekarskyUkonFileName),
            numberOfRecords)
        {
            _oddelenieFilePath = Path.Combine(filePath, SQLRes.OddelenieFileName);
            _zdravotnaKartaFilePath = Path.Combine(filePath, SQLRes.ZdravotnaKartaFileName);
            _pacientFilePath = Path.Combine(filePath, SQLRes.PacientFileName);
        }

        public override void Generate()
        {
            var lekarskyUkon = new List<LekarskyUkon>();           
            int idUkonu;
            int idUkonu2 = 1;
            var zdravotneKartyStr = FileWriter.Read(_zdravotnaKartaFilePath).SkipLast(1).ToList();
            var oddelenieStr = FileWriter.Read(_oddelenieFilePath).SkipLast(1).ToList();
            string osCisloPacientaZKarty;
            var pacientiStr = FileWriter.Read(_pacientFilePath).SkipLast(1).ToList();
            string str2;
            DateTime birth;
            string den;
            string mesiac;
            string rok;
            int result;
            int indexPacienta = 0;
            int pocetGenerovanychUkonov;
            int idOddelenia;

            for (int i = 0; i < zdravotneKartyStr.Count; i++)
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

                if (Int32.Parse(rok) >= 0 && Int32.Parse(rok) <= 22)
                {
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

                    pocetGenerovanychUkonov = Common.RandomMinMax(1, 3);
                    for (int q = 0; q < pocetGenerovanychUkonov; q++)
                    {
                        idUkonu = Common.RandomMinMax(0, Data.LekarskyUkon.Count() - 1);
                        while (_idUkonu.Contains(idUkonu))
                        {
                            idUkonu = Common.RandomMinMax(0, Data.LekarskyUkon.Count() - 1);
                        }
                        _idUkonu.Add(idUkonu);
                    }

                    for (int q = 0; q < pocetGenerovanychUkonov; q++)
                    {
                        DateTime datVykonania = Common.RandomDayWithHoursMinutesSeconds();
                        while (DateTime.Compare(datVykonania, birth) <= 0 && !_datumVykonania.Contains(datVykonania))
                        {
                            datVykonania = Common.RandomDayWithHoursMinutesSeconds();
                        }
                        _datumVykonania.Add(datVykonania);
                    }

                    for (int q = 0; q < pocetGenerovanychUkonov; q++)
                    {
                        idOddelenia = Common.RandomMinMax(1, oddelenieStr.Count);
                        int x = (int)_idUkonu[q];
                        var y = (DateTime)_datumVykonania[q];
                        lekarskyUkon.Add(new LekarskyUkon()
                        {
                            IdUkonu = x + 1,
                            IdKarty = zdravotneKartyStr[i].Split("(")[1].Split(",")[0],
                            IdOddelenia = idOddelenia,
                            DatumVykonania = y,
                            //Popis = ...
                            NazovUkonu = Data.LekarskyUkon[x]
                        });

                    }
                    _datumVykonania.Clear();
                    _idUkonu.Clear();

                    var str = CreateStringCollection(lekarskyUkon);
                    FileWriter.Write(str, _filePath);
                }
                else
                {
                    continue;
                }
            }
        }
        public override List<string> CreateStringCollection(List<LekarskyUkon> collection)
        {
            var res = new List<string>();
            foreach (var c in collection)
            {
                res.Add(string.Format(_insertStr, c.IdUkonu, c.IdKarty, c.IdOddelenia, c.DatumVykonania.ToString("dd.MM.yy HH:mm:ss"), c.Popis ?? "NULL", c.NazovUkonu));            
            }
            return res;
        }

        public static List<LekarskyUkon> ConvertScriptToObject(List<string> list)
        {
            var res = new List<LekarskyUkon>();
            foreach (var line in list)
            {
                var lines = line.Remove(line.Length - 3, 3)[(line.IndexOf("(") + 1)..].Replace("'", "").Split(", ");
                res.Add(new LekarskyUkon()
                {
                    IdUkonu = Convert.ToInt32(lines[0]),
                    IdKarty = lines[1],
                    IdOddelenia = Convert.ToInt32(lines[2]),
                    DatumVykonania = DateTime.ParseExact(lines[3].Split("(")[1], "dd.MM.yy HH:mm:ss",
                                          System.Globalization.CultureInfo.InvariantCulture),
                    Popis = lines[5] == "NULL" ? null: lines[5],
                    NazovUkonu = lines[6]
                });
            }
            return res;
        }
    }
}
