using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using Generator.Resources;

namespace Generator.Generators
{
    internal class ZabrateLozka
    {
        public int OsCisloPacienta { get; set; }
        public int CisloLozka { get; set; }
        public DateTime DatumOd { get; set; }
        public DateTime? DatumDo { get; set; }
    }

    internal class ZabrateLozkaGenerator : Generator<ZabrateLozka>
    {
        private readonly string _lozkoFilePath;
        private readonly string _pacientFilePath;
        public ZabrateLozkaGenerator(string filePath, int numberOfRecords) : base("ZABRATE_LOZKA",
            "{0}, {1}, TO_DATE('{2}', 'dd.mm.yy'), TO_DATE('{3}', 'dd.mm.yy')",
            Path.Combine(filePath, SQLRes.ZabrateLozkaFileName),
            numberOfRecords)
        {
            _lozkoFilePath = Path.Combine(filePath, SQLRes.LozkoFileName);
            _pacientFilePath = Path.Combine(filePath, SQLRes.PacientFileName);
        }

        public override List<string> CreateStringCollection(List<ZabrateLozka> collection)
        {
            var res = new List<string>();
            foreach (var c in collection)
            {
                res.Add(string.Format(_insertStr, c.OsCisloPacienta, c.CisloLozka, c.DatumOd.ToString("dd.MM.yy"), c.DatumDo != null ? c.DatumDo?.ToString("dd.MM.yy") : "NULL"));
            }
            return res;
        }

        public override void Generate()
        {
            var dic = new Dictionary<int, List<ZabrateLozka>>();
            var pacienti = PacientGenerator.ConvertScriptToObject(FileWriter.Read(_pacientFilePath).SkipLast(1).ToList());
            var lozka = LozkoGenerator.ConvertScriptToObject(FileWriter.Read(_lozkoFilePath).SkipLast(1).ToList());
            for (int i = 0; i < _numberOfRecords; i++)
            {
                var lozko = new ZabrateLozka()
                {
                    CisloLozka = lozka[Common.RND.Next(lozka.Count)].CisloLozka,
                    OsCisloPacienta = pacienti[Common.RND.Next(pacienti.Count)].OsCislo,
                    DatumOd = Common.RandomDay(DateTime.Now.Year - 5)
                };
                if (dic.ContainsKey(lozko.CisloLozka))
                {
                    var datum = dic[lozko.CisloLozka].Last().DatumOd;
                    lozko.DatumDo = Common.RandomDay(datum.Year, datum.Month, datum.Day , false);
                    lozko.DatumOd = Common.RandomDay((int)lozko.DatumDo?.Year, (int)lozko.DatumDo?.Month, (int)lozko.DatumDo?.Day, false);
                }
                else
                {
                    lozko.DatumDo = null;
                    dic[lozko.CisloLozka] = new List<ZabrateLozka>();
                }
                dic[lozko.CisloLozka].Add(lozko);
            }
            var zabrateLozka = new List<ZabrateLozka>();
            foreach (var d in dic)
            {
                foreach (var l in d.Value)
                {
                    zabrateLozka.Add(l);
                }
            }
            var str = CreateStringCollection(zabrateLozka);
            FileWriter.Write(str, _filePath);
        }
    }
}
