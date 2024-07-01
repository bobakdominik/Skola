using System.Collections.Generic;
using System.IO;
using System.Linq;

namespace Generator
{
    class FileWriter
    {
        public static void Write(List<string> collection, string fullPath)
        {
            FileInfo fi = new FileInfo(fullPath);
            if (!fi.Directory.Exists)
            {
                System.IO.Directory.CreateDirectory(fi.DirectoryName);
            }
            using (StreamWriter writer = new StreamWriter(fullPath))
            {
                foreach (var line in collection)
                {
                    writer.WriteLine(line);
                }
            }
        }

        public static List<string> Read(string fullPath)
        {
            string readText = File.ReadAllText(fullPath);
            return readText.Split("\n").ToList();
        }
    }
}
