using Generator.Generators;
using System;
using System.IO;
using Generator.Resources;
using System.Reflection.Metadata;

namespace Generator
{
    class Program
    {
        static void Main(string[] args)
        {
            var filePath = args.Length > 0 ? args[0] : "";

            new NemocnicaGenerator(filePath, 1).Generate(); // nechat ako prve
            new OsobaGenerator(filePath, 30000).Generate();
            new PacientGenerator(filePath, 25000).Generate();
            new PoistenieGenerator(filePath, 25000).Generate();//sem musi byt parameter rovnaky ako v PacientGenerator
            new ZdravotnaKartaGenerator(filePath, 25000).Generate();//sem musi byt parameter rovnaky ako v PacientGenerator
            new ChorobaGenerator(filePath, 9487).Generate();//nemenit
            new ZoznamOchoreniGenerator(filePath, 50).Generate();//sem sa generuje podla poctu zdravotnych kariet, parameter generovani moze byt lubovolny
            new OckovanieGenerator(filePath, 50).Generate(); //nechat pocet generovani na 50!
            new ZoznamOckovaniGenerator(filePath, 50).Generate();//sem sa generuje podla poctu zdravotnych kariet, parameter generovani moze byt lubovolny           
            //new PersonalGenerator(filePath, 50).Generate();
            //new OddelenieGenerator(filePath).Generate();
            //new LozkoGenerator(filePath, 30).Generate();
            //new ZabrateLozkaGenerator(filePath, 60).Generate();
            //new PristrojGenerator(filePath, 1000).Generate();
            //new MedicinskyNastrojGenerator(filePath, 1000).Generate();
            //new LiekGenerator(filePath, 4445).Generate();
            //new ZoznamLiekovGenerator(filePath, 50).Generate();
            //new SkladLiekovOddeleniaGenerator(filePath, 50).Generate();//parameter moze byt lubovolny, generuje sa podla poctu oddeleni
            //new LekarskyUkonGenerator(filePath, 50).Generate();//parameter moze byt lubovolny
            //new CennikUkonovGenerator(filePath, 50).Generate();//parameter moze byt lubovolny
            //new PlatbaGenerator(filePath, 50).Generate();
            //new DokumentGenerator(filePath).Generate();

            /* TODO Odkomentovavat         
            new VozidloGenerator(filePath, x).Generate();
            new VyjazdovyTymGenerator(filePath, x).Generate();        
            */
        }
    }
}
