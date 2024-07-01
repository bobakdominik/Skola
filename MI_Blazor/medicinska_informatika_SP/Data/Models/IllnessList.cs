using System.ComponentModel.DataAnnotations;
using System.ComponentModel.DataAnnotations.Schema;

namespace medicinska_informatika_SP.Data.Models
{
    [Table("ZOZNAM_OCHORENI", Schema = "RAPSIK_SP")]
    public class IllnessList
    {
        [Key][Column("ID_CHOROBY")] 
        public int IllnessId { get; set; }

        [Column("ID_KARTY")]
        [ForeignKey("ID_KARTY")]
        public int CardId { get; set; }

        [Key][Column("DATUM_OD")] 
        public DateTime DateFrom { get; set; }

        [Column("DATUM_DO")] 
        public DateTime? DateTo { get; set; }
    }
}
