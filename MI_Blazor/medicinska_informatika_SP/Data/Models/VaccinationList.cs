using System.ComponentModel.DataAnnotations;
using System.ComponentModel.DataAnnotations.Schema;

namespace medicinska_informatika_SP.Data.Models
{
    [Table("ZOZNAM_OCKOVANI", Schema = "RAPSIK_SP")]
    public class VaccinationList
    {
        [Key][Column("ID_VAKCINY")] 
        public int VaccinationId { get; set; }

        [Column("ID_KARTY")]
        [ForeignKey("ID_KARTY")]
        public int CardId { get; set; }

        [Column("DATUM_OD")]
        public DateTime DateFrom { get; set; }

        [Column("DATUM_DO")] 
        public DateTime? DateTo { get; set; }
    }
}
