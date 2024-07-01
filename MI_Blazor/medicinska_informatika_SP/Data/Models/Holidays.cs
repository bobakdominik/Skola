using System.ComponentModel.DataAnnotations;
using System.ComponentModel.DataAnnotations.Schema;

namespace medicinska_informatika_SP.Data.Models
{
    [Table("DOVOLENKY", Schema = "RAPSIK")]
    public class Holidays
    {
        [Key][Column("KTO")] 
        public string user { get; set; }

        [Key][Column("DATUM_OD")] 
        public DateTime DateFrom { get; set; }

        [Column("DATUM_DO")]
        public DateTime DateTo { get; set; }
    }
}
