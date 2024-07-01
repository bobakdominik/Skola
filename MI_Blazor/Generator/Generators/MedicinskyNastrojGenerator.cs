using System;
using System.Collections.Generic;
using System.Globalization;
using System.IO;
using System.Linq;
using Generator.Resources;

namespace Generator.Generators
{
    internal class MedicinskyNastroj
    {
        public string IdNastroja { get; set; }
        public string IdOddelenia { get; set; }
        public string Nazov { get; set; }
        public string Zivotnost { get; set; }
    }
    internal class MedicinskyNastrojGenerator : Generator<MedicinskyNastroj>
    {
        private readonly string _oddelenieFilePath;
        public MedicinskyNastrojGenerator(string filePath, int numberOfRecords) : base("MEDICINSKY_NASTROJ",
            "{0}, {1}, '{2}', TO_DATE('{3}', 'dd.mm.yy')",
            Path.Combine(filePath,SQLRes.MedicinskyNastrojFileName),
            numberOfRecords)
        {
            _oddelenieFilePath = Path.Combine(filePath, SQLRes.OddelenieFileName);
        }

        private readonly string[] _pristroje = new string[] {
        "ušný lievik",
        "diagnostický prúžok",
        "čelný reflektor",
        "čelná lampa",
        "čelné svietidlo",
        "diegnostické pero",
        "žiarovka do diagnostického pera",
        "neurologické kladivko",
        "sluchová vidlica",
        "odberové pero ku glukomeru",
        "lancety k odberovému peru",
        "analyzátor moču",
        "mikrolab analyzátor",
        "sklenená kapilára",
        "pipeta",
        "hrot na pipetu",
        "držiak kapilárok",
        "sklenené kapiláry",
        "kapilárna zátka",
        "gumený prstenec",
        "kiešte na biopsiu",
        "skúšobný rám na dioptrické sklá",
        "predloha na vyšetrenie zrak. ostrosti",
        "kniha na vyšetrenie farebného videnia",
        "chladiaca taška",
        "chladiaca vložka",
        "podložné sklo",
        "krycie sklo",
        "trecia miska",
        "odmerka",
        "kadička",
        "odmerná nádoba",
        "uhlomer na kĺby",
        "kliešťový merač podkožného tuku",
        "merač kožných rias",
        "kysliková fľaša",
        "nosidlo",
        "zdravotnická taška",
        "pinzeta",
        "nožnice",
        "skalpel",
        "hrtanové zrkadlo",
        "rúško",
        "ihla",
        "striekačka",
        "rukavice",
        "vata",
        "obväz",
        "zdravotná postel",
        "gynekologické kreslo",
        "zdravotná stolička",
        "zdravotnícke oblečenie",
        "chirurgické oblečenie",
        "záchranárske oblečenie",
        "olovené oblečenie",
        "zástera",
        "zdravotnícka obuv",
        "kôš na odpadky",
        "škrtidlo"
        };

        public override void Generate()
        {
            var oddelenieStr = FileWriter.Read(_oddelenieFilePath).SkipLast(1).ToList();
            var medicinskeNastroje = new List<MedicinskyNastroj>();
            var num = _numberOfRecords;
            var startNumber = 1;
            DateTime today;
            int idOddelenia;
            for (int i = 0; i < num; i++)
            {
                idOddelenia = Common.RandomMinMax(1, oddelenieStr.Count);
                today = DateTime.Now.AddDays(Common.RandomMinMax(60, 200));
                medicinskeNastroje.Add(new MedicinskyNastroj()
                {
                    IdNastroja = startNumber++.ToString(),
                    IdOddelenia = idOddelenia.ToString(),
                    Nazov = _pristroje[Common.RND.Next(_pristroje.Length)],
                    Zivotnost = today.ToString("dd.MM.yy",
                    CultureInfo.InvariantCulture)
                });
            }
            var str = CreateStringCollection(medicinskeNastroje);
            FileWriter.Write(str, _filePath);
        }

        public override List<string> CreateStringCollection(List<MedicinskyNastroj> collection)
        {
            var res = new List<string>();
            foreach (var c in collection)
            {
                res.Add(string.Format(_insertStr, c.IdNastroja, c.IdOddelenia, c.Nazov, c.Zivotnost));
            }
            return res;
        }
        
    }
}
