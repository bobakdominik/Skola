using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using Generator.Resources;

namespace Generator.Generators
{
    internal class Dokument
    {
        public int IdDokumentu { get; set; }
        public int IdKarty { get; set; }
        public int IdOddelenia { get; set; }
        public string TypDokumentu { get; set; }
        public string Format { get; set; }
        public string Nazov { get; set; }
        public DateTime DatumVystavenia { get; set; }
    }

    internal class BlobData
    {
        public int IdDokumentu { get; set; }
        public string IdSuboru { get; set; }
        public string data { get; set; }
    }

    internal class DokumentGenerator : Generator<Dokument>
    {
        private const string CImageFolder = @"Data\Blob";
        private readonly string _blobSqlScript;
        private readonly string[] _images = new string[]
        {
            "RTG_BrokenLeg.jpg",
            "RTG_Chest.jpg",
            "RTG_FullBody.jpg",
            "RTG_Hand.jpg",
            "RTG_Brain.jpg",
            "RTG_Skull.jpg",
            "RTG_Skeleton.jpg"
        };
        private readonly string _oddeleniaFilePath;
        private readonly string _kartyFilePath;
        private readonly string _blobFilePath;

        public DokumentGenerator(string filePath) : base("DOKUMENT",
            "{0}, {1}, {2}, '{3}', '{4}', '{5}', TO_DATE('{6}', 'dd.mm.yy')",
            Path.Combine(filePath,SQLRes.DokumentFileName),
            0)
        {
            _oddeleniaFilePath = Path.Combine(filePath, SQLRes.OddelenieFileName);
            _kartyFilePath = Path.Combine(filePath, SQLRes.ZdravotnaKartaFileName);
            _blobSqlScript = string.Format(SQLRes.InsertStatement, "BLOB_DATA", "{0}, {1}, '{2}'");
            _blobFilePath = Path.Combine(filePath, SQLRes.BlobDataFileName);
        }

        public override List<string> CreateStringCollection(List<Dokument> collection)
        {
            var res = new List<string>();
            foreach (var item in collection)
            {
                res.Add(string.Format(_insertStr, item.IdDokumentu, item.IdKarty, item.IdOddelenia, item.TypDokumentu, item.Format,item.Nazov, item.DatumVystavenia.ToString("dd.MM.yy")));
            }
            return res;
        }

        public List<string> CreateStringCollection(List<BlobData> collection)
        {
            var res = new List<string>();
            foreach (var item in collection)
            {
                res.Add(string.Format(_blobSqlScript, item.IdDokumentu, item.IdSuboru, item.data));
            }
            return res;
        }

        public override void Generate()
        {
            var oddelenia = OddelenieGenerator.ConvertScriptToObject(FileWriter.Read(_oddeleniaFilePath).SkipLast(1).ToList());
            var karty = ZdravotnaKartaGenerator.ConvertScriptToObject(FileWriter.Read(_kartyFilePath).SkipLast(1).ToList());
            var dokumenty = new List<Dokument>();
            var bloby = new List<BlobData>();
            string imageString;
            byte[] imageArray;
            for (int i = 0; i < _images.Length - 1; i++)
            {
                imageArray = File.ReadAllBytes(Path.Combine(CImageFolder, _images[i]));
                imageString = Convert.ToBase64String(imageArray);
                dokumenty.Add(new Dokument()
                {
                    IdDokumentu = i + 1,
                    IdKarty = Convert.ToInt32(karty[0].IdKarty),
                    IdOddelenia = oddelenia[0].IdOddelenia,
                    TypDokumentu = _images[i].Split('_')[0],
                    Format = _images[i].Split('.')[1],
                    Nazov = _images[i].Split('_')[1].Split('.')[0],
                    DatumVystavenia = Common.RandomDay(DateTime.Now.Year - 2)
                });
                bloby.Add(new BlobData()
                {
                    IdDokumentu = dokumenty[i].IdDokumentu,
                    IdSuboru = (i + 1).ToString(),
                    data = imageString
                });
            }
            dokumenty.Add(new Dokument()
            {
                IdDokumentu = dokumenty.Last().IdDokumentu + 1,
                IdKarty = Convert.ToInt32(karty[1].IdKarty),
                IdOddelenia = oddelenia[1].IdOddelenia,
                TypDokumentu = _images[^1].Split('_')[0],
                Format = _images[^1].Split('.')[1],
                Nazov = _images[^1].Split('_')[1].Split('.')[0],
                DatumVystavenia = Common.RandomDay(DateTime.Now.Year - 2)
            });
            imageArray = File.ReadAllBytes(Path.Combine(CImageFolder, _images[^1]));
            imageString = Convert.ToBase64String(imageArray);
            bloby.Add(new BlobData()
            {
                IdDokumentu = dokumenty[dokumenty.Last().IdDokumentu - 1].IdDokumentu,
                IdSuboru = (_images.Length).ToString(),
                data = imageString
            });
            FileWriter.Write(CreateStringCollection(dokumenty), _filePath);
            FileWriter.Write(CreateStringCollection(bloby), _blobFilePath);
        }
    }
}
