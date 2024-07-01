using Microsoft.Extensions.Hosting;
using System.ComponentModel.DataAnnotations;
using System.ComponentModel.DataAnnotations.Schema;

namespace medicinska_informatika_SP.Data.Models
{
    [Table("LIEK", Schema = "RAPSIK_SP")]
    public class Medicament
    {
        [Key][Column("KOD_LIEKU")] 
        public string MedicamentCode { get; set; }

        [Column("ATC")] 
        public string Atc { get; set; }

        [Column("PREDPIS")]
        public string Prescription { get; set; }

        [Column("NAZOV")]
        public string MedicamentName { get; set; }

        [Column("DOPLNOK")]
        public string Supplement { get; set; }

        [Column("STANDARTNA_DAVKA_LIEKU")]
        public string StandardDose { get; set; }

        [Column("CENA")]
        public int Price { get; set; }

        public List<DepartmentsMedicamentWarehouse> Records { get; set; }
    }
}
