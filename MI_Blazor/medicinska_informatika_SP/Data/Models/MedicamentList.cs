using System.ComponentModel.DataAnnotations;
using System.ComponentModel.DataAnnotations.Schema;

namespace medicinska_informatika_SP.Data.Models
{
    [Table("ZOZNAM_LIEKOV", Schema = "RAPSIK_SP")]
    public class MedicamentList
    {
        [Key][Column("KOD_LIEKU")] 
        public string MedicamentCode { get; set; }

        [Key][Column("DATUM_OD")] 
        public DateTime DateFrom { get; set; }

        [Column("ID_KARTY")]
        [ForeignKey("ID_KARTY")]
        public int CardId { get; set; }

        [Column("DAVKOVANIE")] 
        public string Dosing { get; set; }

        [Column("DATUM_DO")] 
        public DateTime? DateTo { get; set; }
    }
}
